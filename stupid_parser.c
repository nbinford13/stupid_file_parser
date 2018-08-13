#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Structure that mimics a dictionary key and value
struct dict_entry {
    int key;
    int value;
};

int main(int argc, char* argv[])
{
    // Parse file from command line argument
    if (argc != 2)
    {
        printf("Usage:\n");
        printf("./main <file>\n");
        return 1;
    }

    char *file_name = argv[1];

    // Dictionary that holds count of each category
    int dict_size = 40;
    struct dict_entry count_dict[dict_size];
    int i = 0;
    for (i = 0; i < dict_size; i++)
    {
        count_dict[i].key = i;
        count_dict[i].value = 0;
    }

    // The key you are looking for in the file
    char *key = "\"category\":";
    char delimiter = ',';

    // String that will contain the parsed key
    // Size is max number of chars in key (know it won't be longer than that)
    int key_str_size = 3;
    char key_str[key_str_size];
    for (i = 0; i < key_str_size; i++)
        key_str[key_str_size] = ' ';

    // Number of lines in file
    int total = 0;

    // Open file
    FILE* fr = fopen(file_name, "r");
    if (fr == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    // Read file line-by-line
    // Set line and buf_size to NULL and 0 to automatically allocate enough space
    char* line = NULL;
    size_t buf_size = 0;
    while ((getline(&line, &buf_size, fr)) != -1)
    {
        // Substring of file line, starting at desired key
        char* substring = strstr(line, key);
        // Index in substring where you should start looping to get value
        int value_index = strlen(key);
        // Index of storage string, where you want to keep result of verdict
        int key_str_index = 0;
        while (substring[value_index] != delimiter)
        {
            key_str[key_str_index] = substring[value_index];
            value_index++;
            key_str_index++;
        }

        // Extract int verdict from string verdict (atoi is the savior)
        int key_int = atoi(key_str);

        // Update dictionary
        // There's probably a faster way to do this - directly update using memory location?
        for (i = 0; i < dict_size; i++)
        {
            if (count_dict[i].key == key_int)
                count_dict[i].value++;
        }

        // Reset key string
        for (i = 0; i < key_str_size; i++)
            key_str[key_str_size] = ' ';

        total++;
    }

    printf("Total number of lines in file: %d\n", total);

    printf("Total number of each category in file:\n");

    for (i = 0; i < dict_size; i++)
    {
        printf("%d: ", count_dict[i].key);
        printf("%d", count_dict[i].value);
        if (i != (dict_size - 1))
            printf(", ");
    }

    printf("\n");

    fclose(fr);

    // Have to call this at end because getline() automatically allocates space for line
    if (line)
    {
        free(line);
    }
    
    return 0;
}