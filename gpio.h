#ifndef __GPIO_H__
#define __GPIO_H__

#define HIGH 1
#define LOW 0
#define INPUT 0
#define OUTPUT 1


bool export_gpio(int pin);

bool direction_gpio(int pin, int direction);

bool value_gpio(int pin, int value); 



#endif
