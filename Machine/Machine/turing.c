// turing.c : Defines turimg-mashine
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include < string.h > 

#include "normal_alg.h"
#include "turing.h"

#define TURING_LOG 1

void write_log(int deep, char *format, ...);

void write_log_turing_rules(struct turing_rule *rules, int count)
{
	int i;
	for(i=0; i<count; i++)
	{
		write_log(TURING_LOG, 
			"turing rules[%d] = (state:%d symbol:%d - new_state:%d new_symbol:%d move:%d)", 
			i, rules[i].state, rules[i].symbol, 
			rules[i].new_state, rules[i].new_symbol, rules[i].move);
	}
}

// Helper
//
int turing_seek_rule(char symbol, int status, struct turing_rule* rules, int count)
{
	char alf[3] = {(char)status + '0', symbol, 0};
	char str_from[256] = { (char)status + '0', symbol, 0 };
	struct normal_alg_rule *change_array = (struct normal_alg_rule*)malloc((count+1)*sizeof(struct normal_alg_rule));
	int i;
	int ret;

	write_log(TURING_LOG, "turing_seek_rule %c %d %d", symbol, status, count);

	for(i=0; i<count; i++)
	{
		change_array[i].str_from = (char*)malloc(3);
		change_array[i].str_from[0] = (char)rules[i].state + '0';
		change_array[i].str_from[1] = rules[i].symbol=='*' ? symbol : rules[i].symbol;
		change_array[i].str_from[2] = 0;

		change_array[i].str_to = (char*)malloc(2);
		change_array[i].str_to[0] = i + '0';
		change_array[i].str_to[1] = 0;

		change_array[i].is_finish = TRUE;
	}

	change_array[count].str_from = (char*)malloc(3);
	change_array[count].str_from[0] = (char)status + '0';
	change_array[count].str_from[1] = symbol;
	change_array[count].str_from[2] = 0;

	change_array[count].str_to = (char*)malloc(2);
	change_array[count].str_to[0] = '_';
	change_array[count].str_to[1] = 0;

	change_array[count].is_finish = TRUE;

	//
	normal_alg(alf, change_array, count+1);

	//
	ret = (alf[0]=='_') ? -1 : alf[0]-'0';

	//
	for(i=0; i<count+1; i++)
	{
		free(change_array[i].str_from);
		free(change_array[i].str_to);
	}
	free(change_array);

	write_log(TURING_LOG, "turing_seek_rule ret %d", ret);

	return ret;
}

int turing_change_symbol(char *source, int pos, struct turing_rule* rule)
{
	char str_from[256], str_to[256];
	struct normal_alg_rule change = { str_from, str_to, TRUE };

	write_log(TURING_LOG, "turing_change_symbol \"%s\" %d", source, pos);

	strncpy(str_from, source, pos+1);
	str_from[pos+1]=0;
	strncpy(str_to, source, pos+1);
	str_to[pos+1]=0;
	str_to[pos] = rule->new_symbol;
	normal_alg(source, &change, 1);

	write_log(TURING_LOG, "turing_change_symbol return TRUE");

	return TRUE;
}


int turing_change_pos(int *pos, struct turing_rule* rule, int alf_length)
{
	char str_from[2]=" ", str_to[2]=" ";
	struct normal_alg_rule change = { str_from, str_to, TRUE };
	
	write_log(TURING_LOG, "turing_change_pos %d %d", *pos, alf_length);

	if(rule->move!=turing_move_none)
	{
		char alf[2] = { (char)(*pos), 0 };
		str_from[0] = (char)(*pos);
		str_to[0] = (char)(*pos + (rule->move==turing_move_right ? 1 : -1));
		normal_alg(alf, &change, 1);
		if( (short)(alf[0])==-1 || (short)(alf[0])==alf_length+1)
		{
			// todo print error
			return FALSE;
		}
		*pos = (short)(alf[0]);
	}

	write_log(TURING_LOG, "turing_change_pos new pos %d ret %d", *pos, TRUE);

	return TRUE;
}


int turing_change_state(int *state, struct turing_rule* rule)
{
	char alf[2] = { (char)*state, 0 };
	char str_from[2]={ (char)*state, 0 }, str_to[2]={ (char)*state, 0 };
	struct normal_alg_rule change = { str_from, str_to, TRUE };
	int ret = *state != rule->new_state;

	write_log(TURING_LOG, "turing_change_state %d", state);

	str_to[0] = rule->new_state;

	normal_alg(alf, &change, 1);
	*state = (short)(alf[0]);

	write_log(TURING_LOG, "turing_change_state new state %d ret %d", state, ret);

	return ret;
}



// Interface
//
void turing_machine(char *source, int *pos, int *state, struct turing_rule* rules, int count)
{
	char str[256];

	write_log(TURING_LOG, "turing_machine \"%s\" %d %d %d", source, *pos, *state, count);
	write_log_turing_rules(rules, count);

	sprintf(str, "_%s_", source);

	while(turing_step(str, pos, state, rules, count)){};

	strcpy(source, strtok(str, "_"));

	write_log(TURING_LOG, "turing_machine \"%s\" %d %d", source, *pos, *state);
}


int turing_step(char *source, int *pos, int *state, struct turing_rule* rules, int count)
{
	int n;
	int ret = FALSE;

	write_log(TURING_LOG, "turing_step \"%s\" %d %d %d", source, *pos, *state, count);

	// todo seek rule
	n = turing_seek_rule(source[*pos], *state, rules, count);
	write_log(TURING_LOG, "turing_step n %d", n);

	// make rule
	if(n!=-1)
	{
		ret |= turing_change_symbol(source, *pos, &rules[n]);
		ret |= turing_change_pos(pos, &rules[n], strlen(source));
		ret |= turing_change_state(state, &rules[n]);
	}

	write_log(TURING_LOG, "turing_step ret %d", ret);

	return ret;
}
