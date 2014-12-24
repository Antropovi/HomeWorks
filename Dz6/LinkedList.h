
struct node
{
	   int val;
	   struct node *next;
};

void linkedList_Revert(struct node ** head);
void linkedList_Add(int val, struct node ** head);
void linkedList_Print(struct node * head);
void linkedList_Insert(struct node ** head);
