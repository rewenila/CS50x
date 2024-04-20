# Password with 4 digits: only numbers
# from string import digits
# from itertools import product

# for passcode in product(digits, repeat = 4):
#     print(passcode)

# Password with 4 digits: only letters
# from string import ascii_letters
# from itertools import product

# for passcode in product(ascii_letters, repeat=4):
#     print(passcode)

# Password with 4 digits: numbers, letters, and punctuation
from string import ascii_letters, digits, punctuation
from itertools import product

for passcode in product(ascii_letters + digits + punctuation, repeat=8):
    print(passcode)
