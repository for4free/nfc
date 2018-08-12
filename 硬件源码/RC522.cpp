/******************************************************************************
--------------------------------RFID课程设计-----------------------------------
----------------------ARDUINO UNO/RC522/LCD1602--------------------------------
------------------------ID卡签到系统测试程序-----------------------------------
----------------1.开发环境:Arduino IDE-----------------------------------------
----------------2.测试使用开发板型号：Arduino UNO 加强版-----------------------
******************************************************************************/

//Arduino  uno                                      RC522 (������ѹ3.3V)
//D9                  <------------->             RST    (����Ų���ò��Ҳ����)
//D10                 <------------->             SDA   (��RC522�м�ΪCS)
//D11                 <------------->             MOSI
//D12                 <------------->             MISO
//D13                 <------------->             SCK

#include "RC522.h"



/////////////////////////////////////////////////////////////////////
//set the pin
/////////////////////////////////////////////////////////////////////
const int chipSelectPin = 10;
const int NRSTPD = 9;




//-----------------------------------------------


/*
 * Function��ShowCardID
 * Description��Show Card ID
 * Input parameter��ID string
 * Return��Null
 */
void ShowCardID(uchar *id)
{
    int IDlen=4;
    for(int i=0; i<IDlen; i++){
        Serial.print(0x0F & (id[i]>>4), HEX);
        Serial.print(0x0F & id[i],HEX);
    }
    Serial.println("");
}

/*
 * Function��ShowCardType
 * Description��Show Card type
 * Input parameter��Type string
 * Return��Null
 */
void ShowCardType(uchar* type)
{
    Serial.print("Card type: ");
    if(type[0]==0x04&&type[1]==0x00) 
        Serial.println("MFOne-S50");
    else if(type[0]==0x02&&type[1]==0x00)
        Serial.println("MFOne-S70");
    else if(type[0]==0x44&&type[1]==0x00)
        Serial.println("MF-UltraLight");
    else if(type[0]==0x08&&type[1]==0x00)
        Serial.println("MF-Pro");
    else if(type[0]==0x44&&type[1]==0x03)
        Serial.println("MF Desire");
    else
        Serial.println("Unknown");
}

/*
 * Function��Write_MFRC5200
 * Description��write a byte data into one register of MR RC522
 * Input parameter��addr--register address��val--the value that need to write in
 * Return��Null
 */
void Write_MFRC522(uchar addr, uchar val)
{
    digitalWrite(chipSelectPin, LOW);

    //address format��0XXXXXX0
    SPI.transfer((addr<<1)&0x7E); 
    SPI.transfer(val);
    
    digitalWrite(chipSelectPin, HIGH);
}


/*
 * Function��Read_MFRC522
 * Description��read a byte data into one register of MR RC522
 * Input parameter��addr--register address
 * Return��return the read value
 */
uchar Read_MFRC522(uchar addr)
{
    uchar val;

    digitalWrite(chipSelectPin, LOW);

    //address format��1XXXXXX0
    SPI.transfer(((addr<<1)&0x7E) | 0x80); 
    val =SPI.transfer(0x00);
    
    digitalWrite(chipSelectPin, HIGH);
    
    return val; 
}

/*
 * Function��SetBitMask
 * Description��set RC522 register bit
 * Input parameter��reg--register address;mask--value
 * Return��null
 */
void SetBitMask(uchar reg, uchar mask) 
{
    uchar tmp;
    tmp = Read_MFRC522(reg);
    Write_MFRC522(reg, tmp | mask); // set bit mask
}


/*
 * Function��ClearBitMask
 * Description��clear RC522 register bit
 * Input parameter��reg--register address;mask--value
 * Return��null
 */
void ClearBitMask(uchar reg, uchar mask) 
{
    uchar tmp;
    tmp = Read_MFRC522(reg);
    Write_MFRC522(reg, tmp & (~mask)); // clear bit mask
} 


/*
 * Function��AntennaOn
 * Description��Turn on antenna, every time turn on or shut down antenna need at least 1ms delay
 * Input parameter��null
 * Return��null
 */
void AntennaOn(void)
{
    uchar temp;

    temp = Read_MFRC522(TxControlReg);
    if (!(temp & 0x03))
    {
        SetBitMask(TxControlReg, 0x03);
    }
}


/*
 * Function��AntennaOff
 * Description��Turn off antenna, every time turn on or shut down antenna need at least 1ms delay
 * Input parameter��null
 * Return��null
 */
void AntennaOff(void)
{
    ClearBitMask(TxControlReg, 0x03);
}


/*
 * Function��ResetMFRC522
 * Description�� reset RC522
 * Input parameter��null
 * Return��null
 */
void MFRC522_Reset(void)
{
    Write_MFRC522(CommandReg, PCD_RESETPHASE);
}


