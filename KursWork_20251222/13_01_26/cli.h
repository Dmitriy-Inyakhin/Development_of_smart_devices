#ifndef CLI_H
#define CLI_H

void print_help(void);
int parse_arguments(int argc, char *argv[], char **filename, int *month_filter);

#endif // CLI_H