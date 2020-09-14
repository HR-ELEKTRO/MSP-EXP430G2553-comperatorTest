#include <msp430.h> 
#include <stdbool.h>
#include <stdint.h>

/*
 * testprogramma voor comparator
 * 2017 Harry Broeders
 * Als de comparator correct functioneert, gaat de groene led branden.
 * Als de comparator niet correct functioneert, gaat de rode led branden.
 * Zodra een fout gevonden is stopt het programma. Dus je kunt door de outputs
 * van het programma te testen, zien in welke situatie de fout is opgetreden. 
 *
 * Verbindingen:
 * Pin 1.1 = GT
 * Pin 1.2 = LT
 * Pin 1.4 = EQ
 * Pin 2.0 = A0
 * Pin 2.1 = A1
 * Pin 2.2 = A2
 * Pin 2.3 = B0
 * Pin 2.4 = B1
 * Pin 2.5 = B2
 */

int main(void) 
{
    // stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;
    
    // Pin 1.0 = groene led
    // Pin 1.6 = rode led
    
    P1DIR = 1<<6 | 1<<0;
    P1OUT = 0;
    P2DIR = 1<<5 | 1<<4 | 1<<3 | 1<<2 | 1<<1 | 1<<0;
    P2OUT = 0;

    uint8_t a, b;
    bool GT, LT, EQ;
    for (a = 0; a < 8; a++)
    {
        for (b = 0; b < 8; b++)
        {
            P2OUT &= ~(1<<5 | 1<<4 | 1<<3 | 1<<2 | 1<<1 | 1<<0);
            P2OUT |= (b<<3)|a;
            __delay_cycles(1100); // delay 1 ms @ 1.1 MHz
            GT = (P1IN & 1<<1) == 1<<1;
            LT = (P1IN & 1<<2) == 1<<2;
            EQ = (P1IN & 1<<4) == 1<<4;
             
            if (GT != (a > b) || LT != (a < b) || EQ != (a == b))
            {
                P1OUT |= 1<<6;
                while (1); // stop when error is found
            }
        }
    }
    P1OUT |= 1<<0;
    	
    return 0;
}