/*
 * Function��InitMFRC522
 * Description��initilize RC522
 * Input parameter��null
 * Return��null
 */
void MFRC522_Init(void)
{
    digitalWrite(NRSTPD,HIGH);

    MFRC522_Reset();
         
    //Timer: TPrescaler*TreloadVal/6.78MHz = 24ms
    Write_MFRC522(TModeReg, 0x8D); //Tauto=1; f(Timer) = 6.78MHz/TPreScaler
    Write_MFRC522(TPrescalerReg, 0x3E); //TModeReg[3..0] + TPrescalerReg
    Write_MFRC522(TReloadRegL, 30); 
    Write_MFRC522(TReloadRegH, 0);
    
    Write_MFRC522(TxAutoReg, 0x40); //100%ASK
    Write_MFRC522(ModeReg, 0x3D); //CRC initilizate value 0x6363 ???

    //ClearBitMask(Status2Reg, 0x08); //MFCrypto1On=0
    //Write_MFRC522(RxSelReg, 0x86); //RxWait = RxSelReg[5..0]
    //Write_MFRC522(RFCfgReg, 0x7F); //RxGain = 48dB

    AntennaOn(); //turn on antenna
}


/*
 * Function��MFRC522_Request
 * Description��Searching card, read card type
 * Input parameter��reqMode--search methods��
 * TagType--return card types
 * 0x4400 = Mifare_UltraLight
 * 0x0400 = Mifare_One(S50)
 * 0x0200 = Mifare_One(S70)
 * 0x0800 = Mifare_Pro(X)
 * 0x4403 = Mifare_DESFire
 * return��return MI_OK if successed
 */
uchar MFRC522_Request(uchar reqMode, uchar *TagType)
{
    uchar status; 
    uint backBits; //the data bits that received

    Write_MFRC522(BitFramingReg, 0x07); //TxLastBists = BitFramingReg[2..0] ???
    
    TagType[0] = reqMode;
    status = MFRC522_ToCard(PCD_TRANSCEIVE, TagType, 1, TagType, &backBits);

    if ((status != MI_OK) || (backBits != 0x10))
    { 
        status = MI_ERR;
    }
   
    return status;
}


/*
 * Function��MFRC522_ToCard
 * Description��communicate between RC522 and ISO14443
 * Input parameter��command--MF522 command bits
 * sendData--send data to card via rc522
 * sendLen--send data length 
 * backData--the return data from card
 * backLen--the length of return data
 * return��return MI_OK if successed
 */
uchar MFRC522_ToCard(uchar command, uchar *sendData, uchar sendLen, uchar *backData, uint *backLen)
{
    uchar status = MI_OK;
    uchar irqEn = 0x00;
    uchar waitIRq = 0x00;
    uchar lastBits;
    uchar n;
    uint i;

    switch (command)
    {
        case PCD_AUTHENT: //verify card password
        {
            irqEn = 0x12;
            waitIRq = 0x10;
            break;
        }
        case PCD_TRANSCEIVE: //send data in the FIFO
        {
            irqEn = 0x77;
            waitIRq = 0x30;
            break;
        }
        default:
            break;
    }
   
    Write_MFRC522(CommIEnReg, irqEn|0x80); //Allow interruption
    ClearBitMask(CommIrqReg, 0x80); //Clear all the interrupt bits
    SetBitMask(FIFOLevelReg, 0x80); //FlushBuffer=1, FIFO initilizate
    
    Write_MFRC522(CommandReg, PCD_IDLE); //NO action;cancel current command ???

    //write data into FIFO
    for (i=0; i<sendLen; i++)
    { 
        Write_MFRC522(FIFODataReg, sendData[i]); 
    }

    //procceed it
    Write_MFRC522(CommandReg, command);
    if (command == PCD_TRANSCEIVE)
    { 
        SetBitMask(BitFramingReg, 0x80); //StartSend=1,transmission of data starts 
    } 
    
    //waite receive data is finished
    i = 2000; //i should adjust according the clock, the maxium the waiting time should be 25 ms???
    do 
    {
        //CommIrqReg[7..0]
        //Set1 TxIRq RxIRq IdleIRq HiAlerIRq LoAlertIRq ErrIRq TimerIRq
        n = Read_MFRC522(CommIrqReg);
        i--;
    }
    while ((i!=0) && !(n&0x01) && !(n&waitIRq));

    ClearBitMask(BitFramingReg, 0x80); //StartSend=0
    
    if (i != 0)
    { 
        if(!(Read_MFRC522(ErrorReg) & 0x1B)) //BufferOvfl Collerr CRCErr ProtecolErr
        {
            status = MI_OK;
            if (n & irqEn & 0x01)
            { 
                status = MI_NOTAGERR; //?? 
            }
            
            if (command == PCD_TRANSCEIVE)
            {
                n = Read_MFRC522(FIFOLevelReg);
                lastBits = Read_MFRC522(ControlReg) & 0x07;
                if (lastBits)
                { 
                    *backLen = (n-1)*8 + lastBits; 
                }
                else
                { 
                    *backLen = n*8; 
                }
                
                if (n == 0)
                { 
                    n = 1; 
                }
                if (n > MAX_LEN)
                { 
                    n = MAX_LEN; 
                }
                
                //read the data from FIFO
                for (i=0; i<n; i++)
                { 
                    backData[i] = Read_MFRC522(FIFODataReg); 
                }
            }
        }
        else
        { 
            status = MI_ERR; 
        }
        
    }
    
    //SetBitMask(ControlReg,0x80); //timer stops
    //Write_MFRC522(CommandReg, PCD_IDLE); 

    return status;
}


