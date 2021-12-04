// ����, ���, ���� "������ ����������������-2", �++, ���
//
// sample_matrix.cpp - Copyright (c) ������� �.�. 07.05.2001
//   ������������ ��� Microsoft Visual Studio 2008 �������� �.�. (20.04.2015)
//
// ������������ ����������������� �������

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
        cout << "������������ �������� ��������� ������������� ����������� ������\n";
        cout << "�������� �������:\n";
        cout << "1. �������� ������ ������ (size = " << size << ")\n";
        cout << "2. ��������� ������� ���������� �������\n";
        cout << "3. ��������� ������� �������\n";
        cout << "4. ������� �������\n";
        cout << "5. ������� �������\n";
        cout << "6. ������� �������\n";
        cout << "7. �����\n";
        cout << ">";
        cin >> code;
        cin.clear();
        cin.ignore(10000, '\n');
        switch (code) {
        case 1: {
            int s = -1;
            while ((s < 0) || (s > MAX_MATRIX_SIZE)) {
                cout << "������� ����� ������ ������\n";
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
            cout << "������� ��������� ���������� �������\n";
            break;
        }
        case 3: {
            cin >> a >> b;
            cout << "������� ���������\n";
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
            cout << "������� �� �������\n";
        }
        }
        system("pause");
    }
}
//---------------------------------------------------------------------------
