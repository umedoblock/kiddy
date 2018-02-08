/* PB2: _SS , 0x04 <=> 0xfb
 * PB3: MOSI, 0x08 <=> 0xf7
 * PB4: MISO, 0x10 <=> 0xef
 * PB5: SCK,  0x20 <=> 0xdf
   MISOのみInput、他はOutputで定義。
   only PB4 Input.
 */

#define DO_INIT()	DDRB  |= 0x00	/* Initialize port for MMC DO as input */
#define DO			(PINB &	0x10)	/* Test for MMC DO ('H':true, 'L':false) */

#define DI_INIT()	DDRB  |= 0x08	/* Initialize port for MMC DI as output */
#define DI_H()		PORTB |= 0x08	/* Set MMC DI "high" */
#define DI_L()		PORTB &= 0xF7	/* Set MMC DI "low" */

#define CK_INIT()	DDRB  |= 0x20	/* Initialize port for MMC SCLK as output */
#define CK_H()		PORTB |= 0x20	/* Set MMC SCLK "high" */
#define CK_L()		PORTB &= 0xDF	/* Set MMC SCLK "low" */

#define CS_INIT()	DDRB  |= 0x04	/* Initialize port for MMC CS as output */
#define	CS_H()		PORTB |= 0x04	/* Set MMC CS "high" */
#define CS_L()		PORTB &= 0xFB	/* Set MMC CS "low" */

