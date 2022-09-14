#include <iostream>
#include "func.h"

int main() {
    Matrix matrix;
    get_matrix_data(&matrix);
    matrix.string = nullptr;
    for (int i = 0; i < matrix.amount; i++){
        while (true) {
            Point point = get_point(&matrix);
            int number = get_number();
            if (in_matrix(&matrix, point)){
                std::cout << "That point is already in the matrix, try again.\n";
                continue;
            }
            add_node(get_string(&matrix, point.i), point.j, number);
            break;
        }
    }
    print_matrix(&matrix);
    int *vector = create_vector(&matrix, 2);
    std::cout << "vector: ";
    for (int i = 0; i < string_amount(&matrix); i++) std::cout << vector[i] << " ";
    std::cout << std::endl;
    memory_free(&matrix);
    delete [] vector;
    return 0;
}