#include <iostream>
#include <iomanip>

using namespace std;

class Polynom
{
private:
    unsigned int deg; // deg  - степень многочлена
    double* coef; // coef - указатель на тип double (массив коэффициентов)
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

        for (unsigned int i = 0; i <= deg; i++) coef[i] = new_coef[i];

        // Корректировка степени
        if (this->coef[deg] == 0)
        {
            do
            {
                this->deg--;
            } while (this->deg && this->coef[deg] == 0);
        }
    }

    // Конструктор копирования 
    Polynom(const Polynom& polynom)
    {
        deg = polynom.deg;
        coef = new double[deg + 1];

        for (unsigned int i = 0; i <= deg; i++) coef[i] = polynom.coef[i];
    }

    // Деструктор
    ~Polynom()
    {
        delete[] coef;
    }

    // Оператор сложения двух многочленов
    Polynom operator + (const Polynom& poly)
    {
        Polynom* result; // Создаем указатель на тип Polynom

        if (deg > poly.deg) // Если степень первого многочлена больше степени второго
        {
            result = new Polynom(deg, coef); // Выделяем память в куче для многочлена с большей степенью

            for (unsigned int i = 0; i <= poly.deg; i++)
            {
                result->coef[i] = result->coef[i] + poly.coef[i]; // Записываем массив коэффициентов
            }
        }
        else // Иначе
        {
            result = new Polynom(poly.deg, poly.coef); // Выделяем память в куче для многочлена с большей степенью

            for (unsigned int i = 0; i <= deg; i++)
            {
                result->coef[i] = coef[i] + poly.coef[i]; // Записываем массив коэффициентов
            }
        }

        return *result; // Возвращаем полученный многочлен
    }

    // Оператор присваивания 
    Polynom operator = (const Polynom& poly)
    {
        deg = poly.deg; // Запись новой степени
        delete[] coef; //               Удаление старого массива коэффициентов
        coef = new double[deg + 1]; //  и создание нового

        for (unsigned int i = 0; i <= deg; i++) coef[i] = poly.coef[i];

        return *this; // Возвращаем полученный
    }

    // Оператор умножения числа на многочлен
    Polynom operator * (double c)
    {
        if (c == 0) // Если множитель нулевой
        {
            Polynom result; // Создается многочлен нулевой степени

            return result;
        }
        else // Иначе
        {
            int deg = this->deg; // Получаем степень умножаемого многочлена
            double* tmp_coef = new double[deg + 1];

            for (unsigned int i = 0; i <= deg; i++) tmp_coef[i] = c * this->coef[i]; // Умножаем каждый элемент массива коэффициентов на число

            Polynom result(deg, tmp_coef);

            delete[] tmp_coef;

            return result; // Возвращаем порлученный многочлен
        }
    }

    friend ostream& operator << (ostream& stream, const Polynom& poly)
    {
        stream << fixed << setprecision(2);
        
        unsigned int n = poly.deg;

        // Вывод многочлена
        if (poly.coef[n] < 0)
        {
            stream << '-' << (-1) * poly.coef[n] << "x^" << n;
        }
        else
        {
            stream << poly.coef[n] << "x^" << n;
        }

        for (int i = n - 1; i > 0; i--)
        {
            if (poly.coef[i] == 1)
            {
                stream << " + " << "x^" << i;
            }
            else if (poly.coef[i] == -1)
            {
                stream << " - " << "x^" << i;
            }
            else if (poly.coef[i] < 0)
            {
                stream << " - " << (-1) * poly.coef[i] << "x^" << i;
            }
            else if (poly.coef[i] > 0)
            {
                stream << " + " << poly.coef[i] << "x^" << i;
            }
        }

        if (poly.coef[0] > 0)
        {
            stream << " + " << poly.coef[0];
        }
        else if (poly.coef[0] < 0)
        {
            stream << " - " << (-1) * poly.coef[0];
        }

        return stream;
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
    
    cout << "Создан новый многочлен polynom:  " << polynom << endl;
    
    char answer;

    do
    {
        cout << "Хотите ввести степень многочлена и список коэф.? (y/n) ";

        cin >> answer;

        if (answer == 'y')
        {
            delete[] coefs;

            cout << "Введите степень многочлена: ";
            
            cin >> deg;

            coefs = new double[deg + 1];

            cout << "Введите коэффиценты:\n";
            for (int i = 0; i <= deg; i++)
            {
                cin >> coefs[i];
            }
            break;
        }
        else if (answer == 'n')
        {
            break;
        }
    } while (answer != 'y' || answer != 'n');
    

    Polynom voidPoly;

    cout << "Создан новый многочлен нулевой степени voidPoly: " << voidPoly << endl;

    Polynom polynom2(deg, coefs);

    cout << "Создан новый многочлен polynom2: " << polynom2 << endl;

    cout << "(" << polynom << ") + (" << polynom2 << ") = " << polynom + polynom2 << endl;

    return 0;
}
