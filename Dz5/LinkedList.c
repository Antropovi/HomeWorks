// Реализация односвязного списка
// Антропов И М 12.11.2014


#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include < string.h > 

struct node
{
 float val;
 node * next;
};


node * head = NULL;


void Add(float val){
 node * new_node = (node*)malloc(sizeof(node));
 new_node->next = head;
 head = new_node;
 new_node->val=val;
}

void Print(){
 node * curr = head;
 while (curr) {
  printf("%f"  ,curr->val);
  curr=curr->next;
 }
  printf("\n");
}
 
void Remove(float ReVal){
 node *tmp;
 node *curr;

 if ( head!=NULL )
 {
  if(head->val == ReVal)
   {
     tmp=head;
     head = head->next;
     free(tmp);
   }
   else
   {
     curr = head;
     while (curr->next)
     {
       if (curr->next ->val == ReVal) 
       { 
         tmp =curr->next;
        curr->next = curr->next->next;
        free(tmp);
        break;
      }
      curr=curr->next;  
    }
  }
 }
}


int main()
{
 char String[100]="";
  float f;

 scanf("%s", String);
  while(String[0]!='q')
  {
  switch (String[0])
  {
   case 'p' : 
   Print();
   break;
   case 'a' : 
     scanf("%f", &f);
	 Add(f);
   break;
   case 'r' :
     scanf("%f", &f);
	 Remove(f);
   break;
   }
 scanf("%s", String);
}
 return 0;
}