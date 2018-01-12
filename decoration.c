#include <xc.h>

#pragma config OSC = INTIO67   // Oscillator Selection bits (HS oscillator)
#pragma config WDT = OFF  // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRT = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON  // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF   // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF   // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)

#define LED00 LATA5
#define LED01 LATA4
#define LED02 LATA3
#define LED03 LATA2
#define LED04 LATA1
#define LED05 LATA0

#define LED10 LATD1
#define LED11 LATD0
#define LED12 LATC3
#define LED13 LATD7
#define LED14 LATC1
#define LED15 LATC0

#define LED20 LATB0
#define LED21 LATB1
#define LED22 LATB2
#define LED23 LATB3
#define LED24 LATB4
#define LED25 LATB5

#define LED30 LATD2
#define LED31 LATD3
#define LED32 LATC4
#define LED33 LATC5
#define LED34 LATC6
#define LED35 LATC7

void module_init() {
    //Timer0
    RCONbits.IPEN = 1;    //啟用interrupt priority
    INTCONbits.GIEH = 1;    //啟用所有high priority interrupt
    INTCONbits.GIEL = 1;    //啟用所有low priority interrupt

    OSCCONbits.IRCF = 0x03;    //內部震盪設為500kHz

    INTCON2bits.TMR0IP = 1;    //開啟TMR0 priority
    INTCONbits.TMR0IF = 0;    //清空TMR0 interrupt flag
    //TMR0設為16bits，Prescale取128
    T0CON = 0x86;    //10 00 0 110
    //500000/4/128 = 976.56Hz
    TMR0 = 59676;    //65535 - 976.56*6 = 59675.6，6s

    //控制
    TRISDbits.RD6 = 1;

    //LED
    TRISAbits.RA0 = 0;
    TRISAbits.RA1 = 0;
    TRISAbits.RA2 = 0;
    TRISAbits.RA3 = 0;
    TRISAbits.RA4 = 0;
    TRISAbits.RA5 = 0;

    TRISCbits.RC0 = 0;
    TRISCbits.RC1 = 0;
    TRISDbits.RD7 = 0;
    TRISCbits.RC3 = 0;
    TRISDbits.RD0 = 0;
    TRISDbits.RD1 = 0;

    TRISDbits.RD2 = 0;
    TRISDbits.RD3 = 0;
    TRISCbits.RC4 = 0;
    TRISCbits.RC5 = 0;
    TRISCbits.RC6 = 0;
    TRISCbits.RC7 = 0;

    TRISBbits.RB0 = 0;
    TRISBbits.RB1 = 0;
    TRISBbits.RB2 = 0;
    TRISBbits.RB3 = 0;
    TRISBbits.RB4 = 0;
    TRISBbits.RB5 = 0;

    LATA = 0;
    LATB = 0;
    LATC = 0;
    LATD = 0;

    //PWM
    //內部震盪500kHz/4 = 125000Hz，距50Hz(20ms)還有2500倍的空間
    //TMR2的Prescale取16、Postscale維持1:1
    T2CON = 0x07; //0 0000 1 11
    //2500/16 = 156.25 = PR2 + 1
    PR2 = 0x9B; //155
    CCP1CONbits.CCP1M = 0x0C;    //1100，P1A~P1D active high
    CCP1CONbits.P1M = 0x00;    //只用P1A，P1B~D當port
    TRISCbits.RC2 = 0;    //P1D作為PWM output
}

void pwm_duty(unsigned int duty) {    //duty會影響角度
    //CCPR1L:DC1B = (PR2 + 1)*4，同除四可以忽略DC1B
    //0.5~2.4ms = (156.25/40)~(156.25/8.33) = 3.91~18.76
    CCPR1L = duty;
    CCP1CONbits.DC1B = 0;
}

void delay(int time) {
    int j;
    for(j = 0; j < time; j++) {
    }
}

//LED
//內圈
//1:全亮
//0:全暗
void loop1(int mode) {
    int i;
    if(mode) {
        LED00 = 1;
        LED01 = 1;
        LED02 = 1;
        LED03 = 1;
        LED04 = 1;
        LED05 = 1;
        LED10 = 1;
        LED11 = 1;
        LED12 = 1;
        LED13 = 1;
        LED14 = 1;
        LED15 = 1;
    }
    else {
        LED00 = 0;
        LED01 = 0;
        LED02 = 0;
        LED03 = 0;
        LED04 = 0;
        LED05 = 0;
        LED10 = 0;
        LED11 = 0;
        LED12 = 0;
        LED13 = 0;
        LED14 = 0;
        LED15 = 0;
    }
}

