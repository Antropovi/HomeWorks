// normal_alg.c : Defines normal algoritm Markov
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include < string.h > 

#include "lambda.h"
#include "normal_alg.h"

#define NORMAL_LOG 2

void write_log(int deep, char *format, ...);

void write_log_normal_rules(struct normal_alg_rule *rules, int count)
{
	int i;
	for(i=0; i<count; i++)
	{
		write_log(NORMAL_LOG, "normal rules[%d] = (\"%s\" \"%s\" %d)", 
			i, rules[i].str_from, rules[i].str_from, rules[i].is_finish);
	}
}

/*
(lambda_replace 
	alfabet 
	(lambda_get_n_string
		(lambda_search_index 
			alfabet 
			rules.from)
		rules.from)
 	(lambda_get_n_string
		(lambda_search_index 
			alfabet 
			rules.from)
		rules.to)
 	(lambda_get_n_int
		(lambda_search_index 
			alfabet 
			rules.from)
		rules.is_finish)
)
*/

/*	Helper
*/

struct lambda_param *normal_alg_create_queue(char *alfabet, char *result,
									int *index1, int *index2, int *index3, 
									char *string1, char *string2, int *is_finish, 
									struct normal_alg_rule *rules, int count)
{
	int i;
	struct lambda_param *replace;

	replace = (struct lambda_param *)malloc(sizeof(struct lambda_param));
	replace->data = result;
	replace->type = lambda_fn;
	replace->func = &lambda_replace;
	replace->params_count = 4;
	replace->params = (struct lambda_param *)malloc(4*sizeof(struct lambda_param));

	// 0 -aflabet
	replace->params[0].data = alfabet;
	replace->params[0].type = lambda_data;
	replace->params[0].params_count = 0;
	replace->params[0].params = NULL;

	// 1 - get n
	replace->params[1].data = string1;
	replace->params[1].type = lambda_fn;
	replace->params[1].func = &lambda_get_n_string;
	replace->params[1].params_count = 1+count;
	replace->params[1].params = (struct lambda_param *)malloc((1+count)*sizeof(struct lambda_param));

	// 1.0 - get search index
	replace->params[1].params[0].data = index1;
	replace->params[1].params[0].type = lambda_fn;
	replace->params[1].params[0].func = &lambda_search_index;
	replace->params[1].params[0].params_count = 1 + count;
	replace->params[1].params[0].params = (struct lambda_param *)malloc((1+count)*sizeof(struct lambda_param));

	// 1.0.0 - alfabet
	replace->params[1].params[0].params[0].data = alfabet;
	replace->params[1].params[0].params[0].type = lambda_data;
	replace->params[1].params[0].params[0].params_count = 0;

	// 1.0.x - rules.from
	for(i=0; i<count; i++)
	{
		replace->params[1].params[0].params[i+1].data = rules[i].str_from;
		replace->params[1].params[0].params[i+1].type = lambda_data;
		replace->params[1].params[0].params[i+1].params_count = 0;
	}

	// 1.x - rules.from
	for(i=0; i<count; i++)
	{
		replace->params[1].params[i+1].data = rules[i].str_from;
		replace->params[1].params[i+1].type = lambda_data;
		replace->params[1].params[i+1].params_count = 0;
	}

	// 2 - get n
	replace->params[2].data = string2;
	replace->params[2].type = lambda_fn;
	replace->params[2].func = &lambda_get_n_string;
	replace->params[2].params_count = 1+count;
	replace->params[2].params = (struct lambda_param *)malloc((1+count)*sizeof(struct lambda_param));

	// 2.0 - get search index
	replace->params[2].params[0].data = index2;
	replace->params[2].params[0].type = lambda_fn;
	replace->params[2].params[0].func = &lambda_search_index;
	replace->params[2].params[0].params_count = 1 + count;
	replace->params[2].params[0].params = (struct lambda_param *)malloc((1+count)*sizeof(struct lambda_param));

	// 2.0.0 - alfabet
	replace->params[2].params[0].params[0].data = alfabet;
	replace->params[2].params[0].params[0].type = lambda_data;
	replace->params[2].params[0].params[0].params_count = 0;

	// 2.0.x - rules.from
	for(i=0; i<count; i++)
	{
		replace->params[2].params[0].params[i+1].data = rules[i].str_from;
		replace->params[2].params[0].params[i+1].type = lambda_data;
		replace->params[2].params[0].params[i+1].params_count = 0;
	}

	// 2.x - rules.to
	for(i=0; i<count; i++)
	{
		replace->params[2].params[i+1].data = rules[i].str_to;
		replace->params[2].params[i+1].type = lambda_data;
		replace->params[2].params[i+1].params_count = 0;
	}

	// 3 - get n
	replace->params[3].data = is_finish;
	replace->params[3].type = lambda_fn;
	replace->params[3].func = &lambda_get_n_int;
	replace->params[3].params_count = 1+count;
	replace->params[3].params = (struct lambda_param *)malloc((1+count)*sizeof(struct lambda_param));

	// 3.0 - get search index
	replace->params[3].params[0].data = index2;
	replace->params[3].params[0].type = lambda_fn;
	replace->params[3].params[0].func = &lambda_search_index;
	replace->params[3].params[0].params_count = 1 + count;
	replace->params[3].params[0].params = (struct lambda_param *)malloc((1+count)*sizeof(struct lambda_param));

	// 3.0.0 - alfabet
	replace->params[3].params[0].params[0].data = alfabet;
	replace->params[3].params[0].params[0].type = lambda_data;
	replace->params[3].params[0].params[0].params_count = 0;

	// 3.0.x - rules.from
	for(i=0; i<count; i++)
	{
		replace->params[3].params[0].params[i+1].data = rules[i].str_from;
		replace->params[3].params[0].params[i+1].type = lambda_data;
		replace->params[3].params[0].params[i+1].params_count = 0;
	}

	// 3.x - rules.is_finish
	for(i=0; i<count; i++)
	{
		replace->params[3].params[i+1].data = &rules[i].is_finish;
		replace->params[3].params[i+1].type = lambda_data;
		replace->params[3].params[i+1].params_count = 0;
	}

	return replace;
}

void normal_alg_free_queue(struct lambda_param *param)
{
	int i;
	for(i=0; i<param->params_count; i++)
	{
		normal_alg_free_queue(&param->params[i]);
	}
	if(param->params_count!=0)
		free(param->params);
}

/* Interface
*/

void normal_alg(char *alfabet, struct normal_alg_rule *rules, int count)
{
	int index1, index2, index3;
	char string1[256], string2[256];
	int is_finish;
	char str_tmp[256];
	struct lambda_param *params;
	int loop;
	
	write_log(NORMAL_LOG, "normal_alg \"%s\" %d", alfabet, count);
	write_log_normal_rules(rules, count);

	params = normal_alg_create_queue(alfabet, str_tmp, 
		&index1, &index2, &index3,
		string1, string2, &is_finish, 
		rules, count);

	loop = TRUE;
	while(loop)
	{
		loop = lambda_calc(params, 1);
		strcpy(alfabet, (char*)params->data);
	}

	normal_alg_free_queue(params);
	free(params);

	write_log(NORMAL_LOG, "normal_alg \"%s\"", alfabet);
}
