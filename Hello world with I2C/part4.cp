#line 1 "C:/Users/Zx/Desktop/part4/part4.c"







void main(){
 char *text1,*text2,*text3, *data[3];
 int i;
 INTCON=0;
 TRISE =0;
 TRISD =0;
 TRISB =0;
 Soft_I2C_Config(&PORTC, 4, 3);

 TRISB =0x00;
 PORTB =0x00;

 Soft_I2C_Start();
 Soft_I2C_Write(0xA2);
 Soft_I2C_Write(3);

 Soft_I2C_Write("Hello");
 Soft_I2C_Write("World");
 Soft_I2C_Write("Test");
 Soft_I2C_Stop();

 Soft_I2C_Start();
 Soft_I2C_Write(0xA2);
 Soft_I2C_Write(3);
 Soft_I2C_Start();
 Soft_I2C_Stop();
 data[0] = Soft_I2C_Read(1);
 data[1] = Soft_I2C_Read(1);
 data[2] = Soft_I2C_Read(1);
 data[3] = Soft_I2C_Read(0);
 Soft_I2C_Stop();

 Usart_Init(9600);
 text1 =data[0];
 for (i=0;i<strlen(data[0]);i++)
 {
 Usart_Write(text1[i]);
 }
 Usart_Write(' ');
 text2 =data[1];
 for (i=0;i<strlen(data[1]);i++)
 {
 Usart_Write(text2[i]);
 }
 text3 =data[2];
 for (i=0;i<strlen(data[2]);i++)
 {
 Usart_Write(text3[i]);
 }
}
