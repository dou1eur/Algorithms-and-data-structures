#pragma once
namespace std {
	template<typename T>
	class Matrix {
	private:
		T** _data;
	    size_t _rows;
		size_t _columns;
	public:
	Matrix(){
    _rows=0;
    _columns=0;
    _data=nullptr;
    }

	Matrix(size_t rows, size_t columns){
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
	Matrix(size_t rows, size_t columns,T lower,T up){
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
	Matrix(const Matrix& other){
    _rows = other.rows;
    _columns = other.columns;
    _data = new T* [_rows];
    for (int i = 0; i < rows; ++i)
        _data[i] = new T[_columns];

    for (int i = 0; i < _rows; ++i)
        for (int j = 0; j < _columns; ++j)
            _data[i][j] = other(i, j);
    }
	~Matrix(){
    for (int i = 0; i < rows; i++)
        delete[] matrix[i];
    delete[] matrix;
    }
		size_t get_rows() const{
    return _rows;
    }
		size_t get_columns() const{
    return _columns;
    }
		T& operator()(T i,T j){
    if(((i>0)&&(i<_rows))&&((j>0)&&(j<_columns))){
        return _data[i][j];
    }
    else throw "Invalid row/column input"
    }

	Matrix operator+(const Matrix& rhs) {
    if((_rows==rhs._rows)&&(_columns=rhs._columns)){
    Matrix result(_rows,_columns);
    for (int i = 0; i < _rows; ++i)
            for (int j = 0; j < _columns; ++j)
                result._data[i][j] = _data[i][j] + rhs._data[i][j];
        return result;
   } 
   }
   Matrix operator-(const Matrix& rhs){
   if((_rows==rhs._rows)&&(_columns=rhs._columns)){
   Matrix result(_rows,_columns);
   for (int i = 0; i < _rows; ++i)
            for (int j = 0; j < _columns; ++j)
                result._data[i][j] = _data[i][j] - rhs._data[i][j];
        return result;
   } 
   }

	Matrix operator*(const Matrix& rhs){
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
	Matrix operator*(const T scalar){
    Matrix result(_rows,_columns)
    for(size_t i=0;i<_rows;++i){
        for(size_t j=0;j<_columns;++j){
            result._data[i][j]=_data[i][j]*scalar;
        }
    }
    return result;
    }
	Matrix operator/(const T scalar){
    Matrix result(_rows,_columns)
    for(size_t i=0;i<_rows;++i){
        for(size_t j=0;j<_columns;++j){
            result._data[i][j]=_data[i][j]/scalar;
        }
    }
    return result;
    }
    friend Matrix operator*(T scalar,Matrix matrix){
    Matrix result(matrix.get_rows(),matrix.get_columns());
    result=matrix*scalar;
    return result;
    }

    friend Matrix operator/(T scalar,Matrix matrix){
    Matrix result(matrix.get_rows(),matrix.get_columns());
    result=matrix/scalar;
    return result;
    }
    bool operator == (const Matrix& rhs) {
    bool result = true;
    if ((_rows == rhs._rows) && (_columns == rhs._columns)) {
        for (int i = 0; i < _rows; ++i)
            for (int j = 0; j < _columns; ++j)
                if (abs(_data[i][j] - rhs._data[i][j]) != 0) {
                    result = false;
                }
    }
    else {
        result = false;
    }
    return result;
    }
    void EnterMatrix() {
    std::cout << "Number of rows: ";
    int rows = _rows;
    std::cout << "Number of columns: ";
    int columns = _columns;

    Matrix newMatrix(rows, columns);
    for (int i = 0; i < _rows; ++i)
        for (int j = 0; j < _columns; ++j) {
            std::cout << "Cell (" << i << ", " << j << ") = ";
            std::cin >> newMatrix._data[i][j];
        }
   *this = newMatrix;
   }

	T tr(){
    T tr=0;
    for(size_t i=0;i<_rows;++i){
        tr+=_data[i][i];
    }
    return tr;
    }
		//T* random(T lower,T up);
		friend std::ostream& operator<<(std::ostream& out,const Matrix& matrix) {
    for (int i = 0; i < matrix._rows; i++) {
        for (int j = 0; j < matrix._columns; j++)
            out << matrix._data[i][j] << " ";
       out << "\n";
    }
    return out;
    }
};
    //Input Matrix

}