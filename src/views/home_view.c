#include "views/home_view.h"
#include "graphics/graphics.h"
#include "structures/message_list.h"
#include "system/scheduler.h"
#include "system/memory.h"
#include "system/instructions.h"


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
char some_titles[10][20] = {
    "Toets wiskunde",
    "Gesprek Matej",
    "Opdracht programmeren",
    "Boek",
    "Titel5",
    "Titel6",
    "Titel7",
    "Titel8",
    "Titel9",
    "Titel0",
};

char some_bodies[10][60] = {
    "Moet nog leren voor toets wiskunde OP4\n",
    "Laatste keer gesprek voor de deadline van de mirror\n",
    "Verder werken aan de eindopdracht\n",
    "Vandaag komt er een boek binnen\n",
    "Dit is een testbody\n",
    "Dit is een testbody\n",
    "Dit is een testbody\n",
    "Dit is een testbody\n",
    "Dit is een testbody\n",
    "Dit is een testbody\n",
};


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
    init_clock();
    init_nodes();
    init_weather();
}


/**
 * @brief Functie voor het tekenen van het home scherm
 * 
 */
void home_screen_draw()
{
    update_clock();
    // print_notes();

    for (int i = 0; i < 4000000; i++) {
        asm("nop");
    }
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

    draw_string(80, 80, "00:00", 0x0f, 9);
}


/**
 * @brief Functie voor het updaten van de clock
 * 
 */
void update_clock()
{
    unsigned int base_width = 80;
    unsigned int base_offset = 72;

    draw_char(oneth + CHAR_MULTIPLIER, base_width + (base_offset*4), 80, 0x0f, 9);
    draw_char(tenth + CHAR_MULTIPLIER, base_width + (base_offset*3), 80, 0x0f, 9);
    draw_char(hundredth + CHAR_MULTIPLIER, base_width + base_offset, 80, 0x0f, 9);
    draw_char(thousandth + CHAR_MULTIPLIER, base_width, 80, 0x0f, 9);

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

    draw_string(80, 500, "Berichten: ", 0x0f, 8);

    for (i = 0; i < 10; i++) {
        struct MNode message;
        message.title = some_titles[i]; // + (i + CHAR_MULTIPLIER);
        message.body = some_bodies[i];
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
        draw_string(80, height, messages[i].title, 0x0f+10, 4);
        draw_string(80, height+78, messages[i].body, 0x0f, 2);

        height = height+130;
    }
}


/**
 * @brief Functie om het weer op te zetten
 * 
 */
void init_weather()
{
    draw_string(1200, 80, "21 graden", 0x0f, 9);
    draw_string(1200, 172, "Bewolkt - Alblasserdam", 0x0f, 3);
}


/**
 * @brief Functie om de timer app in het geheugen van het systeem te laden
 * 
 */
void load_timer_app()
{
    // Declareer variabeles
    memory_push(0x0001, 0, 0, INT);                 // begint bij 0x01
    memory_push(0x0002, 0, 0, INT);
    memory_push(0x0003, 0, 0, INT);
    memory_push(0x0004, 0, 0, INT);

    // Vergelijk of een seconde gelijk is aan 9
    memory_push(0x0005, 0x0001, 9, GREATERTHAN);
    memory_push(0x0006, 0x0009, 0, JUMP);
    memory_push(0x0007, 0x0001, 1, INCREMENT);
    memory_push(0x0008, 0x0005, 0, RETURN);

    // Kijk 
    memory_push(0x0009, 0x0002, 5, GREATERTHAN);
    memory_push(0x000A, 0x000D, 0, JUMP);
    memory_push(0x000B, 0x0002, 1, INCREMENT);
    memory_push(0x000C, 0x0005, 0, RETURN);

    // 
    memory_push(0x000D, 0x0003, 9, GREATERTHAN);
    memory_push(0x000E, 0x0011, 0, JUMP);
    memory_push(0x000F, 0x0003, 1, INCREMENT);
    memory_push(0x0010, 0x0005, 0, RETURN);

    // 
    memory_push(0x0011, 0x0004, 5, GREATERTHAN);
    memory_push(0x0012, 0x0015, 0, JUMP);
    memory_push(0x0013, 0x0003, 1, INCREMENT);
    memory_push(0x0014, 0x0005, 0, RETURN);

    //
    memory_push(0x0015, 0x0005, 0, RETURN);
}