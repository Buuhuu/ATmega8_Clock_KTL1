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

#include <inttypes.h>

#include "clock.h"

#define SET_MODE_NONE       1
#define SET_MODE_HOUR       2
#define SET_MODE_MINUTES    3
#define SET_MODE_SECONDS    4


uint8_t seconds = 0, minutes = 0, hours = 0;
uint8_t setMode = SET_MODE_NONE;

void increaseTime() {

    if(seconds < 59) {
        seconds += 1;
    } else if(minutes < 59) {
        minutes += 1;
        seconds = 0;
    } else if(hours < 23) {
        hours += 1;
        minutes = 0;
        seconds = 0;
    } else {
        hours = 0;
        minutes = 0;
        seconds = 0;
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
        case SET_MODE_HOUR: setMode = SET_MODE_MINUTES; break;
        case SET_MODE_MINUTES: setMode = SET_MODE_SECONDS; break;
        case SET_MODE_SECONDS: setMode = SET_MODE_NONE; break;
        case SET_MODE_NONE: setMode = SET_MODE_HOUR; break;
        //default setMode = SET_MODE_NONE;
    }
}

void printTime(uint16_t* destination) {

    destination[1] = hours;
    destination[3] = minutes;
    destination[5] = seconds;

    destination[9] = setMode;

    return;
}