//外圈
//1:全亮
//0:全暗
void loop2(int mode) {
    int i;
    if(mode) {
        LED20 = 1;
        LED21 = 1;
        LED22 = 1;
        LED23 = 1;
        LED24 = 1;
        LED25 = 1;
        LED30 = 1;
        LED31 = 1;
        LED32 = 1;
        LED33 = 1;
        LED34 = 1;
        LED35 = 1;
    }
    else {
        LED20 = 0;
        LED21 = 0;
        LED22 = 0;
        LED23 = 0;
        LED24 = 0;
        LED25 = 0;
        LED30 = 0;
        LED31 = 0;
        LED32 = 0;
        LED33 = 0;
        LED34 = 0;
        LED35 = 0;
    }
}

//內外圈切換亮
void change(int time) {
    loop1(1);
    loop2(0);
    delay(time);
    loop1(0);
    loop2(1);
    delay(time);
}

//內外圈同時
//0:順時針依序亮
//1:順時針依序亮後依序暗(一半開始)
//2:順時針依序亮(每次亮三個)
//3:順時針依序亮(每次只亮一個)
void circle(int mode, int time) {
    switch(mode) {
        case 0:    //順時針依序亮
            loop1(0);
            loop2(0);
            LED00 = 1;
            LED20 = 1;
            delay(time);
            LED01 = 1;
            LED21 = 1;
            delay(time);
            LED02 = 1;
            LED22 = 1;
            delay(time);
            LED03 = 1;
            LED23 = 1;
            delay(time);
            LED04 = 1;
            LED24 = 1;
            delay(time);
            LED05 = 1;
            LED25 = 1;
            delay(time);
            LED10 = 1;
            LED30 = 1;
            delay(time);
            LED11 = 1;
            LED31 = 1;
            delay(time);
            LED12 = 1;
            LED32 = 1;
            delay(time);
            LED13 = 1;
            LED33 = 1;
            delay(time);
            LED14 = 1;
            LED34 = 1;
            delay(time);
            LED15 = 1;
            LED35 = 1;
            delay(time);
            break;
        case 1:    //順時針依序亮後依序暗(一半開始)
            loop1(0);
            loop2(0);
            LED00 = 1;
            LED20 = 1;
            LED10 = 0;
            LED30 = 0;
            delay(time);
            LED01 = 1;
            LED21 = 1;
            LED11 = 0;
            LED31 = 0;
            delay(time);
            LED02 = 1;
            LED22 = 1;
            LED12 = 0;
            LED32 = 0;
            delay(time);
            LED03 = 1;
            LED23 = 1;
            LED13 = 0;
            LED33 = 0;
            delay(time);
            LED04 = 1;
            LED24 = 1;
            LED14 = 0;
            LED34 = 0;
            delay(time);
            LED05 = 1;
            LED25 = 1;
            LED15 = 0;
            LED35 = 0;
            delay(time);
            LED10 = 1;
            LED30 = 1;
            LED00 = 0;
            LED20 = 0;
            delay(time);
            LED11 = 1;
            LED31 = 1;
            LED01 = 0;
            LED21 = 0;
            delay(time);
            LED12 = 1;
            LED32 = 1;
            LED02 = 0;
            LED22 = 0;
            delay(time);
            LED13 = 1;
            LED33 = 1;
            LED03 = 0;
            LED23 = 0;
            delay(time);
            LED14 = 1;
            LED34 = 1;
            LED04 = 0;
            LED24 = 0;
            delay(time);
            LED15 = 1;
            LED35 = 1;
            LED05 = 0;
            LED25 = 0;
            delay(time);
            break;
        case 2:    //順時針依序亮(每次亮三個)
            loop1(0);
            loop2(0);
            LED00 = 1;
            LED20 = 1;
            LED10 = 0;
            LED30 = 0;
            delay(time);
            LED01 = 1;
            LED21 = 1;
            LED11 = 0;
            LED31 = 0;
            delay(time);
            LED02 = 1;
            LED22 = 1;
            LED12 = 0;
            LED32 = 0;
            delay(time);
            LED03 = 1;
            LED23 = 1;
            LED00 = 0;
            LED20 = 0;
            delay(time);
            LED04 = 1;
            LED24 = 1;
            LED01 = 0;
            LED21 = 0;
            delay(time);
            LED05 = 1;
            LED25 = 1;
            LED02 = 0;
            LED22 = 0;
            delay(time);
            LED10 = 1;
            LED30 = 1;
            LED03 = 0;
            LED23 = 0;
            delay(time);
            LED11 = 1;
            LED31 = 1;
            LED04 = 0;
            LED24 = 0;
            delay(time);
            LED12 = 1;
            LED32 = 1;
            LED05 = 0;
            LED25 = 0;
            delay(time);
            LED13 = 1;
            LED33 = 1;
            LED10 = 0;
            LED30 = 0;
            delay(time);
            LED14 = 1;
            LED34 = 1;
            LED11 = 0;
            LED31 = 0;
            delay(time);
            LED15 = 1;
            LED35 = 1;
            LED12 = 0;
            LED32 = 0;
            delay(time);
            LED13 = 0;
            LED33 = 0;
            delay(time);
            LED14 = 0;
            LED34 = 0;
            delay(time);
            LED15 = 0;
            LED35 = 0;
            break;
        case 3:    //順時針依序亮(每次只亮一個)
            loop1(0);
            loop2(0);
            LED00 = 1;
            LED20 = 1;
            delay(time);
            LED01 = 1;
            LED21 = 1;
            LED00 = 0;
            LED20 = 0;
            delay(time);
            LED02 = 1;
            LED22 = 1;
            LED01 = 0;
            LED21 = 0;
            delay(time);
            LED03 = 1;
            LED23 = 1;
            LED02 = 0;
            LED22 = 0;
            delay(time);
            LED04 = 1;
            LED24 = 1;
            LED03 = 0;
            LED23 = 0;
            delay(time);
            LED05 = 1;
            LED25 = 1;
            LED04 = 0;
            LED24 = 0;
            delay(time);
            LED10 = 1;
            LED30 = 1;
            LED05 = 0;
            LED25 = 0;
            delay(time);
            LED11 = 1;
            LED31 = 1;
            LED10 = 0;
            LED30 = 0;
            delay(time);
            LED12 = 1;
            LED32 = 1;
            LED11 = 0;
            LED31 = 0;
            delay(time);
            LED13 = 1;
            LED33 = 1;
            LED12 = 0;
            LED32 = 0;
            delay(time);
            LED14 = 1;
            LED34 = 1;
            LED13 = 0;
            LED33 = 0;
            delay(time);
            LED15 = 1;
            LED35 = 1;
            LED14 = 0;
            LED34 = 0;
            delay(time);
            LED15 = 0;
            LED35 = 0;
            delay(time);
            break;
    }
}

