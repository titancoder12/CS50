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
    return sequence

# compare STR counts against each row in CSV, returns winner, otherwise returns string "Not Found"


def compare(consecutives, data):
    winner = "No Match"
    # print("consec:"+str(consecutives))
    # print()
    # print("data:"+str(data))

    for dic in data:
        result = True
        for key in consecutives.keys():
            if str(consecutives[key]) != str(dic[key]):
                result = False
                break
        if result == True:
            winner = dic["name"]
            break
    return winner

# Compute longest run of consecutive repeats in DNA sequence, returns dict


def computeNumberConsecutives(sequence):
    # sequence = test
    # print(str(sequence))
    consecutives = {

    }
    # load headers as keys in consecutives
    for i in range(1, len(headers), 1):
        consecutives[headers[i]] = 0

    for header in headers[1:]:
        tempconsecutive = 0
        maxconsecutive = 0
        header_len = len(header)
        j = 0
        
        while j <= len(sequence):
            temp = ''.join(sequence[j:j+header_len])
            if temp == header:
                tempconsecutive += 1
                j += header_len
            else:
                maxconsecutive = max(tempconsecutive, maxconsecutive)
                tempconsecutive = 0
                j += 1
            consecutives[header] = maxconsecutive

    return consecutives


if __name__ == "__main__":
    main()
