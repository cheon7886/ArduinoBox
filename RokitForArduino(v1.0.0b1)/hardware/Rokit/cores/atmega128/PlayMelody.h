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

#ifndef __PLAYMELODY_LIBRARY_H
#define __PLAYMELODY_LIBRARY_H

#if defined(ARDUINO) && ARDUINO >=100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

void PlayMelody(int pin, char *notes, boolean (*af)() = NULL) ;

#endif
