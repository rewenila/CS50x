# Prints all favorites in CSV using csv.reader
import csv

# Open CSV file
with open("data/favorites.csv", "r") as file:

    # Create DictReader
    reader = csv.DictReader(file)

    # Create empty dictionary
    counts = {}

    # Iterate over rows
    for row in reader:
        favorite = row["language"]
        if favorite in counts:
            counts[favorite] += 1
        else:
            counts[favorite] = 1

# Print counts sorted by value and reversed
for favorite in sorted(counts, key = counts.get, reverse = True):
    print(f"{favorite}: {counts[favorite]}")
