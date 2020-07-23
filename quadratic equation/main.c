//! @mainpage
//!
//! Список функций :
//!
//! - @ref QadraticEquation
//! - @ref enter
//! - @ref unittest
//!


#include <stdio.h>
#include <math.h>

const int Infinity = 10;
//{----------------------------------------------------------------------------------------------------------------
//! @brief   Решает квадратное уравнение.
//!
//! @param   a    - певый коэфицент уравнеия стоящий при  х в квадрате.
//! @param   b    - второй коэфицент уравнеия стоящий при  х.
//! @param   c    - свободный член уравнения находящися по одну сторону с неизвестными.
//! @param   y1   - первый корень решения уравнения.
//! @param   y2   - второй корень решения уравнения.
//!
//! @return  Если операция была успешна и найдено 2 решения -- 2. \n
//!          Если было найдено 1 решение -- 1.\n
//!          Если не надено ни одного решения и при этом их не бесконечно -- 0. \n
//!          Если их бесконечное число -- 10.
//!
//! @code
//!          QadraticEquation (10, 50, 100, 500);
//! @endcode
//}----------------------------------------------------------------------------------------------------------------


int QadraticEquation (double a, double b, double c, double* y1, double* y2)
{

    if (a == 0){
        if (b == 0){
            if (c == 0){
                return Infinity;
            } else {
                return 0;
            }
        } else {
           *y1 = -b / (2 * a);
            return 1;
        }
    } else {
        double d = (b * b - 4 * a * c);
        if (d < 0) {
            return 0;
        } else {
            d = sqrt(d);
            a = 2 * a;
            if (d == 0) {
                if (b == 0){
                    *y1 = 0;
                }
                else
                    *y1 = (-b) / a;
                return 1;
            } else {
                *y1 = (-b + d) / a;
                *y2 = (-b - d) / a;
                return 2;
            }
        }
    }
}

void clear(){
    while (getc(stdin) != EOF){
        ;
    }
}

//{----------------------------------------------------------------------------------------------------------------
//! @brief   Принимает значения коэфицентов при неизвестных.
//!
//! @param   a    - певый коэфицент уравнеия стоящий при  х в квадрате.
//! @param   b    - второй коэфицент уравнеия стоящий при  х.
//! @param   c    - свободный член уравнения находящися по одну сторону с неизвестными.
//!
//!
//! @code
//!          enter (&a, &b, &c);
//! @endcode
//}----------------------------------------------------------------------------------------------------------------

void enter(double *a, double *b, double *c)
{
    printf("Hello dear user, enter a, b, c\n");

    int  max = 5;
    for (int attempts = 0; attempts < max; attempts++)
    {
        char str[100] = "";
        fgets(str, 100, stdin);

        int ok = sscanf(str,"%lg %lg %lg",a, b, c);

        printf("a = %lg, b = %lg, c = %lg, ok = %d \n", *a, *b, *c, ok);

        if (ok == 3)
            break;

        printf("Please enter a, b, c again, you have %d attempts\n", max - attempts - 1);
    }
}


//{----------------------------------------------------------------------------------------------------------------
//! @brief   Проверяет на коректность работу решения квадратног уравнения.
//!
//! @param   a    - певый коэфицент уравнеия стоящий при  х в квадрате.
//! @param   b    - второй коэфицент уравнеия стоящий при  х.
//! @param   c    - свободный член уравнения находящися по одну сторону с неизвестными.
//! @param   y1   - полученный первый корень решения уравнения.
//! @param   y2   - полученный второй корень решения уравнения.
//! @param   x1   - точный первый корень решения уравнения.
//! @param   x2   - точный корень решения уравнения.
//! @param   waitresult   - точное количество решений, которое изначально верно.
//!
//! @return  Если операция была успешна -- all ok. \n
//!          Если было найдено 1 решение -- all bad. \n
//!          A также все значеняи что были использованы в этой функции.\n
//!
//! @code
//!           unittest(1, 2, 1, -1, 0, 1);
//! @endcode
//}----------------------------------------------------------------------------------------------------------------

void unittest(double a,double b,double c,double x1,double x2,int waitresult ){
    double y1 = 0, y2 = 0;
    int resulte = QadraticEquation(a, b, c, &y1, &y2);
     if (( resulte == waitresult) && ((y1 == x1) && (x2 == y2)) )
         printf("all ok\n");

     else
         printf("all bad\n y1 = %lg (should be %lg) \n y2 = %lg (should be %lg) \n number = %d (should be %d) \n ",
                 y1, x1, y2, x2, resulte, waitresult);

}

int main() {
    unittest(1, 2, 1, -1, 0, 1);
    unittest(0, 0, 0, 0, 0, 10);
    unittest(1, 1, 10, 0, 0, 0);
    unittest(1, 0, -4, 2, -2, 2);
    double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;

    enter(&a, &b, &c);

    printf("you are coefficients are \n a = %lf \n b = %lf \n c = %lf \n", a, b, c);

    switch (QadraticEquation(a, b, c, &x1, &x2)) {
        case 10: printf("there are infinite solutions to the equation\n");
            break;
        case 0:printf("there are zero solutions to the equation\n");
            break;
        case 1:printf("there are one solutions to the equation x = %lg \n", x1);
            break;
        case 2:printf("there are one solutions to the equation x1 = %lg x2 = %lg \n", x1, x2);
            break;
        default: return 1;

    }

return 0;
}

