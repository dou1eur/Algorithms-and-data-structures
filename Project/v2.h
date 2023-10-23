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
        Matrix():_rows(0),_columns(0),_data(nullptr) {}
        Matrix(size_t rows,size_t columns):_rows(rows),_columns(columns) {
            if(rows<0||columns<0) {
                throw runtime_error("Uncorrect size of matrix!");
            }
            _data=new T[_columns*_rows];
            for(size_t i=0;i<_rows;++i) {
                for(size_t j=0;j<_columns;++j) {
                    _data[i*_columns+j]=0;
                }
            }
        }

        Matrix(size_t rows,size_t columns,const complex<T> data):_rows(rows),_columns(columns) {
            if(rows<0||columns<0) {
                throw runtime_error("Uncorrect size of matrix!");
            }
            _data=new complex<T>[_columns*_rows];
            for(size_t i=0;i<_rows;++i){
                for(size_t j=0;j<_columns;++j) {
                    _data[i*_columns+j]->real(data[i*_columns+j].real());
                    _data[i*_columns+j]->imag(data[i*_columns+j].imag());
                }
            }
        }

        Matrix(size_t rows, size_t columns,T lower,T up):_rows(rows),_columns(columns) {
            if(rows<0||columns<0) {
                throw runtime_error("Uncorrect size of matrix!");
            }
            _data=new T[_columns*_rows];
            for(size_t i=0;i<_rows;++i) {
                for(size_t j=0;j<_columns;++j) {
                    auto a=rand()%up+lower;
                    _data[i*_columns+j]=a;
                }
            }
        }

        Matrix(const Matrix<T>& other) {
            _rows = other._rows;
            _columns = other._columns;
            _data = new T[_rows * _columns];
            for (int i = 0; i < (_columns*_rows); ++i) {
                _data[i] = other._data[i];
            }
        }

        Matrix(const Matrix<complex<T>>& other) {
            _rows = other.get_rows();
            _columns = other.get_columns();
            _data = new complex<T>[_rows * _columns];
            for (int i = 0; i < (_columns*_rows); ++i) {
                _data[i] ->real(other._data[i].real());
                _data[i] ->imag(other._data[i].imag());
            }
        }

        ~Matrix() {
            if(_data!=nullptr) {
                delete[] _data;
            }
        }

    //get and tr
        size_t get_rows() const {
            return _rows;
        }

        size_t get_columns() const {
            return _columns;
        }

        T tr(){
            if (_rows!=_columns) {
                throw runtime_error("Matrix is not square");
            }
            T tr=0;
            for(size_t i=0;i<_rows;++i) {
                tr+=_data[i*_columns+i];
            }
            return tr;
        }

    //Операторы
        Matrix& operator=(const Matrix<T>& other) {
            _rows=other._rows;
            _columns=other._columns;
            _data = new T[_columns * _rows];
            for(size_t i=0;i<_rows;++i) {
                for(size_t j=0;j<_columns;++j) {
                    _data[i*_columns+j]=other._data[i*_columns+j];
                }
            }
        }

        T& operator()(size_t i, size_t j) {
            if(((i>=0)&&(i<_rows))&&((j>=0)&&(j<_columns))) {
                return _data[i*_columns+j];
            }
            else throw runtime_error("Invalid row/column input");
        }

        Matrix operator+(const Matrix<T>& other) {
            if (_rows != other._rows || _columns != other._columns) {
                throw runtime_error("Invalid row/column");
            }
            Matrix<T> result(_rows,_columns);
            for(size_t i=0;i<_rows;++i) {
                for(size_t j=0;j<_columns;++j) {
                    result._data[i*_columns+j]=_data[i * _columns + j] + other._data[i * _columns + j];
                }
            }
            return result;
        }

        Matrix<complex<T>> operator+(const Matrix<complex<T>>& other) {
            if (_rows != other._rows || _columns != other._columns) {
                throw runtime_error("Invalid row/column");
            }
            Matrix<complex<T>> result(_rows,_columns);
            for(size_t i=0;i<_rows;++i) {
                for(size_t j=0;j<_columns;++j) {
                    result._data[i*_columns+j].real()=_data[i * _columns + j].real() + other._data[i * _columns + j].real();
                    result._data[i*_columns+j].imag()=_data[i * _columns + j].imag() + other._data[i * _columns + j].imag();
                }
            }
            return result;
        }

        Matrix operator-(const Matrix<T>& other) {
            if (_rows != other._rows || _columns != other._columns) {
                throw runtime_error("Invalid row/column");
            }
            Matrix<T> result(_rows,_columns);
            for(size_t i=0;i<_rows;++i) {
                for(size_t j=0;j<_columns;++j) {
                    result._data[i*_columns+j]=_data[i * _columns + j] - other._data[i * _columns + j];
                }
            }
            return result;
        }

        Matrix<complex<T>> operator-(const Matrix<complex<T>>& other) {
            if (_rows != other._rows || _columns != other._columns) {
                throw runtime_error("Invalid row/column");
            }
            Matrix<complex<T>> result(_rows,_columns);
            for(size_t i=0;i<_rows;++i) {
                for(size_t j=0;j<_columns;++j) {
                    result._data[i*_columns+j].real()=_data[i * _columns + j].real() - other._data[i * _columns + j].real();
                    result._data[i*_columns+j].imag()=_data[i * _columns + j].imag() - other._data[i * _columns + j].imag();
                }
            }
            return result;
        }

        Matrix operator*(const Matrix<T>& other) {
            if (can_multiply(other)==false) {
                throw runtime_error("rows!=columns");
            }
            Matrix<T> result(_rows, other._columns);
            for (size_t i = 0; i < _rows; ++i) {
                for (size_t j = 0; j < other._columns; ++j) {
                    T sum = 0;
                    for (size_t k = 0; k < _columns; ++k) {
                        sum += _data[i * _columns + k] * other._data[k * other._columns + j];
                    }
                    result._data[i * result._columns + j] = sum;
                }
            }
            return result;
        }

        Matrix operator*(const T scalar) {
            Matrix<T> result(_rows,_columns);
            for(size_t i=0;i<(_columns*_rows);++i) {
                result._data[i]=_data[i]*scalar;
            }
            return result;
        }

        Matrix<complex<T>> multiplication(const T scalar) {
            Matrix<T> result(_rows,_columns);
            for(size_t i=0;i<(_columns*_rows);++i) {
                result._data[i].real()=_data[i].real()*scalar;
                result._data[i].imag()=_data[i].imag()*scalar;
            }
            return result;
        }

        Matrix operator/(const T scalar) {
            if (scalar==0) {
                throw invalid_argument("/0");
            }
            Matrix<T> result(_rows,_columns);
            for(size_t i=0;i<(_columns*_rows);++i) {
                result._data[i]=_data[i]/scalar;
            }
            return result;
        }

        Matrix<complex<T>> division(const T scalar) {
            if (scalar==0) {
                throw invalid_argument("/0");
            }
            Matrix<T> result(_rows,_columns);
            for(size_t i=0;i<(_columns*_rows);++i) {
                result._data[i].real()=_data[i].real()/scalar;
                result._data[i].imag()=_data[i].imag()/scalar;
            }
            return result;
        }

        bool operator==(const Matrix<T>& other) {
            bool result=true;
            if ((_rows==other._rows) && (_columns==other._columns)) {
                for (int i = 0; i < _rows; ++i){
                    for (int j = 0; j < _columns; ++j) {
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

        bool operator==(const Matrix<complex<T>>& other) {
            bool result=true;
            if ((_rows==other._rows) && (_columns==other._columns)) {
                for (int i = 0; i < _rows; ++i) {
                    for (int j = 0; j < _columns; ++j) {
                        if (abs(_data[i*_columns+_rows].real() - other._data[i*_columns+_rows].real()) != 0 &&abs(_data[i*_columns+_rows].imag() - other._data[i*_columns+_rows].imag()) != 0) {
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

        bool operator!=(const Matrix<T>& other) {
            if(*this==other){
                return false;
            }
            return true;
        }

        bool operator!=(const Matrix<complex<T>>& other) {
            if(*this==other){
                return false;
            }
            return true;
        }

        bool can_multiply(const Matrix<T>& other) {
            return _rows==other._columns;
        }

    //Вывод
        friend std::ostream& operator<<(std::ostream& out,const Matrix<T>& matrix) {
            for (size_t i = 0; i < matrix._rows; ++i) {
                for (size_t j = 0; j < matrix._columns; ++j) {
                    out << matrix._data[i * matrix._columns + j] << " ";
                }
                out << endl;
            }
            return out;
        }
        
        ostream& print(std::ostream& out,const Matrix<complex<T>>& matrix) {
            for (size_t i = 0; i < matrix.get_rows(); ++i) {
                for (size_t j = 0; j < matrix.get_columns(); ++j) {
                    out <<"("<< matrix._data[i * matrix.get_columns() + j].real() << "+"<<matrix._data[i * matrix.get_columns() + j].imag()<<i<<")"<<endl;
                }
                out << endl;
            }
            return out;
        }
};


//Привести заданную квадратную матрицу A к нижнетреугольному виду
template<typename T>
Matrix<T> LU_decomposition(Matrix<T>& A) {
    //Суть метода- разложить матрицу на верхнюю треугольную и нижнюю треугольную
    if (A.get_rows() != A.get_columns()) {
        throw runtime_error("Matrix must be square for LU decomposition.");
    }
    size_t n=A.get_rows();
    Matrix<T> L(n, n);
    Matrix<T> U(n, n);
    for (size_t i = 0; i < n; ++i) {
        for (size_t k = i; k < n; ++k) {
            T sum = 0;
            for (size_t j = 0; j < i; ++j) {
                sum= sum+L(i, j) * U(j, k);
            }
            U(i, k) = A(i, k) - sum;
        }
        for (size_t k = i; k < n; ++k) {
            if (i == k) {
                L(i, i) = 1;
            } 
            else {
                T sum = 0;
                for (size_t j = 0; j < i; ++j) {
                    sum=sum+ L(k, j) * U(j, i);
                }
                L(k, i) = (A(k, i) - sum) / U(i, i);
            }
        }
    }
    return L;
}
}



