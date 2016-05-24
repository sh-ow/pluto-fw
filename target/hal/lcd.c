#include <msp430.h>
#include <string.h>
#include "io.h"
#include "lcd.h"
#include "common/hal/hal.h"
#include "segmap.h"

static uint8_t buf[29];
static uint8_t bbuf[29];

__attribute__((always_inline)) static inline void lcd_enable_seg(uint8_t seg) {
	uint16_t *p = (void*)&LCDCPCTL0;
	p[seg/16] |= (1<<(seg%16));
}

void lcd_init(void)
{
	LCDCCTL0 = LCDDIV_21 | LCDPRE__8 | LCD3MUX;
	LCDCBLKCTL = LCDBLKPRE__16384 | LCDBLKMOD_1;
	LCDCVCTL = 0;

	PCONF(6, 3, FUNC3);
	PCONF(6, 4, FUNC3);
	PCONF(6, 5, FUNC3);

	lcd_enable_seg(0);
	lcd_enable_seg(1);
	lcd_enable_seg(2);
	lcd_enable_seg(3);
	lcd_enable_seg(4);
	lcd_enable_seg(5);
	lcd_enable_seg(6);
	lcd_enable_seg(7);
	lcd_enable_seg(8);
	lcd_enable_seg(9);
	lcd_enable_seg(10);
	lcd_enable_seg(16);
	lcd_enable_seg(17);
	lcd_enable_seg(18);
	lcd_enable_seg(19);
	lcd_enable_seg(20);
	lcd_enable_seg(21);
	lcd_enable_seg(22);
	lcd_enable_seg(23);
	lcd_enable_seg(24);
	lcd_enable_seg(25);
	lcd_enable_seg(26);
	lcd_enable_seg(27);
	lcd_enable_seg(28);

	LCDCMEMCTL |= LCDCLRM | LCDCLRBM;

	LCDCCTL0 |= LCDON;
}

static const uint8_t stab[] = {
	1<<0,
	1<<1,
	1<<2,
	1<<3,
	1<<4,
	1<<5,
	1<<6,
	1<<7,
};

#define SHIFTONE(b) (stab[b])
//#define SHIFTONE(b) (1<<(b))


void hal_lcd_seg_set(uint8_t seg, bool state) {
	uint8_t m = tgt_lcd_map[seg];
	uint8_t bit = m&7;
	uint8_t mem = m>>3;
	if(state) {
		buf[mem] |= SHIFTONE(bit);
	}
	else {
		buf[mem] &= ~SHIFTONE(bit);
	}
}

void hal_lcd_seg_set_blink(uint8_t seg, bool state) {
	uint8_t m = tgt_lcd_map[seg];
	uint8_t bit = m&7;
	uint8_t mem = m>>3;
	if(state) {
		bbuf[mem] |= SHIFTONE(bit);
	}
	else {
		bbuf[mem] &= ~SHIFTONE(bit);
	}
}

void hal_lcd_dig_set(uint8_t dig, uint16_t segments) {
	for(uint8_t i=0; i<9; i++) {
		hal_lcd_seg_set(HAL_LCD_SEG(dig, i), segments&1);
		segments>>=1;
	}
}

void hal_lcd_dig_set_blink(uint8_t dig, uint8_t blink) {
	for(uint8_t i=0; i<9; i++) {
		hal_lcd_seg_set_blink(HAL_LCD_SEG(dig, i), blink);
	}
}

void hal_lcd_dig_set_blink_mask(uint16_t mask) {
	for(uint8_t i=0; i<10; i++) {
		hal_lcd_dig_set_blink(i, mask&1);
		mask>>=1;
	}
}

void hal_lcd_clear(void) {
	memset(buf, 0, sizeof(buf));
	memset(bbuf, 0, sizeof(bbuf));
}

void hal_lcd_update(void) {
	for(uint8_t i = 0; i < 29;i++) {
		LCDMEM[i] = buf[i];
		LCDBMEM[i] = bbuf[i];
	}
}