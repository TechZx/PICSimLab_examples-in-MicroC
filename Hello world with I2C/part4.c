//Author : TechZx
//Device : PIC18F452
//Clock : 8
//About : Printing Hello with I2C
//More info about macros in micro c website


void main(){
    char *text1,*text2,*text3, *data[3];
    int i;
    INTCON=0;
    TRISE =0;
    TRISD =0;
    TRISB =0;
    Soft_I2C_Config(&PORTC, 4, 3); //Use PortC pins 4 and 3

    TRISB =0x00;
    PORTB =0x00;

    Soft_I2C_Start(); // Issue I2C start signal
    Soft_I2C_Write(0xA2); // Send byte via I2C (Address of 24cO2)
    Soft_I2C_Write(3); // Send byte (address of EEPROM location)

    Soft_I2C_Write("Hello");
    Soft_I2C_Write("World");
    Soft_I2C_Write("Test");
    Soft_I2C_Stop();

    Soft_I2C_Start(); // Issue I2C start signal
    Soft_I2C_Write(0xA2); // Send byte (device address + W)
    Soft_I2C_Write(3); // Send byte (EEPROM location to read from)
    Soft_I2C_Start(); // Issue I2C start signal
    Soft_I2C_Stop();
    data[0] = Soft_I2C_Read(1); // Read data (send ACK)
    data[1] = Soft_I2C_Read(1); // Read data (send ACK)
    data[2] = Soft_I2C_Read(1); // Read data (send ACK)
    data[3] = Soft_I2C_Read(0); // Read data (NO ACK)
    Soft_I2C_Stop();

    Usart_Init(9600);
    text1 =data[0];
    for (i=0;i<strlen(data[0]);i++)
        {
        Usart_Write(text1[i]);    // Sending data via USART
        }
    Usart_Write(' ');
    text2 =data[1];
    for (i=0;i<strlen(data[1]);i++)
        {
          Usart_Write(text2[i]);    // Sending data via USART
        }
    text3 =data[2];
    for (i=0;i<strlen(data[2]);i++)
        {
          Usart_Write(text3[i]);    // Sending data via USART
        }
}