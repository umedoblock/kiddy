#include <stdio.h>
#include <string.h>

#include "hd44780.h"  /* EZ-LCD include file */

int init_device(void)
{
    lcd_init();                  /* LCDモジュールの初期化 */
    return 0;
}

#define BUFFER_SIZE (_LCD_ROWS*_LCD_COLS+1)
char work[BUFFER_SIZE];

int init_log(void)
{
    memset(work, '\0', BUFFER_SIZE);
    return 0;
}

int insert_log(char *log, int len)
{
    static int index=0;
    int8_t tail;

    if (len < 0)
        len=strlen(log);
    if (len > _LCD_COLS) {
        len = _LCD_COLS - 1;
        log[len] = '\0';
    }

    if (index < 4){
        sprintf(work+index*_LCD_COLS, "%s", log);
        index++;
        return index;
    }
    tail=_LCD_COLS*(_LCD_ROWS-1);
    memcpy(work, work+_LCD_COLS, tail);
    memcpy(work+tail, log, len+1);

    index++;

    return index;
}

int describe_value(char *describe, int8_t value)
{
    char ss[_LCD_COLS+1];
    int8_t len, index;

    /* pay attention to "describe" in snprintf().
     * "describe" may occur security hole.
     */
    len=snprintf(ss, _LCD_COLS+1, describe, value);
    index=insert_log(ss, len);

    return index;
}

int insert_kv(char *key, int8_t value)
{
    char ss[_LCD_COLS+1];
    int8_t len, index;

    len=snprintf(ss, _LCD_COLS+1, "%s=%d", key, value);
    index=insert_log(ss, len);

    return index;
}

int view_log(void)
{
    int ch;
    int8_t j, i=0;

    for(j=0;j<_LCD_ROWS;j++) {
        lcd_locate(j, 0);
        for(i=0;i<_LCD_COLS;i++) {
            ch=work[j*_LCD_COLS+i];
            if (ch != 0)
                lcd_putc(ch);
            else
                for(;i<_LCD_COLS;i++)
                    lcd_putc(' ');
        }
    }

    return 0;
}

int main (void)
{
    init_device();
    int8_t value = 0x4a;

    insert_log("lcd test start !", -1);
    insert_kv("lcd test", 2);
    insert_kv("lcd test", 3);
    insert_kv("lcd test", 4);
    describe_value("74,0x4a=0x%02x", value);
    view_log();

    return 0;
}
