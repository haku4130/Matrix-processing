#include <iostream>
#include "func.h"

int get_int(char message[]){
    int n;
    std::cout << message;
    while (!(std::cin >> n).good()){
        std::cout << "Inputted number is incorrect, please try again.\n";
        std::cin.clear();
        std::cin.ignore(100,'\n');
    }
    std::cin.clear();
    std::cin.ignore(100,'\n');
    return n;
}

int get_matrix_data(Matrix *matrix){
    while (true) {
        char message[] = "Enter the number of lines: ";
        matrix->n = get_int(message);
        if (matrix->n <= 0) std::cout << "The number of lines cannot be a negative number or zero, try again.\n";
        else break;
    }
    while (true) {
        char message[] = "Enter the number of columns: ";
        matrix->m = get_int(message);
        if (matrix->m <= 0) std::cout << "The number of columns cannot be a negative number or zero, try again.\n";
        else break;
    }
    while (true) {
        char message[] = "Enter the amount of elements: ";
        matrix->amount = get_int(message);
        if (matrix->amount > matrix->n * matrix->m) std::cout << "Too many elements to add, please try again.\n";
        else if (matrix->amount <= 0) std::cout << "The amount of elements cannot be a negative number or zero, try again.\n";
        else break;
    }
    return 0;
}

Point get_point(Matrix *matrix){
    Point point;
    while (true) {
        char message[] = "Enter the line: ";
        point.i = get_int(message);
        if (point.i < 0) std::cout << "The line number cannot be a negative number, try again.\n";
        else if (point.i >= matrix->n) std::cout << "That point cannot be in the matrix, try again.\n";
        else break;
    }
    while (true) {
        char message[] = "Enter the column: ";
        point.j = get_int(message);
        if (point.j < 0) std::cout << "The column number cannot be a negative number, try again.\n";
        else if (point.j >= matrix->m) std::cout << "That point cannot be in the matrix, try again.\n";
        else break;
    }
    return point;
}

int get_number() {
    int number;
    while (true) {
        char message[] = "Enter the number: ";
        number = get_int(message);
        if (number == 0) std::cout << "Zero elements are not stored in the matrix, please try again.\n";
        else break;
    }
    return number;
}

int in_matrix(Matrix *matrix, Point point) {
    String *string = matrix->string;
    while (string) {
        if (string->i == point.i) {
            Node *node = string->column;
            while (node) {
                if (node->j == point.j) return 1;
                node = node->next_column;
            }
        }
        string = string->next_string;
    }
    return 0;
}

String *get_string(Matrix *matrix, int i) {
    String *string = matrix->string;
    String *ptr;
    ptr = new String;
    ptr->column = nullptr;
    ptr->next_string = nullptr;
    ptr->i = i;
    if (!string) {
        matrix->string = ptr;
        return matrix->string;
    }
    if (string->i > i) {
        ptr->next_string = matrix->string;
        matrix->string = ptr;
        return ptr;
    }
    while (string->next_string) {
        if (string->next_string->i == i){
            delete ptr;
            return string->next_string;
        }
        if (string->next_string->i > i) {
            ptr->next_string = string->next_string;
            string->next_string = ptr;
            return ptr;
        }
        string = string->next_string;
    }
    string->next_string = ptr;
    return string->next_string;
}

void add_node(String *string, int j, int number) {
    Node *node = new Node;
    node->next_column = nullptr;
    node->j = j;
    node->number = number;
    if (!string->column) {
        string->column = node;
        return;
    }
    if (string->column->j > j) {
        node->next_column = string->column;
        string->column = node;
        return;
    }
    Node *ptr = string->column;
    while (ptr->next_column) {
        if (ptr->next_column->j > j) {
            node->next_column = ptr->next_column;
            ptr->next_column = node;
            return;
        }
        ptr = ptr->next_column;
    }
    ptr->next_column = node;
}

void print_matrix(Matrix *matrix) {
    String *string = matrix->string;
    while (string) {
        Node *node = string->column;
        while (node) {
            std::cout << "(" << string->i << ";" << node->j << ") = " << node->number << std::endl;
            node = node->next_column;
        }
        string = string->next_string;
    }
}

int string_amount(Matrix *matrix) {
    int res = 0;
    String *string = matrix->string;
    while (string) {
        res++;
        string = string->next_string;
    }
    return res;
}

int criteria_1(int number) {
    int res = 1;
    while ((number /= 10) > 0) res++;
    return res;
}

bool criteria_2(int number) {
    int k = 2;
    while (k * k <= number && number % k != 0) k++;
    return k * k > number;
}

int *create_vector(Matrix *matrix, int criterion) {
    int *vector, i = 0;
    vector = new int[string_amount(matrix)];
    for (int j = 0; j < string_amount(matrix); j++) vector[j] = 0;
    String *string = matrix->string;
    while (string) {
        Node *node = string->column;
        while (node) {
            if (criterion == 1) if (criteria_1(node->number) >= 2) vector[i] += node->number;
            if (criterion == 2) if (criteria_2(node->number)) vector[i] += node->number;
            node = node->next_column;
        }
        i++;
        string = string->next_string;
    }
    return vector;
}

void memory_free(Matrix *matrix) {
    String *string = matrix->string, *string_next = string;
    while (string) {
        string_next = string->next_string;
        Node *node = string->column, *node_next = node;
        while (node) {
            node_next = node->next_column;
            delete node;
            node = node_next;
        }
        delete string;
        string = string_next;
    }
}