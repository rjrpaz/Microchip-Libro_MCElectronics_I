#include <htc.h>
#include <stdio.h>
#include <plib/usart.h>
#include "usart.h"

void putch(unsigned char byte)
{
    /* envía un byte */
    while (TXIF) /* Finalizó la transmisión ? */
        continue;
    TXREG = byte;
}

unsigned char getch(void)
{
    /* recibe un byte */
    while (RCIF) /* Recibió un dato ? */
        continue;
    return RCREG;
}

unsigned char getche(void)
{
    unsigned char c;
    putch(c=getch());
    return c;
}
