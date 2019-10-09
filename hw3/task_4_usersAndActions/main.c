#include <stdio.h>
#include "simpleArrays.h"
#include <stdlib.h>

int main() {
    printf("Enter the number of users, number of actions and time:\n");  // scanning the request
    int numOfUsers = 0;
    int numOfActions = 0;
    int time = 0;
    scanf("%d %d %d", &numOfUsers, &numOfActions, &time);

    int **users = malloc(sizeof(int*) * numOfUsers);  // creating the space for data and scanning it
    int numOfUserAction = 0;
    for (int i = 0; i < numOfUsers; i++)
    {
        printf("(User #%d) Enter the number of user actions:\n", i);
        scanf("%d", &numOfUserAction);
        users[i] = createArrayOfInt(numOfUserAction);
        printf("Enter user actions:\n");
        scanArrayOfInt(0, numOfUserAction - 1, users[i]);
    }

    for (int i = 0; i < numOfUsers; i++)  // deleting the data
    {
        free(users[i]);
    }
    free(users);
    return 0;
}