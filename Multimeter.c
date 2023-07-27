/* 
 * File:   Multimeter.c
 * Author: Ammar Elzeftawy, David Kim, Yaseen ElSherif
 *
 * Created on December 1, 2022, 9:17 PM
 */

#include "xc.h"
#include "UART2.h"
#include "IOs.h"
#include "ADC.h"
#include "Display.h"
#include <stdio.h>

int button; // PB being pressed

void readMultimeter() {
    while(1) {
        int result; // voltage in output
        while(button == 1) { // PB1 pressed             
            XmitUART2('\r', 1); // Xmits Carriage Return
            Disp2String("Currently in Idle Mode");
            Idle();
        }
        while(button == 2) { // PB2 pressed
            XmitUART2('\r', 1); // Xmits Carriage Return
            Disp2String("PB2 being pressed: Measuring Current");
            result = do_ADC();
            XmitUART2('\r', 1); // Xmits Carriage Return
            char str[4];
            Disp2String("Current = ");
            float cur = (result * 3.25) / 1000; // voltage / resistance
            sprintf(str, "%1.3f", cur);
            Disp2String(str); // Prints the current to the display
            Disp2String(" Ampere");
            XmitUART2('\r', 1); // Xmits Carriage Return
        }
        while(button == 3) { // PB3 pressed 
            XmitUART2('\r', 1); // Xmits Carriage Return
            Disp2String("PB3 being pressed: Measuring Resistance");
            result = do_ADC();
            XmitUART2('\r', 1); // Xmits Carriage Return
            Disp2String("Resistance = ");
            uint16_t res = -1000 * ((result * 3.25) / 1024) /(((result * 3.25) / 1024) - 3.25);
            Disp2Dec(res);
            Disp2String(" Ohms");
            XmitUART2('\r', 1); // Xmits Carriage Return
        }   
    }  
}

void __attribute((interrupt, no_auto_psv))_CNInterrupt(void) {
    IOcheck();
    IFS1bits.CNIF = 0; // Reset interrupt
    Nop();
}