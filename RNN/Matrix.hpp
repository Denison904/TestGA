#pragma once
#include <vector>
#include <iostream>
class Matrix{
public:
    Matrix();
    Matrix(std::vector<double>& input, int axis);
    Matrix(std::vector<std::vector<double>>& input);
    Matrix(int a, int b);
    
    void zero();

    int size() const;

    friend const Matrix operator*(const Matrix& left, const Matrix& right);
    friend const Matrix operator+(const Matrix& left, const Matrix& right);
    friend const Matrix operator-(const Matrix& left, const Matrix& right);
    // friend Matrix operator*(Matrix& left, Matrix& right);
    friend Matrix& operator+=(Matrix& left, const Matrix& right);
    friend Matrix& operator-=(Matrix& left, const Matrix& right);
    Matrix& operator=(const Matrix& right);
	std::vector<double>& operator[](int i);
	const std::vector<double>& operator[](int i) const;
private:
    std::vector<std::vector<double>> matrix;
    
};