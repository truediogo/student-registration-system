#include <stdio.h>
#include <string.h>

#include "createStudent.h"

#include "infra/storage/storage.h"
#include "modules/student/entities/student.h"

#define MAX_GRADES 10

int getLastId() {
    int lastId = 0;

    FILE *file = getStorage();

    if (file != NULL) {
        Student temp;
        double grades[MAX_GRADES];
        int result;

        while ((result = fscanf(file, "%d,%[^,],%[^,],%[^,],%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n", &temp.id, temp.full_name, temp.cpf, temp.course, &temp.registration_year, &grades[0], &grades[1], &grades[2], &grades[3], &grades[4], &grades[5], &grades[6], &grades[7], &grades[8], &grades[9])) != EOF) {
            if (result == 15) {
                lastId = temp.id;
            }
        }

        fclose(file);
    }

    return lastId;
}


void createStudent(Student *student) {
    student->id = getLastId() + 1;

    FILE *file = writeStorageOnEnd();

    fprintf(file, "%d,", student->id);
    fprintf(file, "%s,", student->full_name);
    fprintf(file, "%s,", student->cpf);
    fprintf(file, "%s,", student->course);
    fprintf(file, "%d", student->registration_year);

    for (int i = 0; i < MAX_GRADES; i++) {
        fprintf(file, ",%.2lf", student->grades[i]);
    }

    fprintf(file, "\n");

    fclose(file);
}
