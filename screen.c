#include "screen.h"

void screen_init() {
    video = 0xB8000;
    nextTextPos = 0;
    currLine = 0;
}

void print(char *str) {
	int currCharLocationInVidMem, currColorLocationInVidMem;
	
	while (*str != '\0') {
		currCharLocationInVidMem = nextTextPos * 2;
		currColorLocationInVidMem = currCharLocationInVidMem + 1;
		
		video[currCharLocationInVidMem] = *str;
		video[currColorLocationInVidMem] = 15;
		
		++nextTextPos;
		++str;
	}
}

void println() { nextTextPos = ++currLine * 80; }

void printi(int num) {
    char* digitToStr[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

    if (num >= 0 && num <= 9) {
        print(digitToStr[num]);
        return;
    }
    else {
        int remaining = num % 10;
        num /= 10;

        printi(num);
        print(digitToStr[remaining]);
    }
}
