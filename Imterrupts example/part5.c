
//Author : TechZx
//Device : PIC18F452
//Clock : 8
//About : Example of how interrupts are used while other things are done in paralell by microprossesor
//More info about macros in micro c website
void interrupt(){      //settting an inetrupt high priority for the ventilator{
      if(PORTC.F2 ==0)
      PORTC.F2 =1;          //turn on ventilator
      INTCON =  0b11010000;
}
 void interrupt_low(){            // setting a low priority interupt for relay and buzzer
   if(PORTC.F0 ==0)
   {
      PORTC.F0 =1;
      INTCON3 = 0b00010000; }      //turn on  relay
      else  {
      //PORTC.F0 =1;
      PORTC.F1=0;

      INTCON3 = 0b00011000;  }          //turn on buzzer
}
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

unsigned char function_numbers(unsigned char v){
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
void main(){
  char keypressed;
  char *text;
  keypressed = read_keypad();  //Reading a key from the keypad
  TRISD = 0x00;  //Define PORTD to operate as outpout
  TRISA = 0xFB;  // Define PORTA pin 2 as output.
  keypressed = keypressed - 0x30;
  PORTD = function_numbers(keypressed); //Write the appropriate combination of bits to PORTD
  switch (function_numbers(keypressed))
     {
      case 0x6D:
      
        TRISC = 0x00;
        TRISB = 0xFF;
        PORTC.F1 =1;        // sometimes due to bugs of micro c the buzzer needs to be turned off on the begining of void main()
        PORTC.F2 =0;
        INTCON =  0b11010000;
        INTCON3 = 0b00011000;
        RCON =0x80;
        Lcd8_Config(&PORTE, &PORTD, 2,1,0, 7,6,5,4,3,2,1,0);
        Lcd8_Cmd(LCD_CURSOR_OFF); // Turn off blinking cursor
        Lcd8_Cmd(LCD_CLEAR);     // Clear screen
        Lcd8_Out(1, 1, "STEPPER MOTOR ON"); // Printing text on LCD in first line
         while (1)
         {
          text ="ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // printing A-Z with some delay so we see that this is not inerrupted by inerrupts
                 for (i=0;i<26;i++)
                     Lcd8_Chr(2,8, text[i]);
                     delay_ms(2);
         }
  }
}