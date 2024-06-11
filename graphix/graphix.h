#include "mosapi.h"
#include "mos.h"
#pragma once

char exit_key;

int GraphixExitKey(char key){
    exit_key = key;
}

int GraphixMainLoop(){
    char __c;
    ProcessClearSTDIN();
    while (__c != exit_key)
    {
        read(STDIN_FILENO, &__c, 1);
    }
}

int GraphixInit() {
    SwitchToGraphicMode();
}

int GraphixEnd() {
    GMFillScreen(0x000000);
}

int GraphixDrawRect(int x, int y, int w, int h, unsigned int color) {
    for(int i = x; i < x + w; i++){
        for(int j = y; j < y + h; j++){
            GMPutPixel(i, j, color);
        }
    }
}