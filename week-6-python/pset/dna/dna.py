import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Invalid usage. Correct usage: dna.py database.csv sequence.txt")
        return

    # Read database file into a variable
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)

        fields = reader.fieldnames

        people_data = []
        for row in reader:
            people_data.append(row)

    # Read DNA sequence file into a variable
    with open(sys.argv[2]) as file:
        sequence = file.read()

    # Find longest match of each STR in DNA sequence
    strs = fields[1::]
    str_counts = {}

    for str in strs:
        str_counts[str] = longest_match(sequence, str)

    # Check database for matching profiles
    # Compare the STR counts of the sequence with the STR counts of each person
    for person in people_data:
        matches_count = 0

        for key, value in person.items():
            if key != 'name':
                if int(value) == str_counts[key]:
                    matches_count += 1
                else:
                    break

        # Chech if all STR counts match
        if matches_count == len(str_counts):
            print(person['name'])
            return

    # If STR counts do not match with any person
    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()