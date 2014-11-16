/* This is the C code for Il Matto(ATMEGA644P),
 * boost converter project.
 * Wrote by Yubo Zhi (yz39g13@soton.ac.uk)
 */

#ifndef PWM_H
#define PWM_H

#define PWM_MAX		942	// 92% duty cycle
#define PWM_set(v)	\
	do { \
		if ((v) > PWM_MAX) \
			OCR1A = PWM_MAX; \
		else \
			OCR1A = (uint16_t)(v); \
	} while (0)
#define PWM_inc(v)	\
	do { \
		if (OCR1A + (v) <= PWM_MAX) \
			OCR1A += (uint16_t)(v); \
		else \
			OCR1A = PWM_MAX; \
	} while (0)
#define PWM_dec(v)	\
	do { \
		if (OCR1A >= (v)) \
			OCR1A -= (uint16_t)(v); \
		else \
			OCR1A = 0; \
	} while (0)

void PWM_init(void);

#endif
