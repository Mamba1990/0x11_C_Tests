#include <stdio.h>
#include <stdlib.h>

int main() 
{
	printf("$ ");
    
    	char command[100];
    	fgets(command, sizeof(command), stdin);
    
    	printf("%s", command);
    
 return 0;
}
