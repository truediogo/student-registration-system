#include<stdio.h>

#include "removeStudent.h"

#include "infra/gtk/gtk.h"
#include "infra/storage/storage.h"
#include "modules/student/studentsModule.h"

int removeStudent(int id) {
    FILE *file = getStorage();

    Student students[100];
    int numStudents = 0;
    while (fscanf(file, "%d,%[^,],%[^,],%[^,],%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
                  &students[numStudents].id, students[numStudents].full_name, students[numStudents].cpf, students[numStudents].course,
                  &students[numStudents].registration_year, &students[numStudents].grades[0], &students[numStudents].grades[1],
                  &students[numStudents].grades[2], &students[numStudents].grades[3], &students[numStudents].grades[4],
                  &students[numStudents].grades[5], &students[numStudents].grades[6], &students[numStudents].grades[7],
                  &students[numStudents].grades[8], &students[numStudents].grades[9]) != EOF) {
        numStudents++;
    }
    fclose(file);

    int index = -1;
    for (int i = 0; i < numStudents; i++) {
        if (students[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        return 2;
    }

    for (int i = index; i < numStudents - 1; i++) {
        students[i] = students[i + 1];
    }
    numStudents--;

    file = writeStorage();

    for (int i = 0; i < numStudents; i++) {
        fprintf(file, "%d,%s,%s,%s,%d,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf\n",
                students[i].id, students[i].full_name, students[i].cpf, students[i].course, students[i].registration_year,
                students[i].grades[0], students[i].grades[1], students[i].grades[2], students[i].grades[3], students[i].grades[4],
                students[i].grades[5], students[i].grades[6], students[i].grades[7], students[i].grades[8], students[i].grades[9]);
    }

    fclose(file);

    return 0;
}
