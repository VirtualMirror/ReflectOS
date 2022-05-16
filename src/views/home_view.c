#include "views/home_view.h"
#include "graphics/graphics.h"
#include "structures/message_list.h"


#define WIDTH 1920
#define HEIGHT 1080
#define CHAR_MULTIPLIER 0x30


int init_clock_flag = 0;
int time = 0;

unsigned int oneth;
unsigned int tenth;
unsigned int hundredth;
unsigned int thousandth;


struct MNode messages[10];


void init_clock();
void update_clock();
void init_nodes();
void print_notes();


/**
 * @brief Functie voor het opzetten van het start scherm
 * 
 */
void home_screen_init()
{
    init_clock_flag = 0;
    clear_screen(0x00);
    init_clock();
    draw_string(1000, 400, "Andere info: ", 0x0f, 8);
    draw_string(1000, (HEIGHT/2),"Bij deze een demo.", 0x0f, 3);
    draw_string(1000, 540+40,"Van de eerste interface.", 0x0f, 3);
    init_nodes();
}


/**
 * @brief Functie voor het tekenen van het home scherm
 * 
 */
void home_screen_draw()
{
    update_clock();
    print_notes();

    for (int i = 0; i < 4000000; i++) {
        asm("nop");
    }

    // draw_string(WIDTH/4, 80, "Temple OS 2.0", 0x0f + 60, 9);
    //draw_char(3+CHAR_MULTIPLIER, 40, 80,  0x0f, 9);
    // draw_string(m, HEIGHT-200,"Welkom Matej", 0x0f, 7);
}


/**
 * @brief Functie voor het converten van een getal naar een string
 * 
 * @param number 
 * @return unsigned char 
 */
unsigned char stringify(int number)
{
    return "";
}


/**
 * @brief Functie voor het opzetten van een clock module
 * 
 */
void init_clock()
{
    oneth = 0;
    tenth = 0;
    hundredth = 0;
    thousandth = 0;

    draw_string(80, 80, "Tijd: 00:00", 0x0f, 9);
}


/**
 * @brief Functie voor het updaten van de clock
 * 
 */
void update_clock()
{
    draw_char(oneth + CHAR_MULTIPLIER, 792, 80, 0x0f, 9);
    draw_char(tenth + CHAR_MULTIPLIER, 720, 80, 0x0f, 9);
    draw_char(hundredth + CHAR_MULTIPLIER, 576, 80, 0x0f, 9);
    draw_char(thousandth + CHAR_MULTIPLIER, 504, 80, 0x0f, 9);

    oneth++;

    if (oneth > 9) {
        tenth++;
        oneth = 0;
    }

    if (tenth == 6) {
        tenth = 0;
        hundredth++;
    }

    if (hundredth > 9) {
        hundredth = 0;
        thousandth++;
    }

    if (hundredth == 4 && thousandth == 2) {
        hundredth = 0;
        thousandth = 0; 
    }
}


/**
 * @brief Functie voor het opstellen van het berichtenveld
 * 
 */
void init_nodes()
{
    int i;

    draw_string(80, 400, "Berichten: ", 0x0f, 8);

    for (i = 0; i < 10; i++) {
        struct MNode message;
        message.title = "henk "; // + (i + CHAR_MULTIPLIER);
        message.body = "Dit is een testbody\n";
        message.next = NULL;

        messages[i] = message;
        // message_list_add(message);
    }

    // struct MNode* t = message_list_head();
}


/**
 * @brief Functie voor het drukken van de berichten
 * 
 */
void print_notes()
{
   //  struct MNode *t = message_list_get_item(0);
    unsigned int height = 550;

    for (int i = 0; i < 4; i++) {
        draw_string(80, height, messages[i].title, 0x0f+10, 6);
        draw_string(80, height+78, messages[i].body, 0x0f, 4);

        height = height+130;
    }
}