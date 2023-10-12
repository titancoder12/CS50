#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char charcypher(char c, int key);
bool isNumber(string in);

//command line acsess
int main(int argc, string argv[])
{
    
    string plaintext = "void";
    int key = 0;
    

    //checking command line inputs
    if (argc != 2 ||  !isNumber(argv[1]))
    {
        printf("Usage: ./caesar key");
        return 1;
    }
    else
    {
        key = atoi(argv[1]);
        printf("Success \n");
    }
    
    
    key = atoi(argv[1]);
    
    //getting plain text
    plaintext = get_string("plaintext: ");
    
    char cyphered[strlen(plaintext) + 1]; // before: char cyphered[strlen(plaintext)];
    
    
    //going through each char of plaintext, checking if it is an alphabetical char.
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isalpha(plaintext[i]))
        {
            cyphered[i] = charcypher(plaintext[i], key);
        }
        else
        {
            cyphered[i] = plaintext[i];
        }
    }
    cyphered[strlen(plaintext)] = '\0'; // before: cyphered[strlen(cyphered)]
    
    printf("ciphertext: %s\n", cyphered);


    return 0;
}

bool isNumber(string in)
{
    //going through the string 'in', checking if each key is a digit
    for (int i = 0; i < strlen(in); i++)
    {
        if (!isdigit(in[i]))
        {
            return false;
        }
    }
    return true;
}

char charcypher(char c, int key)
{
    int intcyphered = 0;
    //checking if is capital or not to decide which formula to use
    if isupper(c)
    {
        intcyphered = ((c - 'A') + key) % 26;
    }
    if islower(c)
    {
        intcyphered = ((c - 'a') + key) % 26; 
    }
    
    
    char charcyphered;    
    //converting back to char
    if (isupper(c))
    {    
        charcyphered = intcyphered + 'A';
    }
    if (islower(c))
    {    
        charcyphered = intcyphered + 'a';
    }
    
    
    
    //return charcyphered; 
    return charcyphered;

}

