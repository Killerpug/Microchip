/* 
 * File:   oscillation.c
 * Author: eduardo
 *In this project an analog input AN0 recieve a voltage from 0 to 5 v and using a A/D converter
 * CONVERT THE VOLTAGE FROM ANALOG TO DIGITAL and diplay in one led if it is >3 (RC0)v or another(RC3) IF IS LESSER THAN 3 V
 * 
 * Created on 15 de julio de 2017, 11:51 AM
 * GODONE=1 ACTIVES THE AD CONVERSION
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

 //unsigned int counter=0; // count every overflow of timer

             
void timer0_overflow(void){
   static unsigned int counter=0;// the counter can be declared as global variable just writing unsigned int
   //or as static inside a function, this happens in order to keep its value between invocations
   //as a variable in a function is just used during the actual invocation and does not keep its value between them
            counter++;
            TMR0IF=0;//reset overflow flag
            TMR0=6; //reset timer counter
                 if (counter==16)//IF COUNTING ACHIEVE 16*.032seconds per count=512 ms with a 1:256 prescaler
                    {
                      ADON=1; //FUNCIONA COMO UN HABILITADOR DEL ADC
                     ADCON0bits.GODONE=1;//begin conversion. Estatus de conversion. Al colocarlo
                      // en 1 se inicia la conversion. El bit se coloca en 0 
                      // via hardware. 
                     
                    }
                             if ((ADIF == 1)&&(ADIE == 1)) // conversion HAS BEEN FINISHED,is ready to be used, and ad interrupt is enabled
                             {
                                     ADIF = 0; // Apagar la bandera del final de conversion. 
                                     if (ADRESH>3)// ADRESH IS USED BECAUSE IT TELLS THE digits at the left of the decimal point
                                                        //ADRESL WOULD TELL US MILIVOLTS
                                     {
                                         PORTCbits.RC0=0;//turn on led>3v
                                     }
                                     if(ADRESH<3)// ADRESH IS USED BECAUSE IT TELLS THE digits at the left of the decimal point
                                     {
                                         PORTCbits.RC3=0;//turn on led<3v
                                     }
                                                  
                     }
                    
                 if (counter==32)//IF COUNTING ACHIEVE 16*.032seconds per count=512 ms with a 1:256 prescaler
                    {//delay to see the led
                     
                     PORTCbits.RC0=1;//turn off leds
                     PORTCbits.RC3=1;
                     counter=0; //reset counter
                     
                    }
            
        


}


int main(void) {
    //A/D converter configuration
    ADCON1bits.CHSN=0B000;//NEGATIVE amplifier channel input reference is connected to vss so it works as a single input voltage measure (and not as differential)
    ADCON0bits.CHS=0b00000;// select AN0 as positive amplifier channel input reference
    ADCON0bits.GODONE=0; // conversion not initiated  (flag)
    ADCON1bits.VCFG=0b00; //+voltage reference = AVdd
    ADCON1bits.VNCFG=0; //-voltage  reference= AVss 
    ADCON2bits.ADFM=1; //right justify so 4 bits of ADRESH are not used xxxx1111 11111111
    ADCON2bits.ACQT=0b101; //12 TAD (time per bit)
     ADCON2bits.ADCS=0b100;//
    ANCON0bits.ANSEL0=1; //AN0 is configure as an analog channel
    
    //interruptions ADC
    PIE1bits.ADIE = 1; // Bit 6 de PIE1: Habilitador de la interrupcion del ADC.
              // Configurado a habilitar las interrupciones del ADC
    IPR1bits.ADIP = 1; // Bit 6 de IPR1: Prioridad de interrupcion del ADC. 
              // Configurado a alta prioridad.
    PIR1bits.ADIF = 0; // conversion has ended
    RCONbits.IPEN=1; //Habilitador de prioridad en interrupciones.
    
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
