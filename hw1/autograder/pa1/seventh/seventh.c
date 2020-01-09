#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv) {
	if(argc < 2) {
		printf("argc<2\n");
		return 1;
	}
	int len;
	for(int i=1;i<argc;++i) {
		len = strlen(argv[i]);
		putchar(argv[i][len-1]);
	}
	putchar('\n');
	return 0;
}
