// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <iomanip>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size) {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE) {
        throw out_of_range("Vector is too large");
    }
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }

  TDynamicVector(T* arr, size_t s) : sz(s) {
      if (sz == 0)
          throw out_of_range("Vector size should be greater than zero");
      if (sz > MAX_VECTOR_SIZE) {
          throw out_of_range("Vector is too large");
      }
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }

  TDynamicVector(const TDynamicVector& v) {
      sz = v.sz;
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);
  }

  TDynamicVector(TDynamicVector&& v) noexcept {
      sz = v.sz;
      pMem = v.pMem;
      v.pMem = nullptr;
      v.sz = 0;
  }

  ~TDynamicVector() {
      if (pMem != nullptr) {
          delete[] pMem;
          sz = 0;
      }
  }
  TDynamicVector& operator=(const TDynamicVector& v) {
      if (this != &v) {
          TDynamicVector temp(v);
          std::swap(sz, temp.sz);
          std::swap(pMem, temp.pMem);
      }
      return *this;
  }

  TDynamicVector& operator=(TDynamicVector&& v) noexcept {
      if (this != &v) {
          delete[] pMem;
          sz = v.sz;
          pMem = v.pMem;
          v.pMem = nullptr;
          v.sz = 0;
      }
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind) {
      return pMem[ind];
  }

  const T& operator[](size_t ind) const {
      return pMem[ind];
  }

  // индексация с контролем
  T& at(size_t ind) {
      if (ind >= sz) {
          throw out_of_range("index out of vector bounds");
      }
      return pMem[ind];
  }

  const T& at(size_t ind) const {
      if (ind >= sz) {
          throw out_of_range("index out of vector bounds");
      }
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept {
      if (sz != v.sz) {
          return false;
      }
      for (int i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i]) {
              return false;
          }
      }
      return true;
  }

  bool operator!=(const TDynamicVector& v) const noexcept {
      return !((*this) == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val) {
      TDynamicVector temp(*this);
      for (int i = 0; i < sz; i++) {
          temp.pMem[i] += val;
      }
      return temp;
  }

  TDynamicVector operator-(T val) {
      TDynamicVector temp(*this);
      for (int i = 0; i < sz; i++) {
          temp.pMem[i] -= val;
      }
      return temp;
  }

  TDynamicVector operator*(T val) {
      TDynamicVector temp(*this);
      for (int i = 0; i < sz; i++) {
          temp.pMem[i] *= val;
      }
      return temp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v) {
      if (sz != v.sz) {
          throw "different vector sizes";
      }
      TDynamicVector temp(*this);
      for (int i = 0; i < sz; i++) {
          temp.pMem[i] += v.pMem[i];
      }
      return temp;
  }

  TDynamicVector operator-(const TDynamicVector& v) {
      if (sz != v.sz) {
          throw "different vector sizes";
      }
      TDynamicVector temp(*this);
      for (int i = 0; i < sz; i++) {
          temp.pMem[i] -= v.pMem[i];
      }
      return temp;
  }

  T operator*(const TDynamicVector& v) noexcept(noexcept(T())) {
      if (sz != v.sz) {
          throw "different vector sizes";
      }
      T res = T();
      for (int i = 0; i < sz; i++) {
          res += pMem[i] * v.pMem[i];
      }
      return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};



// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (s > MAX_MATRIX_SIZE) {
          throw "Error create too large matrix";
      }
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept {
      return TDynamicVector<TDynamicVector<T>>::operator==(m);
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val) {
      TDynamicMatrix tmp(sz);
      for (int i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] * val;
      }
      return tmp;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v) {
      TDynamicVector<T> tmp(sz);
      for (int i = 0; i < sz; i++) {
          tmp[i] = v * pMem[i];
      }
      return tmp;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m) {
      if (m.size() != this->size()) {
          throw "Error different matrix sizes";
      }
      TDynamicMatrix tmp(sz);
      for (int i = 0; i < sz; i++) {
          tmp[i] = pMem[i] + m.pMem[i];
      }
      return tmp;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m) {
      TDynamicMatrix tmp(sz);
      if (m.size() != this->size()) {
          throw "Error different matrix sizes";
      }
      for (int i = 0; i < sz; i++) {
          tmp[i] = pMem[i] - m.pMem[i];
      }
      return tmp;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m) {
      TDynamicMatrix tmp(sz);
      if (m.size() != this->size()) {
          throw "Error different matrix sizes";
      }
      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz; j++) {
              for (int k = 0; k < sz; k++) {
                  tmp.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
              }
          }
      }
      return tmp;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v) {
      for (int i = 0; i < v.sz; i++) {
          for (int j = 0; j < v.sz; j++) {
              istr >> v.pMem[i][j];
          } 
      }
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v) {
      for (int i = 0; i < v.sz; i++) {
          for (int j = 0; j < v.sz; j++) {
              ostr << setw(6) << v.pMem[i][j];
          }
          ostr << std::endl;
      }
      return ostr;
  }

  size_t size() const noexcept { return sz; }
};


