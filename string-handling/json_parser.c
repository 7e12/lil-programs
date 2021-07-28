/**
 * @author:  7e12
 * @file:    json_parser.c
 * @date:    19 Jul 2021
 * @version: v1.0.0
 * @brief:   Json parser
**/

#include <stdio.h>
#include <string.h>

// User-defined macros
#define DATA_SIZE 1024

// Json parser
int parse_json(const char *p_json, const char *p_name, char *p_value) {
    // Check for existing json, name, and value strings
    if (NULL == p_json || NULL == p_name || NULL == p_value) return -1;

    char *p_writer, *p_anchor;
    p_writer = p_value;

    // Find name if exist
    p_anchor = strstr(p_json, p_name);
    if (NULL == p_anchor) return -1;

    // Write value to output buffer
    p_anchor = p_anchor + strlen(p_name) + 1;
    while (NULL != p_anchor && ',' != *p_anchor && '}' != *p_anchor) {
        if(NULL == strchr(": \r\n\t", *p_anchor)) {
            *p_writer = *p_anchor;
            ++p_writer;
        }

        ++p_anchor;
    }
    *p_writer = 0;

    return 1;
}

// Main program
int main(int argc, char const *argv[]) {
    char full_data[DATA_SIZE]   = "{\r\n\t\"a\": 1,\r\n\t\"b\": 2,\r\n\t\"c\": \"x\",\r\n\t\"d\": \"y\",\r\n}";
    char clean_data[DATA_SIZE]  = "{\"a\":1,\"b\":2,\"c\":\"x\",\"d\":\"y\",}";
    char value[DATA_SIZE]       = {0};

    // Usage for full format data (json)
    printf("Full data:\r\n%s\r\n", full_data);
    printf("Return: %d\r\n", parse_json(full_data, "a", value));
    printf("Value of \"a\": %s\r\n", value);

    // Usage for clean format data (json)
    printf("Clean data:\r\n%s\r\n", clean_data);
    printf("Return: %d\r\n", parse_json(clean_data, "c", value));
    printf("Value of \"c\": %s\r\n", value);

    return 0;
}
