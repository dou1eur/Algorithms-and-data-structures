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
        Matrix(const Matrix& other);
		~Matrix();
		int get_rows() const;
		int get_columns() const;
		T& operator()(T i,T j);
		Matrix operator+(const Matrix& rhs);
		Matrix operator-(const Matrix& rhs);
		Matrix operator*(const Matrix& rhs);
		Matrix operator*(const T scalar);
		Matrix operator/(const T scalar);
		friend Matrix operator*(T scalar,Matrix matrix);
		friend Matrix operator/(T scalar,Matrix matrix);
		T tr();
		friend std::ostream& operator<<(std::ostream& out,const Matrix& matrix);
	};
}