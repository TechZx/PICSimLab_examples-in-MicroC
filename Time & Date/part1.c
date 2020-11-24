
//Author : TechZx
//Device : PIC18F452
//Clock : 8
//About : If 1 is pressed print Date and time in LCD
//More info about macros in micro c website


char *mem_data[10];
char *mem2_data[10];
char *mem3_data [10]  ;
char minutes[2];
char hours[2];
char temph;        //temp hours
char tempm;        //temp minutes
char day[2];
char month[2];
char year[4];
char tempDay;
char tempMonth;
char tempYear;

char  read_keypad()
{
   char var, key;

   PORTD = 0xFF;
   TRISD = 0xFF;    //configure PORT D as inpout

   TRISB = 0x00;     //configure PORT B as outpout
   PORTB = 0xFF;     //set all pins of PORT B to 1;

   key =0;
     do {                       //1-5 buttons (optional)
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


void main(){
     char keypressed;
     int i=0;
    //Reading a key from the keypad
     keypressed = read_keypad();
     TRISD = 0x00;  //Define PORTD to operate as outpout
     TRISA = 0xFB;  // Define PORTA pin 2 as output.
     // convert ASCII code to binary number
     keypressed = keypressed - 0x30;
     PORTD = function_numbers(keypressed); //Write the appropriate combination of bits to PORTD
     switch (function_numbers(keypressed))
     {
        case 0x06:

            TRISE = 0x00; // PORTE is output
            TRISD = 0x00; // PORTD is output
            I2C_Init(100000);
          //the same way is used to read all the data
          //also the same way to write the data and save it
          
          
             //read minutes
             Soft_I2C_Config(&PORTC, 4, 3); //Use Port C pins 4 and 3
             Soft_I2C_Start(); // Issue I2C start signal
             Soft_I2C_Write(0xD0); // Send byte (device address + W)
             Soft_I2C_Write(1); // Send byte (Location of minutes register) ***
             Soft_I2C_Start(); // Issue I2C start signal
             Soft_I2C_Write(0xD1); // Send byte (device address + R)
             tempm = Soft_I2C_Read(0); // Read data (NO ACK)
             Soft_I2C_Stop();
             minutes[0]=((tempm & 0x70)>>4)+0x30;
             minutes[1]= (tempm & 0x0F) +0x30;

             //read hour
             Soft_I2C_Config(&PORTC, 4, 3);
             Soft_I2C_Start();
             Soft_I2C_Write(0xD0);
             Soft_I2C_Write(2); // Send byte (Location of hours register) ***
             Soft_I2C_Start();
             Soft_I2C_Write(0xD1);
             temph = Soft_I2C_Read(0);
             Soft_I2C_Stop();
             hours[0]=((temph & 0x30)>>4)+0x30;
             hours[1]= (temph & 0x0F) +0x30;

             //save time
             Soft_I2C_Config(&PORTC, 4, 3); //Use PortC pins 4 and 3
             Soft_I2C_Start(); // Issue I2C start signal
             Soft_I2C_Write(0xA2); // Send byte via I2C (Address of 24cO2)
             Soft_I2C_Write(2); // Send byte (address of EEPROM location)
             Soft_I2C_Write(hours); // Send data (data to be written)
             Soft_I2C_Write(minutes); // Send data (data to be written)
             Soft_I2C_Stop();

             Soft_I2C_Start(); // Issue I2C start signal
             Soft_I2C_Write(0xA2); // Send byte (device address + W)
             Soft_I2C_Write(2); // Send byte (EEPROM location to read from)
             Soft_I2C_Start(); // Issue I2C start signal
             Soft_I2C_Write(0xA3); // Send byte (device address + R)
             mem_data[0] = Soft_I2C_Read(1); // Read data (send ACK)
             mem_data[1] = Soft_I2C_Read(1); // Read data (send ACK)

             //read day
             Soft_I2C_Config(&PORTC, 4, 3);
             Soft_I2C_Start();
             Soft_I2C_Write(0xD0);
             Soft_I2C_Write(4); )
             Soft_I2C_Start();
             Soft_I2C_Write(0xD1); )
             tempDay = Soft_I2C_Read(0); // Read data (NO ACK)
             Soft_I2C_Stop();
             day[0]=((tempDay & 0x70)>>4)+0x30;
             day[1]= (tempDay & 0x0F) +0x30;

             // read month
             Soft_I2C_Config(&PORTC, 4, 3);
             Soft_I2C_Start(); l
             Soft_I2C_Write(0xD0);
             Soft_I2C_Write(5); // Send byte (Location of month register) **
             Soft_I2C_Start();
             Soft_I2C_Write(0xD1);
             tempMonth = Soft_I2C_Read(0); // Read data (NO ACK)
             Soft_I2C_Stop();
             month[0]=((tempMonth & 0x30)>>4)+0x30;
             month[1]= (tempMonth & 0x0F) +0x30;

             //read year
             Soft_I2C_Config(&PORTC, 4, 3);
             Soft_I2C_Start();
             Soft_I2C_Write(0xD0);
             Soft_I2C_Write(6);
             Soft_I2C_Start();
             Soft_I2C_Write(0xD1);
             tempYear = Soft_I2C_Read(0);
             Soft_I2C_Stop();
             year[0]=((tempYear & 0x70)>>4)+0x30;
             year[1]= (tempYear & 0x0F) +0x30;

            //save date
             Soft_I2C_Config(&PORTC, 4, 3);
             Soft_I2C_Start();
             Soft_I2C_Write(0xA2); // Send byte via I2C (Address of 24cO2)
             Soft_I2C_Write(2); // Send byte (address of EEPROM location) **
             Soft_I2C_Write(day); // Send data (data to be written)
             Soft_I2C_Write(month); // Send data (data to be written)
             Soft_I2C_Write(year); // Send data (data to be written)

             Soft_I2C_Stop();
             Soft_I2C_Start();
             Soft_I2C_Write(0xA2);
             Soft_I2C_Write(2); )
             Soft_I2C_Start();
             Soft_I2C_Write(0xA3); // Send byte (device address + R)
             mem2_data[0] = Soft_I2C_Read(1); // Read data (send ACK)
             mem2_data[1] = Soft_I2C_Read(1); // Read data (send ACK)
             mem2_data[2] = Soft_I2C_Read(1); // Read data (send ACK)

              //printing the data in lcd
              Lcd8_Config(&PORTE, &PORTD, 2,1,0, 7,6,5,4,3,2,1,0);
              Lcd8_Cmd(LCD_CURSOR_OFF); // Turn on blinking cursor
              Lcd8_Cmd(LCD_CLEAR);     // Clear screen
              Lcd8_Out(1, 1,"Time=");
              Lcd8_Out(1, 6,mem_data[0]);
              Lcd8_Out(1, 8,":") ;
              Lcd8_Out(1, 9,mem_data[1]); // Print time on LCD
              Lcd8_Out(1, 11," ") ;  // due to some trash values shown on lcd
              Lcd8_Out(1, 12," ") ;  // Optional just in case there are buggs in the version
              Lcd8_Out(1, 13," ") ;
              Lcd8_Out(1, 14," ") ;
              Lcd8_Out(1, 15," ") ;
              Lcd8_Out(1, 16," ") ;
              Lcd8_Out(2, 1,"Date=");
              Lcd8_Out(2, 6,mem2_data[0]);
              Lcd8_Out(2, 8,"/") ;
              Lcd8_Out(2, 9,mem2_data[1]); // Print month on LCD
              Lcd8_Out(2, 11,"/") ;
              Lcd8_Out(2, 12,mem2_data[2]); // Print year on LCD
              Lcd8_Out(2, 14,mem2_data[2]); // Print year on LCD
      }
}