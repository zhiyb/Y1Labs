/* 
 * Displays the height of an object dropped from a tower until it  
 * hits the ground.    
 */     
 
#include <stdio.h>     
 
#define G    9.80665    /* gravitational constant */     
 
int main(void)   
{    
    double height,    /* height of object       */       
         tower,     /* height of tower        */       
         t,         /* elapsed time           */       
         delta_t;   /* time interval          */     
    
    /* Enter tower height and time interval.
        Try to vary these two.
    */    
    tower = 34;
    delta_t = 2;
    
    /* Display table of object heights as it falls.     */    
    printf("\n  Time   Height\n\n");    
    t = 0.0;    
    for  (height = tower;      
        height > 0.0;      
        height = tower - 0.5 * G * t * t) 
    {     
        printf(" %6.2f  %7.2f\n", t, height);     
        t = t + delta_t;    
    }  
    
    /* Object hits the ground                           */ 
    printf("\nSPLAT!!!\n");   
    
    return 0; 
}      

