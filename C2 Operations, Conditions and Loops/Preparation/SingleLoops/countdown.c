/* Counting down to blast-off */     
 
#include <stdio.h>     
 
int main(void)   
{    
    int time, start;     
    start = 10;       
    printf("\nBegin countdown\n");    
    for  (time = start;      
        time > 0;      
        time = time - 1) {     
        printf("T - %d\n", time);    
    } 
    printf("Blast-off!\n");
 
    return 0; 
}
 
