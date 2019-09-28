// struct with command line options to transfer variables easily between files
struct cmd_options{
	char* config_file;
	char* ppath;
	int show_help;
};
typedef struct cmd_options cmd_options;

void parse_command(int argc, char** argv, cmd_options* opts);

void expand_path(char** filename);
