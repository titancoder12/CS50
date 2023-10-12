import csv
import sys


length = 0
headers = []

def main():

    # check command-line arguments
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # load CSV with data into memory
    data = loadData(sys.argv[1])

    # load TXT with sequence into memory
    sequence = loadSequence(sys.argv[2])

    # Compute Number of consecutive repeats in DNA sequence
    consecutives = computeNumberConsecutives(sequence)

    # compare STR counts against each row in CSV
    result = compare(consecutives, data)

    # look at result to see if any matches
    if result != "Not Found":
        print(result)


# load CSV with data into memory
def loadData(file):
    # open CSV
    with open(file, "r") as fileP:
        reader = csv.reader(fileP)
        # keep track of headers
        counter = 0
        data = []
        for line in reader:
            # load headers
            if counter == 0:
                for i in range(len(line)):
                    headers.append(line[i])

            person = {

            }

            # load person
            for i in range(len(headers)):
                person[headers[i]] = line[i]

            # add person to list
            personcpy = person.copy()
            data.append(personcpy)

            counter += 1

        # return data
        data.pop(0)
        return data

# load TXT with sequence into memory
def loadSequence(file):
    sequence = []

    with open(file) as sequenceP:
        fileP = sequenceP.read()
        length = len(fileP)
        for i in range(length):
            sequence.append(fileP[i])

    # return sequence
    sequence.pop(-1)
    print(sequence)
    return sequence

# compare STR counts against each row in CSV, returns winner, otherwise returns string "Not Found"
def compare(consecutives, data):
    winner = "No Match"

    return winner

# Compute longest run of consecutive repeats in DNA sequence, returns dict
def computeNumberConsecutives(sequence):
    consecutives = {

    }
    print("HEADERS: "+str(headers))
    consecutivetemp = 0
    # load headers as keys in consecutives
    for i in range(1, len(headers), 1):
            consecutives[headers[i]] = 0
    print("consecutives" + str(consecutives))
    # look for consecutives
    """for i in range(length):
        for x in range(1, len(headers), 1):
            while true:
                j = i
                temp = ''.join(sequence[j:j+len(headers[x])])
                if temp == header[x]:
                    consecutives[header[x]] += 1
                    j += len(header[x])
                else:
                    break"""
    """print("sequence: "+str(sequence))
    for i in range(len(sequence)):
        for x in range(1, len(headers), 1):
            j = i
            while True:
                temp = ''.join(sequence[j:j+len(headers[x])])
                print("temp: " + temp)
                if temp == headers[x]:
                    print("found a consecutive", temp)
                    consecutives[headers[x]] += 1
                    j += len(headers[x])
                else:
                    break"""
    for i in range(1, len(headers), 1):
        tempconsecutives = 0
        for j in range(len(sequence) - len(headers[i])):
            temp = ''.join(sequence[j:j+len(headers[i])])
            if temp == headers[i]:
                print("found consecutive " + temp)
                consecutives[headers[i]] += 1
        if tempconsecutives > consecutives[headers[i]]:
            consecutives[headers[i]] = tempconsecutives

    print(consecutives)
    return consecutives




if __name__ == "__main__":
    main()
