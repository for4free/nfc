/******************************************************************************
--------------------------------RFID课程设计-----------------------------------
----------------------ARDUINO UNO/RC522/LCD1602--------------------------------
------------------------ID卡签到系统测试程序-----------------------------------
----------------1.开发环境:Arduino IDE-----------------------------------------
----------------2.测试使用开发板型号：Arduino UNO 加强版-----------------------
******************************************************************************/
#include "RC522.h"
#include <SPI.h>
#include <LiquidCrystal.h>   //液晶显示相关头文件

#define Relay 2
#define Buzzer 8  //定义蜂鸣器输出引脚为8号

LiquidCrystal lcd(7,6,5,4,3,2);      //构造一个LiquidCrystal的类成员。使用数字IO ，12/7,11/6,5,4,3,2

//4 bytes Serial number of card, the 5 bytes is verfiy bytes
unsigned char serNum[5];  //存储卡片ID

void setup() 
{ 
    Serial.begin(9600); 
   // Serial.print("TEST\n");
   while (!Serial) {;} //当没有打开串口时循环在此
    pinMode(Relay,OUTPUT);
    SPI.begin();   
    pinMode(chipSelectPin,OUTPUT); // Set digital pin 10 as OUTPUT to connect it to the RFID /ENABLE pin 
    digitalWrite(chipSelectPin, LOW); // Activate the RFID reader
    pinMode(NRSTPD,OUTPUT); // Set digital Reset , Not Reset and Power-down
    MFRC522_Init();						//初始化RFID
  
   lcd.begin(16,2);    //初始化LCD1602
   lcd.print("Welcome to use !");   //液晶显示Welcome to use！
   delay(1000);        //延时1000ms
   lcd.clear();        //液晶清屏
   
   pinMode(Buzzer,OUTPUT);  //蜂鸣器引脚设定为输出
   digitalWrite(Buzzer,LOW);      //蜂鸣器初始化为低电平
} 


void loop()
{
    unsigned char status;
    int col = 0;
    unsigned char str[MAX_LEN];
   // String comdata = "";

    // 寻卡，返回卡的ID
    status = MFRC522_Request(PICC_REQIDL, str); 
    if (status == MI_OK)			//读取到ID卡时候
    {   
		status = MFRC522_Anticoll(str); 
		// str[0..3]: serial number of the card
		// str[4]: XOR checksum of the SN.
			memcpy(serNum, str, 5);
			//Serial.print("ID:");  //输出'ID
      ShowCardID(serNum);
      delay(200);  
      col = Serial.read();  //接收串口数据 
  /*/  while (Serial.available() > 0)  
    {
        col += char(Serial.read());
        delay(2);
    }
 /*/ 
   //  Serial.print("Read: "); 
   //  Serial.println(col);
    if(col == 49)
    {
			// Check people associated with card ID
		   unsigned char* id = serNum;
      lcd.setCursor(0,1);       //设置液晶开始显示的指针位置
      lcd.print("Successful!!"); //液晶显示
      lcd.setCursor(0,0);       //设置液晶开始显示的指针位置
      lcd.print("ID:"); //液晶显示“The ID is ：”

         for(int ii=0; ii<=3; ii++)   //循环输出至屏幕 4个数组
        {
           lcd.setCursor(2*(ii+1)+1,0);       //设置液晶开始显示的指针位置
          if(id[ii]==0x00)             //代码有点冗余
               lcd.print("00");    
           if(id[ii]==0x01)
               lcd.print("01");
           if(id[ii]==0x02)
               lcd.print("02");
           if(id[ii]==0x03)
               lcd.print("03");
           if(id[ii]==0x04)
               lcd.print("04");
           if(id[ii]==0x05)
               lcd.print("05");
           if(id[ii]==0x06)
               lcd.print("06");
           if(id[ii]==0x07)
               lcd.print("07");
           if(id[ii]==0x08)
               lcd.print("08");
           if(id[ii]==0x09)
               lcd.print("09");
           if(id[ii]>0x09)
               lcd.print(id[ii],HEX);  //液晶显示ID   
          }  
      digitalWrite(Buzzer,HIGH);    //设置输出高电平 蜂鸣器
      delay(200);   
      digitalWrite(Buzzer,LOW);      //设置输出低电平 蜂鸣器停止
		}
   else
   {
      lcd.setCursor(0,0);       //设置液晶开始显示的指针位置
      lcd.print("Failure!!"); //液晶显示
    //  lcd.print(col,DEC); //液晶显示
      digitalWrite(Buzzer,HIGH);    //设置输出高电平 蜂鸣器
      delay(75);   
      digitalWrite(Buzzer,LOW);      //设置输出低电平 蜂鸣器停止
      delay(50);
       digitalWrite(Buzzer,HIGH);    //设置输出高电平 蜂鸣器
      delay(75);   
      digitalWrite(Buzzer,LOW);      //设置输出低电平 蜂鸣器停止
    }
    }
   MFRC522_Halt(); //command the card into sleep mode 
   delay(600);   
   lcd.clear();        //液晶清屏
}
