/* 
 * File:   oscillation.c
 * Author: eduardo
 *In this project a counter from (1 to 9) will be made by using a common anode 7 segment display (5161BS)
 * the table of hex values that correspond to the dec_numbers has to be created to display the correct number.
 * 
 * NOTE: before entering to the 1:256 prescaler, the internal oscillator frequency is divided by 4 (Fosc/4) because each instruction takes 4 cycles
 * Created on 15 de julio de 2017, 11:51 AM
 */
#include <xc.h>     //identifies use and calls appropriate header files.
#include<pic18f25k80.h> 
#include <stdlib.h>
#include <stdio.h>
#pragma config XINST = OFF // extended instruction set and indexeed mode disabled
#pragma config SOSCSEL=0b10;// PINs RC0, RC1 function as general purpose (i/o) pins and not for clock

/*
 * 
 */

 //unsigned int counter=0; // to delay a certain ammount of time
unsigned int count09=0;//count from0 to 9 for hex values
unsigned int counter_hexvalues[9]={0x4F,0X12,0x06,0X4C,0X24,0X20,0X0F,0X00,0X0C};   //HEX VALUES that correspond to number for 7 segment display (1,2,3....)          
void timer0_overflow(void){
   static unsigned int counter=0;// the counter can be declared as global variable just writing unsigned int
   //or as static inside a function, this happens in order to keep its value between invocations
   //as a variable in a function is just used during the actual invocation and does not keep its value between them
            counter++;
            TMR0IF=0;//reset overflow flag
            TMR0=6; //reset timer counter
                 if (counter==16)//IF COUNTING ACHIEVE 16*.032seconds per count=512 ms with a 1:256 prescaler
                    {
                     
                        PORTC=counter_hexvalues[count09];    //display random byte at portc
                        count09++;
                                if(count09==9)//if counter =9, reset
                                {
                                    count09=0;//reset count
                                }
                    }
                    
            if (counter==32) 
            {
                counter=0;//reset counter
            }
        


}


int main(void) {
    //OSCCON=0b01101100;//8 MHZ output frequency of oscilator(default so this line is not required)
     TRISC=0; //set portc as output port
     
    //enabling interruptions 
  // TMR0IE=1;  //ENABLE TIMER0 INTERRUPTS
     //GIEH=1;  //global interrupt enabler
    // TMR0IF=0;    //overflow flag
    INTCON=11111000;

    
    //timer0 control
    T0CON=0b11000111;//enable timer0 as an 8 bit with 1:256 prescaler 
    TMR0=6;//COUNTS; WHEN THE COUNTER REACH 256 THE FLAG TMR0IF MUST BE CLEARED
    
    
        
         while(1)
            {
                  if(TMR0IF==1)//if overflow of TMR0 flag is active
                    {
                      timer0_overflow();//call flag overflow
                    }
            }
}
