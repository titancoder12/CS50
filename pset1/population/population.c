#include <cs50.h>
#include <stdio.h>

int main(void)
{

    int population = 0;
    int start = 0;
    int end = 0;
    // TODO: Prompt for start size
    do
    {
        start = get_int("Start size:\n");

    }
    while (start < 9);

    // TODO: Prompt for end size
    
    do{
        end = get_int("End size:\n");
    
    }while (end < start);

    population = start;
    // TODO: Calculate number of years until we reach threshold
    int year = 0;

    /* WARNING: CODE DOES NOT WORK
    for (int i = population; i != (end-1); i++)
    {
        population = population + (population / 3);
        population = population - (population / 4);
        year = year + 1;
    }*/

    while (population < end){
        int originalPopulation = population; // 100
        population = population + (population / 3); // 100 + 100/3 = 100 + 33 = 133
        population =  population - (originalPopulation / 4); // 133 - 100/4 = 133 - 25 = 108
        year = year + 1;
        //printf("population %d in year %d\n", population, year);

    }

    // TODO: Print number of years
    printf("Years: %i", year);
}
