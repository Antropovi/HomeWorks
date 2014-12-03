struct normal_alg_rule{

	char *str_from;
	char *str_to;
	int is_finish;
};

// Interface for Turing machine

// alfabet - (in/out) alfabet
// rules - array of rules
// count - count rules
void normal_alg(char *alfabet, struct normal_alg_rule *rules, int count);
