#include <stdio.h>
#include <cs50.h>

/*
Verification stages:
    1. Digit count
    2. Luhn's algorithm
    3. Card provider

*/

int main(void)
{
    //-------- Get cc number and verification stage "1" ------------
    long ccNum;       // stores the cc number
    long copyOfCCNum; // stors a modifiable copy of ccNum

    int ccDigCount; // stors the number of digits in ccNum

    do
    {
        ccNum = 4539677908016808; // prompts the user for ccNum

        ccDigCount = 0;
        copyOfCCNum = ccNum;
        while (copyOfCCNum > 0)
        {
            copyOfCCNum = copyOfCCNum / 10;
            ccDigCount++;
        }
    }

    // conditions validating the size of a ccNum in terms of digits count
    while (ccDigCount < 13 || ccDigCount > 16);
    printf("number of digits in the cc number is: %d\n", ccDigCount);
    // printf("%lu\n", ccNum);

    //-----------Luhn's--------------

    // Prep-----------
    copyOfCCNum = ccNum;
    int normalCcArr[ccDigCount];

    int reverseCcNum[ccDigCount];
    for (int i = 0; i < ccDigCount; i++) // gives reversed array of ccNum
    {
        // printf("%d\n", i);
        reverseCcNum[i] = copyOfCCNum % 10;

        copyOfCCNum /= 10;

        // printf("reverseCcNum %d\n", reverseCcNum[i]);
    }

    // printf("ccDigCount: %d\n", ccDigCount);
    for (int i = ccDigCount - 1; i >= 0; i--) // gives normally ordered array of ccNum
    {
        normalCcArr[i] = reverseCcNum[i];
        // printf("normalCcArr at i: %d\n", normalCcArr[i]);
    }
    // printf("normalCcArr[0]: %d\n", normalCcArr[0]);

    // Actual Luhn's algorithm ------

    int x, y, dubed = 0, sum = 0, sumDubed = 0, mod, sumOfSums, lunsIsCongToZero; // vars

    for (x = 1; x <= ccDigCount; x += 2)
    {
        // Sum doublable numbers
        if (x < ccDigCount)
        {
            dubed = normalCcArr[x] * 2;

            // Add doubled numbers' digits
            while (dubed > 0)
            {
                mod = dubed % 10;

                sumDubed = sumDubed + mod;
                dubed = dubed / 10;
            }
            //  printf("sumDubed :  %d\n", sumDubed);
        }

        // Sum none-doublable numbers
        if (x != 0)
        {
            y = x - 1;
            sum += normalCcArr[y];
            // printf("normalCcArr[y]:  %d\n", normalCcArr[y]);

            // printf("sum singles:  %d\n", sum);
        }
    }

    sumOfSums = sum + sumDubed;
    lunsIsCongToZero = sumOfSums % 10;
    // printf("lunsIsCongToZero %d\n", lunsIsCongToZero);

    // Check if the total’s last digit is 0
    if (lunsIsCongToZero == 0)
    {
        printf("Valid Mofoo!!!\n");
    }
    else
    {
        printf("Get a real card you fake ass!!!\n");
        return 0;
    }

    //---------------Prep for card provider check-------------------

    // extracts first digit of ccNum
    long fstDig = ccNum;

    while (fstDig >= 10)
    {
        fstDig = fstDig / 10;
    }

    // printf("First digit of the cc number is: %lu\n", fstDig);

    // Extracts first two digits of ccNum---------
    long fstTwosDig = ccNum;

    // remove last digit from number till only two digit is left */
    while (fstTwosDig >= 100)
    {
        fstTwosDig = fstTwosDig / 10;
    }

    // printf("First two digits of the cc number is: %lu\n", fstTwosDig);

    //---------------Card provider check------------------

    // Validates first digit ------
    if (fstDig < 3 || fstDig > 5)
    {
        printf("Invalid cc provider!\n");
        return 1;
    }

    // Validates for American Express------
    else if (ccDigCount == 15)
    {
        if (fstTwosDig == 34 || fstTwosDig == 37)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("Invalid cc provider!\n");
            return 1;
        }
    }

    // Validates for MasterCard & VISA ------
    else if (ccDigCount == 16 || ccDigCount == 13)
    {
        if (fstTwosDig >= 51 && fstTwosDig <= 55 && ccDigCount == 16)
        {
            printf("MASTERCARD\n");
        }

        // Validates for VISA------
        else if (fstDig == 4)
        {
            printf("VISA\n");
        }

        else
        {
            printf("Invalid cc provider!\n");
            return 1;
        }
    }
    else
    {
        printf("Invalid cc provider!\n");
        return 1;
    }
}
