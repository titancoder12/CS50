// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include dictionary.h

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

//function prototypes
bool isalphabet(const char *word, char exception);

//Number of nodes in total
int numberofnodes;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
int table_size = 676;
node *table[676];


// testing
//int malloc_count = 0;
//int free_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    /*
    printf("Enter Check\n");
    node *cursor;
    int location = hash(word);
    bool x = true;
    cursor = table[location];
    while (x)
    {
        if (cursor == NULL)
        {
            x = false;
            printf("Exit Check\n");
            return false;
        }
        else if (strcasecmp(cursor->word, word) == 0) // Segmentation Fault
        {
            printf("Exit Check\n");
            return true;
        }
        cursor = cursor->next;

    }
    printf("Exit Check\n");
    return false;
    */
    //printf("Check for: %s\n", word);
    bool result = false;
    int location = hash(word);
    //printf("Check: Got a hash with value %d\n", location);
    if (location <= table_size)
    {
        node *cursor = table[location];
        while (cursor != NULL)
        {
            //printf("Check, word in bucket is: %s\n", cursor->word);
            if (strcasecmp(cursor->word, word) == 0)
            {
                result = true;
                break;

            }
            cursor = cursor->next;

        }
    }
    else
    {
        result = false;
    }
    return result;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //printf("Enter Hash\n");
    int location = 0;
    if (isalphabet(word, 39))
    {


        int w0 = toupper(word[0]) - 'A';
        int w1 = 1 + toupper(word[1]) - 'A';
        if (w0 < 0)
        {
            w0 = 0;

        }

        if (w1 < 0)
        {
            w1 = 0;
        }
        location = 27 * w0 + w1;


        /* Daddy
        int w0 = toupper(word[0]) - 'A';
        int w1 = 1+ (toupper(word[1]) - 'A');

        if(w0 <0 )
            w0 = 0;
        if(w1<0)
            w1 = 0;


        location = 27 *w0 + w1;
        */


    }
    else
    {
        //how to return false in usigned int function?
        //printf("hash function returns: %i\n", 0);
        return table_size - 1;//1000;

    }
    //printf("hash function returns: %i\n", location);
    //printf("Exit Hash\n");
    return location;

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //printf("Enter Load\n");
    //printf("Loading dictionary...\n");
    FILE *dic = NULL;
    if ((dic = fopen(dictionary, "r")) == NULL)
    {
        return false;
    }

    bool x = true;
    int counter = 0;
    char *word = malloc(sizeof(char) * 45);
    //malloc_count++;
    while (fscanf(dic, "%s", word) != EOF) // Segmentation Fault?
    {
        //printf("%s\n", word);

        node *cursor = NULL;
        counter++;
        node *nodeP = malloc(sizeof(node));
        //malloc_count ++;
        strcpy(nodeP->word, word);
        nodeP -> next = NULL;

        int location = hash(word);
        //printf("Hash %s into location %i\n", word, location);

        if (location > table_size)
        {

            return false;
        }


        if (table[location] == NULL)//segmentation fault
        {
            table[location] = nodeP;
        }
        else
        {

            //node *cursor == NULL;
            cursor = table[location];
            while (cursor->next != NULL)
            {
                cursor = cursor->next;// segmentation fault
            }
            cursor->next = nodeP;



            /* Daddy Code
            cursor = table[location];
            while(cursor->next != NULL){
                cursor = cursor -> next;
            }
            cursor -> next = nodeP;
            */

        }
        //table[location] = node; //segmentation fault?
        numberofnodes += 1;

    }
    free(word);
    fclose(dic);
    //free_count++;
    //printf("Exit Load\n");

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    //printf("Exit size\n");
    return numberofnodes;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    //printf("Enter unload\n");
    node *cursor;
    node *temp;
    for (int i = 0; i < table_size; i++)
    {

        cursor = table[i];
        while (cursor != NULL)
        {
            temp = cursor;
            cursor = cursor->next;
            //free(temp->word);
            free(temp);
            //free_count++;

        }

    }
    //printf("Exit Unload\n");

    //printf("malloc count: %d\n", malloc_count);
    //printf("free count: %d\n", free_count);

    return true;
}

//Checks if is alphabet, and also takes exception
bool isalphabet(const char *word, char exception)
{
    //printf("Enter IsAlpha\n");
    int wordlen = strlen(word);
    for (int i = 0; i < wordlen; i++)
    {
        char character = toupper(word[i]);
        if (!(((character >= 65) && (character < 90)) || (character == exception)))
        {
            //printf("Exit IsAlpha\n");
            return false;
        }


    }
    //printf("Exit IsAlpha\n");
    return true;

}