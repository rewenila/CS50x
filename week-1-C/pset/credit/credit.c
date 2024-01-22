#include <cs50.h>
#include <math.h>
#include <stdio.h>

bool check_validity(long number);
string get_card_type(long card_number);

int main(void)
{
    // Asks for credit card number
    long card_number;
    do
    {
        card_number = get_long("Number: ");
    }
    while (card_number < 1);

    // Check if credit card has a valid number and prints its type
    bool is_card_valid = check_validity(card_number);
    if (is_card_valid)
    {
        string card_type = get_card_type(card_number);
        printf("%s\n", card_type);
    }
    else
    {
        printf("INVALID\n");
    }
}

string get_card_type(long card_number)
{
    // Get number of digits
    long digits_number = 0;
    long number = card_number;
    while (number > 0)
    {
        digits_number++;
        number = number / 10;
    }

    // Get the first digit and the two firsts digits of the card number
    long first_digit = card_number / pow(10, digits_number - 1);
    long first_two_digits = card_number / pow(10, digits_number - 2);

    // Check if the card is from a specific type or if it is invalid
    if (digits_number == 15 && (first_two_digits == 34 || first_two_digits == 37))
    {
        return "AMEX";
    }
    else if (digits_number == 16 && (first_two_digits == 51 || first_two_digits == 52 || first_two_digits == 53 ||
                                     first_two_digits == 54 || first_two_digits == 55))
    {
        return "MASTERCARD";
    }
    else if ((digits_number == 13 || digits_number == 16) && first_digit == 4)
    {
        return "VISA";
    }
    else
    {
        return "INVALID";
    }
}

bool check_validity(long card_number)
{
    long digit;
    long digit_double;
    long odd_index_digits_sum = 0;
    long even_index_digits_sum = 0;
    long number = card_number;

    while (number > 0)
    {
        // Get the digits at odd indexes and sum it
        digit = number % 10;
        odd_index_digits_sum += digit;

        number = number / 10;

        // Get the digits at even indexes
        digit = number % 10;

        // Double digits at even indexes and sum the digits of the double
        digit_double = digit * 2;
        while (digit_double > 0)
        {
            digit = digit_double % 10;
            even_index_digits_sum += digit;

            digit_double = digit_double / 10;
        }

        number = number / 10;
    }

    // Verify if the last digit of the sum is 0
    long final_sum = odd_index_digits_sum + even_index_digits_sum;
    if (final_sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

