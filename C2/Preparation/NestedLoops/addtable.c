/* 
 * Prints an addition table 
 */ 
#include <stdio.h> 
#define NUM_DIGITS  10 

int main(void) 
{ 
    int addend_1, addend_2, sum;
 
    /* Prints the table heading.              */ 
    printf("+"); 
    for  (addend_2 = 0; 
            addend_2 < NUM_DIGITS; 
            addend_2 = addend_2 + 1) 
    {
        printf("%3d", addend_2);  /* Prints each digit in heading.   */ 
    }
    
    /* Prints the table body.                 */ 
    for  (addend_1 = 0; 
            addend_1 < NUM_DIGITS; 
            addend_1 = addend_1 + 1) { 
        printf("\n%d", addend_1); /* Starts a row with first addend. */ 
    
        for  (addend_2 = 0; 
                addend_2 < NUM_DIGITS; 
                addend_2 = addend_2 + 1) 
        { 
            sum = addend_1 + addend_2; 
            printf("%3d", sum); 
        } 
    } 
    printf("\n"); 
    
    return 0; 
} 

