#include <stdio.h>
#include <stdlib.h>

struct linklist{
	char data;
	struct linklist *llink;
	struct linklist *rlink;
};
typedef struct linklist node;

node *build_platform();
node *newNode();

int main(){
	
	char ch;	
	node *head = build_platform();
		
	/* read file */		
	FILE *fpr;
	fpr = fopen("./data/test1.txt", "r");
		
	while((ch = fgetc(fpr)) != EOF){
		switch(ch){
			case'+':
				if(head->data == ' '){
					head->data = 'A';
				}else if(head->data == 'Z'){
					head->data = ' ';
				}else head->data++;
				break;
			case'-':
				if(head->data == ' '){
					head->data = 'Z';
				}else if(head->data == 'A'){
					head->data = ' ';
				}else{
					head->data--;
				}
				break;
			case'>':
				head = head->rlink;
				break;
			case'<':
				head = head->llink;
				break;
			case'.':
				printf("%c", head->data);
				break;
		}
	}	    	    
			
	fclose(fpr);
		
	return 0;
}

node *build_platform(){
	int i;
	node *head = newNode();
	for(i = 0; i < 19; i++){
		node *temp = newNode();
		temp->rlink = head->rlink;
		head->rlink->llink = temp;
		temp->llink = head;
		head->rlink = temp;
	}
	return head;
}

node *newNode(){
	node *temp = (node *)malloc(sizeof(node));
	temp->data = ' ';
	temp->llink = temp->rlink = temp;
	return temp;	
}
