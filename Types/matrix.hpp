#ifndef MATRIX_HPP_
#define MATRIX_HPP_
#include <cstddef>
#include <vector>
#include <exception>
#include <cmath>
#include <algorithm>
#include <utility>

class SizeUnmatching : public std::exception{
    public:
        const char* what() const noexcept override{
            return "Unmatched matrix sizes!";
        }
};
class NotSquareMatrix : public std::exception{
    public:
        const char* what() const noexcept override{
            return "NotSquareMatrix!";
        }
};

template<typename T>
class Matrix{
    public:
        Matrix() = default;
        Matrix(std::size_t rw, std::size_t cl) : row{rw}, col{cl},data(rw, std::vector<T>(cl)) {}

        int get_row()const{return row;}
        int get_col()const{return col;}

        Matrix identity(const std::size_t n) const{
            Matrix idmatrix(n,n);
            for (std::size_t i{}; i < n; ++i)
                idmatrix[i][i] = 1;

            return idmatrix;
        }

        // Matrix inverse 
        // TODO: fix inverse
        Matrix inverse() const{
            if (row != col){
                throw NotSquareMatrix{};
            }

            // Augment the matrix with an identity matrix
            Matrix augmented(row, 2 * row);
            for (std::size_t i = 0; i < row; ++i)
            {
                for (std::size_t j = 0; j < row; ++j)
                {
                    augmented[i][j] = data[i][j];
                    augmented[i][j + row] = (i == j) ? 1 : 0;
                }
            }

            // Gaussian elimination with partial pivoting
            for (std::size_t i = 0; i < row; ++i)
            {
                // Find pivot row
                std::size_t pivotRow = i;
                for (std::size_t j = i + 1; j < row; ++j)
                {
                    if (std::abs(augmented[j][i]) > std::abs(augmented[pivotRow][i]))
                    {
                        pivotRow = j;
                    }
                }

                // Swap rows if necessary
                if (pivotRow != i)
                {
                    std::swap(augmented[i], augmented[pivotRow]);
                }

                // Perform row operations to obtain zeroes below the pivot
                for (std::size_t j = i + 1; j < row; ++j)
                {
                    T factor = augmented[j][i] / augmented[i][i];
                    for (std::size_t k = i; k < 2 * row; ++k)
                    {
                        augmented[j][k] -= factor * augmented[i][k];
                    }
                }
            }

            // Back-substitution to obtain the inverse
            for (std::size_t i = row - 1; i > 0; --i)
            {
                for (std::size_t j = i - 1; j >= 0; --j)
                {
                    T factor = augmented[j][i] / augmented[i][i];
                    for (std::size_t k = 0; k < 2 * row; ++k)
                    {
                        augmented[j][k] -= factor * augmented[i][k];
                    }
                }
            }

            // Divide each row by the pivot to obtain ones on the diagonal
            for (std::size_t i = 0; i < row; ++i)
            {
                T pivot = augmented[i][i];
                for (std::size_t j = 0; j < 2 * row; ++j)
                {
                    augmented[i][j] /= pivot;
                }
            }

            // Extract the inverse matrix
            Matrix<T> result(row, row);
            for (std::size_t i = 0; i < row; ++i)
            {
                for (std::size_t j = 0; j < row; ++j)
                {
                    result[i][j] = augmented[i][j + row];
                }
            }

            return result;
        }

        // Matrix transpose
        Matrix transpose() const {
            Matrix<T> result(col, row);
            for (std::size_t i{}; i < row; ++i) 
                for (std::size_t j{}; j < col; ++j) 
                    result[j][i] = data[i][j];

            return result;
        }

        T& operator()(int rw, int cl) {
            return data[rw][cl];
        }

        const T& operator()(int rw, int cl) const {
            return data[rw][cl];
        }

        std::vector<T>& operator[](int row) {
            return data[row];
        }

        const std::vector<T>& operator[](int row) const {
            return data[row];
        }

        // Matrix addition
        Matrix& operator+=(const Matrix& other){
            if (row != other.row || col != other.col)
                throw SizeUnmatching{};

            for (std::size_t i{}; i < row; ++i) {
                for (std::size_t j{}; j < col; ++j) {
                    data[i][j] += other[i][j];
                }
            } 
            return *this;
        }

        template<typename U>
        friend Matrix<U> operator+(Matrix<U> lhand, const Matrix<U>& rhand);

        // Matrix substraction
        Matrix& operator-=(const Matrix& other){
            if (row != other.row || col != other.col)
                throw SizeUnmatching{};

            for (std::size_t i{}; i < row; ++i) {
                for (std::size_t j{}; j < col; ++j) {
                    data[i][j] -= other[i][j];
                }
            }         
            return *this;
        }

        template<typename U>
        friend Matrix<U> operator-(Matrix<U> lhand, const Matrix<U>& rhand);

        // Matrix multiplication
        Matrix& operator*=(const Matrix& other){
            if(col != other.row)
                throw SizeUnmatching{};
            
            Matrix result(row, other.col);
            for(size_t i{}; i<row; ++i){
                for(size_t j{}; j<other.col; ++j){
                    for (size_t k{}; k < col; ++k) {
                        result(i, j) += (*this)(i, k) * other(k, j);
                    }
                }
            }
            col = other.col;
            (*this).data = std::move(result.data);

            return *this;
        }

        template<typename U>
        friend Matrix<U> operator*(Matrix<U> lhand, const Matrix<U>& rhand);

        // scalar multiplication
        template<typename X>
        Matrix& operator*=(const X& scalar){
            for (auto& row : data) {
                for (auto& element : row) {
                    element *= scalar;
                }
            }
            return *this;
        }

        template<typename U, typename X>
        friend auto operator*(Matrix<U> matrix_, const X rhand) -> Matrix<decltype(U{}*X{})>;

        // Output stream operator for Matrix
        template<typename U>
        friend std::ostream& operator<<(std::ostream& os, const Matrix<U>& matrix){
            for (const auto& row : matrix.data) {
                for (const auto& element : row) {
                    os << element << ' ';
                }
                os << '\n';
            }
            return os;
        }

    private:
        std::size_t row{}, col{};
        std::vector<std::vector<T>> data;
};

// Matrix addition
template<typename T>
Matrix<T> operator+(Matrix<T> lhand, const Matrix<T>& rhand){
    return lhand += rhand;
}

// Matrix multiplication
template<typename U>
Matrix<U> operator*(Matrix<U> lhand, const Matrix<U>& rhand){
    return lhand *= rhand;
}

// Matrix substraction
template<typename U>
Matrix<U> operator-(Matrix<U> lhand, const Matrix<U>& rhand){
    return lhand -= rhand;
}

// scalar multiplication
template <typename U, typename X>
auto operator*(Matrix<U> matrix_, const X scalar) -> Matrix<decltype(U{}*X{})>{
    Matrix<decltype(U{}*X{})> tempMatrix(matrix_.get_row(), matrix_.get_col());\
    
    for (std::size_t i{}; i < tempMatrix.get_row(); ++i) {
        for (std::size_t j{}; j < tempMatrix.get_row(); ++j) {
            tempMatrix[i][j] = matrix_[i][j];
        }
    }    
    return tempMatrix *= scalar;
}

#endif