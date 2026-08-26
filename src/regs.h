/*
regs.h

This file contains the values for the configuration registers for the MCU.
Please consult the datasheet for register documentation: https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATtiny804-06-07-1604-06-07-DataSheet-DS40002312A.pdf

The MCU is an ATtiny806-S.

Binary format 0b10101010 <-- This is the LSB
*/

/*
AC0 is used to monitor the bus voltage. Output on PA5 is connected to the shutdown pin of the MOSFET gate driver.
*/ 
// 7: Operate in sleep mode.
// 6: Output to pin PA5 enabled.
// 5:4: Interrupt on positive edge.
// 3: Reserved.
// 2:1: 25mV hysteresis.
// 0: AC0 is enabled.
AC0.CTRLA = 0b11110101
// 7: Output is inverted.
// 6:5: Reserved.
// 4:3: AINP1 - PB5 is the bus voltage sense input.
// 2: Reserved.
// 1:0: AINN1 is VREF. 
AC0.MUXCTRLA = 0b10001010
AC0.INTCTRL  = 0x0  // AC0 interrupt is disabled.

/*
LUT0 is used to disable the low side of the boost converter if the bus voltage is too high.
*/
// 7: Edge detector disabled.
// 6: LUT0-TRUTHSEL[2] is the clock source.
// 5:4: Filter is disabled.
// 3: Output to pin PA4 is enabled.
// 2:1: Reserved.
// 0: LUT is enabled.
// LUT0CTRLA = 0b01001001
// LUT0CTRLB = 0x68 // Input 1 is AC0 output. Input 0 is TCA0 WO1
// LUT0CTRLC = 0x0  // Input 2 is masked (unused).
// TRUTH0    = 0b00010000 // The output is TRUE when the input is 0b011

/*
ADC0 
*/
// 7: Run in standby mode.
// 6:3: Reserved.
// 2: 8-bit resolution.
// 1: Freerun disabled.
// 0: ADC0 enabled.
ADC0.CTRLA = 0b10000101
ADC0.CTRLB = 0x3 // 8 results accumulated.
// 7: Reserved.
// 6: Reduced SAMCAP as we're using VREF as the ADC reference.
// 5:4: Using the internal VREF.
// 3: Reserved.
// 2:0: ADC clock is CLK_PER/16.
ADC0.CTRLC = 0b01000011
// 7:5: INITDLY is 64 cycles.
// 4: ASDV is enabled.
// 3:0: Set/updated by ASDV
ADC0.CTRLD = 0b01110000
ADC0.CTRLE = 0x0 // No window comparison.
ADC0.SAMPCTRL = 0x0 // No sample length extension.

// Some parameters are changed per conversion, e.g. for the internal temperature sensor.

/*
USART: This is a LIN client.
*/

/*
TCA: Single-slope PWM for the boost converter.
*/
// 7:4: Reserved
// 3:1: F_TCA = CLK_PER
// 0: TCA is enabled
TCA.CTRLA = 0b00000001
// 7: Reserved
// 2:0: Single-slope PWM
TCA.CTRLB = 0b00010011

// 7:1: Reserved
// 0: Split mode disabled.
TCA.CTRLD = 0b00000000

