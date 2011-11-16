.macro ACMultiplexed
  cbi     ADCSRA, ADEN          ; disable ADC
  in      temp1, SFIOR
  sbr     temp1, (1<<ACME)      ; switch to comparator multiplexed
  out     SFIOR, temp1
.endmacro  

.macro ACNormal
   cbr  temp1, (1<<ACME)        ; set to AN1
   out  SFIOR, temp1
   sbi  ADCSRA, ADEN            ; enable ADC
.endmacro  

.macro ACChannel 
   ldi   temp1, @0              
   out   ADMUX, temp1
.endmacro  
   
#define RPM_TO_COMM_TIME(x) (1000000 * 10 / x)
#define PWR_PCT_TO_VAL(x)   (x*POWER_RANGE/100)

#define PWR_CURVE_POINT(pt, rpm, pwr) \
.equ    RPM_RUN_RANGE_ ## pt  = rpm\
.equ    PCT_PWR_MAX_RPM_ ## pt = pwr


/*
.macro PwmCSEnter
                ldi     temp1, (1<<OCIE1A)+(1<<TOIE1) ; stop timer0 interrupt
                out     TIMSK, temp1                  ;  .. only ONE should change these values at the time
                nop
.endm

.macro PwmCSLeave
                ldi     temp1, (1<<TOIE1)+(1<<OCIE1A)+(1<<TOIE0) ; let timer0 do his work again
                out     TIMSK, temp1 
.endm
*/

.macro PwmCSEnter
                cli
.endm

.macro PwmCSLeave
                sei
.endm

.equ    T1STOP           = 0x00
.equ    T1CK8            = 0x02


.macro WaitForEvent
loop:
                in      tifr_shadow, TIFR
                sbrc    tifr_shadow, OCF1B
                rjmp    loop
                cli
                in      TCNT1L_shadow, TCNT1L
                in      TCNT1H_shadow, TCNT1H
                sei
.endm

.macro SetEvent
                add     @0, TCNT1L_shadow
                adc     @1, TCNT1H_shadow
                cli
                out     OCR1BH, @0
                out     OCR1BL, @1
                sei
                push    temp1
                ldi     temp1, (1<<OCF1B)
                out     TIFR, temp1
                pop     temp1
.endm

.macro CheckEvent
                clc
                in      tifr_shadow, TIFR
                sbrs    tifr_shadow, OCF1B
                rjmp    exit
                cli
                in      TCNT1L_shadow, TCNT1L
                in      TCNT1H_shadow, TCNT1H
                sei
                sec
exit:                
.endm
