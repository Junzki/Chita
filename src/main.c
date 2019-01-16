#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <poll.h>
#include <unistd.h>


void die(const char*);
void bye(int);
void sigint_handler(int);
void get_input(char**, int, ssize_t);
void idiot_core(char*);


int
main(void)
{
    signal(SIGINT, sigint_handler);

    int    retval;

    ssize_t count;  /* Total bytes available. */
    char*   input_str = NULL;

    struct pollfd fdset = {
        .fd = STDIN_FILENO,
        .events = POLLIN
    };

    puts("Hallo, das ist Chita.");

    while (1)
    {
        count = 0;  /* Reset counter. */
        retval = poll(&fdset, 1, 5000);

        if (!retval)
        {
            puts("hhhhhhhhhhh.");
            continue;
        }

        ioctl(STDIN_FILENO, FIONREAD, &count);
        get_input(&input_str, STDIN_FILENO, count);
        puts(input_str);
    }

    return EXIT_SUCCESS;
}


void
get_input(char** input_str, int fd, ssize_t count)
{
    ssize_t nread = 0;
    ssize_t rolls = count / BUFSIZ + 1;
    ssize_t index = 0;

    *input_str = (char*)malloc(count);
    if (NULL == *input_str)
        die("Cannot allocate memory.");

    memset(*input_str, 0, count);

    for (index = 0; index < rolls; ++index)
    {
        ssize_t pos = index * BUFSIZ;
        nread = read(fd, *input_str + pos, BUFSIZ);
    }

    (*input_str)[count] = '\0';  /* Append suffix flag. */
}


void
die(const char *message)
{
    perror(message);
    bye(EXIT_FAILURE);
}


void
bye(int status)
{
    puts("\nVielen Dank!");
    exit(status);
}


void
sigint_handler(int signo)
{
    bye(EXIT_SUCCESS);
}


void idiot_core(char *input)
{
    if (NULL == input)
        return;

    if ('\n' == input[0])
    {
        puts("Nichts da!");
        return;
    }
}
