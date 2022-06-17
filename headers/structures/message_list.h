#pragma once


#ifndef __MESSAGE__LIST__
#define __MESSAGE__LIST__


/**
 * @brief Structure voor het opslaan van berichten
 * 
 */
struct MNode
{
    char *title;
    char *body;
    struct MNode *next;
};


#define NULL ((struct MNode *)0)


struct MNode* message_list_head();
void message_list_add(struct MNode *);
void message_list_update(struct MNode *, unsigned int);
void message_list_delete();
void message_list_size();
struct MNode* message_list_get_item(unsigned int);

#endif