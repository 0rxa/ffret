#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "./ffret.h"
#include "./config.h"


int main(int argc, char** argv)
{
	// Default values of command line options
	cmd_options opts = { "~/.config/ffret/ffret.conf", "$HOME/.config/ffret/plugins/", 0 };

	// Start with an empty list so it can be expanded dynamically
	config* cfg = NULL;

	// Parse command line options
	parse_command(argc, argv, &opts);

	if(opts.show_help)
	{
		printf("Options:\n\
				-c <CONFIGFILE> The path of the config file.\n\
						Default value is: $HOME/.config/ffret.conf\n\
				-p <PATH>	The path to the plugin folder\n\
				-h		Show this message\n");
		return 0;
	}

	// Expand environment variables
	expand_path(&opts.config_file);
	expand_path(&opts.ppath);

	FILE* config_path = fopen(opts.config_file, "r");
	if(!config_path)
	{
		puts(opts.config_file);
		printf("Could not open file\n");
		exit(1);
	}

	char* line;
	ssize_t line_s;
	size_t len = 0;
	while( (line_s = getline(&line, &len, config_path) != -1) )
	{
		regex_t regex;
		int reti;

		// Finds line that does not start with whitespace
		// It's the folder block name
		if( regcomp(&regex, "^[^[:space:]]", 0) )
		{
			printf("Error compiling regex\n");
			exit(1);
		}
		reti = regexec(&regex, line, 0, NULL, 0);

		if( !reti )
		{
			cfg = expand(cfg);
			init_folder_block(line, &cfg);
		}
	}

	printf("Block name: %s\n", cfg->block->name);
	printf("Directories:\n");
	for( int c = 0; c < 2; c++ )
	{
		printf("\t%s\n", cfg->block->directories[c]);
	}
	return 0;
}
