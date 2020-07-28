
//! @mainpage
//!
//! Список функций :
//!
//! - @ref QadraticEquation
//! - @ref enter
//! - @ref unittest
//!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char* read_text (const char *file_name);
long size_file(FILE *f);
void split_lines (char* text, int *lines);
int Compare(const char *str1, const char *str2);
struct indication_beginning_size_lines* indication_beginning (char * text, int lines);
void  printf_file(struct indication_beginning_size_lines *array_pointer_start, int lines);
void printf_array(struct indication_beginning_size_lines *array_pointer_start, int lines, const char *title);
int cmp_alpha(char char1);
int  sort_revers(const char *str1, const char *str2);
void  sort(struct indication_beginning_size_lines *array_pointer_start, int lines, int (*function) (const char *str1, const char *str2));

void unit_test_read ();
void unit_test_size();
void unit_test_indication();

//{----------------------------------------------------------------------------------------------------------------
//! @brief   split_lines - соедининяет сторки в одну сокращая пробелы и заменяя пернос строки на \0\n.
//!          A так же подсчитыет количесво строчек в тексте .
//!
//! @param   text  - весь текст.
//! @param   lines - количество строчек.

//}----------------------------------------------------------------------------------------------------------------

void split_lines (char* text, int *lines)
{
    assert(text != NULL);
    assert(lines != NULL);

    int end_line = 0;

    if (text == NULL)
        printf("error, text is Null, in %s, on %d\n", "split_lines\n", __LINE__);

    assert (lines != 0);
//1test\n2txt\n1end
    for (int i = 0; text[i] != '\0'; i++) {
       // printf("i = %d, text[i] = %c, text[i] = %d\n", i, text[i], text[i]);
        if (text[i] == '\n')
        {
            text[i] = '\0';
           // printf("i change n to 0\n");
        }
        if (text[i] == '\0'  && end_line == 1) {
            (*lines)++;
            end_line = 0;
           // printf("lines ++, and lines = %d\n", *lines);
        }
        if ((text[i] != '\0') && (end_line == 0))
            end_line = 1;
    }
    //printf("\n%s\n", text);
    (*lines)++;
}

//{----------------------------------------------------------------------------------------------------------------
//! @brief  unit_test_split - проверочный тест функции соединяющей строки.
//!
//! @param   text  - весь текст.
//! @param   lines - количество строчек.
//!
//! @return  Если количесто сторк совпало с правильным - split lines is ok.
//!          Если не совпало количество строк          - error in split lines и нужное знасение.
//! @code
//!           unit_test_split();
//! @endcode
//}----------------------------------------------------------------------------------------------------------------

void unit_test_split()
{
    FILE *f = fopen("test.txt","w");
    fprintf(f,"3test\n");
    fprintf(f,"2text\n");
    fprintf(f,"1end");
    fclose(f);

    int lines = 0;
    char *text = read_text("test.txt");
    split_lines(text, &lines);

    if (lines != 3)
    {
        printf("error in split lines = %d, but must = (3)\n", lines);
    } else
        printf("split lines is ok\n");

}

//{----------------------------------------------------------------------------------------------------------------
//! @brief   read_text - Выделяет панять под текст.
//!
//! @param   FILE         - исходный текст.
//! @param   lenght       - количество памяти (в бийтах) занимаемое исходным текстом.
//! @param   leenght_read - количество символов в тексте.
//! @param   text         - весь текст.
//!
//! @return  Указатель на блок памяти под текст.
//!
//}----------------------------------------------------------------------------------------------------------------


char* read_text (const char *file_name)
{
    assert(file_name != NULL);

    FILE *f = fopen(file_name, "r");
    if (f == NULL){
        perror("erorr in read");
    }

    long length = size_file (f);

    char *text = (char *) calloc (length + 1, sizeof (char));
    if (text == NULL)
        return 0;

    fseek(f, 0, SEEK_SET);

    long long length_read = fread (text, sizeof (char), length, f);
    //if (length_read != length)
       // printf ("error of read on linux or only one lines\n");

    fclose(f);
    return text;

}

//{----------------------------------------------------------------------------------------------------------------
//! @brief  Compare - Компоратор для сортировки.
//!
//! @param   str1  - первая сравниваемая строка.
//! @param   str2  - вторая сравниваемая строка.
//!
//! @return  Возвращяет меньшую из строк.
//!
//}----------------------------------------------------------------------------------------------------------------


int Compare(const char *str1, const char *str2)
{
    assert(str1 != NULL);
    assert(str2 != NULL);

    return strcmp(str1,str2) < 0;
}

//{----------------------------------------------------------------------------------------------------------------
//! @brief  size_file - находит размер полученного файла .
//!
//! @param   FILE    - исходный текст.
//! @param   lenght  - количество памяти (в бийтах) занимаемое исходным текстом.
//!
//! @return  Значение размера файла.
//!
//}----------------------------------------------------------------------------------------------------------------


