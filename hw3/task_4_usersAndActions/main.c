#include <stdio.h>
#include "simpleArrays.h"
#include <stdlib.h>

const int defaultSize = 80;

int main() {
    printf("Enter the number of users, number of actions and time:\n");  // scanning the request
    int numOfUsers = 0;
    int requestedNumOfActions = 0;
    int requestedTime = 0;
    scanf("%d %d %d", &numOfUsers, &requestedNumOfActions, &requestedTime);

    /* Since we can check whether a user is suitable
     * for a request or not without data about other users,
     * we will only store data about one user at a time */

    int *userActionsDates = createArrayOfInt(defaultSize);
    int numOfUserAction = 0;
    int result = 0;
    for (int i = 0; i < numOfUsers; i++)
    {
        printf("(User #%d) Enter the number of user actions:\n", i);  // scanning the data for one user
        scanf("%d", &numOfUserAction);
        if (numOfUserAction > defaultSize)  // adding more space if necessary
        {
            userActionsDates = realloc(userActionsDates, sizeof(int) * numOfUserAction);
        }
        printf("Enter user actions:\n");
        scanArrayOfInt(0, numOfUserAction - 1,userActionsDates);

        int suitableActions = 0;  // check whether this user suits the request
        for (int j = 0; j < numOfUserAction; j++)
        {
            if (userActionsDates[j] <= requestedTime)
            {
                suitableActions++;
            }
        }
        if (suitableActions == requestedNumOfActions)
        {
            result++;
        }
    }

    printf("Answer: %d", result);
    free(userActionsDates);
    return 0;
}