#include "headers/structures/pixel_list.h"


/**
 * @brief Structure voor het opzetten van een node uit de linkedlist
 * 
 */
#pragma pack(1)
struct LNode 
{
    unsigned int data;
    struct LNode* next; 
    struct LNode* prev;
} LNode;


/**
 * @brief Functie voor het toevoegen van items aan de linked list
 * 
 * @param node 
 */
void l_add(struct LNode* node)
{
    if (node == NULL) {
        return;
    }

    struct LNode temp = node;

    while (temp.next != NULL) {
        temp = temp.next;
    }

    temp.next = node;
}


/**
 * @brief Functie voor het updaten van een positie in de linked list
 * 
 * @param node 
 * @param position 
 */
void l_update(const struct LNode* node, unsigned int position)
{

}


/**
 * @brief Functie voor het verwijderen van een node uit de linkedlist
 * 
 */
void l_delete()
{

}


/**
 * @brief Functie voor het ophalen van de lengte van de linkedlist
 * 
 * @return unsigned int 
 */
unsigned int l_size()
{
    return 0;
}


/**
 * @brief Get the l node object
 * 
 * @param node 
 * @return struct LNode* 
 */
struct LNode* get_l_node(const struct LNode* node)
{

}