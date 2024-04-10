# Prints all favorites in CSV using csv.reader
import csv
from collections import Counter

# Open CSV file
with open("data/favorites.csv", "r") as file:

    # Create DictReader and Counter
    reader = csv.DictReader(file)
    counts = Counter()

    # Iterate over rows
    for row in reader:
        favorite = row["language"]
        counts[favorite] += 1

# Print counts sorted by value and reversed
for favorite, count in counts.most_common():
    print(f"{favorite}: {counts[favorite]}")
