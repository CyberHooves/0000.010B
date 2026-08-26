/* 
Firmware for HR 0000.010B
Copyright Taiyo Rawle 2026
Released under the GNU GPL v2.0, or at your option, any later version as released by the FSF.

TODO: akchually write it. 

*/

// The MCU is an ATTINY806-S

// Error codes:
#define E_BUS_VOLTS_HIGH 0x01
#define E_TEMP_HIGH      0x02

// Constants:
// #define BUS_VOLTS_MIN 0x00 // Not applicable - the PV input will diode-OR with the DC bus via the body diode of Q1
#define BUS_VOLTS_MAX  0x00 // 56V maximum DC bus voltage. Note that AC1 disables the converter at 64V in case of DC bus disconnection.
#define TEMP_MAX       0x00 // 70&deg;C maximum board temperature
#define P_MAX          0x00 // Maximum power, because somebody will connect a megawatt of panels to a 250W converter.
#define PV_VOLTS_MIN   0x00 // Minimum PV voltage - 

// ADC multiplexer addresses
#define ADC_PVI 0x06  // PV current is on PA6/Pin 4/AIN6
#define ADC_PVV 0x08  // PV voltage is on PB5/Pin 6/AIN8
#define ADC_VB  0x07  // DC bus voltage is on PA7/Pin 5/AIN7

/* 
PWM stuff:
Feed the TCA counter directly from 20MHz CLK_PER with no prescaler, for a ~78kHz switching frequency at 8-bit resolution.
*/

// Measure stuff.
int adc_get( int mux, int *result ){
  return(0);  
}


// Disable converter if the DC bus voltage is too high.
int update_pwm(){
  if( bus_v > BUS_VOLTS_MAX ){
    set_dc(0);
    return( E_BUS_VOLTS_HIGH );
  }
  if( temp > TEMP_MAX ){
    set_dc(0);
    return( E_TEMP_HIGH );
  }

  pv_p = pv_v * pv_i;

  if( pv_p < pv_p_old || pv_p > P_MAX );
    dc_step = -dc_step;
  }
  set_dc( dc += dc_step );
  pv_p_old = pv_p;

  return(0);
}

int main(){
  while(1){
    adc_get( ADC_PVI, *pv_i );
    adc_get( ADC_PVV, *pv_v );
    adc_get( ADC_VB, *bus_v );
    status = update_pwm();
  }
  return(0);
}
