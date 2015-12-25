#ifndef BS40A_H_INCLUDED
#define BS40A_H_INCLUDED

/**
***************************************************************
* For HK Blue Series 40A (not F-40A) -- the same as "bs" but  *
* with flipped AnFET and CnFET pins.                          *
***************************************************************
*/

//*********************
// PORT B definitions *
//*********************
#define DbgLED          5
#define DbgStr          4
#define AnFET           0
#define PORTB_INIT      0
#define PORTB_DD        (1<<AnFET)+(1<<DbgLED)+(1<<DbgStr)

inline void DebugLEDOn()     {PORTB |= _BV(DbgLED);}
inline void DebugLEDOff()    {PORTB &= ~_BV(DbgLED);}
inline void DebugLEDToggle() {PORTB ^= _BV(DbgLED);}

inline void DebugStrOn()     {PORTB |= _BV(DbgStr);}
inline void DebugStrOff()    {PORTB &= ~_BV(DbgStr);}
inline void DebugStrToggle() {PORTB ^= _BV(DbgStr);}

//*********************
// PORT C definitions *
//*********************
#define AnRef           1
#define CpFET           3
#define BnFET           4
#define BpFET           5
#define PORTC_INIT      (1<<AnRef)
#define PORTC_DD        (1<<AnRef)+(1<<CpFET)+(1<<BnFET)+(1<<BpFET)

//*********************
// PORT D definitions *
//*********************
#define c_comp          6
#define CnFET           5
#define ApFET           4
#define rcp_in          2
#define PORTD_INIT      0
#define PORTD_DD        (1<<ApFET)+(1<<CnFET)

inline void ApFETOn()  {PORTD |=  _BV(ApFET);}
inline void ApFETOff() {PORTD &= ~_BV(ApFET);}
inline void AnFETOn()  {PORTB |=  _BV(AnFET);}
inline void AnFETOff() {PORTB &= ~_BV(AnFET);}

inline void BpFETOn()  {PORTC |=  _BV(BpFET);}
inline void BpFETOff() {PORTC &= ~_BV(BpFET);}
inline void BnFETOn()  {PORTC |=  _BV(BnFET);}
inline void BnFETOff() {PORTC &= ~_BV(BnFET);}

inline void CpFETOn()  {PORTC |=  _BV(CpFET);}
inline void CpFETOff() {PORTC &= ~_BV(CpFET);}
inline void CnFETOn()  {PORTD |=  _BV(CnFET);}
inline void CnFETOff() {PORTD &= ~_BV(CnFET);}

#define mux_c           0
#define mux_a           6
#define mux_b           7

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
};

void Board_Idle() {
};

inline void Board_Init() {
  TIMSK = 0;
  // Timer1
  TCCR1A = 0;
  TCCR1B = _BV(CS11);                 /* div 8 clock prescaler */
  PORTB = PORTB_INIT; DDRB = PORTB_DD;
  PORTC = PORTC_INIT; DDRC = PORTC_DD;
  PORTD = PORTD_INIT; DDRD = PORTD_DD;

  ACInit();
}

#endif // BS40A_H_INCLUDED