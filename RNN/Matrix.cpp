#include "Matrix.hpp"

Matrix::Matrix(){}

Matrix::Matrix(std::vector<double>& input, int axis=0){
    // std::cout<<"Constructor Matrix Vector Start\n";
    if(axis == 0){
        this->matrix.resize(1);
        this->matrix[0].resize(input.size());
        for (size_t i = 0; i < input.size(); i++)
        {
            this->matrix[0][i] = input[i];
        }
        
        
    }else{
        
        this->matrix.resize(input.size());
        for (size_t i = 0; i < input.size(); i++)
        {
            this->matrix[i].resize(1);
            this->matrix[i][0] = input[i];
        }
        
    }
    // std::cout<<"Constructor Matrix Vector End\n";
}
Matrix::Matrix(std::vector<std::vector<double>>& input){
    
    this->matrix.resize(input.size());
    for (size_t i = 0; i < input.size(); i++)
    {
        this->matrix[i].resize(input[i].size());
        for (size_t j = 0; j < input[i].size(); j++)
        {
            this->matrix[i][j] = input[i][j];
        }
        
    }
    
}

Matrix::Matrix(int a, int b){
    // std::cout<<"Constructor Matrix col_row Start\n";
    this->matrix.resize(a);
    for (size_t i = 0; i < a; i++)
    {
        this->matrix[i].resize(b);
        for (size_t j = 0; j < b; j++)
        {
            this->matrix[i][j] = 0;
        }
        
    }
    // std::cout<<"Constructor Matrix col_row End\n";
}


void Matrix::zero(){
    for (size_t i = 0; i < this->matrix.size(); i++)
    {
        for (size_t j = 0; j < this->matrix[i].size(); j++)
        {
            this->matrix[i][j]=0.0;
        }
        
    }
    
}

int Matrix::size() const{
    return this->matrix.size();
}


const Matrix operator*(const Matrix& left, const Matrix& right){
    // std::cout<<"left("<<left.size()<<", "<<left[0].size()<<")\n";
    // std::cout<<"right("<<right.size()<<", "<<right[0].size()<<")\n";
    if(left[0].size()==right.size()){
        // std::cout<<"Ok Matrix operator * \n";
        Matrix mat(left.size(),right[0].size());
        for (size_t i = 0; i <  left.size(); i++)
        {
            for (size_t j = 0; j < right[0].size(); j++)
            {
                for (size_t k = 0; k < right.size(); k++)
                {
                    mat[i][j]+=left[i][k]*right[k][j];
                }
                
            }
            
        }
        return mat;
    }else{
        std::cout<<"Error Matrix operator * \n";
        exit(1);
    }
}


const Matrix operator+(const Matrix& left, const Matrix& right){
    if (left.size() == right.size() && left[0].size() == right[0].size())
    {
        Matrix mat(left.size(), left[0].size());
        for (size_t i = 0; i < left.size(); i++)
        {
            for (size_t j = 0; j < left[i].size(); j++)
            {
                mat[i][j] = left[i][j] + right[i][j];
            }
               
        }
        return mat;
    }else
    {
        std::cout<<"Error Matrix operator + \n";
        exit(2);
    }
}

const Matrix operator-(const Matrix& left, const Matrix& right){
    if(left.size() == right.size() && left[0].size() == right[0].size()){
        Matrix mat(left.size(), left[0].size() );
        
        for (size_t i = 0; i < left.size(); i++)
        {
            for (size_t j = 0; j < left[i].size(); j++)
            {
                mat[i][j] = left[i][j]-right[i][j];
            }
            
        }
        return mat;
        
    }else{
        std::cout<<"Error Matrix operator - \n";
        exit(3);
    }
}


Matrix& operator+=(Matrix& left, const Matrix& right){
    if(left.size()==right.size() && left[0].size()==right[0].size()){
        for (size_t i = 0; i < left.size(); i++)
        {
            for (size_t j = 0; j < left[0].size(); j++)
            {
                left[i][j]+=right[i][j];
            }
            
        }
        return left;
    }else{
        std::cout<<"Error Matrix operator += \n";
        exit(4);
    }

}


Matrix& operator-=(Matrix& left, const Matrix &right){
    if(left.size()==right.size() && left[0].size()==right[0].size()){
        for (size_t i = 0; i < left.size(); i++)
        {
            for (size_t j = 0; j < left[0].size(); j++)
            {
                left[i][j]-=right[i][j];
            }
            
        }
        return left;
    }else
    {
        std::cout<<"Error Matrix operator -= \n";
        exit(4);
    }
    

}

Matrix& Matrix::operator=(const Matrix& right){
    for (size_t i = 0; i < this->matrix.size(); i++)
    {
        this->matrix[i].clear();
    }
    this->matrix.clear();
    this->matrix.resize(right.size());

    for (size_t i = 0; i < right.size(); i++)
    {
        this->matrix[i].resize(right[i].size());
        for (size_t j = 0; j < right[i].size(); j++)
        {
            this->matrix[i][j] = right[i][j];
        }
        
    }

	return *this;
}

std::vector<double>& Matrix::operator[](int i)
{
	return this->matrix[i];
}

const std::vector<double>& Matrix::operator[](int i) const
{
	return this->matrix[i];
}



// friend Matrix operator*(Matrix& left, Matrix& right){
//     if(left[0].size()==right.size()){
//         Matrix mat(left.size(),right[0].size());
//         for (size_t i = 0; i <  left.size(); i++)
//         {
//             for (size_t j = 0; j < right.size(); j++)
//             {
//                 for (size_t k = 0; k < left[0].size(); k++)
//                 {
//                     mat[i][j]+=left[i][k]*right[k][j];
//                 }
                
//             }
            
//         }
//         return mat;
//     }else{
//         exit(1);
//     }
// }