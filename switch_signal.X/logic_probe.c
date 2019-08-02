/* 
 * File:   logic_probe.c
 * Author: eduardo
 *in this project a button input signal(RC3) controls a pair of LEDs output (RC4,RC5)
 * Created on 17 de julio de 2017, 12:26 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#define _XTAL_FREQ 800000
/*
 * 
 */
int main() {
    TRISCbits.TRISC3=1; // configure RC3 as an input pin for button
    TRISCbits.TRISC4=0; //configure RC4 as an output pin for led (INPUT TRUE)
    TRISCbits.TRISC5=0; //configure RC5 as an output pin for led (INPUT FALSE)
    //initial conditions
    PORTCbits.RC3=0;
    PORTCbits.RC4=1;
    PORTCbits.RC5=1;
    while(1)
    {
         if(RC3==1)
         {
          RC4=0;
           __delay_ms(500);
           RC4=1;
               
         }
         else
         {
             RC5=0;
             __delay_ms(500);
             RC5=1;
            }
    }
   
}

