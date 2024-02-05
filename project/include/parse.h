#ifndef PARSE_H
#define PARSE_H

// This magic hex code ('LLAD') is used to determine if the file 
// the user is providing us is in fact a database file useable by this program.
#define HEADER_MAGIC 0x4c4c4144

struct dbheader_t
{
    unsigned int magic;
    unsigned short version;
    unsigned short count;
    unsigned int filesize;
};

struct employee_t
{
    char name[255];
    char address[256];
    unsigned int hours;
};

int create_db_header(int fd, struct dbheader_t **headerOut);
int validate_db_header(int fd, struct dbheader_t **headerOut);
int read_employees(int fd, struct dbheader_t *, struct employee_t **employeesOut);
int output_file(int fd, struct dbheader_t *dbhdr);

#endif
