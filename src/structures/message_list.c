#include "structures/message_list.h"
#include "graphics/graphics.h"


struct MNode *message_list;


/**
 * @brief Functie voor het ophalen van het eerste element van de lijst  
 * 
 * @return struct MNode* 
 */
struct MNode* message_list_head()
{
    return message_list;
}


/**
 * @brief Functie voor het toevoegen van een bericht aan de lijst
 * 
 * @param node 
 */
void message_list_add(struct MNode* node)
{
    // if (node == NULL) {
    //     draw_string(80, 200, "Element is leeg!", 0x0f+30, 7);
    //     return;
    // }

    if (message_list == 0) {
        draw_string(80, 200, "Head gezet!", 0x0f+30, 7);
        message_list = node;
    } else {
        struct MNode *temp = message_list;
        draw_string(80, 200, "andere gezet!", 0x0f+30, 7);

        while (temp->next != NULL) {
            draw_string(80, 200, "Loopen!", 0x0f+30, 7);
            temp = temp->next;
        }

        temp->next = node;
    }
}


/**
 * @brief Functie voor het updaten van een node in de lijst
 * 
 * @param node 
 * @param position 
 */
void message_list_update(struct MNode* node, unsigned int position)
{
    if (node == NULL) {
        return;
    }

    struct MNode *n = &message_list;
    struct MNode *temp;
    int size = 0;

    while (n->next != NULL) {
        size++;

        if (size == position) {
            break;
        } else if (size > position) {
            return;
        }

        n = n->next;
    }
}


/**
 * @brief Functie voor het ophalen van een node uit de lijst
 * 
 * @param position 
 * @return struct MNode* 
 */
struct MNode* message_list_get_item(unsigned int position)
{
    if (position < 0) {
        return;
    }

    struct MNode* n = message_list;
    unsigned int size = 0;

    while (n->next != NULL) {
        if (size == position) {
            break;
        }
        
        size++;
        n = n->next;
    }

    return n;
}