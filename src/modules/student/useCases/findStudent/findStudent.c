#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#include "../../entities/student.h"
#include "infra/storage/storage.h"

Student* findStudent(const char* cpf) {
    FILE *file = getStorage();

    if (file != NULL) {
        Student *temp = malloc(sizeof(Student));
        double grades[10];
        int result;

        while ((result = fscanf(file, "%d,%[^,],%[^,],%[^,],%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n", &temp->id, temp->full_name, temp->cpf, temp->course, &temp->registration_year, &grades[0], &grades[1], &grades[2], &grades[3], &grades[4], &grades[5], &grades[6], &grades[7], &grades[8], &grades[9])) != EOF) {
            if (result == 15 && strcmp(temp->cpf, cpf) == 0) {
                fclose(file);
                return temp;
            }
        }

        free(temp);
        fclose(file);
    }

    return NULL;
}

