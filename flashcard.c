#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fatal.h"
#include "wordpronun.h"

#define MAX 1000

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        puts("You must give a input file that contains database and a output file to store your test result (if there is).");
        puts("For example:\n\tflashcard katekana.txt result.txt");
        return -1;
    }

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
        if (wrfile == NULL)
        {
            printf("Error! Can't generate the file:\"%s\"", argv[2]);
            return -1;
        }

        printf("Sorry, you need to spend more effort of these:\n");

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

    DestroyWP(wplist);
    free(randm);
    return 0;
}
