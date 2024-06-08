#include "app.h"

#include <libgen.h>
#include <string.h>

#include "infra/gtk/gtk.h"

#include "modules/student/studentsModule.h"
#include "shared/updateStudentId.h"
#include "infra/storage/storage.h"
#include "shared/studentsFilePath.h"

void startApp(char *argv[]) {
    char *exe_dir = dirname(argv[0]);

    size_t new_path_length = strlen(exe_dir) + strlen("/new_students.txt") + 1;
    new_students_file_path = malloc(new_path_length);
    if (new_students_file_path == NULL) {
        printf("Erro ao inicar aplicação\n");
        exit(1);
    }

    strcpy(new_students_file_path, exe_dir);
    strcat(new_students_file_path, "/new_students.txt");

    size_t path_length = strlen(exe_dir) + strlen("/students.txt") + 1;
    students_file_path = malloc(path_length);
    if (students_file_path == NULL) {
        printf("Erro ao inicar aplicação\n");
        exit(1);
    }

    strcpy(students_file_path, exe_dir);
    strcat(students_file_path, "/students.txt");

    printf("%s", students_file_path);

    FILE *file = fopen(students_file_path, "r");

    if (file == NULL) {
        file = fopen(students_file_path, "w");
        if (file == NULL) {
            printf("Erro: não foi possivel criar o arquivo students.txt\n");

            exit(1);
        }
    }

    fclose(file);

    updateStudentId = 0;
    list = gtk_tree_view_new();

    listStudentsPresentation();
}
