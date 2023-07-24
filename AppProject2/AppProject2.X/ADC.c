/*
 * File:   ADC.c
 * Author: Ammar Elzeftawy, David Kim, Yaseen ElSherif
 *
 * Created on November 14, 2022, 3:19 PM
 */

#include <p24F16KA101.h>
#include "xc.h"
#include "UART2.h"

uint16_t do_ADC(void) {
    uint16_t ADCvalue;
/* -------------ADC INITIALIZATION ------------------*/
    // AD1CON1
    AD1CON1bits.ADON = 1; // Powers the ADC module on
    AD1CON1bits.FORM = 0b00; // Set data output format bits as ints
    AD1CON1bits.SSRC = 0b111; // for SW triggered ADC conversion
    AD1CON1bits.ASAM = 0; // Sampling begins when the SAMP bit is set4
    AD1CON1bits.DONE = 0; // AD conversion is not done
    AD1CON2bits.VCFG = 0b0000; // select AVDD as VR+ and AVSS as Vref
    AD1CON2bits.CSCNA = 0; // do not scan inputs
    AD1CON2bits.SMPI = 0b000; //only if interrupts are used
    AD1CON2bits.BUFM = 0; // buffer configured as one 16-word buffer
    AD1CON2bits.ALTS = 0; // always uses MUX A input multiplexer settings
    AD1CON3bits.ADRC = 0; // ADC use in sleep mode
    AD1CON3bits.SAMC = 0b11111; // sample time bits for X
    AD1CON3bits.ADCS = 0b11111; // select bits for Y
    AD1CHSbits.CH0NA = 0; // channel 0 negative input is VR-
    AD1CHSbits.CH0SA = 0b0101; // channel 0 positive input is AN5
    AD1PCFG = 0x0000; // Pins configured in analog mode; I/O port read disabled; A/D samples pin voltage
    AD1CSSL = 0x0000; // Analog channel omitted from input scan
    
/* -------------ADC SAMPLING AND CONVERSION ------------------*/
    
    AD1CON1bits.SAMP = 1; // A/D sample/hold amplifier is sampling input
    while(AD1CON1bits.DONE == 0){}
    ADCvalue = ADC1BUF0;
    AD1CON1bits.SAMP = 0; // A/D sample/hold amplifier is holding
    AD1CON1bits.ADON = 0; // AD Converter is off
    AD1PCFG = 0xFFFF; // Set pins back to digital mode
    return ADCvalue;
}

void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void)
{
    IFS0bits.AD1IF = 0; // Clear the interrupt flags
    return;
}