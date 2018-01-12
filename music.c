// CONFIG1H
#pragma config OSC = INTIO67      // Oscillator Selection bits (HS oscillator)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = ON       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)
//#pragma config BOREN = ON  // Brown-out Reset Enable bit (BOR enabled)
// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 1        // Watchdog Timer Postscale Select bits (1:1)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <pic18f4520.h>
#define _XTAL_FREQ 4000000
//<editor-fold defaultstate="collapsed" desc="馬達">
void module_init() {

    //馬達
    TRISDbits.RD4 = 0;    //output
    TRISDbits.RD5 = 0;
    TRISDbits.RD6 = 0;
    TRISDbits.RD7 = 0;
    PORTDbits.RD4 = 0;
    PORTDbits.RD5 = 0;
    PORTDbits.RD6 = 0;
    PORTDbits.RD7 = 0;
}

void delay(int time) {
    int j;
    for(j = 0; j < time; j++) {
    }
}
//順時針
void clockwise(int time) {
    delay(time);
    PORTDbits.RD4 = 1;
    PORTDbits.RD5 = 0;
    PORTDbits.RD6 = 0;
    PORTDbits.RD7 = 0;
    delay(time);
    PORTDbits.RD4 = 0;
    PORTDbits.RD5 = 1;
    PORTDbits.RD6 = 0;
    PORTDbits.RD7 = 0;
    delay(time);
    PORTDbits.RD4 = 0;
    PORTDbits.RD5 = 0;
    PORTDbits.RD6 = 1;
    PORTDbits.RD7 = 0;
    delay(time);
    PORTDbits.RD4 = 0;
    PORTDbits.RD5 = 0;
    PORTDbits.RD6 = 0;
    PORTDbits.RD7 = 1;
}
//逆時針
void counter_clockwise(int time) {
    delay(time);
    PORTDbits.RD4 = 0;
    PORTDbits.RD5 = 0;
    PORTDbits.RD6 = 0;
    PORTDbits.RD7 = 1;
    delay(time);
    PORTDbits.RD4 = 0;
    PORTDbits.RD5 = 0;
    PORTDbits.RD6 = 1;
    PORTDbits.RD7 = 0;
    delay(time);
    PORTDbits.RD4 = 0;
    PORTDbits.RD5 = 1;
    PORTDbits.RD6 = 0;
    PORTDbits.RD7 = 0;
    delay(time);
    PORTDbits.RD4 = 1;
    PORTDbits.RD5 = 0;
    PORTDbits.RD6 = 0;
    PORTDbits.RD7 = 0;
}
//</editor-fold>
uint8_t send_buf[10] = {
    0x7E, 0xFF, 0x06, 0x00, 00, 00, 0x00, 00, 00, 0xEF};
void usart_init();
void usart_write(uint8_t a);
void send_cmd (uint8_t cmd);
void mp3_send_cmd (uint8_t cmd, uint16_t arg);
void mp3_send_cmd_1 (uint8_t cmd);
void fill_uint16_bigend (uint8_t *thebuf, uint16_t data);
uint16_t mp3_get_checksum (uint8_t *thebuf);
void mp3_fill_checksum ();
void mp3_play (uint16_t num);
void mp3_pause ();
void mp3_consume ();
void mp3_set_volume (uint16_t volume);

//<editor-fold defaultstate="collapsed" desc="MP3 function define">
void send_func () {
	for (int i = 0; i < 10; i++) {
		usart_write(send_buf[i]);
	}
}
void mp3_send_cmd_1 (uint8_t cmd) {
    send_buf[3] = cmd;
    fill_uint16_bigend ((send_buf+5), 0);
    mp3_fill_checksum ();
    send_func ();
}
void mp3_send_cmd (uint8_t cmd, uint16_t arg) {
    send_buf[3] = cmd;
    fill_uint16_bigend ((send_buf+5), arg);
    mp3_fill_checksum ();
    send_func ();
}
void fill_uint16_bigend (uint8_t *thebuf, uint16_t data) {
    *thebuf = (uint8_t)(data>>8);
    *(thebuf+1) = (uint8_t)data;
}
//calc checksum (1~6 byte)
uint16_t mp3_get_checksum (uint8_t *thebuf) {
    uint16_t sum = 0;
    for (int i=1; i<7; i++) {
        sum += thebuf[i];
    }
    return -sum;
}
//fill checksum to send_buf (7~8 byte)
void mp3_fill_checksum () {
    uint16_t checksum = mp3_get_checksum (send_buf);
    fill_uint16_bigend (send_buf+7, checksum);
}
//
void mp3_play (uint16_t num) {
    mp3_send_cmd (0x12,num);
}
void mp3_pause () {
    mp3_send_cmd_1 (0x0e);
}
void mp3_consume () {
    mp3_send_cmd_1 (0x0d);
}
void mp3_set_volume (uint16_t volume){
    mp3_send_cmd (0x06, volume);
}
//</editor-fold>

void usart_init() {
    /*portC pin6/7 is mult with usart setting their tris*/

    TRISCbits.TRISC6 = 1;

    /*
           Serial Setting
     * 1.   Setting Baud rate
     * 2.   choose sync/async mode
     * 3.   enable Serial port (configures RX/DT and TX/CK pins as serial port pins)
     * 3.5  enable Tx, Rx Interrupt(optional)
     * 4.   Enable Tx & RX
     */
    //Setting baud rate = 2400
    TXSTAbits.SYNC = 0;    //choose the async moode
    TXSTAbits.BRGH = 1;    //high speed
    BAUDCONbits.BRG16 = 1;    //8bits
    SPBRG = 25;    //look up table

    //Serial enable
    RCSTAbits.SPEN = 1;    //open serial port
    //setting TX/RX
    TXSTAbits.TXEN = 1;    //Enable Tx
   // RCSTAbits.CREN = 1;    //Enable Rx
    TXSTAbits.TX9 = 0;
  //  TXSTAbits.SENDB = 1;
    TXREG = 0x00;
   // PIE1bits.TXIE = 0;
}

void usart_write(uint8_t a) {

    TXREG = a;         //write to TXREG will send data
    while(!TXSTAbits.TRMT);  //wait until data sent

}

void main() {
    int mode = 0;
    TRISDbits.RD2 = 1;
    usart_init();
    module_init();
    __delay_ms(100);
    mp3_set_volume(15);
    __delay_ms(100);
    mp3_play(1);
    __delay_ms(50);
    mp3_pause();
    __delay_ms(50);

    while(1) {
       delay(3200);
       while(1){
          if(PORTDbits.RD2){
            if(mode) {
                mode = 0;
              mp3_pause();
              __delay_ms(100);
            }
            else {
                mode = 1;
              mp3_consume();
              __delay_ms(100);
            }
        }
        if(mode)
           clockwise(50);
        else
           break;
       }
    }
}
