#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <poll.h>
#include <unistd.h>


void die(const char*);
void bye(int);
void sigint_handler(int);
void check_locale();

void idiot_core(char*);


int
main(void)
{
    signal(SIGINT, sigint_handler);
    check_locale();

    int    retval;

    ssize_t nread;
    char    buf[BUFSIZ];

    struct pollfd fdset = {
        .fd = STDIN_FILENO,
        .events = POLLIN
    };

    puts("Hallo, das ist Chita.");

    while (1)
    {
        retval = poll(&fdset, 1, 1000);

        if (!retval)
        {
            puts("hhhhhhhhhhh.");
            continue;
        }
            
        nread = 0;
        memset(&buf, 0, BUFSIZ);  /* Flush buffer. */

        nread = read(STDIN_FILENO, buf, BUFSIZ);
        puts(buf);
    }

    return EXIT_SUCCESS;
}


void
die(const char *message)
{
    perror(message);
    bye(EXIT_FAILURE);
}


void
check_locale()
{
    char    *locale    = NULL;
    char    *conv_flag = NULL;
    ssize_t siz        = 0;

    locale = setlocale(LC_CTYPE, "");
    if (NULL == locale || (siz = strlen(locale)) == 0)
        die("Locale not set.");

    conv_flag = strstr(locale, "UTF-8");
    if (NULL == conv_flag)
        die("Bad locale, only UTF-8 supported.");
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
