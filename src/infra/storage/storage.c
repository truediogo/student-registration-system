#include "stdlib.h"

#include "storage.h"
#include "shared/studentsFilePath.h"

FILE* getStorage() {
    FILE *file = fopen(students_file_path, "r");
    if (file == NULL) {
        printf("ERRO: Não foi possível carregar as informações do sistema!\n\n");

        printf("Encerrando programa...\n");
        exit(1);
    }

    return file;
}

FILE* writeStorage() {
    FILE *file = fopen(students_file_path, "w");
    if (file == NULL) {
        printf("ERRO: Não foi possível gravar as informações do sistema!\n\n");

        printf("Encerrando programa...\n");
        exit(1);
    }

    return file;
}

FILE* writeStorageOnEnd() {
    FILE *file = fopen(students_file_path, "a");
    if (file == NULL) {
        printf("ERRO: Não foi possível gravar as informações do sistema!\n\n");

        printf("Encerrando programa...\n");
        exit(1);
    }

    return file;
}