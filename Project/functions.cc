#include "v2.h"

using namespace std;

template<typename T>
size_t Matrix<T>::get_rows() const{
    return _rows;
}

template<typename T>
size_t Matrix<T>::get_columns() const{
    return _columns;
}

template<typename T>
Matrix<T>::Matrix(){
    _rows=0;
    _columns=0;
    _data=nullptr;
}

template<typename T>
Matrix<T>::Matrix(size_t rows,size_t columns){
    if (rows<=0||columns<=0){
        throw "Uncorrect size of matrix!"
    }
    this->_rows=rows;
    this->_columns=columns;
    _data=new T*[_rows];
    for (size_t i=0;i<_rows;++i){
        _data[i]=new T[_columns];
    }
    for(size_t i=0;i<_rows;++i){
        for(size_t j=0;j<_columns;++j){
            _data[i][j]=1;
        }
    }
}

template<typename T>
Matrix<T>::Matrix(size_t rows, size_t columns,T lower,T up){
    if (rows<=0||columns<=0){
        throw "Uncorrect size of matrix!"
    }
    this->_rows=rows;
    this->_columns=columns;
    _data=new T*[_rows];
    for (size_t i=0;i<_rows;++i){
        _data[i]=new T[_columns];
    }
    for(size_t i=0;i<_rows;++i){
        for(size_t j=0;j<_columns;++j){
            for(T k=lower;k<=up;++k){
                _data[i][j]=k;//Наверное все-таки стоит вынести в отдельную функцию
            }
        }
    }
}

template<typename T>
Matrix<T>::Matrix(const Matrix& other){
    _rows = other.rows;
    _columns = other.columns;
    _data = new T* [_rows];
    for (int i = 0; i < rows; ++i)
        _data[i] = new T[_columns];

    for (int i = 0; i < _rows; ++i)
        for (int j = 0; j < _columns; ++j)
            _data[i][j] = other(i, j);
}

template<typename T>
T& Matrix<T>::operator()(T i,T j){
    if(((i>0)&&(i<_rows))&&((j>0)&&(j<_columns))){
        return _data[i][j];
    }
    else throw "Invalid row/column input"
}

template<typename T>
Matrix<T>::Matrix operator+(const Matrix& rhs) {
   if((_rows==rhs._rows)&&(_columns=rhs._columns)){
    Matrix result(_rows,_columns);
    for (int i = 0; i < _rows; ++i)
            for (int j = 0; j < _columns; ++j)
                result._data[i][j] = _data[i][j] + rhs._data[i][j];
        return result;
   } 
}

template<typename T>
Matrix<T>::Matrix operator-(const Matrix& rhs){
   if((_rows==rhs._rows)&&(_columns=rhs._columns)){
    Matrix result(_rows,_columns);
    for (int i = 0; i < _rows; ++i)
            for (int j = 0; j < _columns; ++j)
                result._data[i][j] = _data[i][j] - rhs._data[i][j];
        return result;
   } 
}

template<typename T>
Matrix<T>::Matrix operator*(const Matrix& rhs){
    if(_columns==rhs._rows){
        Matrix result(_rows,rhs._columns);
        for(size_t i=0;i<_rows;++i){
            for(size_t j=0;j<rhs._columns;++j){
                for(size_t k=0;k<_columns;++k){
                    result._data[i][j]+=_data[i][k]*rhs._data[k][j];
                }
            }
        }
    }
    return result;
}

template<typename T>
Matrix<T>::Matrix operator*(const T scalar){
    Matrix result(_rows,_columns)
    for(size_t i=0;i<_rows;++i){
        for(size_t j=0;j<_columns;++j){
            result._data[i][j]=_data[i][j]*scalar;
        }
    }
    return result;
}

template<typename T>
Matrix<T>::Matrix operator/(const T scalar){
    Matrix result(_rows,_columns)
    for(size_t i=0;i<_rows;++i){
        for(size_t j=0;j<_columns;++j){
            result._data[i][j]=_data[i][j]/scalar;
        }
    }
    return result;
}

template<typename T>
Matrix Matrix<T>::operator*(T scalar,Matrix matrix){
    Matrix result(matrix.get_rows(),matrix.get_columns());
    result=matrix*scalar;
    return result;
}

template<typename T>
Matrix Matrix<T>::operator/(T scalar,Matrix matrix){
    Matrix result(matrix.get_rows(),matrix.get_columns());
    result=matrix/scalar;
    return result;
}

//Операторы с аргументом по ссылке не работают*

template<typename T>
T Matrix<T>::tr(){
    T tr=0;
    for(size_t i=0;i<_rows;++i){
        tr+=_data[i][i];
    }
    return tr;
}


