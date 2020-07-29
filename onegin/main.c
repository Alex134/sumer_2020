
//! @mainpage
//!
//! Список функций :
//!
//! - @ref read_text
//! - @ref size_file
//! - @ref split_lines
//! - @ref printf_file
//! - @ref printf_array
//! - @ref cmp_alpha
//! - @ref sort_revers
//! - @ref sort
//! - @ref unit_test_read
//! - @ref unit_test_size
//! - @ref unit_test_indication
//! - @ref Compare
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
int  sort_revers(const struct indication_beginning_size_lines *array_pointer_start_1,
                 const struct indication_beginning_size_lines *array_pointer_start_2);
void sort(struct indication_beginning_size_lines *array_pointer_start, int lines,
          int (*function) (const struct indication_beginning_size_lines *array_pointer_start_1,
                           const struct indication_beginning_size_lines *array_pointer_start_2));

void unit_test_read ();
void unit_test_size();
void unit_test_indication();

struct indication_beginning_size_lines
{
    char  *beginning;
    int size;
};

//{----------------------------------------------------------------------------------------------------------------
//! @brief   Соедининяет сторки в одну сокращая пробелы и заменяя пернос строки на \0\n.
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
//! @brief  Проверочный тест функции соединяющей строки.
//!
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
//! @brief   Выделяет память под текст.
//!
//! @param   file_name  - указатель на файл.
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
//! @brief  Компоратор для сортировки.
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
//! @brief  Находит размер полученного файла .
//!
//! @param   file    - исходный текст.
//!
//! @return  Значение размера файла.
//!
//}----------------------------------------------------------------------------------------------------------------


long size_file(FILE *file)
{

    assert(file != NULL);

//! length -  эта перменная нужна мне потому что я мидия
    long length = 0;

//! last_position - дед сам такой
    long last_position = ftell(file);

    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, last_position, SEEK_END);

    return length;
}

//{----------------------------------------------------------------------------------------------------------------
//! @brief  Проверочный тест функций на размер текста .
//!
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
//! @brief  Проверочный тест функций на коректность текста и размера.
//!
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
//! @brief   Создаёт структуру  указателей на начало строк и длинны этой строки.
//!
//! @param   lines    - количество строк в исходном тексте.
//! @param   text     - исходный текст.
//!
//! @return  Структуру укаазателей на начлао каждой из сторк и их длину.
//!
//}----------------------------------------------------------------------------------------------------------------


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


//{----------------------------------------------------------------------------------------------------------------
//! @brief   Проверяет на коректность работу функции создания стуркуры указателя на начало и длины строки в тексте.
//!
//!
//! @return  Структуру укаазателей на начлао каждой из сторк и их длину.
//!
//}----------------------------------------------------------------------------------------------------------------

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
//! @brief   Сортирует текст в зависимости от переданной в неё функции.
//!
//! @param   lines               - количество строк в исходном тексте.
//! @param   array_pointer_start - структура из массива указателей на начор каждой их строк в тексте и её длинны.
//! @param   function            - компоратор для сортировки.
//!
//! @return  Отсортированные строки текста.
//!
//}----------------------------------------------------------------------------------------------------------------

void sort(struct indication_beginning_size_lines *array_pointer_start, int lines,
          int (*function) (const struct indication_beginning_size_lines *array_pointer_start_1,
                           const struct indication_beginning_size_lines *array_pointer_start_2))
{
    assert( function != NULL);
    assert(array_pointer_start != NULL);


    for(int i = 1; i < lines; i++)
        for(int j = 0; j < lines - i; j++)
            if(function(&array_pointer_start[j], &array_pointer_start[j + 1]) == 1)
            {
                struct indication_beginning_size_lines time_line = array_pointer_start[j];
                array_pointer_start[j] = array_pointer_start[j+1];
                array_pointer_start[j+1] = time_line;
            }
}

//{----------------------------------------------------------------------------------------------------------------
//! @brief   Печатает в файл текущий текст.
//!
//! @param   lines               - количество строк в исходном тексте.
//! @param   array_pointer_start - структура из указателей на начало каждой их строк в тексте и их длины.
//!
//! @return  Текст в файл.
//!
//}----------------------------------------------------------------------------------------------------------------

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

