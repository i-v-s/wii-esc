/**
********************************************
* Keda 12A with all FETs on PORTD          *
* Original fuses are unknown.              *
* On birdie they are lfuse:0xbf hfuse:0xc1 *
********************************************
*/

#ifndef MKBLCTL20_H_INCLUDED
#define MKBLCTL20_H_INCLUDED


//*********************
// PORT B definitions *
//*********************
#define DbgStr          4

#define PORTB_INIT      0
#define PORTB_DD       _BV(DbgLED) | _BV(DbgStr)

inline void DebugStrOn()     {PORTB |= _BV(DbgStr);}
inline void DebugStrOff()    {PORTB &= ~_BV(DbgStr);}
inline void DebugStrToggle() {PORTB ^= _BV(DbgStr);}

//*********************
// PORT C definitions *
//*********************
#define PORTC_INIT      0
#define PORTC_DD        0

//*********************
// PORT D definitions *
//*********************

#define DbgLED          7

inline void DebugLEDOn()     {PORTD |= _BV(DbgLED);}
inline void DebugLEDOff()    {PORTD &= ~_BV(DbgLED);}
inline void DebugLEDToggle() {PORTD ^= _BV(DbgLED);}


#define BpFET           2
#define CpFET           2
#define ApFET           3
#define CnFET           5
#define rcp_in          2
#define AnFET           3
#define BnFET           4

#define PORTD_INIT      0
#define PORTD_DD        /*(1<<ApFET)+(1<<BpFET)+*/(1<<CpFET)+(1<<AnFET)+(1<<BnFET)+(1<<CnFET)

inline void ApFETOn()  {PORTB |=  _BV(ApFET);}
inline void ApFETOff() {PORTB &= ~_BV(ApFET);}
inline void AnFETOn()  {PORTD |=  _BV(AnFET);}
inline void AnFETOff() {PORTD &= ~_BV(AnFET);}

inline void BpFETOn()  {PORTB |=  _BV(BpFET);}
inline void BpFETOff() {PORTB &= ~_BV(BpFET);}
inline void BnFETOn()  {PORTD |=  _BV(BnFET);}
inline void BnFETOff() {PORTD &= ~_BV(BnFET);}

inline void CpFETOn()  {PORTD |=  _BV(CpFET);}
inline void CpFETOff() {PORTD &= ~_BV(CpFET);}
inline void CnFETOn()  {PORTD |=  _BV(CnFET);}
inline void CnFETOff() {PORTD &= ~_BV(CnFET);}

#define mux_a           0
#define mux_b           1
#define mux_c           2

inline void ACInit() {
  ACMultiplexed();
}

inline void ACPhaseA() {
  ACChannel(mux_a);
}

inline void ACPhaseB() {
   ACChannel(mux_b);
}

inline void ACPhaseC() {
   ACChannel(mux_c);
}

void Board_Idle() {
};

inline void Board_Init() {
  TIMSK1 = 0;
  // Timer1
  TCCR1A = 0;
  TCCR1B = _BV(CS11);                 /* div 8 clock prescaler */
  PORTB = PORTB_INIT; DDRB = PORTB_DD;
  PORTC = PORTC_INIT; DDRC = PORTC_DD;
  PORTD = PORTD_INIT; DDRD = PORTD_DD;

  ACInit();
}

#endif //  MKBLCTL20_H_INCLUDED