long size_file(FILE *f)
{

    assert(f != NULL);

    long length = 0;
    long last_position = ftell(f);

    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, last_position, SEEK_END);

    return length;
}

//{----------------------------------------------------------------------------------------------------------------
//! @brief  unit_test_size - проверочный тест функций на размер текста .
//!
//! @param   FILE    - исходный текст.
//! @param   lenght  - количество памяти (в бийтах) занимаемое исходным текстом.
//!
//! @return  Если размер текста совпал с эталонным    -- size is ok. \n
//!          Если размер текста не совпал с эталонным -- problem in function size полученный результат и эталлонный. \n
//!
//! @code
//!           unit_test_read();
//! @endcode
//}----------------------------------------------------------------------------------------------------------------

void unit_test_size()
{
    FILE *f = fopen("test.txt","w");
    fprintf(f,"3test\n");
    fprintf(f,"2text\n");
    fprintf(f,"1end");
    fclose(f);

    FILE *tests = fopen("test.txt","r");
   int tests_size = size_file(tests);
   //printf("program length = %d\n", tests_size);
    if (tests_size != 18)
        printf("problem in function size size = %d, but must be (18)\n", tests_size);
        else {
            printf("size is ok\n");
        }
    }


//{----------------------------------------------------------------------------------------------------------------
//! @brief  unit_test_read - проверочный тест функций на коректность текста и размера.
//!
//! @param   text - текст файла.
//! @param   size - размер файла.
//! @param   c    - свободный член уравнения находящися по одну сторону с неизвестными.
//!
//! @return  Если текст в файле с текстом полученным после чтения равны -- text is ok. \n
//!          Если текст в файле не совпал с считанным тестом -- Error text in file is wrong - (текст из файла). \n
//!          Если размер файла совпал с полученным размером файла -- Size is ok.\n
//!          Если размер файла не совпал с полученным размером файла --
//!          Error size must be (размер который должен был быть) but (размер который получила функция после работы).
//! @code
//!           unit_test_read();
//! @endcode
//}----------------------------------------------------------------------------------------------------------------


void unit_test_read ()
{
    FILE *f = fopen("test.txt","w");
    fprintf(f,"test\n");
    fprintf(f,"text\n");
    fprintf(f,"end");
    fclose(f);

    f = fopen("test.txt","r");
    char *text = read_text(f);
    long size = size_file(f);
    fclose(f);

    if (size != 16){
        printf("Error size must be 15 but %ld\n", size);
    } else{
        printf("Size is ok\n");
    }

    if (strcmp(text, "test\next\nend") != 0){
        printf("Error text in file is wrong - (%s)\n", text);
    } else {
        printf("Text is ok\n");
    }
}

//{----------------------------------------------------------------------------------------------------------------
//! @brief   indication_beginning - создаёт массив указателей на начало строк.
//!
//! @param   lines    - количество строк в исходном тексте.
//! @param   end_line - флаг показывает является ли текущий элемент началом строки или нет.
//! @param   now_line - параметр отображающий номер строки в которй сейчас мы находимся.
//! @param   text     - исходный текст.
//!
//! @return  Массив укаазателей на начлао каждой из сторк и тексте.
//!
//}----------------------------------------------------------------------------------------------------------------
struct indication_beginning_size_lines
{
    char  *beginning;
    int size;
};


struct indication_beginning_size_lines* indication_beginning (char * text, int lines){

    assert(text != NULL);

    struct indication_beginning_size_lines* array_pointers_start =
            (struct indication_beginning_size_lines*) calloc(lines + 1, sizeof(array_pointers_start[0]));

    int end_line = 1;
    int now_line = 0;

    for (int i = 0; now_line < lines; i++) {
        if ((text[i] != '\0') && (end_line != 0))
        {
            end_line = 0;
            array_pointers_start [now_line] .beginning = &text[i];
            array_pointers_start [now_line] .size = strlen(&text[i]);
            now_line++;
        }
        if (text[i] == '\0') {
            end_line = 1;
        }
    }
    return array_pointers_start;
}

void unit_test_indication()
{
    FILE *f = fopen("test.txt","w");
    fprintf(f,"3test\n");
    fprintf(f,"2text\n");
    fprintf(f,"1end");
    fclose(f);

    char *text = read_text("test.txt");
    int lines = 3;
    split_lines(text, &lines);

    struct indication_beginning_size_lines* array_pointers_start = indication_beginning(text, 3);

   // printf_array(array_pointers_start, 3, "after indication begining");
   // printf("++++++++%s %s", array_pointers_start[0], "3test\n");

    if ((strcmp("3test", array_pointers_start [0] .beginning) != 0) ||
        (strcmp("2text", array_pointers_start [1] .beginning) != 0) ||
        (strcmp("1end",  array_pointers_start [2] .beginning) != 0))
    {
        printf("problem in function indication \n");
        printf("result1 = %d\nresult2 = %d\nresult3 = %d\n",
                strcmp("3test", array_pointers_start [0] .beginning) == 0,
                strcmp("2text", array_pointers_start [1] .beginning) == 0,
                strcmp("1end",  array_pointers_start [2] .beginning) == 0);

        for (int i = 0; i < 3 ; i++)
        {
            printf("i = %d - (((%s)))\n", i, array_pointers_start [i] .beginning);
        }
    } else {
        printf("function indication ok \n");

    }

}

