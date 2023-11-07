#include <iostream>
#include <random>
#include <stdexcept>
#include<complex>
namespace std {
	template<class T>
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
        Matrix(size_t rows,size_t columns, complex<T>){
            if(rows<0||columns<0) {
                throw runtime_error("Uncorrect size of matrix!");
            }
            _data=new complex<T>[_columns*_rows];
            for(size_t i=0;i<_rows;++i) {
                for(size_t j=0;j<_columns;++j) {
                    _data[i*_columns+j]=0;
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
                    _data[i*_columns+j]=lower+static_cast<T>(rand())/(static_cast<T>(RAND_MAX)/(up-lower));
                }
            }
        }

        Matrix(size_t rows, size_t columns,complex<T> lower,complex<T> up):_rows(rows),_columns(columns) {
            if(rows<0||columns<0) {
                throw runtime_error("Uncorrect size of matrix!");
            }
            _data=new T[_columns*_rows];
            for(size_t i=0;i<_rows;++i) {
                for(size_t j=0;j<_columns;++j) {
                    T real=lower.real()+static_cast<T>(rand())/(static_cast<T>(RAND_MAX)/(up.real()-lower.real()));
                    T imag=lower.imag()+static_cast<T>(rand())/(static_cast<T>(RAND_MAX)/(up.imag()-lower.imag()));
                    _data[i*_columns+j]=complex<T>(real,imag);
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

        T tr() const{
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

        T& operator()(size_t i, size_t j) const {
            if(((i>=0)&&(i<_rows))&&((j>=0)&&(j<_columns))) {
                return _data[i*_columns+j];
            }
            else throw runtime_error("Invalid row/column input");
        }

        Matrix<T> operator+=(const Matrix<T>& other) {
            if (_rows != other._rows || _columns != other._columns) {
                throw runtime_error("Invalid row/column");
            }
            for(size_t i=0;i<_rows;++i) {
                for(size_t j=0;j<_columns;++j) {
                    _data[i*_columns+j]+=other._data[i * _columns + j];
                }
            }
            return *this;
        }

        Matrix<T> operator+(const Matrix<T>& other){
            return Matrix(*this)+=other;
        }

        Matrix<complex<T>> operator+=(const Matrix<complex<T>>& other) {
            if (_rows != other._rows || _columns != other._columns) {
                throw runtime_error("Invalid row/column");
            }
            for(size_t i=0;i<_rows;++i) {
                for(size_t j=0;j<_columns;++j) {
                    _data[i*_columns+j].real()+=other._data[i * _columns + j].real();
                    _data[i*_columns+j].imag()+=other._data[i * _columns + j].imag();
                }
            }
            return *this;
        }

        Matrix<complex<T>> operator+(const Matrix<complex<T>>& other){
            return Matrix(*this)+=other;
        }

        Matrix<T> operator-=(const Matrix<T>& other) {
            if (_rows != other._rows || _columns != other._columns) {
                throw runtime_error("Invalid row/column");
            }
            for(size_t i=0;i<_rows;++i) {
                for(size_t j=0;j<_columns;++j) {
                    _data[i*_columns+j]-=other._data[i * _columns + j];
                }
            }
            return *this;
        }
        
        Matrix<T> operator-(const Matrix<T>& other){
            return Matrix(*this)-=other;
        }

        Matrix<complex<T>> operator-=(const Matrix<complex<T>>& other) {
            if (_rows != other._rows || _columns != other._columns) {
                throw runtime_error("Invalid row/column");
            }
            for(size_t i=0;i<_rows;++i) {
                for(size_t j=0;j<_columns;++j) {
                    _data[i*_columns+j].real()-=other._data[i * _columns + j].real();
                    _data[i*_columns+j].imag()-=other._data[i * _columns + j].imag();
                }
            }
            return *this;
        }

        Matrix<complex<T>> operator-(const Matrix<complex<T>>& other){
            return Matrix(*this)-=other;
        }

        Matrix operator*(const Matrix<T>& other) const{
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

        Matrix operator*(const T scalar) const{
            Matrix<T> result(_rows,_columns);
            for(size_t i=0;i<(_columns*_rows);++i) {
                result._data[i]=_data[i]*scalar;
            }
            return result;
        }
        Matrix<complex<T>> operator*(const complex<T> scalar) const{
            Matrix<complex<T>> result(_rows,_columns);
            for(size_t i=0;i<(_columns*_rows);++i) {
                result._data[i].real()=_data[i].real()*scalar.real();
                result._data[i].imag()=_data[i].imag()*scalar.imag();
            }
            return result;
        }

        Matrix operator/(const T scalar) const{
            if (scalar==0) {
                throw invalid_argument("/0");
            }
            Matrix<T> result(_rows,_columns);
            for(size_t i=0;i<(_columns*_rows);++i) {
                result._data[i]=_data[i]/scalar;
            }
            return result;
        }        
        Matrix<complex<T>> operator/(const complex<T> scalar) const{
            if (scalar.real()==0) {
                throw invalid_argument("/0");
            }
            Matrix<complex<T>> result(_rows,_columns);
            for(size_t i=0;i<(_columns*_rows);++i) {
                result._data[i].real()=_data[i].real()/scalar.real();
                result._data[i].imag()=_data[i].imag()/scalar.imag();
            }
            return result;
        }


        bool operator==(const Matrix<T>& other) const{
            const float eps=0.0001;
            bool result=true;
            if ((_rows==other._rows) && (_columns==other._columns)) {
                for (int i = 0; i < _rows; ++i){
                    for (int j = 0; j < _columns; ++j) {
                        if (abs(_data[i*_columns+_rows] - other._data[i*_columns+_rows]) != eps) {
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

        bool operator==(const Matrix<complex<T>>& other) const{
            const T eps=0.0005;
            bool result=true;
            if ((_rows==other._rows) && (_columns==other._columns)) {
                for (int i = 0; i < _rows; ++i) {
                    for (int j = 0; j < _columns; ++j) {
                        if (abs(_data[i*_columns+_rows].real() - other._data[i*_columns+_rows].real()) != eps &&abs(_data[i*_columns+_rows].imag() - other._data[i*_columns+_rows].imag()) != eps) {
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

        bool operator!=(const Matrix<T>& other) const{
            if(*this==other){
                return false;
            }
            return true;
        }

        bool operator!=(const Matrix<complex<T>>& other) const{
            if(*this==other){
                return false;
            }
            return true;
        }

        bool can_multiply(const Matrix<T>& other) const{
            return _rows==other._columns;
        }

    //Вывод
       friend ostream& operator<<(std::ostream& out,const Matrix<T>& matrix) {
            for (size_t i = 0; i < matrix._rows; ++i) {
                for (size_t j = 0; j < matrix._columns; ++j) {
                    out << matrix._data[i * matrix._columns + j] << " ";
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
template<typename T>
Matrix<complex<T>> LU_decomposition(Matrix<complex<T>>& A) {
    //Суть метода- разложить матрицу на верхнюю треугольную и нижнюю треугольную
    if (A.get_rows() != A.get_columns()) {
        throw runtime_error("Matrix must be square for LU decomposition.");
    }
    size_t n=A.get_rows();
    Matrix<complex<T>> L(n, n);
    Matrix<complex<T>> U(n, n);
    for (size_t i = 0; i < n; ++i) {
        for (size_t k = i; k < n; ++k) {
            complex<T> sum = 0;
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
                complex<T> sum = 0;
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



