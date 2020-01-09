#include <stdio.h>
#include <stdlib.h>


typedef struct Node{
	int value;
	int height;
	struct Node *left;
	struct Node *right;
}Node;

void lower(Node *root);

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
		}else if(op == 'd') {
			if(root==NULL) {
				printf("fail\n");
				continue;
			}
			
			if(root->value==number) {
				if(root->left==NULL && root->right==NULL) {
					free(root);
					root = NULL;
				}else if(root->left==NULL && root->right!=NULL) {
					current = root;
					root = root->right;
					free(current);
					current = NULL;
					lower(root);
				}else if(root->right==NULL && root->left!=NULL) {
					current = root;
					root = root->left;
					free(current);
					current = NULL;
					lower(root);
				}else {
					// the target node to be deleted is root, and it has 2 children
					Node *min = root->right;
					parent = NULL;
					while(min->left) {
						parent = min;
						min = min->left;
					}
					if(parent==NULL) {
						root->value = min->value;
						root->right = min->right;
						lower(min->right);
						free(min);
						min = NULL;
					}else {
						root->value = min->value;
						parent->left = min->right;
						lower(min->right);
						free(min);
						min = NULL;
					}
				}
				printf("success\n");
				// end for root deleted
			}else {
				// root will not be deleted
				if(root->value<number)	current=root->right;
				else					current=root->left;
				parent = root;
				while(current && current->value!=number) {
					parent = current;
					if(current->value>number)	current=current->left;
					else	current=current->right;
				}
				if(current==NULL)	printf("fail\n");
				else {
					// to delete current
					if(current->left==NULL && current->right==NULL) {
						if(current->value > parent->value) {
							// parent->right
							parent->right = NULL;
						}else {
							parent->left = NULL;
						}
						free(current);
						current = NULL;

					}else if(current->left==NULL && current->right!=NULL) {
						if(current->value > parent->value) {
							// parent->right
							parent->right = current->right;
						}else {
							// parent->left
							parent->left = current->right;
						}
						lower(current->right);
						free(current);
						current = NULL;

					}else if(current->left!=NULL && current->right==NULL) {
						if(current->value > parent->value) {
							// parent->right
							parent->right = current->left;
						}else {
							// parent->left
							parent->left = current->left;
						}
						lower(current->left);
						free(current);
						current = NULL;

					}else {
						// current has 2 children
						Node *min = current->right;
						parent = current;
						while(min->left) {
							parent = min;
							min = min->left;
						}
						current->value = min->value;
						if(parent==current) {
							current->right = min->right;
						}else {
							parent->left = min->right;
						}
						lower(min->right);
						free(min);
						min = NULL;
						// finish the node to delete, has 2 children
					}
					printf("success\n");

				}

			}
		// end for delete
		}
	}

	return 0;
}

void lower(Node *root) {
	if(root==NULL)	return;
	Node *current = root;
	current->height = current->height-1;
	lower(current->left);
	lower(current->right);
}
