
struct number
{
	int sign;
	struct node *head;
};

struct number* numbers_Init();
void numbers_Read(struct number *num, char *string);
void numbers_Free(struct number* num);