//{----------------------------------------------------------------------------------------------------------------
//! @brief   sort - создаёт массив указателей на начало строк.
//!
//! @param   lines               - количество строк в исходном тексте.
//! @param   array_pointer_start - массив указателей на начор каждой их строк в тексте.
//!
//! @return  Отсортированные строки текста.
//!
//}----------------------------------------------------------------------------------------------------------------

void  sort(struct indication_beginning_size_lines *array_pointer_start, int lines, int (*function) (const char *str1, const char *str2))
{
    assert( function != NULL);
    assert(array_pointer_start != NULL);

    for(int i = 1; i < lines; i++)
        for(int j = 0; j < lines - i; j++)
            if(function(array_pointer_start[j].beginning, array_pointer_start[j + 1].beginning) == 1)
            {
                struct indication_beginning_size_lines time_line = array_pointer_start[j];
                array_pointer_start[j] = array_pointer_start[j+1];
                array_pointer_start[j+1] = time_line;
            }
}

void  printf_file(struct indication_beginning_size_lines *array_pointer_start, int lines)
{
    assert(lines != 0);
    assert(array_pointer_start != NULL);

     FILE *f = fopen("SORTOnegin.txt", "w");
     if(f == NULL){
         perror("error fopen");
     }

     for (int i = 0; i  < lines; i++)
     {
       int er = fprintf (f,"%s\n", array_pointer_start[i].beginning);
        if (er == NULL){
            perror("eroor fprintf");
        }
     }

    int error = fclose(f);
     if (error == NULL){
         perror("error fclose");
     }
}

void printf_array(struct indication_beginning_size_lines *array_pointer_start, int lines, const char *title)
{
    printf("\n%s\n", title);

    for (int i =  0 ; i < lines ; i++)
    {
        printf("%d : (%s)\n", i, array_pointer_start[i].beginning);
    }
    printf("\n");
}

int up_sort(const char *str1, const char *str2)
{
    assert(str1 != NULL);
    assert(str2 != NULL);

    if (strcmp(str1, str2) > 0)
        return 1;
}

int down_sort(const char *str1, const char *str2)
{
    assert(str1 != NULL);
    assert(str2 != NULL);

    if (strcmp(str1, str2) > 0)
        return 1;
}

int  sort_revers(const char *str1, const char *str2)
{
    assert(str1 != NULL);
    assert(str2 != NULL);

    int len_1 = strlen(str1);
    int len_2 = strlen(str2);

    const char *end_1 = str1 + len_1;
    const char *end_2 = str2 + len_2;

    while ((end_1 >= str1) || (end_2 >= str2)) {

        for (int i = len_1; i > 0; i--)
            if (cmp_alpha(*end_1) == 0) end_1--;

        for (int j = len_2; j > 0; j--)
            if (cmp_alpha(*end_2) == 0) end_2--;

        if (*end_1 > *end_2) return 1;
        if (*end_1 < *end_2) return -1;
    }
    return 0;
}

int cmp_alpha(char char1)
{
    const unsigned char A = 192;
    const unsigned char Z = 223;
    const unsigned char a = 224;
    const unsigned char z = 255;

    return ((('A' <= char1) && (char1 <= 'Z')) || (('a' <= char1) && (char1 <= 'z')) ||
            (( (A <= char1) && (char1 <= Z)) || (( a <= char1) && (char1 <= z))));
}



int main()
{
    system("dir");

    unit_test_size();
    unit_test_split();
    unit_test_indication();



    int lines = 0;
    char *text = read_text("../Onegin.txt");
    split_lines(text, &lines);
    //printf("(%s)\n", text);
    struct indication_beginning_size_lines *array_pointer_start = indication_beginning(text, lines);
    //printf("lines = %d\n", lines);
    for (int i = 0; i < lines;i++) {
   //     printf("i = %d (%s)\n", i, array_pointer_start[i].beginning);
    }
    sort(array_pointer_start, lines, &up_sort);
    for (int i = 0; i < lines;i++) {
        printf("i = %d (%s)\n", i, array_pointer_start[i].beginning);
    }

    printf_file(array_pointer_start,lines);

    /* unit_test_size();
     unit_test_split();
     unit_test_indication();
     */
return 0;
}