// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector {
private:
    ValType get_value(int pos) const;   // значение вектора
    ValType& TVector<ValType>::at(int pos);   // доступ без проверки
protected:
    ValType* pVector;
    int Size;       // размер вектора
    int StartIndex; // индекс первого элемента вектора
public:
   // TVector() = default;
    TVector(int s = 0, int si = 0);
    TVector(const TVector& v);                // конструктор копирования
    ~TVector();
    int GetSize() { return Size; }            // размер хранимой части вектора
    int GetStartIndex() { return StartIndex; }// индекс первого ненулевого элемента
    ValType& operator[](int pos);             // доступ с проверкой
    bool operator==(const TVector& v) const;  // сравнение
    bool operator!=(const TVector& v) const;  // сравнение
    TVector& operator=(const TVector& v);     // присваивание

    // скалярные операции
    TVector  operator+(const ValType& val);   // прибавить скаляр
    TVector  operator-(const ValType& val);   // вычесть скаляр
    TVector  operator*(const ValType& val);   // умножить на скаляр

    // векторные операции
    TVector  operator+(const TVector& v);     // сложение
    TVector  operator-(const TVector& v);     // вычитание
    ValType  operator*(const TVector& v);     // скалярное произведение

    // ввод-вывод
    friend istream& operator>>(istream& in, TVector& v) {
        for (int i = 0; i < v.Size; i++)
            in >> v.pVector[i];
        return in;
    }
    friend ostream& operator<<(ostream& out, const TVector& v) {
        for (int i = 0; i < v.Size; i++)
            out << v.pVector[i] << " ";
        return out;
    }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si) {
    if (s < 0 || s > MAX_VECTOR_SIZE) throw exception("s < 0 || s > MAX_VECTOR_SIZE");
    if (si < 0)throw exception("si < 0");
    pVector = new ValType[s];
    Size = s;
    StartIndex = si;
}

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType>& v) :TVector(v.Size, v.StartIndex) {
    for (int i = 0; i < Size; i++) {
        pVector[i] = v.pVector[i];
    }
}

template <class ValType>
TVector<ValType>::~TVector() {
    delete[] pVector;
    pVector = nullptr;
    Size = 0;
    StartIndex = 0;
}

template <class ValType> // доступ с проверкой
ValType& TVector<ValType>::operator[](int pos)
{
    if (pos < StartIndex || pos >= StartIndex + Size) throw exception("pos < StartIndex || pos >= StartIndex + Size");
    return pVector[pos - StartIndex];
} /*-------------------------------------------------------------------------*/

