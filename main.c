#include <stdio.h>
#include <stdlib.h>

#include "./ffret.h"

cmd_options opts = { "$HOME/.config/ffret.conf", NULL, 0 };

int main(int argc, char** argv)
{
	parse_command(argc, argv, &opts);

	if(opts.show_help)
	{
		printf("Options:\n\
				-c <CONFIGFILE> The path of the config file.\n\
						Default value is: $HOME/.config/ffret.conf\n\
				-p <PATH>	The path to the plugin folder\n\
				-h		Show this message\n");
	}

	FILE* config = fopen(opts.config_file, "r");
	if(!config)
	{
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
