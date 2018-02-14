/*----------------------------------------------------------------------*/
/* Foolproof FatFs sample project for AVR              (C)ChaN, 2014    */
/*----------------------------------------------------------------------*/

#include <avr/io.h>	/* Device specific declarations */
#include <util/delay.h>

#include "ff.h"		/* Declarations of FatFs API */

#include "kiddy.h"

FATFS FatFs;		/* FatFs work area needed for each volume */
FIL Fil;			/* File object needed for each open file */

int init_device(void)
{
	return 0;
}

int main (void)
{
	UINT count, bw;
	FRESULT res;
	BYTE mode;

	init_device();

	res=f_mount(&FatFs, "", 0);		/* Give a work area to the default drive */

	if (res != FR_OK) {
		// light_error_onoff(res);
		return res;
	}

	mode=FA_WRITE | FA_CREATE_ALWAYS;
	res=f_open(&Fil, "newfile2.txt", mode);

	if (res == FR_OK) {	/* Create a file */
		f_printf(&Fil, "%s\n", get_signature());
		res=f_write(&Fil, "It works2!\r\n", 12, &bw);
		/* Write data to the file */

		for(count=0;count<10;count++) {
			res=f_printf(&Fil, "count=%u\n", count);
			_delay_ms(10);
		}
		res=f_close(&Fil);/* Close the file */
	}

	for (;;) ;
}
