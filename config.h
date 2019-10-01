#include <stdbool.h>

struct folder_block{
	char* name;
	char** directories;
	bool recursive;

	char* rule_name;
	char* rule_matcher;
	char* resulting_filename;
};
typedef struct folder_block folder_block;

// Used a linked list to support an undefined
// number of folder blocks
struct config{
	folder_block* block;
	struct config* next_block;
};
typedef struct config config;

void parse_config(char* line, config** cfg);

config* expand(config* next);


