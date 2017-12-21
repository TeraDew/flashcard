#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fatal.h"
#include "wordpronun.h"

#define MAX 1000

int main(int argc, char *argv[])
{

    int n = linecount(argv[1]);

    printf("%d\n", n);

    int *wronglist;
    wronglist = malloc(sizeof(int) * n);

    ptr2wp wplist;
    wplist = initialwpList(argv[1]);

    int *randm;
    randm = getrandom(n);
    int incorrectnumber = 0;
    for (int i = 0; i < n; i++)
    {
        wronglist[randm[i]] = checkpronun(wplist[randm[i]]) ? 0 : 1; /* if correct, index = 0, else =1 */
        incorrectnumber += wronglist[randm[i]];
    }
    if (incorrectnumber != 0)
    {
        FILE *wrfile;
        wrfile = fopen(argv[2], "w");

        puts("Incorrect record:");

        for (int i = 0; i < n; i++)
        {
            if (wronglist[i] == 1)
            {
                printf("%s:%s\t", wplist[i]->word, wplist[i]->pronunciation);
                fputs(wplist[i]->word, wrfile);
                fputs(",", wrfile);
                fputs(wplist[i]->pronunciation, wrfile);
                fputs("\n", wrfile);
            }
        }

        fclose(wrfile);
    }
    else
        puts("Congratulations! All correct.");

    return 0;
}
