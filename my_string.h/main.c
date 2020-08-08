#include <stdio.h>
#include <string.h>

const char *my_strchr(const char str[], const char ch);
int my_strlen (const char* str);
int my_strpbrk (const char str[], const char set[]);

int my_strlen (const char* str)
{
    if (str == NULL)
    {
        return 0;
    }

    int size = 0;
    for (int i = 0; str[i] != '\0'; i++)
        size++;

    return size;

}

int max (int a, int b)
{
    if (a > b) return a;
    else       return b;
}

int my_strpbrk (const char str[], const char set[])
{

    for (int i_str = 0; str[i_str]; i_str++)
    {
        for (int i_set = 0; set[i_set]; i_set++)
        {

            if (set[i_set] == str[i_str]) return i_str;

        }
    }

    return -1;

}

void unit_tets_strpbrk()
{
    int result = my_strpbrk("bBoAcdef ghij", "aie");


    if (result == 6) printf("strpbrk is ok, result = %d\n",     result);
    else             printf("error in strpbrk, result =  %d\n", result);

}

int my_strspn (const char str[], const char set[])
{
    int result = 0;

    for (int i_str = 0; str[i_str]; i_str++)
    {

            //printf("\nstr[%d] = %d - %c, result = %d... ", i_str, str[i_str], str[i_str], result);
            if (my_strchr(set, str[i_str]))
            {
                result++;
              //  printf("result++ = %d", result);
            }
            else
                return result;

    }
}

const char *my_strchr(const char str[], const char ch)
{
    for(int i_str = 0; str[i_str]; i_str++)
    {
        if (str[i_str] == ch) return &str[i_str];
    }
    return NULL;
}

void uni_tetst_strspn()
{
    int result = my_strspn("ieaaiAaf aij", "aie");
    if (result == 5) printf("strspn is ok, result = %d\n",    result);
    else             printf("error in strspn, result = %d\n", result);
}


char* my_strtok (char str[], const char delimiters[])
{

    char *beginning = NULL;
    static char *finish = NULL;

    if(!str)
    {
        // printf("finish = %c    ", *finish);
        str = finish;
    }

    char *i_str = str;
    for ( ; *i_str; i_str++) {
        // printf("first for is ok, ");
        if (!my_strchr(delimiters, *i_str)) {
            // printf("beginning = %c   ", *beginning);
            break;
        }
    }

    beginning = i_str;

    for (char *i_str_begin = i_str; *i_str_begin; i_str_begin++)
    {
        if (my_strchr(delimiters, *i_str_begin))
        {
            *i_str_begin = '\0';
            finish = i_str_begin + 1;
            //printf("first finish = %d   \n", finish);

            return beginning;
        }
    }

    return NULL;
}

void unit_tets_strtok() {
    char str[] = "; iii_m am ,. stu;";
    char delim[] = " ;";
    char *end = my_strtok(str, delim);
    while (end != NULL) {
        printf("*");
        printf("(%s)\n", end);
        end = my_strtok(NULL, delim);

    }
}


int main() {

    unit_tets_strpbrk();
    uni_tetst_strspn();
    unit_tets_strtok();

    return 0;
}
