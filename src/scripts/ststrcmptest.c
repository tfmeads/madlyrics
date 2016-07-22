#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities.h"

int main(int argc,char **argv){

	char a[128];
	char b[128];

	strcpy(a,"TEST T EA1 S T");
	strcpy(b,"WORD W O2 R D");
	fprintf(stderr,"Result is %i\n",secondTokenStrcmp(a,b));
	fprintf(stderr,"A: %s B: %s\n",a,b);

	return(0);
}
