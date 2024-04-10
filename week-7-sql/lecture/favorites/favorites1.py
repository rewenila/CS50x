# Prints all favorites in CSV using csv.reader
import csv

# Open CSV file
with open("data/favorites.csv", "r") as file:

    # Create DictReader
    reader = csv.DictReader(file)

    # Create counters
    scratch, c, python = 0, 0, 0

    # Iterate over CSV file, incrementing number of favorite language
    for row in reader:
        favorite = row["language"]
        if favorite == "Scratch":
            scratch += 1
        elif favorite == "C":
            c += 1
        elif favorite == "Python":
            python += 1

# Print number of favorite
print(f"Scratch: {scratch}")
print(f"C: {c}")
print(f"Python: {python}")
