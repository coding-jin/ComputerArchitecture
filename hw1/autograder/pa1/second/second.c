#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
	int number;
	struct Node *next;
}Node;

int main(int argc, char **argv) {
	if(argc != 2) {
		printf("argc!=2\n");
		return 1;
	}

	FILE *fp = fopen(argv[1], "r");
	if(fp == NULL) {
		printf("error\n");
		return 0;
	}

	int count=0, number;
	char op;
	Node *head = NULL;
	while(fscanf(fp, "%c %d ", &op, &number) == 2) {
		if(op == 'i') {
			if(count==0) {
				head = (Node*)malloc(sizeof(Node));
				if(head==NULL) {
					printf("malloc fails!\n");
					return 0;
				}
				head->number = number;
				head->next = NULL;
				count++;
			}else {
				Node *current = head;
				Node *prior = NULL;
				while(current && current->number<number) {
					prior = current;
					current=current->next;
				}
				if(current==NULL) {
					prior->next = (Node*)malloc(sizeof(Node));
					if(prior->next == NULL)	{
						printf("malloc for prior->next fails\n");
						return 0;
					}else {
						prior->next->number = number;
						prior->next->next = NULL;
						count++;
					}
				}else if(current->number>number) {
					// current==head
					if(prior == NULL) {
						Node *tmpnode = (Node*)malloc(sizeof(Node));
						if(tmpnode==NULL) {
							printf("malloc for tmpnode fails!\n");
							return 0;
						}
						tmpnode->number = current->number;
						tmpnode->next = current->next;
						current->next = tmpnode;
						current->number = number;
						++count;
					}else {
						prior->next = (Node*)malloc(sizeof(Node));
						if(prior->next == NULL) {
							printf("malloc for prior->next fails!\n");
							return 0;
						}
						prior->next->number = number;
						prior->next->next = current;
						++count;
					}
				}

			}
		// end of 'i'
		}else if(op == 'd') {
			if(count == 0)	continue;
			Node *current = head;
			Node *prior = NULL;
			while(current!=NULL) {
				if(current->number == number) {
					if(prior==NULL) {
						// current==head
						head = head->next;
						count--;
						free(current);
					}else {
						prior->next = current->next;
						count--;
						free(current);
					}
					break;
				}else if(current->number > number)	break;
				else {
					prior = current;
					current = current->next;
				}
			}
		}
		// end of 'd'
	} // end of big while

	printf("%d\n", count);
	if(count==0)	return 0;
	
	Node *tmp;
	while(count--) {
		printf("%d\t", head->number);
		tmp = head;
		head = head->next;
		free(tmp);
	}
	printf("\n");
	return 0;
}

