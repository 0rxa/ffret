#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#include "config.h"

config* expand(config* next)
{
	config* new_entry = malloc(sizeof(config));
	new_entry->block = malloc(sizeof(folder_block));
	new_entry->next_block = next;

	return new_entry;
}

// Inline function to keep the parse_config clean
// It's a little slower but it shouldn't be noticable
// since lines can not logically be very long
inline void populate_name(char* line, config** cfg)
{
	int c;
	for( c = 0; c < strlen(line); c++ )
	{
		if(line[c] == ' ' && line[c+1] == '(')
		{
			break;
		}
	}

	*cfg = expand(*cfg);
	config* tmp = *cfg; // So I can later replace *cfg with tmp
	tmp->block->name = malloc(c*sizeof(char));
	strncpy(tmp->block->name, line, c);
	*cfg = tmp;
}

void parse_config(char* line, config** cfg)
{
	regex_t regex;
	int reti;

	if( regcomp(&regex, "^[^[:space:]]", 0) )
	{
		printf("Error Compiling Regex");
		exit(1);
	}

	reti = regexec(&regex, line, 0, NULL, 0);

	if( !reti )
	{
		// Regex matches line that does not start with whitespace
		// This is the folder block
		populate_name(line, cfg);
	}
}