//兩側同時
//0:兩邊依序亮
//1:兩邊依序亮，順向依序暗
//2:兩邊依序亮，反向依序暗
//3:順時針依序亮(只亮對稱四個)
//4:順時針依序亮(每次亮對稱四個)
//5:間隔的一起亮/暗
//6:分兩區亮/暗
void both(int mode, int time) {
    switch(mode) {
        case 0:    //兩邊依序亮
            loop1(0);
            loop2(0);
            LED00 = 1;
            LED15 = 1;
            LED20 = 1;
            LED35 = 1;
            delay(time);
            LED01 = 1;
            LED14 = 1;
            LED21 = 1;
            LED34 = 1;
            delay(time);
            LED02 = 1;
            LED13 = 1;
            LED22 = 1;
            LED33 = 1;
            delay(time);
            LED03 = 1;
            LED12 = 1;
            LED23 = 1;
            LED32 = 1;
            delay(time);
            LED04 = 1;
            LED11 = 1;
            LED24 = 1;
            LED31 = 1;
            delay(time);
            LED05 = 1;
            LED10 = 1;
            LED25 = 1;
            LED30 = 1;
            delay(time);
            break;
        case 1:    //兩邊依序亮，順向依序暗
            loop1(0);
            loop2(0);
            LED00 = 1;
            LED15 = 1;
            LED20 = 1;
            LED35 = 1;
            delay(time);
            LED01 = 1;
            LED14 = 1;
            LED21 = 1;
            LED34 = 1;
            delay(time);
            LED02 = 1;
            LED13 = 1;
            LED22 = 1;
            LED33 = 1;
            delay(time);
            LED03 = 1;
            LED12 = 1;
            LED23 = 1;
            LED32 = 1;
            delay(time);
            LED04 = 1;
            LED11 = 1;
            LED24 = 1;
            LED31 = 1;
            delay(time);
            LED05 = 1;
            LED10 = 1;
            LED25 = 1;
            LED30 = 1;
            delay(time);
            LED00 = 0;
            LED15 = 0;
            LED20 = 0;
            LED35 = 0;
            delay(time);
            LED01 = 0;
            LED14 = 0;
            LED21 = 0;
            LED34 = 0;
            delay(time);
            LED02 = 0;
            LED13 = 0;
            LED22 = 0;
            LED33 = 0;
            delay(time);
            LED03 = 0;
            LED12 = 0;
            LED23 = 0;
            LED32 = 0;
            delay(time);
            LED04 = 0;
            LED11 = 0;
            LED24 = 0;
            LED31 = 0;
            delay(time);
            LED05 = 0;
            LED10 = 0;
            LED25 = 0;
            LED30 = 0;
            delay(time);
            break;
        case 2:    //兩邊依序亮，反向依序暗
            loop1(0);
            loop2(0);
            LED00 = 1;
            LED15 = 1;
            LED20 = 1;
            LED35 = 1;
            delay(time);
            LED01 = 1;
            LED14 = 1;
            LED21 = 1;
            LED34 = 1;
            delay(time);
            LED02 = 1;
            LED13 = 1;
            LED22 = 1;
            LED33 = 1;
            delay(time);
            LED03 = 1;
            LED12 = 1;
            LED23 = 1;
            LED32 = 1;
            delay(time);
            LED04 = 1;
            LED11 = 1;
            LED24 = 1;
            LED31 = 1;
            delay(time);
            LED05 = 1;
            LED10 = 1;
            LED25 = 1;
            LED30 = 1;
            delay(time);
            LED05 = 0;
            LED10 = 0;
            LED25 = 0;
            LED30 = 0;
            delay(time);
            LED04 = 0;
            LED11 = 0;
            LED24 = 0;
            LED31 = 0;
            delay(time);
            LED03 = 0;
            LED12 = 0;
            LED23 = 0;
            LED32 = 0;
            delay(time);
            LED02 = 0;
            LED13 = 0;
            LED22 = 0;
            LED33 = 0;
            delay(time);
            LED01 = 0;
            LED14 = 0;
            LED21 = 0;
            LED34 = 0;
            delay(time);
            LED00 = 0;
            LED15 = 0;
            LED20 = 0;
            LED35 = 0;
            delay(time);
            break;
        case 3:    //順時針依序亮(只亮對稱四個)
            loop1(0);
            loop2(0);
            LED00 = 1;
            LED03 = 1;
            LED10 = 1;
            LED13 = 1;
            LED20 = 1;
            LED23 = 1;
            LED30 = 1;
            LED33 = 1;
            delay(time);
            loop1(0);
            loop2(0);
            LED01 = 1;
            LED04 = 1;
            LED11 = 1;
            LED14 = 1;
            LED21 = 1;
            LED24 = 1;
            LED31 = 1;
            LED34 = 1;
            delay(time);
            loop1(0);
            loop2(0);
            LED02 = 1;
            LED05 = 1;
            LED12 = 1;
            LED15 = 1;
            LED22 = 1;
            LED25 = 1;
            LED32 = 1;
            LED35 = 1;
            delay(time);
            break;
        case 4:    //順時針依序亮(每次亮對稱四個)
            loop1(0);
            loop2(0);
            LED00 = 1;
            LED03 = 1;
            LED10 = 1;
            LED13 = 1;
            LED20 = 1;
            LED23 = 1;
            LED30 = 1;
            LED33 = 1;
            delay(time);
            LED01 = 1;
            LED04 = 1;
            LED11 = 1;
            LED14 = 1;
            LED21 = 1;
            LED24 = 1;
            LED31 = 1;
            LED34 = 1;
            delay(time);
            LED02 = 1;
            LED05 = 1;
            LED12 = 1;
            LED15 = 1;
            LED22 = 1;
            LED25 = 1;
            LED32 = 1;
            LED35 = 1;
            delay(time);
            break;
        case 5:    //間隔的一起亮/暗
            loop1(0);
            loop2(0);
            LED00 = 1;
            LED02 = 1;
            LED04 = 1;
            LED10 = 1;
            LED12 = 1;
            LED14 = 1;
            LED20 = 1;
            LED22 = 1;
            LED24 = 1;
            LED30 = 1;
            LED32 = 1;
            LED34 = 1;
            delay(time);
            loop1(0);
            loop2(0);
            LED01 = 1;
            LED03 = 1;
            LED05 = 1;
            LED11 = 1;
            LED13 = 1;
            LED15 = 1;
            LED21 = 1;
            LED23 = 1;
            LED25 = 1;
            LED31 = 1;
            LED33 = 1;
            LED35 = 1;
            delay(time);
            break;
        case 6:    //分兩區亮/暗
            loop1(0);
            loop2(0);
            LED00 = 1;
            LED01 = 1;
            LED02 = 1;
            LED15 = 1;
            LED14 = 1;
            LED13 = 1;
            LED20 = 1;
            LED21 = 1;
            LED22 = 1;
            LED35 = 1;
            LED34 = 1;
            LED33 = 1;
            delay(time);
            loop1(0);
            loop2(0);
            LED03 = 1;
            LED04 = 1;
            LED05 = 1;
            LED12 = 1;
            LED11 = 1;
            LED10 = 1;
            LED23 = 1;
            LED24 = 1;
            LED25 = 1;
            LED32 = 1;
            LED31 = 1;
            LED30 = 1;
            delay(time);
    }
}

