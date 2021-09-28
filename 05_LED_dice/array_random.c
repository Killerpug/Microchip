/* 
 * File:   array_random.c
 * Author: eduardo
 *This program display in a dice alike led structure a given random number when 
 * a signal comming from a button is high
 * Created on 17 de julio de 2017, 09:51 PM
 */

#include <xc.h>     //identifies use and calls appropriate header files.
#include <stdlib.h>
#include <stdio.h>
#pragma config SOSCSEL=0b10;// PINs RC0, RC1 function as general purpose (i/o) pins and not for clock
#define _XTAL_FREQ 800000
/*
 * 
 */
unsigned int dice_array[6]={0xF7,0XBE,0xB6,0XAA,0XA2,0X88};
unsigned char random6=0;
int main() {
    TRISC=0B10000000; //DEFINE RC7 as input button pin and rc0-rc6 as output dice leds
    while(1)
    {
        random6++;
        if(random6==5)//as the program runs too fast it could be seen as if it generates a random number instead of count
        {
            random6=0;
        }
        if(RC7==1)//IF BUTTON PRESS, generate a random number and display
        {
            PORTC=dice_array[random6];//display corresponding value of dice according to random number generated
             __delay_ms(3000);
        }
        
    
    }

}

