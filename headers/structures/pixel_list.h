#ifndef __LINKED__LIST__
#define __LINKED__LIST__


struct LNode;


void l_add(struct LNode *);
void l_update(const struct LNode *, unsigned int);
void l_delete();
unsigned int l_size();
struct LNode * get_l_node(const struct LNode *);


#endif