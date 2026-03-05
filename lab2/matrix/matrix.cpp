#include <vector>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

template<typename T>
class Matrix {
private:
    std::vector<T> data;
    unsigned rows_, cols_;

public:
    Matrix(unsigned rows, unsigned cols, const T& value = T()) 
        : rows_(rows), cols_(cols), data(rows * cols, value) {

    }

    unsigned rows() const { return rows_; }
    unsigned cols() const { return cols_; }

    T& operator()(unsigned row, unsigned col) {
        return data[row * cols_ + col];
    }
    
    const T& operator()(unsigned row, unsigned col) const {
        return data[row * cols_ + col];
    }


    static T random(T min, T max) {
        return min + std::rand() / T(RAND_MAX) * (max - min);
    }

    static Matrix generateWithDeterminant(unsigned n, T target_det) {    
        Matrix matrix(n, n);
        // А если у типа T нет конструктора от int?
        // В любом случае лучше писать static_cast<T>(1), так будет покрыто большее количество типов T
        T curr_det = T(1);
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    matrix(i, j) = random(T(1), T(5));
                    curr_det *= matrix(i, j);
                } else if (i < j) {
                    matrix(i, j) = random(T(-5), T(5));
                } else {
                    matrix(i, j) = T(0);
                }
            }
        }
        T scale = (target_det / curr_det);
            matrix(0, 0) *= scale;
        
        // Этот код сильно напоминает прибавление одной строчки матрицы к другой с заданным коэффициентом
        // Такое нужно дальше для расчета детерминанта, почему бы не сделать это отдельным методом, а затем переиспользовать?
        for (int i = 0; i < n*2; i++) {
            int row1 = rand() % n;
            int row2;
            do {
                row2 = rand() % n;
            } while (row1 == row2);

            T lambda = (rand()/(T)RAND_MAX - 0.5) * 0.5;
        for (int j = 0; j < n; j++){
            matrix(row1, j) += lambda * matrix(row2, j);
        } 
    }
    return matrix;
}

    Matrix& transpose() {
        if (rows_ != cols_) {
            // Да ладно?
            std::cout << "Транспонирование возможно только для квадратных матриц" << std::endl;
            return *this;
        }
        for (int i = 0; i < rows_; i++) {
            for(int j = i+1; j < cols_; j++){
                T temp = (*this)(i,j);
                (*this)(i,j) = (*this)(j,i);
                (*this)(j,i) = temp;
            }
        }
        return *this;
    }

    Matrix transpose() const {
        Matrix result(cols_, rows_);
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                result(j, i) = (*this)(i, j);
            }
        }
        return result;
    }

// Два метода traspose делают формально одно и тоже с одним исплючениием: один копирует, другой изменяет себя
// Один из них можно оперделеить через другой, но нудно подумать

void print() const {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            std::cout << (*this)(i,j) << " ";
        }
        std::cout << std::endl;
    }
}

};

template<typename T>
T determinant(const Matrix<T>& matrix) {
    int n = matrix.rows();

    Matrix<T> temp = matrix;
    T det = T(1);

    for (int i = 0; i < n; i++) {
        if (temp(i,i) == T(0)) {
            return T(0);
            // Получается, что у матрицы [ [0, 1] [1, 0] ] нулевой детерминант?
        }
        det *= temp(i,i);

        // И вот как раз тут можно было бы использовать метод с вычитанием строк
        for (int j = i +1; j < n; j++) {
            T lambda = temp(j,i)/temp(i,i);
            for (int k = i; k < n; k++) {
                temp(j, k) -= lambda * temp(i,k);
            }
        }
    }
    return det;
}
int main() {
    std::srand(std::time(0));
    Matrix<double> m5 = Matrix<double>::generateWithDeterminant(5, 23.0);
    m5.print();
    double det5 = determinant(m5);
    double det5transposed = determinant(m5.transpose());
    std::cout << det5 << std::endl;
    std::cout << det5transposed << std::endl;
    std::cout << "---------------------------" << std::endl;

    Matrix<double> m50 = Matrix<double>::generateWithDeterminant(50, 4.0);
    m50.print(); // чето очень много цифр на экран вывалилось
    double det50 = determinant(m50);
    double det50transposed = determinant(m50.transpose());
    std::cout << det50 << std::endl;
    std::cout << det50transposed << std::endl;
    std::cout << "---------------------------" << std::endl;

    Matrix<double> m100 = Matrix<double>::generateWithDeterminant(100, 3542.0);
    m100.print();
    double det100 = determinant(m100);
    double det100transposed = determinant(m100.transpose());
    std::cout << det100 << std::endl;
    std::cout << det100transposed << std::endl;
    std::cout << "---------------------------" << std::endl;

    return 0;
}