// Динамический вектор для верхнетреугольной матрицы - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVectorTriangle {
protected:
    size_t sz;
    T* pMem;
    size_t si; // номер строки
public:
    TDynamicVectorTriangle(size_t size = 1, size_t _si = 0) : sz(size), si(_si) {
        if (sz == 0)
            throw out_of_range("Vector size should be greater than zero");
        if (sz > MAX_VECTOR_SIZE) {
            throw out_of_range("Vector is too large");
        }
        if (si > MAX_VECTOR_SIZE) {
            throw out_of_range("Vector is too large");
        }
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }

    TDynamicVectorTriangle(T* arr, size_t s, size_t _si) : sz(s), si(_si) {
        if (sz == 0)
            throw out_of_range("Vector size should be greater than zero");
        if (sz > MAX_VECTOR_SIZE) {
            throw out_of_range("Vector is too large");
        }
        if (si > MAX_VECTOR_SIZE) {
            throw out_of_range("Vector is too large");
        }
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }

    TDynamicVectorTriangle(const TDynamicVectorTriangle& v) {
        sz = v.sz;
        pMem = new T[sz];
        si = v.si;
        std::copy(v.pMem, v.pMem + sz, pMem);
    }

    TDynamicVectorTriangle(TDynamicVectorTriangle&& v) noexcept {
        sz = v.sz;
        pMem = v.pMem;
        si = v.si;
        v.pMem = nullptr;
        v.sz = 0;
        v.si = 0;
    }

    ~TDynamicVectorTriangle() {
        if (pMem != nullptr) {
            delete[] pMem;
            sz = 0;
            si = 0;
        }
    }

    TDynamicVectorTriangle& operator=(const TDynamicVectorTriangle& v) {
        if (this != &v) {
            TDynamicVectorTriangle temp(v);
            std::swap(sz, temp.sz);
            std::swap(si, temp.si);
            std::swap(pMem, temp.pMem);
        }
        return *this;
    }

    TDynamicVectorTriangle& operator=(TDynamicVectorTriangle&& v) noexcept {
        if (this != &v) {
            delete[] pMem;
            sz = v.sz;
            pMem = v.pMem;
            si = v.si;
            v.pMem = nullptr;
            v.sz = 0;
            v.si = 0;
        }
        return *this;
    }

    size_t size() const noexcept { return sz; }
    size_t num_strok() const noexcept { return si; }

    // индексация
    T& operator[](size_t ind) {
        return pMem[ind - si];
    }

    const T& operator[](size_t ind) const {
        return pMem[ind - si];
    }

    // индексация с контролем
    T& at(size_t ind) {
        if (ind - si >= sz) {
            throw out_of_range("index out of vector bounds");
        }
        return pMem[ind - si];
    }

    const T& at(size_t ind) const {
        if (ind - si >= sz) {
            throw out_of_range("index out of vector bounds");
        }
        return pMem[ind - si];
    }

    // сравнение
    bool operator==(const TDynamicVectorTriangle& v) const noexcept {
        if (sz != v.sz || si != v.si) {
            return false;
        }
        for (int i = 0; i < sz; i++) {
            if (pMem[i] != v.pMem[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const TDynamicVectorTriangle& v) const noexcept {
        return !((*this) == v);
    }

    // скалярные операции
    TDynamicVectorTriangle operator+(T val) {
        TDynamicVectorTriangle temp(*this);
        for (int i = 0; i < sz; i++) {
            temp.pMem[i] += val;
        }
        return temp;
    }

    TDynamicVectorTriangle operator-(T val) {
        TDynamicVectorTriangle temp(*this);
        for (int i = 0; i < sz; i++) {
            temp.pMem[i] -= val;
        }
        return temp;
    }

    TDynamicVectorTriangle operator*(T val) {
        TDynamicVectorTriangle temp(*this);
        for (int i = 0; i < sz; i++) {
            temp.pMem[i] *= val;
        }
        return temp;
    }

    // векторные операции
    TDynamicVectorTriangle operator+(const TDynamicVectorTriangle& v) {
        if (sz != v.sz) {
            throw "different vector sizes";
        }
        TDynamicVectorTriangle temp(*this);
        for (int i = 0; i < sz; i++) {
            temp.pMem[i] += v.pMem[i];
        }
        return temp;
    }

    TDynamicVectorTriangle operator-(const TDynamicVectorTriangle& v) {
        if (sz != v.sz) {
            throw "different vector sizes";
        }
        TDynamicVectorTriangle temp(*this);
        for (int i = 0; i < sz; i++) {
            temp.pMem[i] -= v.pMem[i];
        }
        return temp;
    }

    T operator*(const TDynamicVectorTriangle& v) noexcept(noexcept(T())) {
        if (sz != v.sz) {
            throw "different vector sizes";
        }
        T res = T();
        for (int i = 0; i < sz; i++) {
            res += pMem[i] * v.pMem[i];
        }
        return res;
    }

    friend void swap(TDynamicVectorTriangle& lhs, TDynamicVectorTriangle& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.si, rhs.si);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVectorTriangle& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVectorTriangle& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};




// Динамическая верхнетреугольная матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrixTriangle : private TDynamicVectorTriangle<TDynamicVectorTriangle<T>>
{
    using TDynamicVectorTriangle<TDynamicVectorTriangle<T>>::pMem;
    using TDynamicVectorTriangle<TDynamicVectorTriangle<T>>::sz;
    using TDynamicVectorTriangle<TDynamicVectorTriangle<T>>::si;
public:
    TDynamicMatrixTriangle(size_t s = 1) : TDynamicVectorTriangle<TDynamicVectorTriangle<T>>(s)
    {
        if (s > MAX_MATRIX_SIZE) {
            throw "Error create too large matrix";
        }
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVectorTriangle<T>(sz-i, i);
    }

    using TDynamicVectorTriangle<TDynamicVectorTriangle<T>>::operator[];

    // сравнение
    bool operator==(const TDynamicMatrixTriangle& m) const noexcept {
        return TDynamicVectorTriangle<TDynamicVectorTriangle<T>>::operator==(m);
    }

    // матрично-скалярные операции
    TDynamicMatrixTriangle operator*(const T& val) {
        TDynamicMatrixTriangle tmp(sz);
        for (int i = 0; i < sz; i++) {
            tmp.pMem[i] = pMem[i] * val;
        }
        return tmp;
    }

    // матрично-векторные операции
    TDynamicVectorTriangle<T> operator*(const TDynamicVectorTriangle<T>& v) {
        if (v.size() != sz || v.num_strok() != 0) {
            throw "Error different vector sizes";
        }
        TDynamicVectorTriangle<T> tmp(sz);
        for (int i = 0; i < sz; i++) {
            for (int j = i; j < sz; j++) {
                tmp[i] += v[j] * pMem[i][j];
            }

        }
        return tmp;
    }

    // матрично-матричные операции
    TDynamicMatrixTriangle operator+(const TDynamicMatrixTriangle& m) {
        if (m.size() != this->size()) {
            throw "Error different matrix sizes";
        }
        TDynamicMatrixTriangle tmp(sz);
        for (int i = 0; i < sz; i++) {
            tmp[i] = pMem[i] + m.pMem[i];
        }
        return tmp;
    }
    TDynamicMatrixTriangle operator-(const TDynamicMatrixTriangle& m) {
        TDynamicMatrixTriangle tmp(sz);
        if (m.size() != this->size()) {
            throw "Error different matrix sizes";
        }
        for (int i = 0; i < sz; i++) {
            tmp[i] = pMem[i] - m.pMem[i];
        }
        return tmp;
    }
    TDynamicMatrixTriangle operator*(const TDynamicMatrixTriangle& m) {
        TDynamicMatrixTriangle tmp(sz);
        if (m.size() != this->size()) {
            throw "Error different matrix sizes";
        }
        for (int i = 0; i < sz; i++) {
            for (int j = i; j < sz; j++) {
                for (int k = i; k <= j; k++) {
                    tmp.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
                }
            }
        }
        return tmp;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrixTriangle& v) {
        T trash;
        for (int i = 0; i < v.sz; i++) {
            for (int k = 0; k < i; k++) {
                istr >> trash;
            }
            for (int j = i; j < v.sz; j++) {
                istr >> v.pMem[i][j];
            }
        }
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrixTriangle& v) {
        for (int i = 0; i < v.sz; i++) {
            for (int k = 0; k < i; k++) {
                ostr << setw(6) << T();
            }
            for (int j = i; j < v.sz; j++) {
                ostr << setw(6) << v.pMem[i][j];
            }
            ostr << std::endl;
        }
        return ostr;
    }

    size_t size() const noexcept { return sz; }
};



#endif