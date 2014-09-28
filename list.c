#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* your list function definitions */

void list_clear(struct node *list) {
    while (list != NULL) {
        struct node *tmp = list;
        list = list->next;
        free(tmp);
    }
}

void list_print(const struct node *list) {
    int i = 0;
    printf("***List Contents Begin***\n");
    while (list != NULL) {
        printf("List item %d: %d\n", i++, list->num);
        list = list->next;
    }
	printf("***List Contents End***\n");
}

void list_appendsort(int num, struct node **head) {   //append num in order
    struct node *tmp=*head;
	struct node *new=malloc(sizeof(struct node));
	
	new->num=num;
	if(tmp==NULL){
	
		*head=malloc(sizeof(struct node));
		(*head)->num=num;
		free(new);
	}else if(tmp->next==NULL){
		if(num>=(tmp->num)){
			tmp->next=new;
		}else{
			new->next=tmp;
			*head=new;
		}
	}else if(num<(tmp->num)){
		new->next=tmp;
		*head=new;
	}else{                              
		while(tmp->next!=NULL){
			if(num>=(tmp->num)){
				if(tmp->next==NULL){
					tmp->next=new;
					return;
				}else if(num>=(tmp->next->num)){
					tmp=tmp->next;
				}else{
					new->next=tmp->next;
					tmp->next=new;
					return;
				}
			}
			
		}
		tmp->next=new;
		
	}
	
}



/*int main(int argc, char **argv){
	struct node *list=NULL;
	list_appendsort(3,&list);
	list_appendsort(2,&list);
	list_appendsort(5,&list);
	list_appendsort(4,&list);
	list_print(list);
}*/
