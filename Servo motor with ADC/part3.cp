#line 1 "C:/Users/ZX/Desktop/Final 1323 George Zacharis/part3/part3.c"



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
unsigned char ch;
unsigned int adc_rd,adc_final;
void main()
{
 char keypressed;
 char text[6] ="00000";
 keypressed = read_keypad();
 TRISD = 0x00;
 TRISA = 0xFB;
 keypressed = keypressed - 0x30;
 PORTD = function_numbers(keypressed);
 switch (function_numbers(keypressed))
 {
 case 0x4F:

 Pwm_Init(500);


 Lcd8_Config(&PORTE, &PORTD, 2,1,0, 7,6,5,4,3,2,1,0);
 Lcd8_Cmd(LCD_CLEAR);
 Lcd8_Out(1, 1, "Servo Motor");
 Lcd8_Out(2, 1, "Speed :");


 while (1)
 { Pwm_Start();
 adc_rd = ADC_read(0);
 adc_final= adc_rd*0.25;
 wordToStr(adc_final, text);
 Lcd8_Out(2,8, text);
 Pwm_Change_Duty(adc_final);
 }
 }
}
