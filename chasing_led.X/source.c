/* 
 * File:   PDL.c
 * Author: eduardo
 *CHASING LEDS: THERE ARE 8 LEDS CONNECTED TO THE PORTC OF THE MICROCONTROLLER
 * THE LEDS MUST TURN ON ALTERNATELY IN CLOCKWISE DIRECTION, ONLY ONE LED AT A TIME IS ACTIVE
 * A 500 MS DELAY IS SET TO SHOW THE PROPER ACTIVE LED
 * 
 * 
 * Created on 13 de julio de 2017, 05:30 PM
 */

#define _XTAL_FREQ 8000000//SE USA DEBIDO A QUE ESTOY USANDO EL COMANDO __DELAY_MS, LE DA LA FREQUENCIA
#include <xc.h>     //identifies use and calls appropriate header files.
#include <pic18f25k80.h>
 #pragma config XINST = OFF // extended instruction set and indexeed mode disabled
#pragma config SOSCSEL=0b10;// PINs RC0, RC1 function as general purpose(i/o) pins and not for clock

int main(void) {
    TRISC=0;    //configure portc as output
    
    unsigned char ibyte=0b11111110; //initial byte to set port c 
     unsigned char sbyte=0b11111111;//sample byte
    unsigned int brotation=2; // variable to substract from sample byte in order to look like if the bit is rotating

    while(1)
    {
        PORTC=ibyte;    //output of portc
        __delay_ms(500);
        ibyte=sbyte - brotation;    //substraction to rotate bit
        brotation=brotation*2;  //set up the next substraction (times 2 because is higher the next bit value)
        
        if(ibyte==0b01111111) // when reach the last led return to initial state
        {
            PORTC=ibyte;    //show last value
            __delay_ms(500);
            ibyte=0b11111110;//reset conditions
            brotation=2;        //
        }
       
        
    }
    
    
  
}

