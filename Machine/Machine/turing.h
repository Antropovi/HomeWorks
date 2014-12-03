
enum turing_move {
	turing_move_none = 0,
	turing_move_left = 1,
	turing_move_right = 2,
};

struct turing_rule {
	// condition
	int state;	// 1, 2, ...
	char symbol;	// '_' empty symbol (pos==-1 || pos>=length(string))
	// changes
	char new_symbol;
	enum turing_move move;
	int new_state;
};

/*
  alfabet - in/out alfabet
  pos - in/out position
  rules - array of rule (last==NULL)

  result - exsist changes (symbol and/or position
*/
int turing_step(char* alfabet, int* pos, int* status, struct turing_rule* rules, int count);

/*
  alfabet - in/out alfabet
  pos - in/out position
  rules - array of rule (last==NULL)

  result - exsist changes (symbol and/or position
*/
void turing_machine(char *alfabet, int *pos, int *status, struct turing_rule* rules, int count);

