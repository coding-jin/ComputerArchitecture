#include <stdio.h>
#include <stdlib.h>

#define BUCKETSIZE 1000

typedef struct Node{
	int value;
	struct Node *next;
}Node;


Node buckets[BUCKETSIZE];

void clean();

int main(int argc, char **argv) {
	if(argc != 2) {
		printf("argc!=2\n");
		return 0;
	}

	FILE *fp = fopen(argv[1], "r");
	if(fp == NULL) {
		printf("error\n");
		return 0;
	}

	char op;
	int value, index;
	int duplicate;

	for(int i=0;i<BUCKETSIZE;++i)	buckets[i].next = NULL;

	Node *node, *current, *prior;
	while(fscanf(fp, "%c %d ", &op, &value) == 2) {
		index = value>=0? value:-value;
		index = index % BUCKETSIZE;
		if(op == 'i') {
			current = buckets[index].next;
			if(current==NULL) {
				node = (Node*)malloc(sizeof(Node));
				if(node == NULL) {
					printf("malloc for node fails!\n");
					return 0;
				}
				buckets[index].next = node;
				node->value = value;
				node->next = NULL;
				printf("inserted\n");
			}else {
				duplicate = 0;
				while(current) {
					if(current->value == value) {
						printf("duplicate\n");
						duplicate = 1;
						break;
					}
					prior = current;
					current = current->next;
				}
				if(duplicate == 1)	continue;
				current = (Node*)malloc(sizeof(Node));
				if(current == NULL) {
					printf("malloc for node fails!\n");
					return 0;
				}
				current->value = value;
				current->next = NULL;
				prior->next = current;
				printf("inserted\n");
			}

		}else if(op == 's') {
			current = buckets[index].next;
			while(current) {
				if(current->value == value)	{
					printf("present\n");
					break;
				}
				current = current->next;
			}
			if(current == NULL)	printf("absent\n");
		}
	}
	clean();
	return 0;
}

void clean() {
	Node *tmp, *current;
	for(int i=0;i<BUCKETSIZE;++i) {
		current = buckets[i].next;
		while(current) {
			tmp = current;
			current = current->next;
			free(tmp);
		}
		buckets[i].next = NULL;
	}
}

