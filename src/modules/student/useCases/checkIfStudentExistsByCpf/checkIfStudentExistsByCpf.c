#include<string.h>
#include<stdlib.h>

#include "checkIfStudentExistsByCpf.h"

#include "infra/storage/storage.h"

int checkIfStudentExistsByCpf(const char *cpf, int excludeId) {
    printf("%d", excludeId);

    FILE *file = getStorage();

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        int id = atoi(token);
        token = strtok(NULL, ",");
        token = strtok(NULL, ",");
        if (token != NULL && strcmp(token, cpf) == 0 && (excludeId == -1 || id != excludeId)) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);

    return 0;
}
