// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// sample_matrix.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (20.04.2015)
//
// Тестирование верхнетреугольной матрицы

#include <iostream>
#include "utmatrix.h"
//---------------------------------------------------------------------------

void main()
{
    int size = 5;
    TMatrix<int> a(size), b(size);
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    int code = -1, Exit = 7;
    while (code != Exit) {
        system("cls");
        cout << "Тестирование программ поддержки представления треугольных матриц\n";
        cout << "Выберите команду:\n";
        cout << "1. Изменить размер матриц (size = " << size << ")\n";
        cout << "2. Заполнить матрицы случайными числами\n";
        cout << "3. Заполнить матрицы вручную\n";
        cout << "4. Вывести матрицы\n";
        cout << "5. Сложить матрицы\n";
        cout << "6. Вычесть матрицы\n";
        cout << "7. Выход\n";
        cout << ">";
        cin >> code;
        cin.clear();
        cin.ignore(10000, '\n');
        switch (code) {
        case 1: {
            int s = -1;
            while ((s < 0) || (s > MAX_MATRIX_SIZE)) {
                cout << "Введите новый размер матриц\n";
                cin >> s;
                cin.clear();
                cin.ignore(10000, '\n');
            }
            size = s;
            a = b = TMatrix<int>(size);
            break;
        }
        case 2: {
            for (int i = 0; i < size; i++) {
                for (int j = i; j < size; j++) {
                    a[i].set(j, rand());
                    b[i].set(j, rand());
                }
            }
            cout << "Матрицы заполнены случайными числами\n";
            break;
        }
        case 3: {
            cin >> a >> b;
            cout << "Матрицы заполнены\n";
            break;
        }
        case 4: {
            cout << a << "\n";
            cout << b << "\n";
            break;
        }
        case 5: {
            cout << a;
            cout << "+\n";
            cout << b;
            cout << "=\n";
            cout << a + b << "\n";
            break;
        }
        case 6: {
            cout << a;
            cout << "-\n";
            cout << b;
            cout << "=\n";
            cout << a - b << "\n";
            break;
        }
        default: {
            cout << "Команда не найдена\n";
        }
        }
        system("pause");
    }
}
//---------------------------------------------------------------------------
