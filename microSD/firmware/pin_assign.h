/* PB2: _SS , 0x04 <=> 0xfb
 * PB3: MOSI, 0x08 <=> 0xf7
 * PB4: MISO, 0x10 <=> 0xef
 * PB5: SCK,  0x20 <=> 0xdf
   MISOのみInput、他はOutputで定義。
   only PB4 Input.

        Master  Slave
   MISO       <-
   MOSI       ->
   SCLK       ->
     CS       ->
 */

#define DO_PIN (0x10)
#define DO_INIT()  DDRB  |= 0x00     /* Initialize port for MMC DO as input */
#define DO        (PINB  &  0x10)   /* Test for MMC DO ('H':true, 'L':false) */

#define DI_PIN (0x08)
#define DI_INIT()   DDRB |= DI_PIN   /* Initialize port for MMC DI as output */
#define DI_H()     PORTB |= DI_PIN   /* Set MMC DI "high" */
#define DI_L()     PORTB &= ~DI_PIN  /* Set MMC DI "low" */

#define CK_PIN (0x20)
#define CK_INIT()   DDRB |= CK_PIN   /* Initialize port for MMC SCLK as output */
#define CK_H()     PORTB |= CK_PIN   /* Set MMC SCLK "high" */
#define CK_L()     PORTB &= ~CK_PIN  /* Set MMC SCLK "low" */

#define CS_PIN (0x04)
#define CS_INIT()   DDRB |= CS_PIN   /* Initialize port for MMC CS as output */
#define CS_H()     PORTB |= CS_PIN   /* Set MMC CS "high" */
#define CS_L()     PORTB &= ~CS_PIN  /* Set MMC CS "low" */
