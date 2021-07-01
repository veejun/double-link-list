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
int search_cost(node *, char, int);

int main(){
	
	char ch;
	int i;
	int fill = 0;
	int pos;	
	node *head = build_platform();
		
	/* read file */		
	FILE *fpr;
	fpr = fopen("./data/test1.txt", "r");

	//first letter	
	ch = fgetc(fpr);
	
	if(ch != ' '){
		fill++;
		head->data = ch;
		if(ch <= 'M'){
			for(i = 0; i < ch - 64; i++){
				printf("+");
			}
			printf(".");
		}else{
			for(i = 0; i < 91 - ch; i++){
				printf("-");
			}
			printf(".");		
		}	
	}else{
		printf(".");
	}
	
		
	while((ch = fgetc(fpr)) != EOF){
		if(abs(fill) < 5){
			pos = search_cost(head, ch, 2);
		}else if(5 <= abs(fill) < 14){
			pos = search_cost(head, ch, 3);
		}else{ // fill >= 14
			pos = search_cost(head, ch, 6);
		}
		//printf("\nch = %c, old = %c   ", ch, head->data);
		// move to coerrect position
		if(pos > 0){
			for(i = 0; i < pos; i++){
				head = head->rlink;
				printf(">");
			}
		}else if(pos < 0){
			for(i = 0; i < -pos; i++){
				head = head->llink;
				printf("<");
			}
		}
		//printf("   ,head->data = %c   ", head->data);
		
		// move to coerrect letter
		if(head->data != ch){
			if(head->data == ' '){
				fill++;
				if(ch <= 'M'){
					for(i = 0; i < ch - 64; i++){
						printf("+");
					}
					head->data = ch;
					printf(".");
				}else{
					for(i = 0; i < 91 - ch; i++){
						printf("-");
					}
					head->data = ch;
					printf(".");		
				}								
			}else{ //head->data is a letter
				if(ch == ' '){
					fill--;
					if(head->data <= 'M'){
						for(i = 0; i < head->data - 64; i++){
							printf("-");
						}
						head->data = ch;
						printf(".");
					}else{
						for(i = 0; i < 91 - head->data; i++){
							printf("+");
						}
						head->data = ch;
						printf(".");		
					}
				}else{ //head->data is a letter, ch is a letter
					if(ch - head->data > 0){ //go +
						if(ch - head->data < 27 - (ch - head->data)){
							for(i = 0; i < ch - head->data; i++){
								printf("+");
							}
							head->data = ch;
							printf(".");
						}else{ // 27 - (ch - head->data) is smaller
							for(i = 0; i < 27 - (ch - head->data); i++){
								printf("-");
							}
							head->data = ch;
							printf(".");
						}
					}else{ //go -
						if(head->data - ch < 27 - (head->data - ch)){
							for(i = 0; i < head->data - ch; i++){
								printf("-");
							}
							head->data = ch;
							printf(".");
						}else{ // 27 - abs(ch - head->data) is smaller
							for(i = 0; i < 27 - (head->data - ch); i++){
								printf("+");
							}
							head->data = ch;
							printf(".");
						}
					}
				}
			}			
		}else{ //head->data == ch
			printf(".");
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

int search_cost(node *head, char ch, int n){
	int i;
	int cost;
	int temp_cost;
	int pos = 0;
	node *temp = head;
	
	// the cost when temp == head
	if(ch == ' '){
		if(head->data == ' '){
			cost = 0;
		}else{
			cost = (head->data - 64) < (91 - head->data) ? (head->data - 64) : (91 - head->data);
		}
	}else{ //ch is a letter
		if(head->data == ' '){
			cost = (ch - 64) < (91 - ch) ? (ch - 64) : (91 - ch);
		}else{
			cost = abs(head->data - ch) < (27 - abs(head->data - ch)) ? abs(head->data - ch) : (27 - abs(head->data - ch));
		}
	}
	
	/* search case */
	if(ch == ' '){		
		for(i = 1; i <= n; i++){
			temp = temp->rlink;
			if(temp->data == ' '){ //ch == temp->data == ' '
				temp_cost = i;
			}else{  //ch == ' ', temp->data is a letter
				temp_cost = ((temp->data - 64) < (91 - temp->data) ? (temp->data - 64) : (91 - temp->data)) + i;
			}
			if(temp_cost < cost){ 
				cost = temp_cost;
				pos = i;
			}
		}
		temp = head;
		for(i = 1; i <= n; i++){
			temp = temp->llink;
			if(temp->data == ' '){ //ch == temp->data == ' '
				temp_cost = i;
			}else{  //ch == ' ', temp->data is a letter
				temp_cost = ((temp->data - 64) < (91 - temp->data) ? (temp->data - 64) : (91 - temp->data)) + i;
			}
			if(temp_cost < cost){ 
				cost = temp_cost;
				pos = -i;
			}
		}	
	}else{ //ch is a letter
		for(i = 1; i <= n; i++){
			temp = temp->rlink;
			if(temp->data == ' '){ //temp->data == ' ', ch is a letter
				temp_cost = ((ch - 64) < (91 - ch) ? (ch - 64) : (91 - ch)) + i;
			}else{    //temp->data is a letter, ch is a letter
				temp_cost = (abs(temp->data - ch) < (27 - abs(temp->data - ch)) ? abs(temp->data - ch) : (27 - abs(temp->data - ch))) + i;
			}
			if(temp_cost < cost){
				cost = temp_cost;
				pos = i;
			}
		}
		temp = head;
		for(i = 1; i <= n; i++){
			temp = temp->llink;
			if(temp->data == ' '){ //temp->data == ' ', ch is a letter
				temp_cost = ((ch - 64) < (91 - ch) ? (ch - 64) : (91 - ch)) + i;
			}else{    //temp->data is a letter, ch is a letter
				temp_cost = (abs(temp->data - ch) < (27 - abs(temp->data - ch)) ? abs(temp->data - ch) : (27 - abs(temp->data - ch))) + i;
			}
			if(temp_cost < cost){
				cost = temp_cost;
				pos = -i;
			}
		}		
	} 

	return pos;
}
