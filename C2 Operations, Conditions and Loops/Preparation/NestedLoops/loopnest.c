/* 
 * Illustrates a pair of nested counting loops 
 */ 
 
#include <stdio.h> 
 
int main(void) 
{ 
    /* loop control variables */ 
    int i, j;   
    
    /* print column labels */ 
    printf("           I    J\n");
    
    /* heading of outer for loop */ 
    for  (i = 1;  i < 4;  i = i + 1) 
    {   
        printf("Outer %6d\n", i); 
        /* heading of inner loop */ 
        for  (j = 0;  j < i;  j = j + 1)
        {   
            printf("  Inner%9d\n", j); 
        }   
        /* end of inner loop */ 
    }   
    /* end of outer loop */ 
    
    return 0; 
} 

