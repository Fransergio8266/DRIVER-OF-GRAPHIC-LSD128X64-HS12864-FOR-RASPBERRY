#!/bin/bash
#GENERATE OBJECT FILE OF EACH PROJECT LIBRARY
gcc -c ../hs12864.c
gcc -c ../spi_driver.c
#GENERATE STATIC LIB BASED ON  OBJECT FILES
ar rcs lib_static.a hs12864.o spi_driver.o
#GENERATE OBJECT FILE OF MAIN INCLUDING HEADER FILES
gcc ../hs12864.h ../spi_driver.h -c ../main.c
#GENERATE EXECUTABLE FROM OBJECT MAIN AND FROM STATIC LIB
gcc -o main main.o lib_static.a 
