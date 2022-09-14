#ifndef LAB1_CPP_FUNC_H
#define LAB1_CPP_FUNC_H

typedef struct Node {
    int number, j;
    Node *next_column;
} Node;

typedef struct String {
    int i;
    Node *column;
    String *next_string;
} String;

typedef struct Matrix {
    int n, m, amount;
    String *string;
} Matrix;

typedef struct Point {
    int i, j;
} Point;

int get_int(char message[]);
int get_matrix_data(Matrix *matrix);
Point get_point(Matrix *matrix);
int get_number();
int in_matrix(Matrix *matrix, Point point);
String *get_string(Matrix *matrix, int i);
void add_node(String *string, int j, int number);
void print_matrix(Matrix *matrix);
int string_amount(Matrix *matrix);
int criteria_1(int number);
bool criteria_2(int number);
int *create_vector(Matrix *matrix, int criterion);
void memory_free(Matrix *matrix);

#endif