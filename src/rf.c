#include "rf.h"

static int check_extension(char *filename, char *expected)
{
    char *e = calloc(1, sizeof(char));
    int e_i = 0;

    for(int i = 0; i < str_len(filename); i++)
    {
        if(filename[i] == '.')
        {
            i++;
            while(i < str_len(filename))
            {
                e[e_i] = filename[i];

                e = realloc(
                    e,
                    (e_i + 2) * sizeof(char)
                );
                i++;
                e_i++;
            }
            break;
        }
    }
    return (cmp_str(e, expected) == 0) ? 0 : 1;
}

char *read_file(char *filename)
{
    if(check_extension(filename, "mffs") == 0)
    {
        FILE* file = fopen(filename, "r");

        if(!(file))
        {
            fprintf(stderr, "No such file %s", filename);
            exit(EXIT_FAILURE);
        }

        fseek(file, 0, SEEK_END);
        size_t size = ftell(file);
        fseek(file, 0, SEEK_SET);

        if((int)size < 0)
        {
            fprintf(stderr, "No metadata in %s", filename);
            exit(EXIT_FAILURE);
        }

        char *data = calloc(1, size);
        fread(data, 1, size, file);
        fclose(file);

        return data;
    } else {
        fprintf(stderr, "Expected .mffs file.");
        exit(EXIT_FAILURE);
    }
}