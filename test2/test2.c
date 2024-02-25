#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

    #define CHAR_MAX 255
    int main (int argc, char ** argv) {
        char buf[CHAR_MAX] = {0};
        FILE * fd;
        char c = 0;

        if (argc != 2) 
            return 1;

        if ((fd = fopen(argv[1], "r")) == NULL)
            return 1;

        while ((c = (char)fgetc(fd)) != EOF)
            buf[c]++;

        for (int i = 0; i < CHAR_MAX; i++) {
            if (buf[i] == 0 || !isprint(i))
                continue;
            printf("%c: ", i);
            for (int j = 0; j < buf[i]; j++) 
                putchar('#');	
            putchar('\n');
        }
        fclose(fd);
        return 0;
    }
