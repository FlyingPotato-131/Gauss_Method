/*
Реализация метода Гаусса взята из учебника Ф.Г. Авхадиева "Основы численных методов"

ссылка на учебник: https://kpfu.ru//staff_files/F240899232/OsnChM_Avkhadiev_FG.pdf

*/


#include <iostream>
#include <vector>
#include <iomanip>

#include "functions.hpp" // импорт функций, связанных с матрицей и преобразованиями


// int main()
// {
//     Matrix my_matrix;
//     my_matrix.matrix_body = {
//         {1, 2, 3},
//         {4, 9, 13},
//         {9, 19, 29}
//     };
//     my_matrix.addition = {10, 41, 92};
//     my_matrix.rows = 3;


//     std::cout << "Input:" << std::endl;
//     matrix_out(my_matrix);

//     gauss_algo_first_part(my_matrix);


//     std::cout << std::endl << "Matrix after gauss algo first part:" << std::endl;
//     matrix_out(my_matrix);

//     gauss_algo_second_part(my_matrix);
//     matrix_answers_out(my_matrix);

//     return 0;
// }

int main(){
    Matrix mtr;

    std::cout << "Input height and width" << std::endl;
    std::cin >> mtr.rows >> mtr.columns;
    mtr.matrix_body.resize(mtr.rows);
    for(int row = 0; row < mtr.rows; row++){
        mtr.matrix_body[row].resize(mtr.columns);
    }

    std::cout << "Input matrix by rows" << std::endl;
    for(int h = 0; h < mtr.rows; h++){
        for(int w = 0; w < mtr.columns; w++){
            // std::cout << "norm";
            std::cin >> mtr.matrix_body[h][w];
        }
    }

    std::cout << std::endl;
    matrix_out(mtr);

    std::cout << std::endl << "Converting to triangle form" << std::endl << std::endl;
    gauss_algo_first_part(mtr);
    std::cout << std::endl << "Converting to diagonal form" << std::endl;
    gauss_fin(mtr);
    std::cout << "Done" << std::endl;
    // matrix_out(mtr);
}