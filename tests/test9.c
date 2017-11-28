#include <malloc/malloc.h>
#include <stdio.h>
#include "../includes/malloc.h"
#include <stdlib.h>
int main()
{ 
int i; 
char *addr; 
size_t total;
i = 0; 
while (i < 1000) 
{
addr = (char*)malloc(-1);
printf("%zu\n", malloc_size(addr)); 
addr[42] = 42;
i++; 
}
show_alloc_mem();
return (0); 
}