unsigned int Dcntr, yaxis , xaxis ,time ,x;
float distance;
 void mymsDelay(unsigned int k){//Dealy
 Dcntr=0;
 while(Dcntr<k)
 k--;

}
unsigned char K;
unsigned int j;
void mdelay()
{
for(K=0;K<200;K++)
for(j=0;j<300;j++)
K=K;
j=j;

}
  unsigned int ADC_read1(){//Analog to digital
 ADCON0 = ADCON0 | 0x04;
 while(ADCON0&0x04);
 return (ADRESH<<8)| ADRESL;


}

 unsigned int ADC_read2(){ //Analog to digital
 ADCON0 = ADCON0 | 0x0C;
 while(ADCON0&0x04);
 return (ADRESH<<8)| ADRESL;


}
void ADC()
{
    ADCON0 = 0X45;
    ADCON1 = 0XC2;
    TRISA = 0X03;
}

void interrupt(void){

  PORTC= 0X02;
  PORTD= 0X80;
  mdelay();
  xaxis = ADC_read2();  //reading x-axis
  while (xaxis <= 530 && xaxis >= 490){
     xaxis = ADC_read2();
  }
   PORTC= 0X00;
   PORTD= 0X00;

 ////////////////////////////////////////// xaxis right
  if( (xaxis > 530 )  )
{
PORTD= 0X80;
mdelay();
PORTD= 0X00;
mdelay();
PORTD= 0X80;
mdelay();
PORTD= 0X00;
mdelay();
PORTD= 0X80;


 PORTB =  0X10;
  mdelay();

 PORTB =  0X00;
 mdelay();


}


////////////////////////////////////////// xaxis left
else if((xaxis < 490)  )
{
//PORTD= 0X80;
PORTC= 0X02;
mdelay();
PORTD= 0X00;
mdelay();
PORTC= 0X02;
mdelay();
  PORTC= 0X00;
mdelay();
PORTC= 0X02;

  PORTB =  0X04;
  mdelay();
 PORTB =  0X00;
 mdelay();


}
     PORTC= 0X00;
   PORTD= 0X00;
 INTCON = INTCON & 0xFC;
}

void main ()
{
ADC();
TRISB = 0X01;
PORTB =0x00;

TRISC = 0X01;
PORTC = 0x00;
TRISD = 0X04;  // 0000 0100
PORTD = 0X01;
INTCON = 0x90;
OPTION_REG= OPTION_REG & 0XBF;
T1CON = 0x10;
while (1)
{



////////////////////////////////// yaxis Top  .
yaxis = ADC_read1();//read y-axis
 if((yaxis > 530) && (yaxis < 730)) //level 1(slowest)
{
 PORTB =  0X0A;      ///  rb1 = 1 , rb2 = 0 go forward      0000 1010
 mymsDelay(50);
 PORTB =  0X00;
 mymsDelay(200);


}

else if((yaxis >= 730) && (yaxis < 980) ) //level 2(medium speed)
{
 PORTB =  0X0A;      ///  rb1 = 1 , rb2 = 0 go forward      0000 1010
  mymsDelay(125);
 PORTB =  0X00;
 mymsDelay(125);


}
  else if((yaxis >= 980))    // level 3(fastest speed)
{
 PORTB =  0X0A;      ///  rb1 = 1 , rb2 = 0 go forward      0000 1010
  mymsDelay(200);
 PORTB =  0X00;
 mymsDelay(50);


}

////////////////////////////////////////// yaxis bottom
else if( (yaxis < 490) && ( yaxis  >= 200)) // level 1(slowest speed)
{
 PORTB =  0X14;    ///// rb1 = 0 , rb2 = 1 , rb3=0 ,rb4=1 M1 & M2 go backward ;;;; 0001 0100
 mymsDelay(50);
 PORTB =  0X00;
 mymsDelay(200);


}
else if((yaxis < 200) && ( yaxis  >= 50))  ////level 2(medium speed)
{
PORTB =  0X14;    ///// rb1 = 0 , rb2 = 1 , rb3=0 ,rb4=1 M1 & M2 go backward ;;;; 0001 0100
 mymsDelay(125);
 PORTB =  0X00;
 mymsDelay(125);


}


else if((yaxis < 50)  )  //level 3(fastest speed)
{
  PORTB =  0X14;    ///// rb1 = 0 , rb2 = 1 , rb3=0 ,rb4=1 M1 & M2 go backward ;;;; 0001 0100
   mymsDelay(200);
 PORTB =  0X00;
 mymsDelay(50);

}
else
{
PORTB=0X00;
PORTC=0X00;
PORTD=0X00;

}
TMR1H = 0;
TMR1L = 0;
PORTD = PORTD | 0X02;
mymsDelay(10);
PORTD = PORTD & 0XFD; //1111 1101

x=0;

if(!(PORTD & 0X04)){
T1CON = T1CON | 0X01;  /* enable the Timer1 */

  mymsDelay(10);
   while(PORTD& 0X04){
   x=1;}  /* wait till echo to go low */
     T1CON = T1CON & 0XFE; /*disable timer1 */
}


if(x == 0)
{
} else {

time= 343*(TMR1L | (TMR1H<<8))/2; //convert duration into distance
distance = (float)time * 0.0343 / 20.0;

  if(distance > 0 && distance < 0.2){
    INTCON = INTCON | 0x92;

     }}
}
}