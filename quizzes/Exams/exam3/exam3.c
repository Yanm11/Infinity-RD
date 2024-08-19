#include <stdio.h>
#include <string.h>

// Function to swap characters
void swap(char *x, char *y) {
    char temp = *x;
    *x = *y;
    *y = temp;
}

// Function to generate permutations of a given string
void permute(char *str, int left, int right) {
    int i;
    if (left == right) {
        printf("%s\n", str);
    } else {
        for (i = left; i <= right; i++) {
            swap((str + left), (str + i));
            permute(str, left + 1, right);
            swap((str + left), (str + i)); // backtrack
        }
    }
}

// Function to generate all permutations of all substrings
void generate_permutations(char *str) {
    int len = strlen(str);
    int i, j;

    // Generate all substrings
    for (i = 0; i < len; i++) {
        for (j = i; j < len; j++) {
            char substring[100]; // Assumes a maximum substring length of 99
            strncpy(substring, &str[i], j - i + 1);
            substring[j - i + 1] = '\0';

            // Generate permutations of the substring
            permute(substring, 0, strlen(substring) - 1);
        }
    }
}

int main() {
    char str[] = "abcd";
    generate_permutations(str);
    return 0;
}