//15s
void part1() {
    circle(0, 2500);
    change(1700);
    change(1700);
    change(1700);
    both(3, 2000);
    both(4, 2000);
    both(1, 1500);
    both(2, 1500);
    both(1, 1500);
    both(2, 1500);
}
//11s
void part2() {
    both(5, 2000);
    both(5, 2000);
    both(5, 2000);
    both(5, 2000);
    change(2000);
    both(1, 1700);
    change(2000);
    change(2000);

    both(5, 2000);
    both(5, 2000);
    both(5, 2000);
    both(5, 2000);
    change(2000);
    both(1, 1700);
    change(2000);
    change(2000);
}
//13s
void part3() {
    both(3, 2000);
    both(4, 2000);
    both(3, 2000);
    both(4, 2000);
    both(6, 2000);
    both(6, 2000);

    both(3, 2000);
    both(4, 2000);
    both(3, 2000);
    both(4, 2000);
    both(0, 2000);
    both(6, 2000);
    change(2000);
    circle(2, 2600);
}
//23s
void refrain() {
    both(5, 2500);
    both(5, 2500);
    both(5, 2500);
    both(0, 2000);
    both(4, 3000);
    change(2000);
    change(2000);
    change(2000);

    both(5, 2500);
    both(5, 2500);
    both(5, 2500);
    both(5, 2500);
    both(0, 2000);
    both(4, 3000);
    both(6, 2000);
    both(6, 2000);
    both(6, 2000);

    circle(3, 1500);
    circle(1, 2000);
    circle(3, 1500);
    circle(1, 2000);
    change(2000);
    both(4, 2000);
    change(2000);
}
//6s
void part4() {
    both(1, 1500);
    both(2, 1500);
    change(2000);
    change(2000);
    change(2000);
}

int mode = 0;
void main() {
    module_init();
    while(1) {
        if(PORTDbits.RD6) {
            INTCONbits.TMR0IE = 1;
            part1();
            part2();
            part3();
            refrain();
            part4();
            part2();
            part3();
            refrain();
        }
    }
}

int count = 0;
void interrupt check(void) {    //觸發TMR0 overflow interrupt
    count++;
    if(count >= 4) {    //搖擺2次
        pwm_duty(9);
        delay(500);
        pwm_duty(14);
        delay(500);
        pwm_duty(9);
        delay(500);
        pwm_duty(14);
        count = 0;
    }
    else {
        pwm_duty(9);
        delay(500);
        pwm_duty(14);
    }
    INTCONbits.TMR0IF = 0;    //清空TMR0 interrupt flag
    TMR0 = 59676;    //6s
}
