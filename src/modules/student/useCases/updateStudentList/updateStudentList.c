#include "infra/gtk/gtk.h"
#include "infra/storage/storage.h"

#include "modules/student/studentsModule.h"

void updateStudentList() {
    FILE *file = getStorage();

    GtkListStore *store;
    GtkTreeIter iter;

    store = gtk_list_store_new(7, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING, G_TYPE_BOOLEAN);

    Student student;
    while (fscanf(file, "%d,%[^,],%[^,],%[^,],%d,", &student.id, student.full_name, student.cpf, student.course, &student.registration_year) == 5) {
        char grades[100] = "";
        for(int i = 0; i < 10; i++) {
            if(fscanf(file, "%lf,", &student.grades[i]) == 1) {
                if (student.grades[i] != -1.0) {
                    char grade[10];
                    sprintf(grade, "%.2f ", student.grades[i]);
                    strcat(grades, grade);
                }
            } else {
                student.grades_provided = false;
                break;
            }
        }

        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, 0, student.id, 1, student.full_name, 2, student.cpf, 3, student.course, 4, student.registration_year, 5, grades, 6, student.grades_provided, -1);
    }

    fclose(file);

    gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));
    g_object_unref(store);
}
