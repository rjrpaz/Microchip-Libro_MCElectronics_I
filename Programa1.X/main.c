/* 
 * File:   main.c
 * Author: roberto
 *
 * Para este programa y los siguientes, se utiliza la placa
 * de MC Electronics, Webserver, que incluye un
 * PIC18F9760 con soporte de Ethernet
 *
 * A diferencia de la placa usada para probar
 * los programas de esta parte del libro
 * (pag 59 en adelante):
 * - Los 4 pulsadores ocupan los puertos RB0-RB3
 * - Los 8 leds ocupan los puertos RJ0-RJ7
 */

#include <xc.h>

#pragma config WDT=OFF
#pragma config STVR=OFF
#pragma config XINST=OFF
#pragma config CP0=OFF
#pragma config FOSC=HS
#pragma config FOSC2=OFF
#pragma config FCMEN=OFF
#pragma config IESO=OFF
#pragma config WDTPS=1
#pragma config EASHFT=OFF
#pragma config MODE=MM
#pragma config BW=8
#pragma config WAIT=OFF
#pragma config CCP2MX=OFF
#pragma config ECCPMX=OFF
#pragma config ETHLED=OFF

void main(void) {
    /* RB0-RB3 entradas */
    TRISB=0x0F;

    /* RBJ como salidas */
    TRISJ=0;

    for(;;) {
        if (RB0 == 1)
            RJ0=0;
        else
            RJ0=1;

        if (RB1 == 1)
            RJ1=0;
        else
            RJ1=1;

        if (RB2 == 1)
            RJ2=0;
        else
            RJ2=1;
    }
}

