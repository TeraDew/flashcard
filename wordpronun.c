#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fatal.h"
#include "wordpronun.h"

#define MAX 1000

// struct wordpronun
// {
//     char *word;
//     char *pronunciation;
// };

wp initialwp(char *s1word, char *s2pronun)
{
    /* generate a struct wordpronun */
    wp wopr;
    wopr = malloc(sizeof(struct wordpronun));
    if (wopr == NULL)
        FatalError("Out of space!!!");
    wopr->word = malloc(sizeof(char) * (strlen(s1word) + 1));
    if (wopr->word == NULL)
        FatalError("Out of space!!!");
    wopr->pronunciation = malloc(sizeof(char) * (strlen(s2pronun) + 1));
    strcpy(wopr->word, s1word);
    if (wopr->pronunciation == NULL)
        FatalError("Out of space!!!");
    strcpy(wopr->pronunciation, s2pronun);
    return wopr;
}

ptr2wp initialwpList(char *filename)
{
    /* generate a list of struct wordpronun */

    int lineCnt = linecount(filename);

    FILE *fp = fopen(filename, "rt");

    if (fp == NULL)
        FatalError("No such a file!!!");

    char s1[MAX],
        *s2, *s3;

    wp *wplist;
    wplist = malloc(sizeof(wp) * lineCnt);
    if (wplist == NULL)
        FatalError("Out of space!!!");
    int i;
    for (i = 0; i < lineCnt; i++)
    {
        fgets(s1, MAX, fp);
        s2 = strtok(s1, ",\n");
        s3 = strtok(NULL, ",\n");
        wplist[i] = initialwp(s2, s3);
    }
    fclose(fp);

    return wplist;
}

int checkpronun(wp wopr)
{
    //printf("%s,%s", wopr->word, wopr->pronunciation);
    char s[MAX];
    printf("%s:", wopr->word);
    fgets(s, MAX, stdin);
    StripEnter(s);
    if (strcmp(wopr->pronunciation, s) == 0)
    {
        puts("correct!");
        return 1;
    }
    else
    {
        printf("wrong, %s\n", wopr->pronunciation);
        return 0;
    }
}

int linecount(char filename[])
{
    FILE *pfile;
    pfile = fopen(filename, "rt");

    if (pfile == NULL)
        FatalError("No such a file!!!");

    char buf[MAX];
    int lineCnt = 0;
    if (!pfile)
        FatalError("No such a file!");
    while (fgets(buf, MAX, pfile))
        lineCnt++;
    fclose(pfile);
    return lineCnt;
}

int *getrandom(int length)
{
    /* get random integer from 0 to n-1 and fill it in the array */
    int *n;
    int *m;
    int i, j;
    n = malloc(sizeof(int) * length);
    m = malloc(sizeof(int) * length);
    if (n == NULL || m == NULL)
        FatalError("Out of space!!!");
    srand((unsigned)time(NULL));

    for (i = 0; i < length; i++)
    { /* mark if this integer has generated */
        m[i] = 1;
    }

    for (i = 0; i < length; i++)
    {
        do
        {
            j = rand() % length;
        } while (m[j] == 0);

        n[i] = j;
        m[j] = 0;
    }
    free(m);
    return n;
}

int StripEnter(char *s)
{
    int i;
    i = strlen(s);
    while (s[i - 1] != '\n' && i > 0)
        i--;
    if (i == 0)
        return -1;
    else
    {
        s[i - 1] = '\0';
        return 1;
    }
}