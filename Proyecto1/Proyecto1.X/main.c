/*
 * File:   main.c
 * Author: roberto
 *
 * Created on 8 de julio de 2014, 23:42
 *
 * Ejercicio de la página 23
 * 
 */


#include <xc.h>
#include <plib/delays.h>
// #define _XTAL_FREQ 1000000

#pragma config FOSC = INTIO67, FCMEN = OFF, IESO = OFF                       // CONFIG1H
#pragma config PWRT = OFF, BOREN = SBORDIS, BORV = 30                        // CONFIG2L
#pragma config WDTEN = OFF, WDTPS = 32768                                    // CONFIG2H
#pragma config MCLRE = OFF, LPT1OSC = OFF, PBADEN = ON, CCP2MX = PORTC       // CONFIG3H
#pragma config STVREN = ON, LVP = OFF, XINST = OFF                                                            // CONFIG4L
#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF                   // CONFIG5L
#pragma config CPB = OFF, CPD = OFF                                         // CONFIG5H
#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF                // CONFIG6L
#pragma config WRTB = OFF, WRTC = OFF, WRTD = OFF                            // CONFIG6H
#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF           // CONFIG7L
#pragma config EBTRB = OFF                                                  // CONFIG7H


void main(void) {
//    ANSEL=0;
//    ANSELH=0;
    PORTD=0;
    TRISD=0;

    while (1) {
        LATDbits.LATD7 = ~LATDbits.LATD7;
        Delay1KTCYx(100);
    }
}
