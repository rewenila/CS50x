from cs50 import get_string


def check_validity(card_number):
    digits_number = len(card_number)

    # Sum digits at odd indexes starting from the last
    odd_index_digits = []
    for i in range(digits_number - 1, -1, -2):
        odd_index_digits.append(int(card_number[i]))

    odd_index_digits_sum = sum(odd_index_digits)

    # Double digits at even indexes starting from second-to-last and sum the digits of the doubles
    even_index_digits_double = []
    for i in range(digits_number - 2, -1, -2):
        even_index_digits_double.append(int(card_number[i]) * 2)

    even_index_digits_double_digits_sum = 0
    for double in even_index_digits_double:
        double_digits = list(map(int, str(double)))
        even_index_digits_double_digits_sum += sum(double_digits)

    # Verify if the last digit of the final sum is 0
    final_sum = odd_index_digits_sum + even_index_digits_double_digits_sum

    return final_sum % 10 == 0


def get_card_type(card_number):
    digits_number = len(card_number)
    first_digit = int(card_number[:1])
    first_two_digits = int(card_number[:2])

    if digits_number == 15 and (first_two_digits == 34 or first_two_digits == 37):
        return "AMEX"
    elif digits_number == 16 and (first_two_digits >= 51 and first_two_digits <= 55):
        return "MASTERCARD"
    elif (digits_number == 13 or digits_number == 16) and first_digit == 4:
        return "VISA"
    else:
        return "INVALID"


# Ask the user for card number
card_number = get_string("Card number: ")

# Check if credit card has a valid number and print its type
is_card_valid = check_validity(card_number)

if (is_card_valid):
    card_type = get_card_type(card_number)
    print(card_type)
else:
    print("INVALID")
