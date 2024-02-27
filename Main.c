#include "StrList.h"

char *getString()
{
    int maxLen = 5;
    char *str = (char *)malloc(maxLen * sizeof(char));

    int charecters = 0;
    char c;
    while (1) 
    {
        c = getchar();
        if (c == ' ' || c == '\n')
        { 
            if (charecters == 0)
            {
                continue;
            }
            str[charecters] = '\0';
            break; 
        }
        str[charecters] = c;
        charecters++;
        if (charecters >= maxLen)
        {
            maxLen *= 2;                               
            str = realloc(str, maxLen * sizeof(char)); 
        }
    }
    return str;
}

int main(void)
{
    int comm, index, words;
    char *str;
    StrList *p_strlist = StrList_alloc();

    do
    {
        scanf("%d", &comm);
        if (comm == 1)
        {
            scanf("%d", &words);
            for (int i = 0; i < words; i++)
            {
                str = getString();
                if (str != NULL)
                {
                    StrList_insertLast(p_strlist,str);
                    free(str);
                }
            }
        }
        if (comm == 2)
        {
            scanf(" %d", &index);
            str = getString();
            if (str != NULL)
            {
                StrList_insertAt(p_strlist, str, index);
                free(str);
            }
        }
        if (comm == 3)
        {
            StrList_print(p_strlist);
        }
        if (comm == 4)
        {
            printf("%ld\n", StrList_size(p_strlist));
        }
        if (comm == 5)
        {
            scanf(" %d", &index);
            StrList_printAt(p_strlist, index);
        }
        if (comm == 6)
        {
            printf("%d\n", StrList_printLen(p_strlist));
        }
        if (comm == 7)
        {
            str = getString();
            if (str != NULL)
            {
                printf("%d\n", StrList_count(p_strlist, str));
                free(str);
            }
        }
        if (comm == 8)
        {
            str = getString();
            if (str != NULL)
            {
                StrList_remove(p_strlist, str);
                free(str);
            }
        }
        if (comm == 9)
        {
            scanf(" %d", &index);
            StrList_removeAt(p_strlist, index);
        }
        if (comm == 10)
        {
            StrList_reverse(p_strlist);
        }
        if (comm == 11)
        {
            StrList_free(p_strlist);
        }
        if (comm == 12)
        {
            StrList_sort(p_strlist);
        }
        if (comm == 13)
        {
            if (StrList_isSorted(p_strlist))
                printf("true\n");
            else
                printf("false\n");
        }
    } while (comm != 0);
    StrList_free(p_strlist);
    free(p_strlist);

    return 0;
}