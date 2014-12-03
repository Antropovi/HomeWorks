enum lambda_param_type{
	lambda_none,
	lambda_data,
	lambda_fn
};

struct lambda_param;

typedef int (*lambda_cb)(struct lambda_param *params, int count, void *result);

struct lambda_param{
	enum lambda_param_type type;

	void *data;		// параметр или результат
	lambda_cb func;
	int params_count;
	struct lambda_param *params;
};

// Interface for Normal Algorifm Markov

int lambda_calc(struct lambda_param *params, int count);


// params - array of string (first - source string, next - template, last equal NULL)
// result - index ( int* ), -1 - not found
int lambda_search_index(struct lambda_param *params, int count, void *result);

// params - strings: source, str_from, str_to
// result - result string
int lambda_replace(struct lambda_param *params, int count, void *result);

// params - first: index, next: strings
// result - result string
int lambda_get_n_string(struct lambda_param *params, int count, void *result);

// params - first: index, next: pointer int
// result - result pointer int
int lambda_get_n_int(struct lambda_param *params, int count, void *result);
