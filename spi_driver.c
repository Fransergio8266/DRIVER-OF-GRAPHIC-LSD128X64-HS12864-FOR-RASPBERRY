#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include "spi_driver.h"


#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))


static unsigned char mode = SPI_MODE_3 | SPI_CS_HIGH;
static unsigned char bits = 8;
static uint32_t speed = 1000000;
static uint16_t delay=0;
int fd;


void config_spi(const char *device)
{
int ret;
fd = open(device,O_RDWR);

if(fd<0)
{
printf("Can't open device\n");	
}

ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
if (ret == -1)
{
printf("Can't set spi mode\n");
}

ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
if (ret == -1)
{
printf("Can't set bits per word\n");
}

ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
if (ret == -1)
{
printf("can't set max speed hz\n");
}

}

void write_spi(unsigned char *tx)
{
int ret;
unsigned char rx[ARRAY_SIZE(tx)] = {0, };
struct spi_ioc_transfer tr = 
{
.tx_buf = (unsigned long)tx,
.rx_buf = (unsigned long)rx,
.len = 1,
.delay_usecs = delay,
.speed_hz = speed,
.bits_per_word = bits,
};

ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
if (ret < 1)
{
printf("Can't send spi message");
}
}
