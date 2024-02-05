#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>

#include "../include/parse.h"
#include "../include/common.h"

void list_employees(struct dbheader_t *dbhdr, struct employee_t *employees)
{
    for (int i = 0; i < dbhdr->count; i++)
    {
        printf("Employee: %d\n", i);
        printf("\tName: %s\n", employees[i].name);
        printf("\tAddr: %s\n", employees[i].address);
        printf("\tHours: %d\n", employees[i].hours);
    }
}

int add_employee(struct dbheader_t *dbhdr, struct employee_t *employees, char *addstring)
{
    char *name = strtok(addstring, ",");
    char *addr = strtok(NULL, ",");
    char *hours = strtok(NULL, ",");

    strncpy(employees[dbhdr->count-1].name, name, sizeof(employees[dbhdr->count-1].name));
    strncpy(employees[dbhdr->count-1].address, addr, sizeof(employees[dbhdr->count-1].address));
    employees[dbhdr->count-1].hours = atoi(hours);
    
    return STATUS_SUCCESS;
}

int read_employees(int fd, struct dbheader_t *dbhdr, struct employee_t **employeesOut)
{
    if (fd < 0)
    {
        printf("Got a bad file from the user\n");
        return STATUS_ERROR;
    }

    int count = dbhdr->count;

    struct employee_t *employees = calloc(count, sizeof(struct employee_t));
    if (employees == NULL)
    {
        printf("Employee memroy allocation failed\n");
        return STATUS_ERROR;
    }

    if (read(fd, employees, count*sizeof(struct employee_t)) == -1)
    {
        perror("read");
        free(employees);
        return STATUS_ERROR;
    }

    for (int i = 0; i < count; i++)
    {
        employees[i].hours = ntohl(employees[i].hours);
    }

    *employeesOut = employees;

    return STATUS_SUCCESS;
}

int output_file(int fd, struct dbheader_t *dbhdr, struct employee_t *employees)
{
    if (fd < 0)
    {
        printf("Got a bad file from the user\n");
        return STATUS_ERROR;
    }

    int realcount = dbhdr->count;

    dbhdr->magic = htonl(dbhdr->magic);
    dbhdr->filesize = htonl(sizeof(struct dbheader_t) + (sizeof(struct employee_t) * realcount));
    dbhdr->count = htons(dbhdr->count);
    dbhdr->version = htons(dbhdr->version);

    lseek(fd, 0, SEEK_SET);
    if (write(fd, dbhdr, sizeof(struct dbheader_t)) == -1)
    {
        printf("Failed to write database header\n");
        return STATUS_ERROR;
    }

    for (int i = 0; i < realcount; i++)
    {
        employees[i].hours = htonl(employees[i].hours);
        if (write(fd, &employees[i], sizeof(struct employee_t)) == -1)
        {
            printf("Failed to write employee to database\n");
            return STATUS_ERROR;
        }
    }

    return STATUS_SUCCESS;
}

int validate_db_header(int fd, struct dbheader_t **headerOut)
{
    if (fd < 0)
    {
        printf("Got a bad file from the user\n");
        return STATUS_ERROR;
    }

    struct dbheader_t *header = calloc(1, sizeof(struct dbheader_t));
    if (header == NULL)
    {
        printf("Failed to create db header\n");
        return STATUS_ERROR;
    }

    if (read(fd, header, sizeof(struct dbheader_t)) != sizeof(struct dbheader_t))
    {
        perror("read");
        free(header);
        return STATUS_ERROR;
    }

    header->version = ntohs(header->version);
    header->count = ntohs(header->count);
    header->magic = ntohl(header->magic);
    header->filesize = ntohl(header->filesize);

    if (header->magic != HEADER_MAGIC)
    {
        printf("Failed file type validation check\n");
        free(header);
        return STATUS_ERROR;
    }

    if (header->version != 1)
    {
        printf("Improper header version\n");
        free(header);
        return STATUS_ERROR;
    }

    struct stat dbstat = {0};
    fstat(fd, &dbstat);
    if (header->filesize != dbstat.st_size)
    {
        printf("Corrupted database\n");
        free(header);
        return STATUS_ERROR;
    }

    *headerOut = header;

    return STATUS_SUCCESS;
}

int create_db_header(int fd, struct dbheader_t **headerOut)
{
    struct dbheader_t *header = calloc(1, sizeof(struct dbheader_t));
    if (header == NULL)
    {
        printf("Failed to create db header\n");
        return STATUS_ERROR;
    }

    header->version = 0x1;
    header->count = 0;
    header->magic = HEADER_MAGIC;
    header->filesize = sizeof(struct dbheader_t);

    *headerOut = header;

    return STATUS_SUCCESS;
}
