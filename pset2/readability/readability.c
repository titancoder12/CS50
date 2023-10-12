if #include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


int compute_sentences(string sentence1)
{
    int computedsentences = 0;
    for (int i = 0, c = strlen(sentence1); i != c; i++)
    {
        if (sentence1[i] == '.')
        {
            computedsentences += 1;
        }

        if (sentence1[i] == '!')
        {
            computedsentences += 1;
        }

        if (sentence1[i] == '?')
        {
            computedsentences += 1;
        }
    }

    return computedsentences;

}

int compute_words(string sentence2)
{
    int computedwords = 0;
    for (int i = 0, c = strlen(sentence2); i != c; i++)
    {
        if (sentence2[i] == ' ')
        {
            computedwords++;
        }
    }

    return computedwords + 1; //+1 because number of words is always number of spaces + 1
}

int compute_letters(string sentence3)
{
    int letters = 0;
    for (int i = 0, c = strlen(sentence3); i != c; i++)
    {
        if (isalpha(sentence3[i]))
        {
            letters += 1;
        }
    }
    return letters;
}


int main(void)
{
    string sentence = get_string("Text: ");

    int numSentences = compute_sentences(sentence); // number of sentences
    int numWords = compute_words(sentence); // number of words
    int numLetters = compute_letters(sentence); // number of letters



    //float lettersaverage = (float) letters / ((float)words * 100.00);
    //float sentencesaverage = (float) sentences / ((float)words * 100.00);

    float L = numLetters / (float)numWords * 100; // Average number of letters per 100 words
    float S = numSentences / (float)numWords * 100; // Average number of sentences per 100 words


    int index = round(0.0588 * L - 0.296 * S - 15.8);
    
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
    
}
