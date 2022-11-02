#include <iostream>
#include <iomanip>

using namespace std;

class Polynom
{
private:
    unsigned int deg; // deg  - степень многочлена
    double* coef; // coef - указатель на тип double (массив коэффициентов)
    void correctDeg(); // Функция корректировки степени

public:
    // Конструктор без параметров
    // deg - степень многочлена, 
    // coef - массив коэффициентов многочлена, где 
    //        coef[i] - коэф. при i-ой степени переменной,
    //        coef[0] - коэф. при 0-ой степени перменной.
    // Создается многочлен нулевой степени.
    Polynom()
    {
        deg = 0;
        coef = new double[deg + 1];
        coef[0] = 0.0;
    }

    // Конструктор с параметрами 
    // new_deg - степень многочлена,
    // new_coef - массив коэффициаентов, где
    //        new_coef[i] - коэф. при i-ой степени переменной,
    //        new_coef[0] - коэф. при 0-ой степени перменной.  
    Polynom(unsigned int new_deg, double* new_coef)
    {
        deg = new_deg;
        coef = new double[deg + 1];

        for (int i = 0; i <= deg; i++) coef[i] = new_coef[i];

        this->correctDeg();
    }

    // Конструктор копирования 
    Polynom(const Polynom& polynom)
    {
        deg = polynom.deg;
        coef = new double[deg + 1];

        for (int i = 0; i <= deg; i++) coef[i] = polynom.coef[i];
    }

    // Деструктор
    ~Polynom()
    {
        delete[] coef;
    }

    // Функция корректировки степени полинома:
    // коэффициент при наибольшей степени не должен быть нулевым
    void correctDeg()
    {
        if (coef[deg] == 0)
        {
            do
            {
                deg--;
            }
            while (deg && coef[deg] == 0);
        }
    }

    // Оператор сложения двух многочленов
    Polynom operator + (const Polynom& poly)
    {
        Polynom* result; // Создаем указатель на тип Polynom

        if (deg > poly.deg) // Если степень первого многочлена больше степени второго
        {
            result = new Polynom(deg, coef); // Выделяем память в куче для многочлена с большей степенью

            for (int i = 0; i <= poly.deg; i++)
            {
                result->coef[i] = result->coef[i] + poly.coef[i]; // Записываем массив коэффициентов
            }
        }
        else // Иначе
        {
            result = new Polynom(poly.deg, poly.coef); // Выделяем память в куче для многочлена с большей степенью

            for (int i = 0; i <= deg; i++)
            {
                result->coef[i] = result->coef[i] + poly.coef[i]; // Записываем массив коэффициентов
            }
        }

        result->correctDeg(); 

        return *result; // Возвращаем полученный многочлен
    }

    // Оператор присваивания 
    Polynom operator = (const Polynom& poly)
    {
        deg = poly.deg; // Запись новой степени
        delete[] coef; //               Удаление старого массива коэффициентов
        coef = new double[deg + 1]; //  и создание нового

        for (int i = 0; i <= deg; i++) coef[i] = poly.coef[i];

        return *this; // Возвращаем полученный
    }

    // Оператор умножения числа на многочлен
    Polynom operator * (double c)
    {
        if (c == 0) // Если множитель нулевой
        {
            Polynom* result; // Создается многочлен нулевой степени

            return *result;
        }
        else // Иначе
        {
            int deg = this->deg; // Получаем степень умножаемого многочлена

            for (int i = 0; i <= deg; i++) this->coef[i] = c * this->coef[i]; // Умножаем каждый элемент массива коэффициентов на число

            return *this; // Возвращаем порлученный многочлен
        }
    }

    // Функция вывода многочлена
    void outputPoly()
    {
        cout << fixed << setprecision(2); // Ограничиваем вывод двумя знаками после запятой
        
        // Вывод многочлена
        if (coef[deg] < 0)
        {
            cout << '-' << (-1) * coef[deg] << "x^" << deg;
        }
        else
        {
            cout << coef[deg] << "x^" << deg;
        }

        for (int i = deg - 1; i > 0; i--)
        {
            if (coef[i] == 1)
            {
                cout << " + " << "x^" << i;
            }
            else if (coef[i] == -1)
            {
                cout << " - " << "x^" << i;
            }
            else if (coef[i] < 0)
            {
                cout << " - " << (-1) * coef[i] << "x^" << i;
            }
            else if (coef[i] > 0)
            {
                cout << " + " << coef[i] << "x^" << i;
            }
        }

        if (coef[0] > 0)
        {
            cout << " + " << coef[0];
        }
        else if (coef[0] < 0)
        {
            cout << " - " << (-1) * coef[0];
        }
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");

    unsigned int deg = 3;
    double* coefs = new double[deg + 1];

    for (int i = 0; i <= deg; i++)
    {
        coefs[i] = i + 2;
    }

    Polynom polynom(deg, coefs);

    polynom.outputPoly();

    cout << endl;

    polynom = polynom * 3;

    polynom.outputPoly();

    return 0;
}
