#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <wordexp.h>

#include "./ffret.h"

void parse_command(int argc, char** argv, cmd_options* opts)
{
	int opt;

	while( (opt = getopt(argc, argv, "c:p:h")) != -1 )
	{
		size_t str_length;
		switch(opt)
		{
			// show_help boolean will be used later to stop the program
			// on invalid inputs or if the user used the -h option
			case 'h':
				opts->show_help = 1;
				opt = 0; // To break the while loop if user used the -h option
				break;
			case 'c':
				str_length = strlen(optarg);
				opts->config_file = malloc(str_length);
				strncpy(opts->config_file, optarg, str_length);
				break;
			case 'p':
				str_length = strlen(optarg);
				opts->ppath = malloc(str_length);
				strncpy(opts->ppath, optarg, str_length);
				break;
			case ':':
				opts->show_help = 1;
				break;
			case '?':
				opts->show_help = 1;
				break;
		}

		// If user used the -h option, don't parse the other options
		if(!opt)
		{
			break;
		}
	}
}

// Use a char** in order to not create and return another
// variable for the result (pass pointer by reference)
void expand_path(char** filename)
{
	wordexp_t filename_struct;
	char* expanded_filename;
	wordexp(*filename, &filename_struct, 0);

	// Dereference the char** to char*
	*filename = malloc(strlen(filename_struct.we_wordv[0]));
	strcpy(*filename, filename_struct.we_wordv[0]);

	wordfree(&filename_struct);
}
