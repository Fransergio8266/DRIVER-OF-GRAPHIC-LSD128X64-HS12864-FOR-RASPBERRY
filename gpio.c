#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <fcntl.h>
#include "gpio.h"





bool export_gpio(int pin)
{
	int arquive=0;
    	arquive = open ("/sys/class/gpio/export", O_WRONLY);
    	if (arquive==-1)
    	{
            	printf("Arquivo abriu incorretamente no export\n");
            	return false;
    	}
	char buffer[3];
    	snprintf(buffer, 3, "%d", pin);
    	if(write(arquive, buffer, 3) == -1)
    	{
		printf("Falhou no export\n");
            	close(arquive);
            	return false;
    	}


    	close(arquive);


    	return true;
}

bool direction_gpio(int pin, int direction)
{
    	int arquive=0;
	char path [33];
    	snprintf(path, 33, "/sys/class/gpio/gpio%d/direction", pin);
    	arquive = open (path, O_WRONLY);
    	if (arquive==-1)
    	{
		printf("Arquivo abriu incorretamente no direction\n");
            	return false;
    	}
	char buffer[3];
    	snprintf(buffer, 3, "%d", pin);
    	if (write( arquive, ((direction == INPUT)?"in":"out"), 3 )==-1)
    	{
		printf("Falhou no direction\n");
            	close(arquive);
            	return false;
    	}
    	close(arquive);
    	return true;
}


bool value_gpio(int pin, int value)
{
    	int arquive=0;
	char path [35];
    	snprintf(path, 35, "/sys/class/gpio/gpio%d/value", pin);
    	arquive = open(path, O_WRONLY);
    	if (arquive == -1)
    	{
		printf("Arquivo abriu incorretamente no value\n");
            	return false;
    	}
    	if (write (arquive, ((value == HIGH)?"1":"0"), 1) == -1)
    	{
		printf("Falhou no value\n");
            	close(arquive);
            	return false;
    	}
    	close(arquive);
    	return true;
}
