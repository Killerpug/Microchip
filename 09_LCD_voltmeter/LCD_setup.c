
#include <pic18f25k80.h>
 #pragma config XINST = OFF // extended instruction set and indexeed mode disabled
#include <string.h>
#include <stdio.h>
#include <xc.h>     //identifies use and calls appropriate header files.
#pragma config SOSCSEL=0b10;// PINs RC0, RC1 function as general purpose (i/o) pins and not for clock
long int count;
char c; //Character to be printed to LCD

#define LCD_D4	PORTCbits.RC0
#define LCD_D5	PORTCbits.RC1
#define LCD_D6	PORTCbits.RC2
#define LCD_D7	PORTCbits.RC3
#define LCD_EN	PORTCbits.RC4
#define LCD_RS	PORTCbits.RC5



// Functions
void LCD_Init ( void );
void LCD_SetPosition ( unsigned int c );

void LCD_PutCmd ( unsigned int c );
void LCD_PulseEnable ( void );
void delay(void);
void upper (unsigned int c);

void lower(unsigned int c);
void LCD_PutChar ( unsigned int c );


int main(void) {
    
     LCD_Init();
     c=0x78;
     LCD_PutChar(c);
}
void LCD_Init(void) //Initialize display
{
PORTC = 0;
TRISC = 0x00;

delay ();	/* wait enough time after Vdd rise */
delay ();
delay ();
delay();

LCD_RS =0 ;
PORTC = 0x03;
LCD_PulseEnable();
delay ();

LCD_PulseEnable();
delay ();
LCD_PulseEnable();
PORTC =  0x02 ;	/* set 4-bit interface */
LCD_PulseEnable();

//LCD_Putcmd Envia 2 comandos por byte, debido a que son 4 bits de datos(d4-d7), la funcion upper& lower los separa y los envia al lcd, no rquiere RS pq es inicializacion
LCD_PutCmd ( 0x2C );	// function set (all lines, 5x7 characters). 
LCD_PutCmd ( 0x0C );	/* display ON, cursor off, no blink */
LCD_PutCmd ( 0x01 );	/* clear display */

LCD_PutCmd ( 0x06 );	/* entry mode set, increment & scroll left */
}

void LCD_SetPosition ( unsigned int c )

{
/* this subroutine works specifically for 4-bit Port A */
upper ( c | 0x08 );
 
LCD_PulseEnable();
lower ( c );
LCD_PulseEnable();

}



void LCD_PutCmd ( unsigned int c )
{
/* this subroutine works specifically for 4-bit Port A */
upper ( c );	/* send high nibble */

LCD_PulseEnable();
lower ( c );	/* send low nibble */
LCD_PulseEnable();
}

void LCD_PulseEnable ( void )
{
LCD_EN = 1;

delay();	// was 10
LCD_EN =0;
delay();	// was 5
}

void delay(void)
{
for(count = 1; count < 10000; count++);

}

void upper (unsigned int c)
{

if(c & 0x80) LCD_D7=1; else LCD_D7=0; //si C mascara con 80 =1, entonces el dato 7 es igual a 1 EX.-->c=  0b1001 0100
                                                                                                  //0x80= 0b1000 0000   &
                                                                                                 //      =0B1000 0000  
                                                                                //POR LO TANTO es verdadero pq true es cualquier numero =! de 0
if(c & 0x40) LCD_D6=1; else LCD_D6=0;
if(c & 0x20) LCD_D5=1; else LCD_D5=0;
if(c & 0x10) LCD_D4=1; else LCD_D4=0;
}

void lower(unsigned int c) //enuentra los 4 bits menos significativos del byte c
{
if(c & 0x08) LCD_D7=1; else LCD_D7=0;

if(c & 0x04) LCD_D6=1; else LCD_D6=0;
if(c & 0x02) LCD_D5=1; else LCD_D5=0;
if(c & 0x01) LCD_D4=1; else LCD_D4=0;
}

void LCD_PutChar ( unsigned int c )
{
/* this subroutine works specifically for 4-bit Port A */

LCD_RS =1;  //sending data mode, comienza comunicacion
upper ( c );	/* send high nibble */
LCD_PulseEnable(); //tiempo para pasar la parte alta del dato

lower ( c );	/* send low nibble */
LCD_PulseEnable();  //tiempo para la parte baja del dato
LCD_RS =0;      //termina la comunicacion

}
