#include <stdio.h>
#include <stdlib.h>

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
	int n, n2;

	fscanf(fp, "%d ", &n);
	n2 = n*n;
	int *visit = (int*)malloc(sizeof(int)*n2);
	if(visit == NULL) {
		printf("error\n");
		return 0;
	}
	for(int i=0;i<n2;++i)	visit[i] = 0;

	int **matrix = (int**)malloc(sizeof(int*)*n);
	if(matrix==NULL) {
		printf("error\n");
		return 0;
	}
	for(int i=0;i<n;++i) {
		matrix[i] = (int*)malloc(sizeof(int)*n);
		if(matrix[i] == NULL) {
			printf("error\n");
			return 0;
		}
		for(int j=0;j<n;++j) {
			fscanf(fp, "%d ", &matrix[i][j]);
			if(matrix[i][j]>=1 && matrix[i][j]<=n2)	visit[matrix[i][j]-1] = 1;
			else {
				printf("not-magic\n");
				return 0;
			}
		}
	}

	// diff number?
	for(int i=0;i<n2;++i)
		if(visit[i]==0) {
			printf("not-magic\n");
			return 0;
		}

	// same sum
	int sum = 0;
	for(int i=0;i<n;++i)	sum += matrix[i][i];
	int tmpsum = 0;
	for(int i=0;i<n;++i)	tmpsum += matrix[i][n-1-i];
	if(tmpsum != sum) {
		printf("not-magic\n");
		return 0;
	}
	for(int i=0;i<n;++i) {
		tmpsum = 0;
		for(int j=0;j<n;++j)	tmpsum += matrix[i][j];
		if(tmpsum != sum) {
			printf("not-magic\n");
			return 0;
		}

		tmpsum = 0;
		for(int j=0;j<n;++j)	tmpsum += matrix[j][i];
		if(tmpsum != sum) {
			printf("not-magic\n");
			return 0;
		}
	}
	printf("magic\n");
	return 0;
}



