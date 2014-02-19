/*
  PlayMelody.cpp : Play melody library for Arduino & Wiring.
  Copyright (c) 2011 Sookmook,  All right reserved.

  Created : 2011/08/31 (Ver. 1.00)

  This library is public domain.
  You can use this library for Non-Commercial purpose.
  If you modify source, or use for commercial purpose, or ask anything
  about this library, you have to contact me.

  My e-Mail address : sookmook@naver.com

  Description :

    The functions of this library similar to statement playing MML of
    BASIC language. MML(Music Macro Language) is a music description
    language used in sequencing music on GW-BASIC, MSX-BASIC or some
    of video game system platforms.

  Syntax :

    PlayMelody(pin, notes)
    PlayMelody(pin, notes, af)

  Parameters :

    pin : the pin on which to play melody.
    notes : the string that includes note charaters. (See below...)
      C : Do
      D : Re
      E : Mi
      F : Fa
      G : Sol
      A : Ra
      B : Si
      #, + : Sharp the note.
      $, - : Flat the note.
      R, P : Rest note.
      > : Step up one octave.
      < : Step down one octave.
      O : Followed by a number, select octave. (Default is 4.)
      T : Followed by a number, specifies the tempo.
          How many eighth notes per a minute. (Default is 120.)
      L : Followed by a number, specifies the default length used by
          notes or rests which do not explicitly define one.
          (Default is 4.)
      . : 1.5 times specified length
    af : The function pointer that allow play melody.
         If return value of the function is false, not play melody more.
         The function is called during play melody. (Each note charaters.)

  For examples :

    PlayMelody(9, "CDEFGAB>C<L16CDE") ;
    PlayMelody(11, "CDE2C4.EG16CD8EC8EG.", AllowFunc) ;
*/

#include "PlayMelody.h"

/*
#define DEBUG 1
*/

static int _tempO = 120 ;
static int _lengtH = 4 ;
static int _octavE = 4 ;
static char *_notEpointeR ;

static const char _notEchaR[19] = "CDEFGAB#+$-RP><OTL" ;
static const char _notEindeX[7] = {1, 3, 5, 6, 8, 10, 12} ;
static const float _notEratE[14] = {
  0.561,
  0.595, 0.630,
  0.668, 0.707,
  0.750,
  0.793, 0.841,
  0.891, 0.943,
  1.000, 1.059,
  1.123,
  1.189
} ;

static int _tOnumbeR(void)
{
  int n, ret = 0 ;

  while ((n = *_notEpointeR) != '\0') {
    if ((n >= '0') && (n <= '9')) {
      ret = ret * 10 + (n - '0') ;
      _notEpointeR++ ;
    } else break ;
  }
  return ret ;
}

static char _wherEnotEchaR(const char nc)
{
  char c ;

  for (c = 0; c < sizeof(_notEchaR); c++)
    if (nc == _notEchaR[c]) return c ;
  return 99 ;
}

void PlayMelody(int pin, char *notes, boolean (*af)())
{
  char nc, w ;
  int n, t, l ;

  pinMode(pin, OUTPUT) ;
  _notEpointeR = notes ;

  while ((nc = *_notEpointeR++) != '\0') {
    if ((af != NULL) && (af() == false)) return ;
    t = l = 0 ;
    if ((nc >= 'a') && (nc <= 'z')) nc -= 32 ;
#ifdef DEBUG
    Serial.print(_tempO, DEC) ;
    Serial.print(", ") ;
    Serial.print(_octavE, DEC) ;
    Serial.print(", ") ;
    Serial.print(nc, BYTE) ;
    Serial.print(", ") ;
#endif
    w = _wherEnotEchaR(nc) ;
    if (w < 7) {
      nc = _notEindeX[w] ;
      w = _wherEnotEchaR(*_notEpointeR) ;
      if ((w == 7) || (w == 8)) {
        _notEpointeR++ ;
        nc++ ;
      }
      if ((w == 9) || (w == 10)) {
        _notEpointeR++ ;
        nc-- ;
      }
      t = _notEratE[nc] * (55 << (_octavE - 1)) ;
      w = 99 ;
      tone(pin, t) ;
    }
    n = _tOnumbeR() ;
    if ((t > 0) || (w == 11) || (w == 12)) {
      if (w == 11) noTone(pin) ;
      if (n == 0) n = _lengtH ;
      l = 12000 / _tempO * 40 / n ;
      if (*_notEpointeR == '.') {
        _notEpointeR++ ;
        l *= 1.5 ;
      }
    }
    if ((w == 13) && (_octavE < 8)) _octavE++ ;
    if ((w == 14) && (_octavE > 1)) _octavE-- ;
    if ((w == 15) && (n >= 1) && (n <= 8)) _octavE = n ;
    if ((w == 16) && (n >= 1) && (n <= 512)) _tempO = n ;
    if ((w == 17) && (n >= 1) && (n <= 128)) _lengtH = n ;
#ifdef DEBUG
    Serial.print(t, DEC) ;
    Serial.print(", ") ;
    Serial.println(l, DEC) ;
#endif
    if (l > 0) delay(l) ;
    noTone(pin) ;
  }
}
