/* Conversion of Celsius to Fahrenheit temperatures */

#include <stdio.h>

/* Constant macros */
#define CBEGIN 10
#define CLIMIT -5
#define CSTEP 5

int main(void)
{
    /* Variable declarations */    
    int    celsius;    
    double fahrenheit;     
    
    /* Print the table heading */    
    printf("  Celsius  Fahrenheit\n");     
    
    /* Print the table */    
    for  (celsius = CBEGIN;      
            celsius >= CLIMIT;      
            celsius = celsius - CSTEP) 
    {
        fahrenheit = 1.8 * celsius + 32.0;     
        printf("  %3d    %7.2f\n", celsius, fahrenheit);    
    }  
    
    return 0; 
}      

