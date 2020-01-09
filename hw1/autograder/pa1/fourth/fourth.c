#include <stdio.h>
#include <stdlib.h>

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

	int l, m1;
	fscanf(fp, "%d %d ", &l, &m1);
	int **matrix1 = (int**)malloc(sizeof(int*)*l);
	if(matrix1 == NULL) {
		printf("error\n");
		return 0;
	}
	for(int i=0;i<l;++i) {
		matrix1[i] = (int*)malloc(sizeof(int)*m1);
		if(matrix1[i] == NULL) {
			printf("error\n");
			return 0;
		}
		for(int j=0;j<m1;++j) {
			fscanf(fp, "%d ", &matrix1[i][j]);
		}
	}

	// second matrix
	int m2, n;
	fscanf(fp, "%d %d ", &m2, &n);
	if(m1 != m2) {
		printf("bad-matrices\n");
		return 0;
	}
	int **matrix2 = (int**)malloc(sizeof(int*)*m2);
	if(matrix2 == NULL) {
		printf("error\n");
		return 0;
	}
	for(int i=0;i<m2;++i) {
		matrix2[i] = (int*)malloc(sizeof(int)*n);
		if(matrix2[i] == NULL) {
			printf("malloc for matrix2[i] fails!\n");
			return 0;
		}
		for(int j=0;j<n;++j)	fscanf(fp, "%d ", &matrix2[i][j]);
	}

	// matrix multiplication
	int **matrix = (int**)malloc(sizeof(int*)*l);
	if(matrix == NULL) {
		printf("error\n");
		return 0;
	}
	for(int i=0;i<l;++i) {
		matrix[i] = (int*)malloc(sizeof(int)*n);
		if(matrix[i] == NULL) {
			printf("error\n");
			return 0;
		}
		for(int j=0;j<n;++j)
			matrix[i][j] = 0;

	}
	
	for(int i=0;i<l;++i)
		for(int j=0;j<n;++j) {
			for(int k=0;k<m1;++k)	matrix[i][j] += matrix1[i][k]*matrix2[k][j];
			if(j!=n-1)	printf("%d\t", matrix[i][j]);
			else		printf("%d\n", matrix[i][j]);
		}

	return 0;
}


