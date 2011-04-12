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
#include <avr/interrupt.h>
#include <inttypes.h>

#include "main.h"
#include "input/input.h"
#include "output/display_12_10.h"
#include "clock/clock.h"

bitmap_t bitmap = {0,0,0,0,0,0,0,0,0,0};

int main(void)
{

    init();

    while(1) {
        handleKeyInput();

        // XXX: this should only be called if there is actually something new
        printTime(bitmap, THEME_BARS);
        scanout(bitmap);
    }

    return 0;
}

void init() {
    // set i/o pin direction
    DDRB = 0xdf;    // external crystal pins must be 0
    DDRC = 0x0f;
    DDRD = 0xf0;

    initKeys(KEYS);
    initClock();

    sei();
}

inline void handleKeyInput() {
    initKeys(KEYS);
    if(getKeyPressed(KEY0)) {
        switchToNextMode();
    }
}
