#ifndef _Wordpronun_H
#define _Wordpronun_H

struct wordpronun
{
    char *word;
    char *pronunciation;
};
typedef struct wordpronun *wp;
typedef wp *ptr2wp;

int checkpronun(wp wopr);
int linecount(char filename[]);
wp initialwp(char *s1word, char *s2pronun);
ptr2wp initialwpList(char *filename);
int *getrandom(int length);
int StripEnter(char *s);
void DestroyWP(ptr2wp);

#endif /* _Wordpronun_H */