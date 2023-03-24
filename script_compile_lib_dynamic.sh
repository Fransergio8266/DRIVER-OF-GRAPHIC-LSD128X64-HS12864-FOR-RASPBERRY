#!/bin/bash
#GENERATE JUST OBJECT MAIN FILE
gcc -c -o main.o main.c
#GENERATE OBJECT FILE FROM PROJECT LIRARIES WITH INDEPENDENT POSITION 
gcc -c -fPIC -o spi_driver.o spi_driver.c
gcc -c -fPIC -o hs12864.o hs12864.c 
#gcc -c -fPIC -o gpio.o gpio.c
#GENERATE DYNAMIC LIBRARY WITH OBJECTS SOURCES SHARED
gcc -o dynlib.so -shared gpio.o hs12864.o spi_driver.o
#GENERATE MAIN EXECUTABLE FROM DYNAMIC LIBRARY
gcc -o main main.o dynlib.so
#GIVE PATH OF DYNAMIC LIBRARY TO SYSTEM
export LD_LIBRARY_PATH=.
