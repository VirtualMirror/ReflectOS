#include "io/io.h"
#include "io/keyboard.h"
#include "graphics/graphics.h"


#define WIDTH 100
#define HEIGHT 100


unsigned char ch;
unsigned char action;
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

/**
 * @brief Once a key is pressed
 * @param action
 */
void key_pressed(action) {
/**
 * Skip the first 31 since they are actions
 * 33 - 64 are special characters and numbers (i.e !@#$1234)
 * 65 - 90 are uppercase letters (i.e XYZ)
 * 91 - 96 are, once again, special characters (i.e [\]^_`)
 * 97 - 122 are lowercase letters (i.e xyz)
 * 123 - 165 are, once again, special characters (i.e {|}~)
 * 166 - 223 are special symbols (i.e ªº¿⌐)
 */
    if ((ch = check_key())) {
        if (action == "print") {
            switch (ch) {
                case ' ':
                    draw_char(' ', WIDTH + offset, HEIGHT + offset, 0x0f, 1);
                case '!':
                    draw_char('!', WIDTH + offset, HEIGHT + offset, 0x0f, 1);
                case '"':
                    draw_char('"', WIDTH + offset, HEIGHT + offset, 0x0f, 1);
                case '#':
                    draw_char('#', WIDTH + offset, HEIGHT + offset, 0x0f, 1);
                case '$':
                    draw_char('$', WIDTH + offset, HEIGHT + offset, 0x0f, 1);
                case '%':
                    draw_char('%', WIDTH + offset, HEIGHT + offset, 0x0f, 1);
                case '&':
                    draw_char('&', WIDTH + offset, HEIGHT + offset, 0x0f, 1);
                case '(':
                    draw_char('(', WIDTH + offset, HEIGHT + offset, 0x0f, 1);
                case ')':
                    draw_char(')', WIDTH + offset, HEIGHT + offset, 0x0f, 1);
                case '*':
                    draw_char('*', WIDTH + offset, HEIGHT + offset, 0x0f, 1);
                case '+':
                    draw_char('+', WIDTH + offset, HEIGHT + offset, 0x0f, 1);
                case ',':
                    draw_char(',', WIDTH + offset, HEIGHT + offset, 0x0f, 1);
                case '-':
                    draw_char('-', WIDTH + offset, HEIGHT + offset, 0x0f, 1);
                case '.':
                    draw_char('.', WIDTH + offset, HEIGHT + offset, 0x0f, 1);
                case '/':
                    draw_char('/', WIDTH + offset, HEIGHT + offset, 0x0f, 1);
                case 'w':
                    draw_char('w', WIDTH + offset, HEIGHT + offset, 0x0f, 1);
                case 'a':
                    draw_char('a', WIDTH + offset, HEIGHT + offset, 0x0f, 1);
                case 's':
                    draw_char('s', WIDTH + offset, HEIGHT + offset, 0x0f, 1);
                case 'd':
                    draw_char('d', WIDTH + offset, HEIGHT + offset, 0x0f, 1);
                default:
                    return;
            }
        }
        offset++;
    }
}