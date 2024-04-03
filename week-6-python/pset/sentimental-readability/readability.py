from cs50 import get_string


def main():
    text = get_string("Text: ")

    number_letters = get_number_letters(text)
    number_words = get_number_words(text)
    number_sentences = get_number_sentences(text)

    index = calculate_coleman_liau_index(number_letters, number_words, number_sentences)

    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


def get_number_letters(text):
    number_letters = 0

    for c in text:
        if c >= 'A' and c <= 'z':
            number_letters += 1

    return number_letters


def get_number_words(text):
    number_spaces = 0

    for c in text:
        if c == ' ':
            number_spaces += 1

    return number_spaces + 1


def get_number_sentences(text):
    number_punctuation_marks = 0

    for c in text:
        if c == '.' or c == '!' or c == '?':
            number_punctuation_marks += 1

    return number_punctuation_marks


def calculate_coleman_liau_index(number_letters, number_words, number_sentences):
    L = number_letters / (number_words / 100.0)
    S = number_sentences / (number_words / 100.0)

    index = round(0.0588 * L - 0.296 * S - 15.8)

    return index


main()
