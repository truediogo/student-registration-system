#ifndef STUDENT_H
#define STUDENT_H

#include <stdbool.h>

typedef struct {
    int id;
    char full_name[100];
    char cpf[12];
    char course[100];
    int registration_year;
    double grades[10];
    bool grades_provided;
} Student;

#endif //STUDENT_H
