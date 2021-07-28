/**
 * @author:  7e12
 * @file:    json_generator.c
 * @date:    19 Jul 2021
 * @version: v1.0.0
 * @brief:   Json generator
**/

#include <stdio.h>
#include <string.h>

// User-defined macros
#define DATA_SIZE 1024

// Json generator
char* generate_json(char *p_json, const char *p_name, const char *p_value, const int index) {
    // Check for non-empty name and positive index
    if (0 == strlen(p_name) || 0 >= index) return p_json;

    // Create local variables
    char mark[2] = {0};
    char *p_anchor;
    int space, length, times = 0;

    // Check value is alpha or digit
    for (int i = 0; i < strlen(p_value); ++i) {
        if(p_value[i] < '0' || p_value[i] > '9') {
            sprintf(mark, "\"");
            break;
        }
    }

    // Add curly brackets if not exist
    if (NULL == strchr(p_json, '{')) {
        sprintf(p_json, "{\r\n}");
    }

    p_anchor = strchr(p_json, '{') + 1;
    space = strlen(p_name) + strlen(p_value) + 32;

    // Add name and value to json string
    if (1 == index) {
        strcpy(p_anchor + space, p_anchor);
        length = sprintf(p_anchor, "\r\n\t\"%s\": %s%s%s,", p_name, mark, p_value, mark);
        strcpy(p_anchor + length, p_anchor + space);
    } else {
        // Find position to add name and value
        while (times < index - 1) {
            if (NULL == strchr(p_anchor, ',')) break;

            p_anchor = strchr(p_anchor, ',') + 1;
            ++times;
        }

        strcpy(p_anchor + space, p_anchor);
        length = sprintf(p_anchor, "\r\n\t\"%s\": %s%s%s,", p_name, mark, p_value, mark);
        strcpy(p_anchor + length, p_anchor + space);
    }

    return p_json;    
}

// Main program
int main(int argc, char const *argv[]) {
    char data[DATA_SIZE] = {0};

    // Wrong adding
    generate_json(data, "", "", 1);
    generate_json(data, "z", "0", 0);

    // Right adding
    generate_json(data, "a", "1", 1);
    generate_json(data, "c", "x", 2);
    generate_json(data, "d", "y", 3);
    generate_json(data, "b", "2", 2);

    // Result
    printf("Data:\r\n%s\r\n", data);

    return 0;
}
