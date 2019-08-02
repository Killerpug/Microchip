/* 
 * File:   oscillation.c
 * Author: eduardo
 *In this project a counter from (1 to 9) will be made by using a common anode 7 segment display (5161BS)
 * the table of hex values that correspond to the dec_numbers has to be created to display the correct number.
 * TIMER1 HAS BEEN MODIFY TO USE THE INTERNAL OSCILLATOR BLOCK
 
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
unsigned int counter_hexvalues[9]={0x4F,0X12,0x06,0X4C,0X24,0X20,0X0F,0X00,0X0C};   //HEX VALUES that correspond to binary numbers for 7 segment to display DEC (1,2,3....9)
void timer1_overflow(void){
   static unsigned int counter=0;// the counter can be declared as global variable just writing unsigned int
   //or as static inside a function, this happens in order to keep its value between invocations
   //as a variable in a function is just used during the actual invocation and does not keep its value between them
            counter++;
            TMR0IF=0;//reset overflow flag
            TMR0=0; //reset timer counter
                 if (counter==6000)//I
                    {
                     
                        PORTC=counter_hexvalues[count09];    //display numberat portc
                        PORTBbits.RB0=0;
                        count09++;// increment nex number
                                if(count09==9)//if counter =9 (maximum value for display in 7 segment), go back to 1
                                {
                                    count09=0;//reset count
                                }
                    }
                    
            if (counter==12000) //12000 counts is about 1 second
            {
                counter=0;//reset counter
                PORTBbits.RB0=1;
            }
        


}


int main(void) {
    
    //3.6 internal oscillator block
    OSCCONbits.SCS=0b10; //system block select bits> internal oscillator block selected
    OSCTUNEbits.INTSRC=1;//hf derived freq device clock
    OSCCON2bits.MFIOSEL=0; //MF oscilattor is not used 
    OSCCONbits.IRCF=0b011;//HF-INTOSC/2=1 MHZ output frequency oscilator,
    
    
     TRISC=0; //set portc as output port
     TRISB=0; //set portB as output port
    //enabling interruptions 
  // TMR0IE=1;  //ENABLE TIMER0 INTERRUPTS
     //GIEH=1;  //global interrupt enabler
    // TMR0IF=0;    //overflow flag
    INTCON=11111000;

    
    
    //timer0 control
    T1CON=0b01111111;// clock source system clock, 1:8 prescaler
    
    TMR1=0;//PIR: COUNTS; WHEN THE COUNTER REACH 256 THE FLAG TMR0IF MUST BE CLEARED
    
    
        
         while(1)
            {
                  if(PIR1bits.TMR1IF)//if overflow of TMR0 flag is active
                    {
                      timer1_overflow();//call flag overflow
                    }
            }
}
