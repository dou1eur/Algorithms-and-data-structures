#pragma once
namespace std {
	template<typename T>
	class Matrix {
	private:
		T** _data;
	    size_t _rows;
		size_t _columns;
	public:
		Matrix();
		Matrix(size_t rows, size_t columns);
		Matrix(size_t rows, size_t columns,T lower,T up);
		Matrix(const Matrix& other);
		~Matrix();
		size_t get_rows() const;
		size_t get_columns() const;
		T& operator()(T i,T j);
		Matrix operator+(const Matrix& rhs);
		Matrix operator-(const Matrix& rhs);
		Matrix operator*(const Matrix& rhs);
		Matrix operator*(const T scalar);
		Matrix operator/(const T scalar);
        Matrix operator*(T scalar,Matrix matrix);
        Matrix operator/(T scalar,Matrix matrix);
		T tr();
		//T* random(T lower,T up);
		friend std::ostream& operator<<(std::ostream& out,const Matrix& matrix);
	};

}