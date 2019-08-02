/* 
 * File:   oscillation.c
 * Author: eduardo
 *In this project 8 leds are connected to port c of pic18f25k80 operated at a frequency of 8MHZ, 
 * the program flashes a random number at portc after an interrupt of.5 miliseconds 
 * NOTE: before entering to the 1:256 prescaler, the internal oscillator frequency is divided by 4 (Fosc/4) because each instruction takes 4 cycles
 * Created on 15 de julio de 2017, 11:51 AM
 */
#include <xc.h>     //identifies use and calls appropriate header files.
#include<pic18f25k80.h> 
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#pragma config XINST = OFF // extended instruction set and indexeed mode disabled
#pragma config SOSCSEL=0b10;// PINs RC0, RC1 function as general purpose (i/o) pins and not for clock

/*
 * 
 */

 //unsigned int counter=0;
   //unsigned int r_number;
             
void timer0_overflow(void){
   static unsigned int counter=0;// the counter can be declared as global variable just writing unsigned int
   //or as static inside a function, this happens in order to keep its value between invocations
   //as a variable in a function is just used during the actual invocation and does not keep its value between them
  static unsigned int r_number;//save value of random number
            counter++;
            TMR0IF=0;//reset overflow flag
            TMR0=6; //reset timer counter
                 if (counter==16)//IF COUNTING ACHIEVE 16*.032seconds per count=512 ms with a 1:256 prescaler
                    {
                     r_number=rand();//generate a random number
                     
                     PORTC=r_number;    //display random byte at portc
                     counter=0; //reset counter
                     
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
    PORTC=0b00000000;
    
    srand(10);//intialize random seed
        
         while(1)
            {
                  if(TMR0IF==1)//if overflow of TMR0 flag is active
                    {
                      timer0_overflow();//call flag overflow
                    }
            }
}
