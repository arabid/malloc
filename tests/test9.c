#include <stdio.h>
#include "../includes/malloc.h"
#include <stdlib.h>
int main()
{ 
int i; 
char *addr; 

i = 0; 
while (i < 1) 
{
addr = (char*)malloc(1024); 
i++; 
}
show_alloc_mem();
return (0); 
}