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

int split_paths(char* path_string, folder_block** block )
{
	int dirnum = 0;
	for( int c = 0; c < strlen(path_string); c++ )
	{
		if( path_string[c] == ',' ) dirnum++;
	}
	dirnum++; // One delimiter separates two strings

	char** paths = malloc(sizeof(char*)*dirnum);
	int last_ix = 0, str_ix = 0;
	int c;
	for( c = 0; c < strlen(path_string); c++ )
	{
		if( path_string[c] == ':' ) break; // Break if no more paths
		if( path_string[c] == ',' || path_string[c+1] == '\0' )
		{
			size_t sizeof_path = (c-last_ix+1);
			paths[str_ix] = malloc(sizeof(char)*sizeof_path);

			strncpy(paths[str_ix], &path_string[last_ix], sizeof_path-1);
			paths[str_ix][sizeof_path-1] = '\0';

			last_ix = c+1;
			str_ix++;
		}
	}

	folder_block* block_alias = *block;
	block_alias->directories = malloc(sizeof(char*)*dirnum);
	memcpy(block_alias->directories, paths, sizeof(char*)*dirnum);

	return dirnum;
}

void init_folder_block(char* line, config** cfg)
{
	regex_t regex;
	size_t nmatch = 4;
	regmatch_t match[nmatch];
	int reti;
	char* regex_str = "^(\\w+\\s\\w+)\\s\\((.*):(recursive\\)|\\)):";

	if( regcomp(&regex, regex_str, REG_EXTENDED) )
	{
		printf("Could not compile regex\n");
		exit(1);
	}

	reti = regexec(&regex, line, nmatch, match, 0);

	if( reti )
	{
		puts("NO MATCH");
		exit(1);
	}

	config* cfg_alias = *cfg;

	size_t sizeof_name = match[1].rm_eo-match[1].rm_so;
	cfg_alias->block->name = malloc(sizeof_name*sizeof(char));
	strncpy(cfg_alias->block->name, &line[match[1].rm_so], sizeof_name);

	size_t sizeof_paths = match[2].rm_eo-match[2].rm_so;
	char* path_string = malloc(sizeof_paths*sizeof(char));
	strncpy(path_string, &line[match[2].rm_so], sizeof_paths);

	cfg_alias->block->number_of_directories = split_paths(path_string, &cfg_alias->block);

	if(match[3].rm_eo-match[3].rm_so > 1)
	{
		cfg_alias->block->recursive = true;
	}
}
