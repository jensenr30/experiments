#include <stdio.h>
#include <time.h>
int main ()
{
    time_t sec;
    sec = time (NULL);

    printf ("Number of seconds since January 1, 1970 is %ld \n", sec);
    system("pause");
    return 0;
}
