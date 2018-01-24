#include <iostream>
#include <cmath>

using namespace std;

/*int rows =  sizeof matrix / sizeof matrix[0]; // 2 rows

int cols = sizeof matrix[0] / sizeof(int); // 5 cols*/

void swap_rows(double ** matrix, int rows, int col, int swap1, int swap2){
   int temp;
    for (int i = 0; i < col; ++i) {
        temp = matrix[swap1][i];
        matrix[swap1][i] = matrix[swap2][i];
        matrix[swap2][i] = temp;
    }
}

double multiply_row(double** matrix, int row_to_scale, int col, double factor){
    return  matrix[row_to_scale][col] * factor;

}
void add_rows(double** matrix, int rows, int col, int add1, int add2){
    double factor;
    int col_to_zero=0;
    for (int i = 0; i < col ; ++i) {
        if (matrix[add1][i] != 0 && matrix[add2][i] != 0 ){
            col_to_zero = i;
            i = col;
        }
    }
    factor = isnan(matrix[add2][col_to_zero]/matrix[add1][col_to_zero]) ? 0 : matrix[add2][col_to_zero]/matrix[add1][col_to_zero] ;

    for (int j = 0; j <col ; ++j) {
        matrix[add2][j] = matrix[add2][j] - multiply_row(matrix,add1,j,factor);
    }
}
void print_matrix(double** matrix, int row, int col){
    for (int i = 0; i <row ; ++i) {
        cout<< "[ ";
        for (int j = 0; j < col; ++j) {
            cout<< matrix[i][j]<<" ";
        }
        cout<< "] "<<endl;
    }
}
void row_echleon(double** matrix, int row, int col){
    int error=0;
    for (int i = 0; i < row-1 ; ++i) {
        for (int j = 0; j < col ; ++j) {
            if (matrix[i][j] == 0){
                error++;
            }
        }
        if (error == 4){
            swap_rows(matrix,row,col,i,i+1);
            i--;
        }
        error = 0;
    }
    for (int j = 0; j < row-1 ; ++j) {
        for (int i = j+1; i < row ; ++i) {
            add_rows(matrix, row, col, j, i);
        }
    }
}
void reduce_matrix(double** matrix, int row, int col){
    double variable[row];
    for (int i = row-1; i > -1 ; --i) {
        for (int j = i -1; j > -1 ; --j){
            add_rows(matrix, row, col, j, i);
        }
    }
}
int main() {
    cout << "Hello, World!" << endl;
    int col = 4;
    int row = 3;
    double **matrix;
    double list[row][col] = {{8,1,2,3},{0,2,2,3},{1,2,5,3}};

    matrix = static_cast<double **>(malloc(row * sizeof * matrix));
    for (int i = 0; i < row; ++i) {
        matrix[i] = static_cast<double *>(malloc(col * sizeof * matrix[i]));
    }
    for (int i = 0; i <row ; ++i) {
        for (int j = 0; j < col; ++j) {
            matrix[i][j] = list[i][j];
        }
    }
    cout<< **matrix << endl;
    cout<< *matrix << endl;
    cout<< matrix << endl;
    cout<< list << endl;

    print_matrix(matrix, row, col);
    cout<< endl;
    cout<< endl;
    row_echleon(matrix,row,col);
    print_matrix(matrix, row, col);


    return 0;
}