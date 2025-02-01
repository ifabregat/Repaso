#include <stdlib.h>
#include <string.h>

// Given a string s, find the length of the longest
// substring
// without repeating characters.

int lengthOfLongestSubstring(char* s) {
    size_t len = strlen(s);
    size_t i = 0;
    size_t max = 0;

    while (i < len) {
        size_t j = i;
        size_t count = 0;
        char* chars = (char*)calloc(256, sizeof(char));

        while (j < len && chars[s[j]] == 0) {
            chars[s[j]] = 1;
            count++;
            j++;
        }

        if (count > max) {
            max = count;
        }

        free(chars);
        i++;
    }

    return max;
}