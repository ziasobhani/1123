#include <mega16.h>
#asm
   .equ __lcd_port=0x1B ;PORTA
#endasm
#include <lcd.h> 
#include<delay.h>
void display_no(int no); 
void direction(char dir);
void main(void)
{
PORTA=0x00;
DDRA=0x00;
PORTB=0x00;
DDRB=0x08;
PORTC=0x00;
DDRC=0x00;
PORTD=0x00;
DDRD=0xFF;
TCCR0=0x6A;
TCNT0=0x00;
OCR0=0x00;
MCUCR=0x00;
MCUCSR=0x00;
TIMSK=0x00;
ACSR=0x80;
SFIOR=0x00;
lcd_init(16);
PORTC=255;
direction(3); 
while (1)
      {    
      if (PINC.2==0 || PINC.3==0 || PINC.4==0 ) 
      {    
          delay_ms(10); 
          if (PINC.2==0) 
                  direction(1);
          if (PINC.3==0) 
                 direction(2);
          if (PINC.4==0) 
                 direction(3);
                 
       } 
       
      lcd_gotoxy(0,1);
      lcd_putsf("           ");
      lcd_gotoxy(0,1);
      lcd_putsf("OCR0: ");
      display_no(OCR0);
         
      if (PINC.0==0 || PINC.1==0 ) 
      {    
          delay_ms(10);
          
          if (PINC.0==0) 
          {     
              
              if (OCR0> 250)
                  OCR0=255; 
              else
                  OCR0=OCR0+5;
          }    
          else if (PINC.1==0) 
          {     
                   
                   if(OCR0<5)
                      OCR0=0;
                   else      
                      OCR0=OCR0-5;
          }         
       }
       else
       {
          
             
       }    
        
    }
} 
void direction(char dir)
{
   switch(dir)
   {
         case 1:
         PORTD.0=0;
         PORTD.1=1;
         lcd_clear();
         lcd_putsf("Direction: Left ");
         break;
         
         case 2:
         PORTD.0=1;
         PORTD.1=0; 
         lcd_clear();
         lcd_putsf("Direction: Right ");
         break;
         
         case 3:
         PORTD.0=0;
         PORTD.1=0;
         lcd_clear();
         lcd_putsf("Direction: Brake ");
         break;
   }
}
void display_no(int no)
{   
   int array[5];
   int i=0,j;
   /*if( no < 0)
   {
      lcd_putchar('-');
      no=-1*no;
   }
   else
      lcd_putchar('+');*/
    while(no > 9)
    {
       array[i++]= no % 10;
       no/=10;
    }
    array[i]=no;
    for(j=i;j >=0 ;j--)   
    {
       lcd_putchar(48+array[j]);
       delay_us(100);
    }
}