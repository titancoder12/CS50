from cs50 import get_string


# compute sentences
def compute_sentences(sentence):
    # compute number of sentences
    computed_sentences = sentence.count(".") + sentence.count("!") + sentence.count("?")

    # return sentences
    return computed_sentences


# compute words
def compute_words(sentence):
    # initialize needed variables
    computedwords = 0

    # loop through chars in sentences, looking for spaces
    for i in range(len(sentence)):
        if sentence[i] == " ":
            computedwords += 1

    # return words
    computedwords += 1
    return computedwords


# compute letters
def compute_letters(sentence):
    # initialize needed variables
    letters = 0

    # loop through chars in sentences, counting the number of alphabetical chars
    for i in range(len(sentence)):
        if sentence[i].isalpha():
            letters += 1

    # return letters
    return letters


def main():
    # get text from user
    sentence = get_string("Text: ")

    # call functions to get values needed for later
    numSentences = compute_sentences(sentence)
    numWords = compute_words(sentence)
    numLetters = compute_letters(sentence)

    # caculate grade using the Coleman-Liau formula
    L = float(numLetters / numWords * 100)
    S = float(numSentences / numWords * 100)

    grade = round(0.0588 * L - 0.296 * S - 15.8)
    
    # print grade
    if grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    elif grade > 1 and grade < 16:
        print(f"Grade {grade}")


# run main
if __name__ == "__main__":
    main()
