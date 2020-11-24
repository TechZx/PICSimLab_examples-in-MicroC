
//Author : TechZx
//Device : PIC18F452
//Clock : 8
//About : Moving Servo motor using potentiometer  (Servo pin1=RC2)
//More info about macros in micro c website

 char  read_keypad(){
   char var, key;
   PORTD = 0xFF;
   TRISD = 0xFF;    //configure PORT D as inpout
   TRISB = 0x00;     //configure PORT B as outpout
   PORTB = 0xFF;     //set all pins of PORT B to 1;
   key =0;
    do {                       //1-5 buttons
           // first scan
           PORTB.F0 = 0;
           delay_ms(10);
           var = PORTD;

           if (var.F2 == 0) key = '4';
           else if (var.F3 == 0) key = '1';
           PORTB.F0 =1;

           //  second scan
           PORTB.F1 = 0;
           delay_ms(10);
           var = PORTD;

           if (var.F2 == 0)key = '5';
           else if (var.F3 == 0)key = '2';
           PORTB.F1 =1;

           // third scan
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
void main(){
  char keypressed;
  char text[6] ="00000";
  keypressed = read_keypad();//Reading a key from the keypad
  TRISD = 0x00;  //Define PORTD to operate as outpout
  TRISA = 0xFB;  // Define PORTA pin 2 as output.
  keypressed = keypressed - 0x30;
  PORTD = function_numbers(keypressed);//Write the appropriate combination of bits to PORTD
  switch (function_numbers(keypressed)){
        case 0x4F:
        Pwm_Init(500);
        //configuring lcd
       //then printing the data on LCD
        Lcd8_Config(&PORTE, &PORTD, 2,1,0, 7,6,5,4,3,2,1,0);
        Lcd8_Cmd(LCD_CLEAR);     // Clear screen
        Lcd8_Out(1, 1, "Servo Motor"); // Print text on LCD
        Lcd8_Out(2, 1, "Speed :"); // Print text on LCD
        // using ADC
        while (1){
            Pwm_Start();
            adc_rd  = ADC_read(0);       // get ADC value from first channel
            adc_final= adc_rd*0.25;     //convert adc values to [0-255] (optional)
            wordToStr(adc_final, text);
            Lcd8_Out(2,8, text);
            Pwm_Change_Duty(adc_final);// adjusting the speed of the servo motor depending on the ADC values
        }
      }
}