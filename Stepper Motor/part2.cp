#line 1 "C:/Users/ZX/Desktop/Final 1323 George Zacharis/part2/part2.c"



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


void main()
{
 char keypressed;
 int i=0;

 keypressed = read_keypad();
 TRISD = 0x00;
 TRISA = 0xFB;


 keypressed = keypressed - 0x30;
 PORTD = function_numbers(keypressed);


 switch (function_numbers(keypressed) )
 {
 case 0x5B :
 TRISB.F4 =0x00;
 TRISB.F5 =0x00;
 TRISB.F6 =0x00;
 TRISB.F7 =0x00;
 PORTB=0x00;

 while(1)
 {
 PORTB.F4 =0;
 PORTB.F5 =1;
 PORTB.F6 =0;
 PORTB.F7 =1;
 delay_ms(3);

 PORTB.F4 =1;
 PORTB.F5 =0;
 PORTB.F6 =0;
 PORTB.F7 =1;
 delay_ms(3);

 PORTB.F4 =1;
 PORTB.F5 =0;
 PORTB.F6 =1;
 PORTB.F7 =0;
 delay_ms(3);

 PORTB.F4 =0;
 PORTB.F5 =1;
 PORTB.F6 =1;
 PORTB.F7 =0;
 delay_ms(3);
 }
 }
}
