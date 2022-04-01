#include "io.h"
#include "graphics.h"


#define WIDTH 100
#define HEIGHT 100


unsigned char ch;
unsigned int offset = 0;


/**
 * @brief Key Handler - check if key is pressed
 * @returns ch
 * Ex: while (!getUart()); // Wait for keypress to start game
 */
unsigned char check_key() {
    ch = 0;
    if (uart_is_read_byte_ready()) ch = uart_read_byte();
    return ch;
}


void key_pressed() {
    if ((ch = check_key())) {
        // Skip the first 31 since they are actions
            // 33 - 64 are special characters and numbers (i.e !@#$1234)
            // 65 - 90 are uppercase letters (i.e XYZ)
            // 91 - 96 are, once again, special characters (i.e [\]^_`)
            // 97 - 122 are lowercase letters (i.e xyz)
            // 123 - 165 are, once again, special characters (i.e {|}~)
            // 166 - 223 are special symbols (i.e ªº¿⌐)
            switch (ch) {
                case ' ': draw_char(' ', WIDTH + offset, HEIGHT + offset,  0x0f, 1);
                case '!': draw_char('!', WIDTH + offset, HEIGHT + offset,  0x0f, 1);
                case '"': draw_char('"', WIDTH + offset, HEIGHT + offset,  0x0f, 1);
                case '#': draw_char('#', WIDTH + offset, HEIGHT + offset,  0x0f, 1);
                case '$': draw_char('$', WIDTH + offset, HEIGHT + offset,  0x0f, 1);
                case '%': draw_char('%', WIDTH + offset, HEIGHT + offset,  0x0f, 1);
                case '&': draw_char('&', WIDTH + offset, HEIGHT + offset,  0x0f, 1);
                case '(': draw_char('(', WIDTH + offset, HEIGHT + offset,  0x0f, 1);
                case ')': draw_char(')', WIDTH + offset, HEIGHT + offset,  0x0f, 1);
                case '*': draw_char('*', WIDTH + offset, HEIGHT + offset,  0x0f, 1);
                case '+': draw_char('+', WIDTH + offset, HEIGHT + offset,  0x0f, 1);
                case ',': draw_char(',', WIDTH + offset, HEIGHT + offset,  0x0f, 1);
                case '-': draw_char('-', WIDTH + offset, HEIGHT + offset,  0x0f, 1);
                case '.': draw_char('.', WIDTH + offset, HEIGHT + offset,  0x0f, 1);
                case '/': draw_char('/', WIDTH + offset, HEIGHT + offset,  0x0f, 1);
                default: return;
            }
        }

        offset++;
    }