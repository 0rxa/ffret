#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./ffret.h"


int main(int argc, char** argv)
{
	// Default values of command line options
	cmd_options opts = { "~/.config/ffret/ffret.conf", "$HOME/.config/ffret/plugins/", 0 };

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

	FILE* config = fopen(opts.config_file, "r");
	if(!config)
	{
		puts(opts.config_file);
		printf("Could not open file\n");
		exit(1);
	}

	char* line;
	ssize_t line_s;
	size_t len = 0;
	while( (line_s = getline(&line, &len, config) != -1) )
	{
		puts(line);
	}
}
