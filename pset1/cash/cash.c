#include <cs50.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int main(void)
{
    int coins = 0;
    float changeowed = 0;
    do
    {
        changeowed = get_float("Change owed:");
    }
    while (changeowed < 0);
    
    changeowed = round(changeowed * 100.00);
    float qter = 25.00;
    float dme = 10.00;
    float nk = 5.00;
    float pn = 1.00;
    
    bool owechange = true;
    
    while (changeowed > 0)
    {
        if (qter <= changeowed)
        {
            
            changeowed -= qter;
            coins += 1;
            
        }
        else if (dme <= changeowed)
        {
            changeowed -= dme;
            coins += 1;
            
        }
        else if (nk <= changeowed)
        {
            changeowed -= nk;
            coins += 1;
            
        }
        else
        {   
            changeowed -= pn;
            coins += 1;
            
        }
        
    }
    
    owechange = false;
    printf("%i", coins);
    
}

