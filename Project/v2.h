#include <iostream>
#include <random>
#include <stdexcept>
#include<complex>
namespace std {
	template<typename T>
	class Matrix {
	private:
		T* _data;
	    size_t _rows;
		size_t _columns;
    public:
    //Конструкторы
    Matrix():_rows(0),_columns(0),_data(nullptr){}
    Matrix(size_t rows,size_t columns):_rows(rows),_columns(columns){
        if(rows<0||columns<0){
            throw runtime_error("Uncorrect size of matrix!");
        }
        _data=new T[_columns*_rows];
        for(size_t i=0;i<_rows;++i){
            for(size_t j=0;j<_columns;++j){
                _data[i*_columns+j]=1;
            }
        }
    }
    Matrix(size_t rows, size_t columns,T lower,T up):_rows(rows),_columns(columns){
                if(rows<0||columns<0){
            throw runtime_error("Uncorrect size of matrix!");
        }
        _data=new T[_columns*_rows];
        for(size_t i=0;i<_rows;++i){
            for(size_t j=0;j<_columns;++j){
            _data[i]=rand()%up+lower;
            }
        }
    }
    Matrix(const Matrix<T>& other){
    _rows = other._rows;
    _columns = other._columns;
    _data = new T[_rows * _columns];
    for (int i = 0; i < (_columns*_rows); ++i) {
        _data[i] = other._data[i];
    }
    }
    ~Matrix(){
        if(_data!=nullptr){
            delete[] _data;
        }
    }
    //get and set
    size_t get_rows() const{
    return _rows;
    }
	size_t get_columns() const{
    return _columns;
    }
    T tr(){
        if (_rows!=_columns){
            throw runtime_error("Matrix is not square");
        }
        T tr=0;
        for(size_t i=0;i<_rows;++i){
            tr+=_data[i*_columns+i];
        }
        return tr;
    }
    //Операторы
    Matrix& operator=(const Matrix<T>& other){
        _rows=other._rows;
        _columns=other._columns;
        _data = new T[_columns * _rows];
        for(size_t i=0;i<_rows;++i){
            for(size_t j=0;j<_columns;++j){
                _data[i*_columns+j]=other._data[i*_columns+j];
        }
    }
    }
    T& operator()(T i,T j){
        if(((i>=0)&&(i<_rows))&&((j>=0)&&(j<_columns))){
        return _data[i*_columns+j];
        }
        else throw runtime_error("Invalid row/column input");
    }
    Matrix operator+(const Matrix<T>& other){
        if (_rows != other._rows || _columns != other._columns){
             throw runtime_error("Invalid row/column");
        }
        Matrix<T> result(_rows,_columns);
        for(size_t i=0;i<_rows;++i){
            for(size_t j=0;j<_columns;++j){
                result._data[i*_columns+j]=_data[i * _columns + j] + other._data[i * _columns + j];
            }
        }
        return result;
    }
    Matrix operator-(const Matrix<T>& other){
        if (_rows != other._rows || _columns != other._columns){
             throw runtime_error("Invalid row/column");
        }
        Matrix<T> result(_rows,_columns);
        for(size_t i=0;i<_rows;++i){
            for(size_t j=0;j<_columns;++j){
                result._data[i*_columns+j]=_data[i * _columns + j] - other._data[i * _columns + j];
            }
        }
        return result;
    }
    Matrix operator*(const Matrix<T>& other){
        if (can_multiply(other)==false){
             throw runtime_error("rows!=columns");
        }
        Matrix<T> result(_rows, other._columns);
        for (size_t i = 0; i < _rows; i++) {
            for (size_t j = 0; j < other._columns; j++) {
                T sum = 0;
                for (size_t k = 0; k < _columns; k++) {
                    sum += _data[i * _columns + k] * other._data[k * other._columns + j];
                }
                result._data[i * result._columns + j] = sum;
            }
        }
        return result;
    }
    Matrix operator*(const T scalar){
        Matrix<T> result(_rows,_columns);
        for(size_t i=0;i<(_columns*_rows);++i){
            result._data[i]=_data[i]*scalar;
        }
        return result;
    }
    Matrix operator/(const T scalar){
        if (scalar==0){
             throw invalid_argument("/0");
        }
        Matrix<T> result(_rows,_columns);
        for(size_t i=0;i<(_columns*_rows);++i){
            result._data[i]=_data[i]/scalar;
        }
        return result;
    }
    bool operator==(const Matrix<T>& other) {
    bool result=true;
    if ((_rows==other._rows) && (_columns==other._columns)){
        for (int i = 0; i < _rows; ++i){
            for (int j = 0; j < _columns; ++j){
                if (abs(_data[i*_columns+_rows] - other._data[i*_columns+_rows]) != 0) {
                    result = false;
                }
            }
        }
    }
    else {
        result = false;
    }
    return result;
    }
    bool operator!=(const Matrix<T>& other){
        if(*this==other){
        return false;
        }
        return true;
    }
    bool can_multiply(const Matrix<T>& other){
        return _rows==other._columns;
    }
    friend std::ostream& operator<<(std::ostream& out,const Matrix<T>& matrix) {
        for (size_t i = 0; i < matrix._rows; i++) {
            for (size_t j = 0; j < matrix._columns; j++) {
                out << matrix._data[i * matrix._columns + j] << " ";
            }
            out << endl;
        }
        return out;
    }
};
}

//Привести заданную квадратную матрицу A к нижнетреугольному виду.
template<typename T>
T* lower_triangular_matrix(std::Matrix<T>& matrix){
    size_t rows = matrix.get_rows();
    size_t columns = matrix.get_columns();
    T* result=new T[columns*rows];
    for (T i = 0; i < rows; i++) {
        for (T j = i + 1; j < columns; j++) {
            T tmp = matrix(j,i) / matrix(i,i);
            for (size_t k = i; k < columns; k++) {
                result(i,j)=matrix(i,j)-matrix(k,j)*tmp;
            }
        }
    }
    return result;
  }