//{----------------------------------------------------------------------------------------------------------------
//! @brief   Печатает массив структур .
//!
//! @param   lines               - количество строк в исходном тексте.
//! @param   array_pointer_start - структура из указателей на начало каждой их строк в тексте и их длины.
//! @param   title               - название или заголовок рспечатки.
//!
//! @return  Текст в файл.
//!
//}----------------------------------------------------------------------------------------------------------------

void printf_array(struct indication_beginning_size_lines *array_pointer_start, int lines, const char *title)
{
    printf("\n%s\n", title);

    for (int i =  0 ; i < lines ; i++)
    {
        printf("%d : (%s)\n", i, array_pointer_start[i].beginning);
    }
    printf("\n");
}

//{----------------------------------------------------------------------------------------------------------------
//! @brief   Функция для сортировки текста по возростанию .
//!
//! @param   array_pointer_start_1 - первая структура с строкой для сортировики.
//! @param   array_pointer_start_2 - вторая структура с строкой для сортировки.
//!
//!
//! @return  1 - если сорировка прошла успешно.
//!
//}----------------------------------------------------------------------------------------------------------------

int up_sort (const struct indication_beginning_size_lines *array_pointer_start_1,
             const struct indication_beginning_size_lines *array_pointer_start_2)
{
    assert(array_pointer_start_1 != NULL);
    assert(array_pointer_start_2 != NULL);

    if (strcmp(array_pointer_start_1->beginning, array_pointer_start_2->beginning) > 0)
        return 1;
}

//{----------------------------------------------------------------------------------------------------------------
//! @brief   Функция для сортировки текста по убыванию.
//!
//! @param   array_pointer_start_1 - первая структура с строкой для сортировики.
//! @param   array_pointer_start_2 - вторая структура с строкой для сортировки.
//!
//!
//! @return  1 - если сорировка прошла успешно.
//!
//}----------------------------------------------------------------------------------------------------------------

int down_sort(const struct indication_beginning_size_lines *array_pointer_start_1,
              const struct indication_beginning_size_lines *array_pointer_start_2)
{
    assert(array_pointer_start_1 != NULL);
    assert(array_pointer_start_2 != NULL);

    if (strcmp(array_pointer_start_1->beginning, array_pointer_start_2->beginning) > 0)
        return 1;
}

//{----------------------------------------------------------------------------------------------------------------
//! @brief   Функция для сортировки текста начиная с конца по возрастанию .
//!
//! @param   array_pointer_start_1 - первая структура с строкой для сортировики.
//! @param   array_pointer_start_2 - вторая структура с строкой для сортировки.
//!
//!
//! @return  1 - если сорировка прошла успешно.
//!
//}----------------------------------------------------------------------------------------------------------------

int  sort_revers(const struct indication_beginning_size_lines *array_pointer_start_1,
                 const struct indication_beginning_size_lines *array_pointer_start_2)
{
    assert(array_pointer_start_1 != NULL);
    assert(array_pointer_start_2 != NULL);


    int len_1 = array_pointer_start_1->size;
    int len_2 = array_pointer_start_2->size;

    const char *end_1 = array_pointer_start_1->beginning + len_1;
    const char *end_2 = array_pointer_start_2->beginning + len_2;

    while ((end_1 >= array_pointer_start_1->beginning) || (end_2 >= array_pointer_start_2->beginning)) {

        for (int i = len_1; i > 0; i--)
            if (cmp_alpha(*end_1) == 0) end_1--;

        for (int j = len_2; j > 0; j--)
            if (cmp_alpha(*end_2) == 0) end_2--;

        if (*end_1 > *end_2) return 1;
        if (*end_1 < *end_2) return -1;
    }
    return 0;
}
//{----------------------------------------------------------------------------------------------------------------
//! @brief   Функция для проверки является ли символ буквой .
//!
//! @param   char1 - символ передающийся для проверки.
//!
//! @return  1 - если буква и 0 - если  нет.
//!
//}----------------------------------------------------------------------------------------------------------------

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