#include <stdio.h>
#include "listByStudent.h"

int main()
{
    List* newList = createList();
    for (int i = 0; i < 9; i++)
    {
        append(newList, i, i);
    }
    printList(newList);
    for (int i = 5; i > 0; i--)
    {
        pop(newList, i);
    }
    printList(newList);
    append(newList, 78, 0);
    append(newList, 12, 1);
    printList(newList);
    sortList(newList);
    printList(newList);
    deleteList(newList);
    return 0;
}
