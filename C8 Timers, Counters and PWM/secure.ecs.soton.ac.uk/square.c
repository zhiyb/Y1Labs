/*  Author: Klaus-Peter Zauner
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *          View this license at http://creativecommons.org/about/licenses/
 *   Notes: F_CPU must be defined to match the clock frequency
 */
#include <avr/io.h>
#include <util/delay.h>

#define FREQ 4000



unsigned long toneClock;   /* set at timer initialisation and used
                              to calculate TOP when setting frequency */ 

void init_tone(void);
void tone(uint16_t frequency);

int main(void) {

    init_tone();
    
    for (;;) tone(FREQ);

}



/* init_tone ---
   Setup timer as a tone frequency oscillator.
*/
void init_tone(void)
{
    /******************************
    /  STUB:
    /  Replace this comment 
    /  with an implementation
    /
    ******************************/
}

/* tone ---
   Set oscillator output to desired frequency
*/
void tone(uint16_t frequency)
{

    /******************************
    /  STUB:
    /  Replace this comment 
    /  with an implementation
    /
    ******************************/

}


