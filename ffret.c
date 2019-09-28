#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "./ffret.h"

void parse_command(int argc, char** argv, cmd_options* opts)
{
	int opt;

	while( (opt = getopt(argc, argv, "c:p:h")) != -1 )
	{
		size_t str_length;
		switch(opt)
		{
			case 'h':
				opts->show_help = 1;
				opt = 0;
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

		}

		if(!opt)
		{
			break;
		}
	}
}
