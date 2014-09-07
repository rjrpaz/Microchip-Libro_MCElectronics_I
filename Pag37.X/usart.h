/* 
 * File:   usart.h
 * Author: roberto
 *
 * Created on 13 de julio de 2014, 22:40
 */

#ifndef USART_H
#define	USART_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef _SERIAL_H_
#define _SERIAL_H_

#define BAUD 9600
#define FREQOSC 4000000L
#define NINE 0 /* vale 1 si usa 9 BITS */

#define DIVIDER ((int) (FREQOSC/(16UL*BAUD)-1))
#define HIGH_SPEED 1

#if NINE==1
#define NINE_BITS 0x40
#else
#define NINE_BITS 0
#endif

#if HIGH_SPEED==1
#define SPEED 0x4
#else
#define SPEED 0
#endif

// Definición de los pines de la USART según el micro
#if defined(_16F87) || defined(_16F88)
#define RX_PIN TRISB2
#define TX_PIN TRISB5
#else
#define RX_PIN TRISC7
#define TX_PIN TRISC6
#endif

/* Inicialización de la USART */
#define init_comms() \
    RX_PIN=0; \
    TX_PIN=1; \
    SPBRG = DIVIDER; \
    RCSTA=(NINE_BITS | 0x90); \
    TXSTA=(SPEED|NINE_BITS|0x20)

void putch(unsigned char);
unsigned char getch(void);
unsigned char getche(void);

#endif

#ifdef	__cplusplus
}
#endif

#endif	/* USART_H */

