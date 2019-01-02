#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>


void
bye()
{
    puts("\nVielen Dank!");
    exit(EXIT_SUCCESS);
}


void
sigint_handler(int signo)
{
    bye();
}


int
main(void)
{
    signal(SIGINT, sigint_handler);

    fd_set rfds;
    struct timeval tv;
    int    retval;

    ssize_t nread;
    char    buf[BUFSIZ];

    FD_ZERO(&rfds);
    FD_SET(STDIN_FILENO, &rfds);

    tv.tv_sec = 5;
    tv.tv_usec = 0;

    puts("Hallo, das ist Chita.");

    retval = select(1, &rfds, NULL, NULL, &tv);
    while (retval)
    {
        nread = 0;
        memset(&buf, 0, BUFSIZ);  /* Flush buffer. */

        nread = read(STDIN_FILENO, buf, BUFSIZ);
        puts(buf);
    }

    if (-1 == retval)
    {
        perror("Something wrong with `select()`.");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
