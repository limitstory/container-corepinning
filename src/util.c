#include "util.h"

void rid_off_symbol(char *str)
{
    char *temp = (char*)malloc(sizeof(char) * strlen(str) + 1);
    char *ary_fisrt_addr = str;
    char ch;
    int i = 0;
    while (*str)
    {
        ch = *str;
        if ((ch == 95) || (ch == 32) || (ch >= 48 && ch <= 57) || (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122))
        {
            temp[i++] = *str;
        }
        str++;
    }
    strcpy(ary_fisrt_addr, temp);
    free(temp);
    return;
}

void div_byte_recursive(long diviend, long divisor)
{
    if (diviend == 0)
    {
        printf("0B");
         return;
    }
      
    if (diviend / divisor == 0)
        div_byte_recursive(diviend, divisor / KB);
    else
    {
        char unit[5];
        switch (divisor)
        {
            case GB: strcpy(unit, "GB"); break;
            case MB: strcpy(unit, "MB"); break;
            case KB: strcpy(unit, "KB"); break;
            case BYTE: strcpy(unit, "B"); break;
        }
        printf("%.2lf%s", (double)diviend / divisor, unit);
    }
}

void div_bibyte_recursive(long diviend, long divisor)
{
    if (diviend == 0)
    {
        printf("0B");
         return;
    }

    if (diviend / divisor == 0)
        div_bibyte_recursive(diviend, divisor / KiB);
    else
    {
        char unit[5];
        switch (divisor)
        {
            case GiB: strcpy(unit, "GiB"); break;
            case MiB: strcpy(unit, "MiB"); break;
            case KiB: strcpy(unit, "KiB"); break;
            case BYTE: strcpy(unit, "B"); break;
        }
        printf("%.2lf%s", (double)diviend / divisor, unit);
    }
}