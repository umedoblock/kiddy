/*----------------------------------------------------------------------*/
/* Foolproof FatFs sample project for AVR              (C)ChaN, 2014    */
/*----------------------------------------------------------------------*/

#include <avr/io.h>	/* Device specific declarations */
#include "ff.h"		/* Declarations of FatFs API */

FATFS FatFs;		/* FatFs work area needed for each volume */
FIL Fil;			/* File object needed for each open file */

int init_device(void)
{
	return 0;
}

int main (void)
{
	UINT bw;
	FRESULT res;
	BYTE mode;

	init_device();

	res=f_mount(&FatFs, "", 0);		/* Give a work area to the default drive */

	if (res != FR_OK) {
		// light_error_onoff(res);
		return res;
	}

	mode=FA_WRITE | FA_CREATE_ALWAYS;
	res=f_open(&Fil, "newfile.txt", mode);

	if (res == FR_OK) {	/* Create a file */
		res=f_write(&Fil, "It works!\r\n", 11, &bw);	/* Write data to the file */
		res=f_close(&Fil);								/* Close the file */
	}

	for (;;) ;
}