/*
 * Function��MFRC522_Anticoll
 * Description��Prevent conflict, read the card serial number 
 * Input parameter��serNum--return the 4 bytes card serial number, the 5th byte is recheck byte
 * return��return MI_OK if successed
 */
uchar MFRC522_Anticoll(uchar *serNum)
{
    uchar status;
    uchar i;
    uchar serNumCheck=0;
    uint unLen;
    
    //ClearBitMask(Status2Reg, 0x08); //strSensclear
    //ClearBitMask(CollReg,0x80); //ValuesAfterColl
    Write_MFRC522(BitFramingReg, 0x00); //TxLastBists = BitFramingReg[2..0]
 
    serNum[0] = PICC_ANTICOLL;
    serNum[1] = 0x20;
    status = MFRC522_ToCard(PCD_TRANSCEIVE, serNum, 2, serNum, &unLen);

    if (status == MI_OK)
    {
        //Verify card serial number
        for (i=0; i<4; i++)
        { 
            serNumCheck ^= serNum[i];
        }
        if (serNumCheck != serNum[i])
        { 
            status = MI_ERR; 
        }
    }

    //SetBitMask(CollReg, 0x80); //ValuesAfterColl=1

    return status;
} 


/*
 * Function��CalulateCRC
 * Description��Use MF522 to caculate CRC
 * Input parameter��pIndata--the CRC data need to be read��len--data length��pOutData-- the caculated result of CRC
 * return��Null
 */
void CalulateCRC(uchar *pIndata, uchar len, uchar *pOutData)
{
    uchar i, n;

    ClearBitMask(DivIrqReg, 0x04); //CRCIrq = 0
    SetBitMask(FIFOLevelReg, 0x80); //Clear FIFO pointer
    //Write_MFRC522(CommandReg, PCD_IDLE);

    //Write data into FIFO 
    for (i=0; i<len; i++)
    { 
        Write_MFRC522(FIFODataReg, *(pIndata+i)); 
    }
    Write_MFRC522(CommandReg, PCD_CALCCRC);

    //waite CRC caculation to finish
    i = 0xFF;
    do 
    {
        n = Read_MFRC522(DivIrqReg);
        i--;
    }
    while ((i!=0) && !(n&0x04)); //CRCIrq = 1

    //read CRC caculation result
    pOutData[0] = Read_MFRC522(CRCResultRegL);
    pOutData[1] = Read_MFRC522(CRCResultRegM);
}



/*
 * Function��MFRC522_Write
 * Description��write block data
 * Input parameters��blockAddr--block address;writeData--Write 16 bytes data into block
 * return��return MI_OK if successed
 */
uchar MFRC522_Write(uchar blockAddr, uchar *writeData)
{
    uchar status;
    uint recvBits;
    uchar i;
    uchar buff[18]; 
    
    buff[0] = PICC_WRITE;
    buff[1] = blockAddr;
    CalulateCRC(buff, 2, &buff[2]);
    status = MFRC522_ToCard(PCD_TRANSCEIVE, buff, 4, buff, &recvBits);

    if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A))
    { 
        status = MI_ERR; 
    }
        
    if (status == MI_OK)
    {
        for (i=0; i<16; i++) //Write 16 bytes data into FIFO
        { 
            buff[i] = *(writeData+i); 
        }
        CalulateCRC(buff, 16, &buff[16]);
        status = MFRC522_ToCard(PCD_TRANSCEIVE, buff, 18, buff, &recvBits);
        
        if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A))
        { 
            status = MI_ERR; 
        }
    }
    
    return status;
}


/*
 * Function��MFRC522_Halt
 * Description��Command the cards into sleep mode
 * Input parameters��null
 * return��null
 */
void MFRC522_Halt(void)
{
    uchar status;
    uint unLen;
    uchar buff[4]; 

    buff[0] = PICC_HALT;
    buff[1] = 0;
    CalulateCRC(buff, 2, &buff[2]);
 
    status = MFRC522_ToCard(PCD_TRANSCEIVE, buff, 4, buff,&unLen);
}
