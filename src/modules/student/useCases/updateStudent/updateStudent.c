#include<stdio.h>
#include<string.h>

#include "../../entities/student.h"

#include "updateStudent.h"
#include "infra/storage/storage.h"
#include "shared/updateStudentId.h"
#include "shared/studentsFilePath.h"

void updateStudent(Student *student) {
    FILE *newFile = fopen(new_students_file_path, "w");
    if (newFile == NULL) {
        perror("Erro ao atualizar estudante (1)");
        return;
    }

    FILE *file = fopen(students_file_path, "r");
    if (file == NULL) {
        perror("Erro ao atualizar estudante (2)");
        return;
    }

    Student temp;
    double grades[10];
    int result;

    while ((result = fscanf(file, "%d,%[^,],%[^,],%[^,],%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n", &temp.id, temp.full_name, temp.cpf, temp.course, &temp.registration_year, &grades[0], &grades[1], &grades[2], &grades[3], &grades[4], &grades[5], &grades[6], &grades[7], &grades[8], &grades[9])) != EOF) {

        if (result == 15) {
            if (temp.id == updateStudentId) {
                fprintf(newFile, "%d,%s,%s,%s,%d", updateStudentId, student->full_name, student->cpf, student->course, student->registration_year);

                for (int i = 0; i < 10; i++) {
                    fprintf(newFile, ",%.2lf", student->grades[i]);
                }
                fprintf(newFile, "\n");
            } else {
                fprintf(newFile, "%d,%s,%s,%s,%d", temp.id, temp.full_name, temp.cpf, temp.course, temp.registration_year);
                for (int i = 0; i < 10; i++) {
                    fprintf(newFile, ",%.2lf", grades[i]);
                }
                fprintf(newFile, "\n");
            }
        }
    }

    if (fclose(file) != 0) {
        perror("Erro ao finalizar atualização do estudante (1)");
    }

    if (fclose(newFile) != 0) {
        perror("Erro ao finalizar atualização do estudante (2)");
    }

    if (remove(students_file_path) != 0) {
        perror("Erro ao finalizar atualização do estudante (3)");
    }

    if (rename(new_students_file_path, students_file_path) != 0) {
        perror("Erro ao finalizar atualização do estudante (4)");
    }
}
