#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isValid(int number);
int isPrime(int number);

int main(int argc, char **argv) {
	if(argc != 2) {
		printf("argc!=2\n");
		return 1;
	}
	FILE *fp = fopen(argv[1], "r");
	if(fp == NULL) {
		printf("cannot open the file[%s]\n", argv[1]);
		return 1;
	}
	int num, number;
	if(fscanf(fp, "%d ", &num) == 1) {
		for(int i=0;i<num;++i) {
			if(fscanf(fp, "%d ", &number) == 1) {
				if(isValid(number))	printf("yes\n");
				else				printf("no\n");
			}
		}
	}
	return 0;
}

int isValid(int number) {
	if(number<=1)	return 0;
	else if(number==2)	return 1;
	else {
		if(!isPrime(number))	return 0;
		int tmp = number/10;
		while(tmp) {
			if(tmp==1)	return 0;
			else if(!isPrime(tmp))	return 0;

			tmp = tmp/10;
		}
		return 1;
	}
}

int isPrime(int number) {
	if(number == 2)	return 1;
	else if(number % 2 ==0)	return 0;
	else {
		for(int i=3;i<=number/2;i=i+2) {
			if(number%i == 0)	return 0;
		}
		return 1;
	}
}
