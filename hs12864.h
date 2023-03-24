#ifndef __HS12864_H__
#define __HS12864_H__


void delayMicroseconds(int t_us);

void initinal(void);

void initina2(void);

void lcd_mesg(unsigned char *adder1, int len, unsigned char line);

void DisplayGraphic(unsigned char *adder, int len);
#endif
