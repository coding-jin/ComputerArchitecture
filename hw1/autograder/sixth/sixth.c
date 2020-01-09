#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isV(char c) {
	if(c=='a' || c=='A' || c=='e' || c=='E' || c=='i' || c=='I' || c=='o' || c=='O' || c=='u' || c=='U')	return 1;
	else	return 0;
}

int main(int argc, char **argv) {
	if(argc < 2) {
		printf("argc<2\n");
		return 1;
	}

	char *str, head;
	char ss[1024];
	int len;
	for(int i=1;i<argc;++i) {
		str = argv[i];
		head = str[0];
		len = strlen(str);
		if(isV(head)) {
			strcpy(ss, str);
			ss[len] = 'y';
			ss[len+1] = 'a';
			ss[len+2] = 'y';
			ss[len+3] = 0;
		}else {
			if(len==1) {
				ss[0] = head;
				ss[1] = 'a';
				ss[2] = 'y';
				ss[3] = 0;
			}else if(isV(str[1])) {
				strcpy(ss, str+1);
				ss[len-1] = str[0];
				ss[len] = 'a';
				ss[len+1] = 'y';
				ss[len+2] = 0;
			}else {
				int j;
				for(j=1;j<len;++j) {
					if(isV(str[j]))	break;
				}
				if(j==len) {
					// no vowel
					strcpy(ss, str);
					ss[len] = 'a';
					ss[len+1] = 'y';
					ss[len+2] = 0;
				}else {
					strcpy(ss, str+j);
					strncpy(ss+len-j, str, j);
					ss[len] = 'a';
					ss[len+1] = 'y';
					ss[len+2] = 0;
				}
			}
		}
		printf("%s", ss);
		if(i!=argc-1)	printf(" ");
		else			printf("\n");
	}
	return 0;
}
