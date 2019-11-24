#include <stdio.h>
#include "circularList.h"
#include <stdlib.h>

int main()
{
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
        for (stepsLeft = killedNumber - 1; stepsLeft != 0; stepsLeft--)
        {
            setRootToNext(circle);
        }
        deleteRootElement(circle);
        numOfKnights--;
    }

    printf("Surviving knight position:\n%d", getValueFromRoot(circle));
    deleteRootElement(circle);
    free(circle);
    return 0;
}