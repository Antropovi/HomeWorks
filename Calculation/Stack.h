
struct stack
{
	// or operation: '+', '-', '*', '/' or number 'n'
	char operation;

	struct number *number;

	struct stack *next;
};


struct stack *stack_Add(struct stack *stack, struct node *lexem);
int stack_Process(struct stack **stack);
void stack_Print(struct stack *stack);
void stack_Free(struct stack *stack);
