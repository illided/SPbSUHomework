#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H

struct circularList;
struct circularListElement;

typedef struct circularList circularList;
typedef struct circularListElement circularListElement;

circularList* createCircularList();
void append(int value, circularList* list);
void setRootToNext(circularList* list);
int getValueFromRoot(circularList* list);
int size(circularList* list);
void delete(circularList* list);



#endif
