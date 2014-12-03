// algols.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdarg.h>
#include <stdlib.h>

#include "turing.h"


FILE *logger;

void write_log(int deep, char *format, ...)
{
	va_list args;
	char str[]="                    ";

	str[4*deep] = 0;
	fprintf(logger, str);

	va_start(args, format);
	vfprintf(logger, format, args);
	va_end(args);

	fprintf(logger, "\n");

	fflush(logger);  
}

int get_rule(FILE *file, struct turing_rule *rule)
{
	int state;
	char symbol;
	char new_symbol;
	enum turnig_move move;
	int new_state;

	int n = fscanf(file, "%d %c %c %d %d\n", &state, &symbol, &new_symbol, &move, &new_state);

	if (n==5)
	{
		rule->state = state;
		rule->symbol = symbol;
		rule->new_symbol = new_symbol;
		rule->move = move;
		rule->new_state = new_state;
	}
	return n==5;

}

int main()
{
	char source_string[256];
	char file_name[256];
	struct turing_rule *rules = NULL;
	int i;
	FILE *file;

	int pos;
	int state;

	logger = fopen("log.txt","w");

	i = 0;
	rules = (struct turing_rule*)malloc((i+1)*sizeof(struct turing_rule));

	// read
	printf("Write file's name ");
	scanf("%s", file_name);
	file = fopen(file_name, "r");

	fscanf(file, "%[^\n]", source_string);	// skip comments
	
	fscanf(file, "%s", source_string);
	
	while ( get_rule(file, &rules[i]) )
	{
		i++;
		rules = (struct turing_rule *)realloc(rules, (i+1)*sizeof(struct turing_rule));
	}

	fclose(file);

	// run
	pos = 1;
	state = 1;
	turing_machine(source_string, &pos, &state, rules, i-1);

	// write
	file = fopen("output.txt", "w");
	fprintf(file, "result: \"%s\" status: %d pos: %d\n", source_string, pos, state);
	fclose(file);

	// free data
	free(rules);

	//
	fclose(logger);

	return 0;
}
