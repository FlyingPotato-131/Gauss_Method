#pragma once


#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include "fraction.hpp"

// struct floatmatrix{
//     std::vector < std::vector <fraction> > matrix_body; // тело матрицы
//     std::vector < fraction > addition; // дополнение матрицы
//     std::vector < fraction > roots; // вектор ответов
//     unsigned int rows; // количество строк
//     unsigned int columns; // количество столбцов
// }

struct Matrix
{
    std::vector < std::vector <fraction> > matrix_body; // тело матрицы
    std::vector < fraction > addition; // дополнение матрицы
    std::vector < fraction > roots; // вектор ответов
    unsigned int rows; // количество строк
    unsigned int columns; // количество столбцов
    // float determinant; // определитель матрицы
    /*
    пока не подберу адекватный по ассимтотике алгоритм для детерминанта, тут будет коммент вместо поля определителя
    */
};


void matrix_out(const Matrix& matrix)
{
    for (unsigned int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.columns; j++)
        {
            std::cout << std::setprecision(3) << std::setw(8) << matrix.matrix_body[i][j];
        }
        std::cout << std::endl;

        // std::cout << "  |\t" <<  matrix.addition[i] << std::endl;
    }
}


void matrix_answers_out(const Matrix& matrix)
{
    std::cout << std::endl;

    for (unsigned int i = 0; i < matrix.rows; i++)
    {
        std::cout << 'x' << i + 1 << "  =  " << matrix.roots[i] << std::endl;
    }
}

// деление строки, применяется непосредственно в методе Гаусса
void matrix_line_division(Matrix& matrix, unsigned int line, fraction scalar)
{
    std::cout << "divide line " << line << " by " << scalar << std::endl;
    for (unsigned int i = 0; i < matrix.columns; i++)
    {
        matrix.matrix_body[line][i] /= scalar;
    }

    // matrix.addition[line] /= scalar;
}


// вычитание строк друг из друга, возможно домножение
void matrix_line_subtraction(Matrix& matrix, unsigned int line_1, unsigned int line_2, fraction koefficient=frac(1))
{
    std::cout << "subtract " << koefficient << " * line " << line_1 << " from line " << line_2 << std::endl;
    for (unsigned int i = 0; i < matrix.columns; i++)
    {
        matrix.matrix_body[line_2][i] -= matrix.matrix_body[line_1][i] * koefficient;
    }

    // matrix.addition[line_2] -= matrix.addition[line_1] * koefficient;
}


// замена строк местами
void matrix_line_swap(Matrix& matrix, unsigned int line_1, unsigned int line_2)
{
    std::cout << "swap lines " << line_1 << " and " << line_2 << std::endl;
    std::vector <fraction> swap_line(matrix.columns);
    // fraction swap_value;

    swap_line = matrix.matrix_body[line_1];
    matrix.matrix_body[line_1] = matrix.matrix_body[line_2];
    matrix.matrix_body[line_2] = swap_line;

    //swap_value = matrix.addition[line_1];
    // matrix.addition[line_1] = matrix.addition[line_2];
    // matrix.addition[line_2] = swap_value;
}


// замена строки с нулем на диагонали
int matrix_zero_change(Matrix& matrix, unsigned int line, unsigned int koefficient_number)
{
    for (unsigned int i = line + 1; i < matrix.rows; i++)
    {
        if (matrix.matrix_body[i][koefficient_number] != frac(0))
        {
            matrix_line_swap(matrix, line, i);
            return 1;
        }
    }
    return 0;
}


// прямой ход метода Гаусса
void gauss_algo_first_part(Matrix& matrix)
{
    
    for (unsigned int element_index_now = 0; element_index_now < matrix.rows; element_index_now++)
    {
        // проверим на ноль элемент на диагонали
        if (matrix.matrix_body[element_index_now][element_index_now] == frac(0)) // в случае нахождении нуля на диагонали заменяем его
        { 
            int result = matrix_zero_change(matrix, element_index_now, element_index_now);
            
            if (result == 0) // если поменять строку с нулем не получилось, то матрицу решить не получится, завершаем программу
            {
                // std::cout << "matrix has been simplified" << std::endl;
                break;
            }
        }  


        // разделим на первый элемент всю строку, тем самым приведем ее к виду "0 ... 1 ..."
        matrix_line_division(matrix, element_index_now, matrix.matrix_body[element_index_now][element_index_now]); 


        // зануляем весь оставшийся столбец
        for (unsigned int i = element_index_now + 1; i < matrix.rows; i++)
        {
            matrix_line_subtraction(matrix, element_index_now, i, matrix.matrix_body[i][element_index_now]);
        }

        std::cout << std::endl;
        matrix_out(matrix);
        std::cout << std::endl;
    }
}

//преобразовать до единичной
void gauss_fin(Matrix& mtr){
    unsigned int size = 0;
    while(mtr.matrix_body[size][size] != frac(0)){
        size++;
        if(size == std::min(mtr.rows, mtr.columns)){
            break;
        }
    }

    for(unsigned int h = size - 1; h != 4294967295; h--){
        for(unsigned int w = h + 1; w < size; w++){
            matrix_line_subtraction(mtr, w, h, mtr.matrix_body[h][w]);
        }

        std::cout << std::endl;
        matrix_out(mtr);
        std::cout << std::endl;
    }
}



// обратный ход метода Гаусса
void gauss_algo_second_part(Matrix& matrix)
{
    std::vector <fraction> answers(matrix.rows);
    matrix.roots = answers;
    matrix.roots[matrix.rows - 1] = matrix.addition[matrix.rows - 1];
    

    for (int element_index_now = matrix.rows - 2; element_index_now >= 0; element_index_now -= 1)
    {
        matrix.roots[element_index_now] = matrix.addition[element_index_now];

        for (unsigned int j = matrix.rows - 1; j > element_index_now; j -= 1)
        {
            matrix.roots[element_index_now] -= matrix.matrix_body[element_index_now][j] * matrix.roots[j];    
        }
    }

}


// функция детерминанта, но с кринжовой ассимптотикой (там вообще жесть, чет вроде факториал пополоам)
// fraction determinant(Matrix& matrix)
// {
//     float result = 0;

//     /*
//     разделим реализацию на два случая
//     1) когда размер матрицы 2x2
//     2) остальные случаи
//     */

//     if (matrix.rows == 2)
//     {
//         return matrix.matrix_body[0][0] * matrix.matrix_body[1][1] - matrix.matrix_body[1][0] * matrix.matrix_body[0][1]; 
//     } // нашли детерминант в случае матрицы 2x2
    
//     /*
//     если матрица не 2x2, то рекурсивно посчитаем сумму алгебраических дополнений
//     */


//     for (int count = 0; count < matrix.rows; count++) // пройдемся по всем элементам первой строки и посчитаем для них алгебраические дополнения
//     {
//         Matrix new_matrix;

//         std::vector < std::vector <float> > new_matrix_body(matrix.rows - 1);

//         for (int i = 1; i < matrix.rows; i++)
//         {

//             for (int j = 0; j < matrix.rows; j++)
//             {
//                 if (j != count) { new_matrix_body[i - 1].push_back(matrix.matrix_body[i][j]); }
//             }
//         }


//         new_matrix.matrix_body = new_matrix_body;
//         new_matrix.rows = matrix.rows - 1;


//         result += std::pow(-1, 2 + count) * matrix.matrix_body[0][count] * determinant(new_matrix); 
//     }

//     return result;
// }
