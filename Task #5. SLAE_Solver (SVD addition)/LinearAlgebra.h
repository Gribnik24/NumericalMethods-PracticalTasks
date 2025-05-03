#pragma once
#include <vector>
#include <cmath>
#include <stdexcept>
#include <chrono>

using Matrix = std::vector<std::vector<double>>;
using Vector = std::vector<double>;

// Matrix operations
Matrix createMatrix(int N);
Matrix transpose(const Matrix& A); // Добавлено
Matrix multiply(const Matrix& A, const Matrix& B); // Добавлено
Vector createRightHandSide(const Matrix& A);
double computeError(const Vector& x, const Vector& x_exact);
double computeConditionNumber(const Matrix& A);  // Добавлено

// LU decomposition
void luDecomposition(Matrix& A, std::vector<int>& pivot);
Vector solveLU(const Matrix& LU, const std::vector<int>& pivot, const Vector& f);

// QR decomposition
void householderQR(const Matrix& A, Matrix& Q, Matrix& R);
Vector solveQR(const Matrix& Q, const Matrix& R, const Vector& f);

// SVD decomposition
void svdDecomposition(const Matrix& A, Matrix& U, Vector& S, Matrix& V);  // Добавлено
Vector solveSVD(const Matrix& U, const Vector& S, const Matrix& V, const Vector& f);  // Добавлено