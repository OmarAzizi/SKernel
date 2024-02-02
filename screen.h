#ifndef SCREEN_H
#define SCREEN_H

volatile unsigned char* video;

int nextTextPos;
int currLine;

void screen_init(); // will be called by kernel once it starts running
void print(char*);
void println();
void printi(int);

#endif
