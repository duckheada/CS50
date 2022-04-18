#include <stdio.h>
#include <cs50.h>

int main (void)
{
    float change;//--Prompts-- the user for a change as a positive floating-point-value
    do
    {
         change = get_float("Enter change as a positive decimal (e.g 0.43): ");
    }
    while (change <= 0);//--Prompts-- /end.

    int workingChange = change * 100;//--Converts-- change into an integer to simplify the following processes /ends.

    int coinArr [4]= {25, 10, 5, 1}; //--Stores-- various coin values in cents /end.
    int numCoins = 0; //--Stores-- number of coins to be returned as change /ends.

    for(int i = 0; i < 4; i++)
    {
        float dResu = workingChange / coinArr[i]; // Count number of coins needed to return the change
        int diviResult;

        if (dResu >= 0) // --Rounds-- the division result from a float into an integer
        {
            diviResult = (int)(dResu + 0.5);
        }

        else
        {
            diviResult = (int)(dResu - 0.5);
        } // --Rounds-- /end.


        if (diviResult >= 0) //--Increments-- number of coins to be returned
        {
            numCoins = numCoins + (1 * diviResult);
        }
        else
        {
            return 0;
        } //--Increments-- /end.
        workingChange = workingChange - (diviResult * coinArr[i]); //--Updates-- change to be processed /end.

    }

    printf("The change would amount to %d coins.\n", numCoins);//--Prints-- number of coins to be returned as change /end.

}