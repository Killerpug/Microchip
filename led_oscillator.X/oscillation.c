/* 
 * File:   oscillation.c
 * Author: eduardo
 *In this project 8 leds are connected to port c of pic18f25k80 operated at a frequency of 8MHZ, 
 * the program flashes the 4 highier bits and after an interrupt every .5 miliseconds it alternates with the 4 lower bits
 * NOTE: before entering to the 1:256 prescaler, the internal oscillator frequency is divided by 4 (Fosc/4) because each instruction takes 4 cycles
 * Created on 14 de julio de 2017, 03:32 PM
 */
#include <xc.h>     //identifies use and calls appropriate header files.
#include <stdio.h>
#include <stdlib.h>
#pragma config SOSCSEL=0b10;// PINs RC0, RC1 function as general purpose (i/o) pins and not for clock
#include <pic18f25k80.h>
 #pragma config XINST = OFF // extended instruction set and indexeed mode disabled
/*
 * 
 */
unsigned int counter=0;
int main(void) {
    //OSCCON=0b01101100;//8 MHZ output frequency of oscilator(default so this line is not required)
     TRISC=0; //set portc as output port
     
    //enabling interruptions 
   // INTCONbits.TMR0IE=1;  //ENABLE TIMER0 INTERRUPTS
    //INTCONbits.GIE=1;  //global interrupt enabler
  //  INTCONbits.PEIE_GIEL=1;
   // INTCONbits.TMR0IF=0;    //overflow flag
    INTCON=11111000;

    
    //timer0 control
    T0CON=0b11000111;//enable timer0 as an 8 bit with 1:256 prescaler 
    TMR0=6;//COUNTS; WHEN THE COUNTER REACH 256 THE FLAG TMR0IF MUST BE CLEARED
    PORTC=0b00000000;
    while(1)
    {
        if(TMR0IF==1)//if overflow of TMR0 flag is active
        {
            
            counter++;
            TMR0IF=0;//reset overflow flag
            TMR0=6; //reset timer counter
                 if (counter==16)//IF COUNTING ACHIEVE 16*.032seconds per count=512 ms with a 1:256 prescaler
                    {
                     
                     PORTC=0b11110000;    //display byte at portc
                     
                    }
                    if (counter==32)//496 ms with a 1:256 prescaler
                    {
                     counter=0; //reset counter
                     PORTC=0b00001111;    //display byte at portc 
                    }
            
        }
    }
}

