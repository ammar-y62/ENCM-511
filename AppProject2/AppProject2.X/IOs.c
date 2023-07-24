/* 
 * File:   IOs.c
 * Author: Ammar Elzeftawy, David Kim, Yaseen ElSherif
 *
 * Created on October 10, 2022, 6:32 PM
 */

#include "xc.h"
#include <p24fxxxx.h>
#include <p24F16KA101.h>
#include "UART2.h"
#include "IOs.h"

extern int button;

void IOinit(void) {
    // Set inputs on RA2, RA4, and RB4
    TRISAbits.TRISA2 = 1; // PB1
    TRISAbits.TRISA4 = 1; // PB2
    TRISBbits.TRISB4 = 1; // PB3
    
    // Set pull up resistors on RA2(CN30), RA4(CN0), and RB4(CN1)
    CNPU1bits.CN0PUE = 1;
    CNPU1bits.CN1PUE = 1;
    CNPU2bits.CN30PUE = 1;

    CNEN1bits.CN0IE = 1;  // enable CN on CN0
    CNEN1bits.CN1IE = 1;  // enable CN on CN1
    CNEN2bits.CN30IE = 1;  // enable CN on CN30
    
    TRISBbits.TRISB15 = 0;  // Set RB15 as output for REFO
    REFOCONbits.ROEN = 1; // Ref oscillator is enabled
    REFOCONbits.ROSSLP = 0; // Ref oscillator is disabled in sleep
    REFOCONbits.ROSEL = 0; // Output base clk showing clock switching
    REFOCONbits.RODIV = 0b0000;
    
    //CN Interrupt settings
    IPC4bits.CNIP = 7; // 7 is highest priority, 1 is lowest, 0 is disabled interrupt
    IFS1bits.CNIF = 0; // Clear interrupt flag
    IEC1bits.CNIE = 1; // Enable CN interrupts
    
    TRISBbits.TRISB8 = 0; // Make GPIO RB8 as a digital output
    
    AD1PCFG = 0xFFFF; // set all analog pins as digital 
}

void IOcheck(void) {
    if(PORTAbits.RA2 == 0 && PORTAbits.RA4 == 1 && PORTBbits.RB4 == 1 ) { // PB1 pressed
        button = 1;
    } 
    else if(PORTAbits.RA2 == 1 && PORTAbits.RA4 == 0 && PORTBbits.RB4 == 1) { // PB2 pressed
        button = 2;
    } 
    else if(PORTAbits.RA2 == 1 && PORTAbits.RA4 == 1 && PORTBbits.RB4 == 0) { // PB3 pressed
        button = 3;
    }
}