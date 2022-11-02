#include <iostream>
#include <iomanip>

using namespace std;

class Polynom
{
private:
    int deg;
    double* coef;
    void correctDeg();

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
    // коэййициент при наибольшей степение не должен быть нулевым
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
        int i;
        Polynom* result;

        if (deg > poly.deg)
        {
            result = new Polynom(deg, coef);

            for (int i = 0; i <= poly.deg; i++)
            {
                result->coef[i] = result->coef[i] + poly.coef[i];
            }
        }
        else
        {
            result = new Polynom(poly.deg, poly.coef);

            for (int i = 0; i <= deg; i++)
            {
                result->coef[i] = result->coef[i] + poly.coef[i];
            }
        }

        result->correctDeg();

        return *result;
    }

    // Оператор присваивания 
    Polynom operator = (const Polynom& poly)
    {
        deg = poly.deg;
        delete[] coef;
        coef = new double[deg + 1];

        for (int i = 0; i <= deg; i++) coef[i] = poly.coef[i];

        return *this;
    }

    // Оператор умножения числа на многочлен
    Polynom operator * (double c)
    {
        if (c == 0)
        {
            Polynom result;

            return result;
        }
        else 
        {
            int deg = this->deg;

            for (int i = 0; i <= deg; i++) this->coef[i] = c * this->coef[i];

            return *this;
        }
    }

    // Функция вывода многочлена
    void outputPoly()
    {
        cout << fixed << setprecision(2);
        
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
