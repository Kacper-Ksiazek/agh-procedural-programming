#ifndef CLION_UTILS_H
#define CLION_UTILS_H

typedef struct KeyValuePair {
    char *key;
    char *value;
} KeyValuePair;

KeyValuePair extract_data_from_a_single_line(const char *line);

#endif //CLION_UTILS_H
