#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
for(int i = 0; i < argc; i++)
printf("argv[%d]=%s\n", i, argv[i]);

printf("argc: %d\n", argc);

printf("argv[0]=%s\n", argv[0]);
printf("argv[1]=%s\n", argv[1]);
printf("argv[2]=%s\n", argv[2]);
printf("argv[3]=%s\n", argv[3]);
return 0;
}