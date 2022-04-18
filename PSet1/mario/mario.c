#include <stdio.h>
#include <cs50.h>

int main(void)
{
  //prompts the user for an intiger "numBlocks" that's between 1 and 8 inclusive

  int height, spaces, hashesleft, hashesRight;
  do
  {
    height = get_int("Shoot a number between 1 and 300: ");
  }
  while (height < 1 || height > 300);

  //Building the pyramid
  for (int rows = 1; rows <= height; rows++) //builds a row if the number of rows is less than or equal to the height entered by the user
  {
    for (spaces = (height - rows) - 1; spaces >= 0; spaces--)//adds spaces to fill up the left side before the hashes
      {
          printf(" ");
      }
      for (hashesleft = 1; hashesleft <= rows; hashesleft++)//prints hashes of the left side of the pyramid if the number of hashes on the right is less than or euqal to the number of rows (big loo
      //)
      {

          printf("#*");
      }
            printf("  ");

      for(hashesRight = 1; hashesRight <= rows; hashesRight++)//prints hashes of the right side of the pyramid if the number of hashes on the left is less than or euqal to the number of rows (big loo
      //)
        {
            printf("#*");
        }
            printf("\n");
  }

}

