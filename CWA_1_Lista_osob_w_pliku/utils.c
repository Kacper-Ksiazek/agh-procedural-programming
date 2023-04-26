#include "utils.h"
#include "string.h"
#include "stdlib.h"

KeyValuePair extract_data_from_a_single_line(const char *line){
    char* key = (char*)calloc(32,sizeof(char));
    int key_length = 0;

    char* value = (char*)calloc(32,sizeof(char));
    int value_length = 0;

    int i =0;
    // Remove all spaces from the beginning
    while(line[i]==' ') i++;
    while(line[i]!=':') key[key_length++]=line[i++];

    i+=2;
    while(line[i]!='\n') value[value_length++] = line[i++];

    return (KeyValuePair){key,value};
}
