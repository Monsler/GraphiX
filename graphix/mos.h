#pragma once

typedef unsigned int pixel_t;

int TerminalSetTextColor(unsigned int color){
    asm volatile("movl %0, %%ebx" : : "a"(color));
    asm volatile(   
        "movl $81001, %eax\n"
        "int $0x80\n"
    );
}

int TerminalSetTextBgColor(unsigned int color){
    asm volatile("movl %0, %%ebx" : : "a"(color));
    asm volatile(   
        "movl $81002, %eax\n"
        "int $0x80\n"
    );
}

int TerminalSetTextSpacing(unsigned int spacing){
    asm volatile("movl %0, %%ebx" : : "a"(spacing));
    asm volatile(   
        "movl $81003, %eax\n"
        "int $0x80\n"
    );
}

int TerminalGetTextAreaSize(unsigned int *w, unsigned int *h){
    int ret;
    asm volatile("int $0x80" : "=b"(*w), "=c"(*h) : "a"(81004));
}

int TerminalSetTextCursor(unsigned int x, unsigned int y){
    int ret;
    asm volatile("int $0x80" : : "b"(x), "c"(y), "a"(81005));
}

int SwitchToGraphicMode(void){
    int ret;
    asm volatile("int $0x80" : "=b"(ret) : "a"(80500));
}

int GMFillScreen(unsigned int color){
    int ret;
    asm volatile("int $0x80" : "=b"(ret) : "a"(80501), "b"(color));
}

int GMPutPixel(unsigned int x, unsigned int y, pixel_t color){
    int ret;
    asm volatile("int $0x80" : "=b"(ret) : "a"(80502), "b"(x), "c"(y), "d"(color));
}

int GMGetScreenSize(unsigned int *width, unsigned int *height, unsigned int screen){
    int ret;
    asm volatile("int $0x80" : "=b"(*width), "=c"(*height) : "a"(80504), "b"(screen));
}

int GMDrawBuffer(unsigned int x, unsigned int y, unsigned int w, unsigned int h, pixel_t* buff){
    int ret;
    asm volatile("movl %0, %%esi" : : "a"(h));
    asm volatile("movl %0, %%edi" : : "a"(buff));
    asm volatile("int $0x80" : "=b"(ret) : "a"(80505), "b"(x), "c"(y), "d"(w));
}