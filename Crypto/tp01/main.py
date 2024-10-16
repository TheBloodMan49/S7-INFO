import sys
import matplotlib.pyplot as plt
from matplotlib.pyplot import title

LETTER_FREQUENCY_EN = [0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094, 0.06966, 0.00153,
                       0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056,
                       0.02758, 0.00978, 0.02360, 0.00150, 0.01974, 0.00074]

def encrypt(plaintext: str, key: str) -> str:
    plaintext = plaintext.upper()
    key = key.upper()
    ciphertext = ''
    for i in range(len(plaintext)):
        if plaintext[i] == ' ':
            ciphertext += ' '
            continue
        ciphertext += chr(((ord(plaintext[i]) - ord('A') + ord(key[i % len(key)]) - ord('A')) % 26) + ord('A'))
    return ciphertext

def decrypt(ciphertext: str, key: str) -> str:
    ciphertext = ciphertext.upper()
    key = key.upper()
    plaintext = ''
    for i in range(len(ciphertext)):
        if ciphertext[i] == ' ':
            plaintext += ' '
            continue
        plaintext += chr(((ord(ciphertext[i]) - ord('A') - (ord(key[i % len(key)]) - ord('A')) + 26) % 26) + ord('A'))
    return plaintext.lower()

def crack(ciphertext: str, keylen: int) -> str:
    ciphertext = ciphertext.upper()
    # Create a list of keylen strings
    text_split = ['' for i in range(keylen)]
    for i, letter in enumerate(ciphertext):
        text_split[i % keylen] += letter
    print(f'Split cesar strings are {len(text_split[-1])} long')

    key = ''
    for text in text_split:
        key += find_cesar_cipher_using_frequency_distribution(text)

    print(f'Key is "{key.lower()}"')
    return decrypt(ciphertext, key)

def find_cesar_cipher_using_frequency_distribution(string: str) -> str:
    # Build a frequency distribution of the string
    frequencies: list[float] = [0]*26
    for char in string:
        if char == ' ':
            continue
        frequencies[(ord(char)-ord('A'))%26] += 1

    # Normalize frequencies
    total = float(sum(frequencies))
    for i in range(len(frequencies)):
        frequencies[i] /= total

    # Find the best shift
    best_shift = 0
    best_score = 0
    for i in range(26):
        score = 0
        # Compute a scalar product of the two frequency distributions
        for j in range(26):
            score += frequencies[j] * LETTER_FREQUENCY_EN[(j-i)%26]
        if score > best_score:
            best_score = score
            best_shift = i

    # Uncomment to plot the frequency distributions !
    '''
    frequencies_shifted = [frequencies[(i+best_shift)%26] for i in range(26)]
    # x is the list of letters
    x = [chr(i+ord('A')) for i in range(26)]
    kwargs = dict(alpha=0.5, edgecolor='k')
    plt.bar(x, LETTER_FREQUENCY_EN, **kwargs, color='cyan', label='Theoretical')
    plt.bar(x, frequencies_shifted, **kwargs, color='yellow', label='Actual')
    plt.title(f'Found key letter: {chr(best_shift + ord("A"))}')
    plt.legend()
    plt.show()
    '''

    return chr(best_shift + ord('A'))

def usage(argc: int):
    if argc == 2:
        print("Usage: python3 main.py [decrypt|encrypt|crack]")
    elif sys.argv[1] == 'decrypt' or sys.argv[1] == 'encrypt':
        print("Usage: python3 main.py [decrypt|encrypt] [textfile] [key]")
    elif sys.argv[1] == 'crack':
        print("Usage: python3 main.py crack [textfile] [keylength]")
    else:
        print("Invalid mode")
    sys.exit(1)

def main():
    if(len(sys.argv) < 3):
        usage(2)
    mode = sys.argv[1]
    textfile = sys.argv[2]
    key = sys.argv[3]
    with open(textfile, "r") as f:
        text = f.read().strip()
        if mode == 'encrypt':
            print(encrypt(text, key))
        elif mode == 'decrypt':
            print(decrypt(text, key))
        elif mode == 'crack':
            print(crack(text, int(key)))
        else:
            usage(3)

if __name__ == '__main__':
    main()
