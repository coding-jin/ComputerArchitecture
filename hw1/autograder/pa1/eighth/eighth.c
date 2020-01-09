#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int value;
	int height;
	struct Node *left;
	struct Node *right;
}Node;


int main(int argc, char **argv) {
	if(argc != 2) {
		printf("error\n");
		return 0;
	}

	FILE *fp = fopen(argv[1], "r");
	if(fp == NULL) {
		printf("error\n");
		return 0;
	}

	char op;
	int number;
	Node *root = NULL, *current, *parent;
	while(fscanf(fp, "%c %d ", &op, &number) == 2) {
		if(op == 'i') {
			if(root==NULL) {
				root = (Node*)malloc(sizeof(Node));
				if(root==NULL) {
					printf("error, failed to malloc root\n");
					return 0;
				}
				root->height = 1;
				root->value = number;
				root->left = NULL;
				root->right = NULL;
				printf("inserted %d\n", 1);
			}else {
				current = root;
				parent = NULL;
				while(current!=NULL && current->value!=number) {
					parent = current;
					if(current->value > number)	current = current->left;
					else	current = current->right;
				}
				if(current==NULL) {
					current = (Node*)malloc(sizeof(Node));
					current->value = number;
					current->left = NULL;
					current->right = NULL;
					current->height = parent->height+1;
					if(current==NULL) {
						printf("fails to malloc for current!\n");
						return 0;
					}
					if(parent->value > number)	parent->left = current;
					else						parent->right = current;

					printf("inserted %d\n", current->height);
				}else {
					printf("duplicate\n");
				}
			}
			// end for insert
		}else if(op == 's') {
			if(root==NULL)	printf("absent\n");
			else {
				current = root;
				while(current) {
					if(current->value == number) {
						printf("present %d\n", current->height);
						break;
					}else if(current->value < number)	current = current->right;
					else	current = current->left;
				}
				if(current == NULL)	printf("absent\n");
			}
			// end for search
		}
	}

	return 0;
}

