#include <stdio.h>
#include <stdlib.h>

#define MAGIC_NUMBER 0x12345678

int main (int argc, char * argv[])
{
	FILE * fptr = NULL;
	fptr = fopen (argv[1], "r");
	if (fptr){
		int magic;
		fread(&magic, sizeof(int), 1, fptr);
		if (magic != MAGIC_NUMBER){
			printf("Show the magic !!No magic for you");
			exit(1);
		}
		else{
			printf("Show the magic -- I will show you a magic");
		}
	}
	fclose(fptr);
	return 0;
}
