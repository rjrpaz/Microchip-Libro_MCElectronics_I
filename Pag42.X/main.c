/* 
 * File:   main.c
 * Author: roberto
 *
 * Created on 13 de julio de 2014, 22:38
 *
 * La lectura de lo que el MCU escribe, en vez de mostrarse en un display,
 * se captura en una Raspberry Pi, ya que los niveles de tensión son TTL
 * en ambos casos, por lo que no es necesaria una adaptación mediante MAX-232
 * o similar.
 *
 * Referencias útiles:
 * https://www.youtube.com/watch?v=crSuPZy5EUQ
 * http://www.microchip.com/forums/m624475.aspx
 * http://www.instructables.com/id/Programming-PIC-Microcontrollers/step6/Configure-Oscillator/
 *
 * La redefinición de "putch()" necesaria para que funcione correctamente la función
 * printf() con el USART, se inspiró en:
 * http://www.microchip.com/forums/m702322.aspx
 */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <plib/usart.h>

#pragma config FOSC = INTIO67, FCMEN = OFF, IESO = OFF                       // CONFIG1H
#pragma config PWRT = OFF, BOREN = SBORDIS, BORV = 30                        // CONFIG2L
#pragma config WDTEN = OFF, WDTPS = 32768                                    // CONFIG2H
#pragma config MCLRE = OFF, LPT1OSC = OFF, PBADEN = ON, CCP2MX = PORTC       // CONFIG3H
#pragma config STVREN = ON, LVP = OFF, XINST = OFF                           // CONFIG4L                                 // CONFIG4L
#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF                    // CONFIG5L
#pragma config CPB = OFF, CPD = OFF                                          // CONFIG5H
#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF                // CONFIG6L
#pragma config WRTB = OFF, WRTC = OFF, WRTD = OFF                            // CONFIG6H
#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF            // CONFIG7L
#pragma config EBTRB = OFF                                                   // CONFIG7H

void putch(unsigned char byte)
{
    while (!TXIF)
        continue;
    TXREG = byte;
}

unsigned char getch()
{
    /* retrieve one byte */
    while(!RCIF)
        continue;
    return RCREG;
}

unsigned char getche()
{
    unsigned char c;
    putch(c = getch());
    return c;
}

void main(void) {
    int opcion, valor, res;
    char buf[80];
    /*
     *  El oscilador interno por defecto, es 1 Mhz. Con esta velocidad, y la configuración
     * del modo de UART que voy a utilizar, no podré alcanzar los 9600 bps. Por lo menos
     * debo tener una velocidad de 4 Mhz, lo cual lo puedo lograr a partir del oscilador
     * interno si configuro los bits del registro de control del oscilador.
     * Ver pag. 29 de la hoja de datos para mayor información
     */
    OSCCONbits.IRCF = 0b101;

    /* La función OpenUSART utiliza 2 argumentos: configuración del puerto, y velocidad */
    /*
     * La configuración elegida para el uso del puerto, se define como:
     * - deshabilito interrupción para la transmición
     * - deshabilito interrupción para la recepción
     * - modo asíncrono
     * - tranmisión de 8 bits
     * - recepción continua de bytes
     * - bit BRGH=1
     *
     * Ver pag. 1152 del documento del XC8 Peripheral Libraries
     */
    unsigned char config = USART_TX_INT_OFF & USART_RX_INT_OFF & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX & USART_BRGH_HIGH;
    /*
     * En función de la configuración elegida, para alcanzar la velocidad de 9660 bps
     * se debe configurar el segúndo argumento de la función OpenUSART con el valor=25
     * Ver tabla 18.5, pag 251 de la datasheet del MCU, tabla correspondiente a los
     * valores: SYNC=0, BRGH=1, BRG16=0, FOSC=4Mhz
     */
    unsigned int spbrg = 25;

    // Abre y configura el puerto serie.
    OpenUSART(config, spbrg);

    for(;;) {
        printf("Introduzca un valor entero mayor que 0:\n\r");
        if (gets(buf))
            valor=atoi(buf);
        printf("***MENU DE OPCIONES***\n\r");
        printf("1-Averguar el cuadrado:\n\r");
        printf("2-Averguar el cubo:\n\r");
        printf("3-Averguar si es par o no:\n\r");
        printf("\n\rIngrese la opcion:\n\r\n\r");
        if (gets(buf))
            opcion=atoi(buf);

        switch(opcion) {
            case 1:
                res = valor*valor;
                printf("El cuadrado de %i es %i\n\r", valor, res);
                break;
            case 2:
                res = valor*valor*valor;
                printf("El cubo de %i es %i\n\r", valor, res);
                break;
            case 3:
                res = valor%2;
                if (res)
                    printf("El numero %i es impar\n\r", valor);
                else
                    printf("El numero %i es par\n\r", valor);
                break;
            default:
                printf("Opcion erronea\n\r");

        }
    }
}
