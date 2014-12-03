// lambda.c : Defines lambda-system
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include < string.h > 

#include "lambda.h"

#define LAMBDA_LOG 3

void write_log(int deep, char *format, ...);

/*	Helper
*/
int lambda_calc(struct lambda_param *params, int count)
{
	int ret = TRUE;
	int i;

	for(i=0; i<count && ret==TRUE; i++)
	{
		write_log(LAMBDA_LOG, "param 0x%x type %d", &params[i], params[i].type); 

		if(params[i].type == lambda_fn)
		{
			struct lambda_param *pt = params[i].params;
			ret = (*params[i].func)(pt, params[i].params_count, params[i].data);
		}
	}

	return ret;
}

/* Interface
*/


int lambda_search_index(struct lambda_param *params, int count, void *result)
{
	size_t pos, pos_best;
	char *source;
	int i;
	int *result_i;
	char *p_str;

	write_log(LAMBDA_LOG, "lambda_search_index");

	if( !lambda_calc(params, count) )
		return FALSE;

	pos_best = 0x7fff;
	result_i = (int*)result;
	*result_i = -1;

	source = (char*)params[0].data;

	for(i=1; i<count; i++)
	{
		p_str = strstr(source, (char*)(params[i].data));
		if (p_str != NULL)
		{
			pos = p_str-source;
			write_log(LAMBDA_LOG, "i %d pos %d", i, pos);
			if(pos < pos_best)
			{
				pos_best = pos;
				*result_i = i-1;
			}
		}
	}
	write_log(LAMBDA_LOG, "lambda_search_index %d pos_best %d", *result_i, pos_best);

	return (*result_i != -1) ? TRUE : FALSE;
}

int lambda_replace(struct lambda_param *params, int count, void *result)
{
	char *source;
	char *str_from;
	char *str_to;
	int is_finish;
	char *result_str;

	char* pointer;

	write_log(LAMBDA_LOG, "lambda_replace");

	if( !lambda_calc(params, count) )
		return FALSE;

	if( count<4)
		return FALSE;

	result_str = (char*)result;

	source = (char*)params[0].data;
	str_from = (char*)params[1].data;
	str_to = (char*)params[2].data;
	is_finish = *(int*)params[3].data;

	write_log(LAMBDA_LOG, "lambda_replace \"%s\" \"%s\" \"%s\" %d",
		source, str_from, str_to, is_finish);

	pointer = strstr(source, str_from);

	if(pointer != source)
		strncpy(result_str, source, pointer - source);
	else
		result_str[0] = 0;
	strcat(result_str, str_to);
	strcat(result_str, pointer + strlen(str_from));

	write_log(LAMBDA_LOG, "lambda_replace \"%s\"", result_str);

	return is_finish ? FALSE : TRUE;
}

int lambda_get_n_string(struct lambda_param *params, int count, void *result)
{
	int index;
	char *str_from;
	char *result_str;

	write_log(LAMBDA_LOG, "lambda_get_n_string");

	if( !lambda_calc(params, count) )
		return FALSE;

	if (count<1)
		return FALSE;
	result_str = (char*)result;

	index = *(int*)params[0].data;
	write_log(LAMBDA_LOG, "index %d", index);

	if (index+1 >= count)
		return FALSE;

	str_from = (char*)params[1+index].data;
	write_log(LAMBDA_LOG, "str_from \"%s\"", str_from);

	strcpy(result_str, str_from);
	write_log(LAMBDA_LOG, "lambda_get_n_string \"%s\"", result_str);

	return TRUE;
}

int lambda_get_n_int(struct lambda_param *params, int count, void *result)
{
	int index;
	int *result_i;

	write_log(LAMBDA_LOG, "lambda_get_n_int");

	if( !lambda_calc(params, count) )
		return FALSE;

	if (count<1)
		return FALSE;
	result_i = (int*)result;

	index = *(int*)params[0].data;
	write_log(LAMBDA_LOG, "index %d", index);

	if (index+1 >= count)
		return FALSE;

	*result_i = *(int*)params[1+index].data;
	write_log(LAMBDA_LOG, "lambda_get_n_int %d", *result_i);

	return TRUE;
}
