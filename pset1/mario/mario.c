#include <stdio.h>
#include <cs50.h>


int main(void)
{
   int height = 0;
   
   do
   {
   height = get_int("Height:");
   
   }
   while (height < 1 || height > 8);
   
   for (int i = 1; i <= height; i++)
   {
      int spaces = height - i;
      
      for (int y = 0; y < spaces; y++)
      {
         printf("  ");
            
      }
         
      for (int x = 1; x <= i; x++)
      {
         
         printf("#");
      
         
      }
      
      printf("\n");
   
      
   }

   
}
  