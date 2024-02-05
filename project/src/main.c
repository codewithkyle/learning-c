#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>

#include "../include/common.h"
#include "../include/file.h"
#include "../include/parse.h"

void print_usage(char *argv[])
{
    printf("Usage: %s -n -f <database file>\n", argv[0]);
    printf("\t -n  - create new database file\n");
    printf("\t -f  - (required) path to database file\n");
}

int main(int argc, char *argv[])
{
    bool newFile = false;
    char *filepath = NULL;
    int c;

    int dbfd = -1;
    struct dbheader_t *dbhdr = NULL;

    while ((c = getopt(argc, argv, "nf:")) != -1)
    {
        switch (c)
        {
            case 'n':
                newFile = true;
                break;
            case 'f':
                filepath = optarg; // optarg exists becaues of the : after f in getopt 
                break;
            case '?':
                printf("Unknown option -%c\n", c);
                break;
            default:
                return -1;
        }
    }

    if (filepath == NULL)
    {
        printf("Filepath is a requried argument\n");
        print_usage(argv);
        return 0;
    }

    if (newFile)
    {
        dbfd = create_db_file(filepath);
        if (dbfd == STATUS_ERROR)
        {
            printf("Unable to create database file\n");
            return -1;
        }
        if (create_db_header(dbfd, &dbhdr) == STATUS_ERROR)
        {
            printf("Unable to create database header\n");
            return -1;
        }
    }
    else
    {
        dbfd = open_db_file(filepath);
        if (dbfd == STATUS_ERROR)
        {
            printf("Unable to open database file\n");
            return -1;
        }
        if (validate_db_header(dbfd, &dbhdr) == STATUS_ERROR)
        {
            printf("Failed to validate database header\n");
            return -1;
        }
    }

    printf("Newfile: %d\n", newFile);
    printf("Filepath: %s\n", filepath);

    if (output_file(dbfd, dbhdr) == STATUS_ERROR)
    {
        printf("Unable to write to database file\n");
        return -1;
    }

    return 0;
}
