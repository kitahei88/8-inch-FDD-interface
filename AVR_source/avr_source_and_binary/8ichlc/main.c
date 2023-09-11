/*
 * 8inchlc.c
 *
 * Created: 2022/08/30 
 *  Author: takuya fukuda
 *	8inch drive用　Low current信号生成
 *	***仕様***
 *	8inch ドライブに必要な low current 信号を自動で生成
 *	step, direction, track00, write gateを入力して low current を出力
 *	low current はYEでは Write中の場合 　0~43でH 44~76でLとし、Read中は0~59でH 60~76でL
 *	NEC FD1165は、 read writeに関係なく0~42でH、43~76でL
 *	Attiny13Aで作成
 *	pin数の関係でリセットを無効、GPIOとしている
 */ 

/*
	* FUSE bit(0 is enable)
	* 
	* Low 0x7A
	* SPIEN 0, EESAVE 1, WDTON 1, CKDIV8 1, SUT1:0 2'b01, CKSEL1:0 2'b10 ( internal RC Osc9.6MHz, statup 14ck+64ms)  
	* High 0xFE
	* BODLEVEL1:0 2'b11, DWEN 1, RSTBIDBL 0, SELFPRGEN 1;
	* Lock bit 0xFF means no lock 
*/

//#include <xc.h>
#include <avr/io.h>
#define F_CPU 9600000UL  // 9.6MHz internal clock
#include <util/delay.h>
#include <avr/interrupt.h>
#include "integer.h"

#define MAX_TRACK	76
#define YE	0
#define NEC	1
#define WR	0
#define RD	1

#define TRACK0		PINB0
#define	STEP		PINB1
#define WRITEGATE	PINB2
#define LOWCURRENT	PORTB3
#define DIRECTION	PINB4
#define MODEL		PINB5

#define EEPADD	0

/*	deprecated.h	*/
#define cbi(addr,bit) addr &= ~_BV(bit)	/* clear bit	*/
#define sbi(addr,bit) addr |= _BV(bit)	/* set bit		*/
#define ibi(addr,bit) addr ^= _BV(bit)	/* invert bit	*/ 

/*
	Step : INT0(PB1, pin6)
	Track00, write gate : PCINT0(Track00:PCINT0,PB0, pin5. write gate: PCINT2,PB2,pin 7.)
	direction: PB4,pin3 (Direction is low, head move to inner track,track number is up, high vise verse) 
	low current: PB3,pin2 (out)
	NEC and YE change: PB5(RST), select with jumper
*/

/* 	global valuable	*/ 
	CHAR	trk	 = 0;	// current track number
	CHAR	mode = YE;	// Drive model select
	CHAR	rw	 = RD;	// current read or write status

/*	global function	*/

void eeprom_write (unsigned char add, unsigned char dat)
{
	while(EECR & (1<<EEPE));
	EECR = (0<<EEPM1)|(0<<EEPM0);
	EEARL = add;
	EEDR = dat;
	EECR |= (1<<EEMPE);
	EECR |= (1<<EEPE);
}

unsigned char eeprom_read(unsigned char add)
{
	while(EECR & (1<<EEPE));
	EEARL = add;
	EECR |= (1<<EERE);
	return EEDR;	
}

/*	global function	end	*/
	
static inline
void init(void)
{
	cli();
	
	MCUCR	= 0x02;	/*	ISC1:0 = 2'b10, down trigger for INT0 */
	PCMSK	= 0x05;	/*	PCINT0 and PCINT2 is enable	*/
	PRR		= 0x03;	/*	Power Reduction setting (ADC disable, timer disable)	*/
	
	/* set PORTB I/O */
	DDRB	= 0b00001000;
	PORTB	= 0b00011111;
	// PB3 is out, other pins are input , pullup.
	
	GIMSK	= 0x60;	/*	INT0 and PCINT are enable	*/
  	sei();
	trk = eeprom_read(EEPADD);
}


ISR(INT0_vect)		// step signal is assert
{
	if ( bit_is_set(PINB,DIRECTION) ) // go to low track
		{	if (trk>0)  trk--;
		} else { // got high track
			if (trk<MAX_TRACK) trk++;
		}
	eeprom_write(EEPADD,trk);	
}

ISR(PCINT0_vect)	// Track00 or write gate is changed 
{ 
	if ( bit_is_set(PINB,WRITEGATE) )	rw = RD;
	if ( bit_is_clear(PINB,WRITEGATE) )	rw = WR;
	if ( bit_is_clear(PINB,TRACK0) )  {
		trk = 0;
		eeprom_write(EEPADD,trk);
		}
}


int main(void)
{
	init();
	if (bit_is_set(PINB,MODEL)) 	mode = NEC;
	
	while (1) {
		switch (mode)	{
			case NEC:
				if (trk<42) { PORTB &= ~(1<<LOWCURRENT);	// NPN tr switch, inverted out
					} else { PORTB |= (1<<LOWCURRENT);		// NPN tr switch, inverted out
					}
				break;
			case YE:
				if (rw == WR) {
					if (trk<44) { PORTB &= ~(1<<LOWCURRENT); 
						} else { PORTB |= (1<<LOWCURRENT);
						}
				} else {
					if (trk<60) { PORTB &= ~(1<<LOWCURRENT);
						} else { PORTB |= (1<<LOWCURRENT);
						}	
				}
				break;	
			default:
				break;
		}
	_delay_us(100);
	}
    return 0;
}


