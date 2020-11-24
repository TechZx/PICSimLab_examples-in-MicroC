#line 1 "C:/Users/ZX/Desktop/Final 1323 George Zacharis/part5/part5.c"



void interrupt()
{
 if(PORTC.F2 ==0)
 PORTC.F2 =1;
 INTCON = 0b11010000;
}
 void interrupt_low()
 {
 if(PORTC.F0 ==0)
 {
 PORTC.F0 =1;
 INTCON3 = 0b00010000; }
 else {

 PORTC.F1=0;

 INTCON3 = 0b00011000; }
}
 char read_keypad()
{
 char var, key;
 PORTD = 0xFF;
 TRISD = 0xFF;
 TRISB = 0x00;
 PORTB = 0xFF;
 key =0;
 do {

 PORTB.F0 = 0;
 delay_ms(10);
 var = PORTD;

 if (var.F2 == 0) key = '4';
 else if (var.F3 == 0) key = '1';
 PORTB.F0 =1;


 PORTB.F1 = 0;
 delay_ms(10);
 var = PORTD;

 if (var.F2 == 0)key = '5';
 else if (var.F3 == 0)key = '2';
 PORTB.F1 =1;


 PORTB.F2 =0;
 delay_ms(10);
 var = PORTD;

 if (var.F3 == 0) key = '3';
 PORTB.F2 =1;

 }while (key == 0);

 return key;
}

unsigned char function_numbers(unsigned char v)
{
 switch(v)
 {
 case 1:
 return 0x06;
 case 2:
 return 0x5B;
 case 3:
 return 0x4F;
 case 4:
 return 0x66;
 case 5:
 return 0x6D;
 }
 return 0;
}
int i;
void main()
{

 char keypressed;
 char *text;
 keypressed = read_keypad();
 TRISD = 0x00;
 TRISA = 0xFB;
 keypressed = keypressed - 0x30;
 PORTD = function_numbers(keypressed);
 switch (function_numbers(keypressed))
 {
 case 0x6D:

 TRISC = 0x00;
 TRISB = 0xFF;
 PORTC.F1 =1;
 PORTC.F2 =0;
 INTCON = 0b11010000;
 INTCON3 = 0b00011000;

 RCON =0x80;
 Lcd8_Config(&PORTE, &PORTD, 2,1,0, 7,6,5,4,3,2,1,0);
 Lcd8_Cmd(LCD_CURSOR_OFF);
 Lcd8_Cmd(LCD_CLEAR);

 Lcd8_Out(1, 1, "STEPPER MOTOR ON");
 while (1)
 {

 text ="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
 for (i=0;i<24;i++)
 Lcd8_Chr(2,8, text[i]);
 delay_ms(2);
 }
 }
}