template <class ValType> // значение
ValType TVector<ValType>::get_value(int pos) const
{
    return (pos >= StartIndex ? this->pVector[pos - StartIndex] : 0);
} /*-------------------------------------------------------------------------*/
template <class ValType> // доступ без проверки
ValType& TVector<ValType>::at(int pos)
{
    return pVector[pos - StartIndex];
}
template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector& v) const
{
    if ((this->Size != v.Size) || (this->StartIndex != v.StartIndex))return false;
    for (int i = 0; i < Size; i++) {
        if (this->pVector[i] != v.pVector[i]) {
            return false;
        }
    }
    return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector& v) const {
    return !this->operator==(v);
}

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector& v) {
    if (*this != v) {
        if (Size != v.Size) {
            ValType* temp = new ValType[v.Size];
            delete[] pVector;
            pVector = temp;
            Size = v.Size;
        }
        StartIndex = v.StartIndex;
        for (int i = 0; i < Size; i++) {
            pVector[i] = v.pVector[i];
        }
    }
    return *this;
}

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType& val)
{
    int n = 0;
    /*if (val == 0) {
        n = StartIndex;
    }
    else {
        n = 0;
    }*/
    //считаем кол-во нулей в новом векторе
    while (n < (StartIndex + Size) && (get_value(n) + val) == 0) {
        n++;
    }
    TVector<ValType> temp(StartIndex + Size - n, n);
    for (int i = n; i < StartIndex + Size; i++) {
        temp.at(i) = get_value(i) + val;
    }
    return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType& val)
{
    int n = 0;
    /*if (val == 0) {
        n = StartIndex;
    }
    else {
        n = 0;
    }*/
    //считаем кол-во нулей в новом векторе
    while (n < (StartIndex + Size) && (get_value(n) - val) == 0) {
        n++;
    }
    TVector<ValType> temp(StartIndex + Size - n, n);
    for (int i = n; i < StartIndex + Size; i++) {
        temp.at(i) = get_value(i) - val;
    }
    return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType& val)
{
    int n = 0;
    /*if (val == 0) {
        n = StartIndex + Size;
    }
    else {
        n = StartIndex;
    }*/
    //считаем кол-во нулей в новом векторе
    while (n < (StartIndex + Size) && (get_value(n) * val) == 0) {
        n++;
    }
    TVector<ValType> temp(StartIndex + Size - n, n);
    for (int i = n; i < StartIndex + Size; i++) {
        temp.at(i) = get_value(i) * val;
    }
    return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType>& v)
{
    if ((Size + StartIndex != v.Size + v.StartIndex)) throw exception("vector sizes are not equal");
    int n = StartIndex < v.StartIndex ? StartIndex : v.StartIndex; //min(StartIndex, v.StartIndex)
    //считаем кол-во нулей в новом векторе
    while (n < (StartIndex + Size) && (get_value(n) + v.get_value(n)) == 0) {
        n++;
    };
    TVector<ValType> temp(StartIndex + Size - n, n);
    for (int i = n; i < StartIndex + Size; i++) {
        temp.at(i) = get_value(i) + v.get_value(i);
    }
    return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType>& v)
{
    if ((Size + StartIndex != v.Size + v.StartIndex)) throw exception("vector sizes are not equal");
    int n = StartIndex < v.StartIndex ? StartIndex : v.StartIndex; //min(StartIndex, v.StartIndex)
    //считаем кол-во нулей в новом векторе
    while (n < (StartIndex + Size) && (get_value(n) - v.get_value(n)) == 0) {
        n++;
    }
    TVector<ValType> temp(StartIndex + Size - n, n);
    for (int i = n; i < StartIndex + Size; i++) {
        temp.at(i) = get_value(i) - v.get_value(i);
    }
    return temp;
}/*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType>& v)
{
    if ((Size + StartIndex != v.Size + v.StartIndex)) throw exception("vector sizes are not equal");
    int n = StartIndex > v.StartIndex ? StartIndex : v.StartIndex; //max(StartIndex, v.StartIndex)
    ValType sum = 0;
    for (int i = n; i < Size + StartIndex; i++) {
        sum += get_value(i) * v.get_value(i);
    }
    return sum;
} /*-------------------------------------------------------------------------*/


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> > {
public:
    TMatrix(int s = 10);
    TMatrix(const TMatrix& mt);                    // копирование
    TMatrix(const TVector<TVector<ValType> >& mt); // преобразование типа
    ~TMatrix();                                    // деструктор
    bool operator==(const TMatrix& mt) const;      // сравнение
    bool operator!=(const TMatrix& mt) const;      // сравнение
    TMatrix& operator= (const TMatrix& mt);        // присваивание
    TMatrix  operator+ (const TMatrix& mt);        // сложение
    TMatrix  operator- (const TMatrix& mt);        // вычитание

    // ввод / вывод
    friend istream& operator>>(istream& in, TMatrix& mt)
    {
        for (int i = 0; i < mt.Size; i++)
            in >> mt.pVector[i];
        return in;
    }
    friend ostream& operator<<(ostream& out, const TMatrix& mt)
    {
        for (int i = 0; i < mt.Size; i++)
            out << mt.pVector[i] << "\n";
        return out;
    }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType> >(s)
{
    if (s > MAX_MATRIX_SIZE)throw exception("s > MAX_MATRIX_SIZE");
    for (int i = 0; i < Size; i++) {
        pVector[i] = TVector<ValType>(Size - i, i);
    }
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt) : TVector<TVector<ValType> >(mt) {}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& mt) : TVector<TVector<ValType> >(mt) {}

template <class ValType> // деструктор
TMatrix<ValType>::~TMatrix() {};
template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& mt) const
{
   return TVector<TVector<ValType> >::operator==(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType>& mt) const
{
    return !TVector<TVector<ValType> >::operator==(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& mt)
{
    TVector<TVector<ValType>>::operator=(mt);
    return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType>& mt)
{
    if (this->Size != mt.Size)throw exception("this->Size != mt.Size");
    TMatrix<ValType> mat(Size);
    for (int i = 0; i < Size; i++) {
        mat[i] = this->pVector[i] + mt.pVector[i];
    }
    return mat;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType>& mt)
{
    if (this->Size != mt.Size)throw exception("this->Size != mt.Size");
    TMatrix<ValType> mat(Size);
    for (int i = 0; i < Size; i++) {
        mat[i] = this->pVector[i] - mt.pVector[i];
    }
    return mat;
} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
