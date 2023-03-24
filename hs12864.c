#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "hs12864.h"
//#include "gpio.h"
#include "spi_driver.h"

static void SendByteLCD(unsigned char WLCDData)
{
/* SPI BYTE WIRITE */
unsigned char * tx;
tx = &WLCDData;
write_spi(tx);

/* GPIO BYTE WRITE */
/*
unsigned char i;
for(i=0;i<8;i++)
{
if((WLCDData<<i)&0x80)
{value_gpio(SID, HIGH);}

else
{value_gpio(SID, LOW);;}

value_gpio(SCLK, LOW); ;
value_gpio(SCLK, HIGH);
}
*/
}

static void SPIWR(unsigned char Wdata,unsigned char RS)
{
SendByteLCD((0xF8)+(RS<<1));
SendByteLCD((Wdata)&(0xF0));
SendByteLCD((Wdata<<4)&0xF0);
}

static void TransferData(unsigned char data1, bool DI)  //if DI=0  Transfer command DI=1  Transfer data
{

if(DI==1)
{SPIWR(data1,1);} //DATA

else
{SPIWR(data1,0);} //CMD
}

void delayMicroseconds(int t_us){
float s = ((float)t_us)/1000000.0;
struct timespec t;
int seg;
seg = s;
t.tv_sec = seg;
t.tv_nsec = (s-seg)*1e9;
nanosleep(&t,NULL);
}

static void delayMiliseconds(int t_ms){
float s = ((float)t_ms)/1000.0;
struct timespec t;
int seg;
seg = s;
t.tv_sec = seg;
t.tv_nsec = (s-seg)*1e9;
nanosleep(&t,NULL);
}


void lcd_mesg(unsigned char *adder1, int len, unsigned char line)
{

switch(line)
{
case 1:
TransferData(0x80,0); //Set RAM Address
break;
case 2:
TransferData(0x90,0); //Set RAM Address
break;
case 3:
TransferData(0x88,0); //Set RAM Address
break;
case 4:
TransferData(0x98,0); //Set RAM Address
break;
default:
TransferData(0x80,0);
}

unsigned char i;
delayMicroseconds(100);
for(i=0;i<len;i++)
{
TransferData(*adder1,1);
adder1++;
}
}

void initinal(void)           //LCD initinal  Fonts Mode
{
TransferData(0x30,0);  //Extended Function Set :8BIT,RE=0: basic instruction set, G=0 :graphic display OFF
delayMicroseconds(100);
TransferData(0x30,0);  //Function Set
delayMicroseconds(37);
TransferData(0x08,0);  //Display on Control
delayMicroseconds(100);
TransferData(0x10,0);  //Cursor Display Control
delayMicroseconds(100);
TransferData(0x0C,0);  //Display Control,D=1,display on
delayMicroseconds(100);
TransferData(0x01,0);  //Display Clear
delayMiliseconds(10);
TransferData(0x06,0);  //Enry Mode Set
delayMicroseconds(100);
}

void initina2(void)           //Graphic display Mode
{
TransferData(0x30,0);  //Extended Function Set RE=1: extended instruction
delayMicroseconds(100);
TransferData(0x01,0);  //Display Clear
delayMiliseconds(10);
TransferData(0x36,0);  //Extended Function Set:RE=1: extended instruction set
delayMicroseconds(37);
TransferData(0x3E,0);  //EXFUNCTION(DL=8BITS,RE=1,G=1)
delayMicroseconds(100);
}



void DisplayGraphic(unsigned char *adder, int len)
{
    int i, j;
 //   printf("%d\n", len);
    if (len <= 512)
    {
        int v_adder = (int)(len / 16.0);
        //*******display top half screen
        for (i = 0; i < 32; i++) //
        {
            TransferData((0x80 + i), 0); // SET   VERTICAL ADDRESS
            TransferData(0x80, 0);       // SET   HORIZONTAL ADDRESS
            if (i < v_adder)
            {
                for (j = 0; j < 16; j++)
                {
                    TransferData(*adder, 1);
                    adder++;
                }
            }
            else
            {
                {
                    for (j = 0; j < 16; j++)
                    {
                        TransferData(0x00, 1);
                        adder++;
                    }
                }
            }
        }
        //*******display bottom half screen
        for (i = 0; i < 32; i++) //
        {
            TransferData((0x80 + i), 0); // SET VERTICAL ADDRESS
            TransferData(0x88, 0);       // SET HORIZONTAL ADDRESS

            for (j = 0; j < 16; j++)
            {
                TransferData(0x00, 1);
                adder++;
            }
        }
    }

    else
    {

            int v_adder = (int)((len - 512.0)/16.0);
            //*******display top half screen
            for (i = 0; i < 32; i++) //
            {
                TransferData((0x80 + i), 0); // SET   VERTICAL ADDRESS
                TransferData(0x80, 0);       // SET   HORIZONTAL ADDRESS
                
                    for (j = 0; j < 16; j++)
                    {
                        TransferData(*adder, 1);
                        adder++;
                    }

            }
            //*******display bottom half screen
            for (i = 0; i < 32; i++) //
            {
                TransferData((0x80 + i), 0); // SET VERTICAL ADDRESS
                TransferData(0x88, 0);       // SET HORIZONTAL ADDRESS
            if(i<v_adder)
            {
                for (j = 0; j < 16; j++)
                {
                    TransferData(*adder, 1);
                    adder++;
                }
            }
            else
            {
                for (j = 0; j < 16; j++)
                {
                    TransferData(0x00, 1);
                    adder++;
                }
            }
            }        
    }
}
