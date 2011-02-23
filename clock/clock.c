/*
Copyright (C) 2011  Dirk Rudolph, Lucas Stach, Paul Ritter

Dieses Programm ist freie Software. Sie können es unter den Bedingungen der GNU
General Public License Version 2, wie von der Free Software Foundation veröffentlicht,
weitergeben und/oder modifizieren.

Die Veröffentlichung dieses Programms erfolgt in der Hoffnung, daß es Ihnen von Nutzen
sein wird, aber OHNE IRGENDEINE GARANTIE, sogar ohne die implizite Garantie der
MARKTREIFE oder der VERWENDBARKEIT FÜR EINEN BESTIMMTEN ZWECK. Details finden Sie in
der GNU General Public License.

Sie sollten ein Exemplar der GNU General Public License zusammen mit diesem Programm
erhalten haben. Falls nicht, schreiben Sie an die Free Software Foundation, Inc., 51
Franklin St, Fifth Floor, Boston, MA 02110, USA.
*/

#include <avr/io.h>
#include <inttypes.h>

#include "../output/display_12_10.h"
#include "clock.h"
#include "themes_12_10/simpleBinary.h"
#include "themes_12_10/raisingBars.h"
#include "themes_12_10/analogClock.h"
#include "themes_12_10/dices.h"

uint8_t seconds = 0, minutes = 0, hours = 0;
uint8_t setMode = SET_MODE_NONE;

void increaseTime() {

    switch(setMode) {
        case SET_MODE_NONE:
        case SET_MODE_SECONDS:
            seconds ++;
            break;
        case SET_MODE_MINUTES:
            minutes ++;
            break;
        case SET_MODE_HOUR:
            hours ++;
            break;
    }


    if(seconds == 60) {
        minutes ++;
        seconds = 0;
    }

    if(minutes == 60) {
        hours ++;
        minutes = 0;
    }

    if(hours == 24) {
        hours = 0;
    }

    return;
}

void resetTime() {
    hours = 0;
    minutes = 0;
    seconds = 0;
}

void nextSetMode() {
    switch(setMode) {
        case SET_MODE_HOUR:
            setMode = SET_MODE_MINUTES;
            break;
        case SET_MODE_MINUTES:
            setMode = SET_MODE_SECONDS;
            break;
        case SET_MODE_SECONDS:
            setMode = SET_MODE_NONE;
            startTimer();
            break;
        case SET_MODE_NONE:
            setMode = SET_MODE_HOUR;
            stopTimer();
            break;
        //default setMode = SET_MODE_NONE;
    }
}

void printTime(bitmap_t destination) {

    //simpleBinary(destination, hours, minutes, seconds, setMode);
    raisingBars(destination, hours, minutes, seconds, setMode);
    //analogClock(destination, hours, minutes, seconds, setMode);
    //dices(destination, hours, minutes, seconds, setMode);

    return;
}

inline void startTimer() {
    // Timer1 (16Bit) CPU-Takt/1024
    // http://www.info-rlp.de/lernteams/eli05/abschnitt_3_mikrocontroller/problemloesung_2/timer.htm
    TCNT1 = 0;
    TCCR1B |= (1 << CS12) | (1 << CS10);
}

inline void stopTimer() {
    // Stop Timer0
    TCCR1B &= ~((1 << CS12) | (1 << CS10));
}
