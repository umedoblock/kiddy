/* Copyright (C) 2018, 梅濁酒(umedoblock), all right reserved. */

#include "kiddy.h"

#ifdef _USE_CHAN_SPI
#define SIGNATURE "This SPI communication is emurated by ChaN."
#elif _USE_AVR_SPI
#error "Not yet ready to develop."
// #define SIGNATURE "This SPI communication is made by AVR."
#else
#error "no man knows how to communicate with SPI."
#endif

char *get_signature(void)
{
    return SIGNATURE;
}
