#include <stdio.h>
#include "circularList.h"

int main() {
    int numOfKnights = 0;
    int killedNumber = 0;
    circularList* circle = createCircularList();
    printf("Enter the n and m:\n");
    scanf("%d %d", &numOfKnights, &killedNumber);
    if ((numOfKnights <= 0) || (killedNumber <= 0))
    {
        printf("Incorrect input");
        return 0;
    }
    for (int i = 1; i <= numOfKnights; i++)
    {
        append(i, circle);
    }

    int stepsLeft = killedNumber;
    while (numOfKnights != 1)
    {
        stepsLeft = killedNumber - 1;
        while (stepsLeft != 0)
        {
            setRootToNext(circle);
            stepsLeft--;
        }
        delete(circle);
        numOfKnights--;
    }

    printf("%d", getValueFromRoot(circle));

    return 0;
}