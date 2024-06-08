#include "viewStudentPresentation.h"

#include "infra/gtk/gtk.h"
#include "modules/student/entities/student.h"

void viewStudentPresentation(Student *student) {
    GtkWidget *viewStudentWindow;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *close_button;

    viewStudentWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(viewStudentWindow), "Visualizar estudante");
    gtk_window_set_position(GTK_WINDOW(viewStudentWindow), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(viewStudentWindow), 10);

    gtk_window_set_modal(GTK_WINDOW(viewStudentWindow), TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(viewStudentWindow), GTK_WINDOW(window));

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_container_add(GTK_CONTAINER(viewStudentWindow), grid);

    char buffer[256];

    sprintf(buffer, "ID: %d", student->id);
    label = gtk_label_new(buffer);
    gtk_label_set_xalign(GTK_LABEL(label), 0);
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);

    sprintf(buffer, "Nome completo: %s", student->full_name);
    label = gtk_label_new(buffer);
    gtk_label_set_xalign(GTK_LABEL(label), 0);
    gtk_grid_attach(GTK_GRID(grid), label, 0, 1, 1, 1);

    sprintf(buffer, "CPF: %s", student->cpf);
    label = gtk_label_new(buffer);
    gtk_label_set_xalign(GTK_LABEL(label), 0);
    gtk_grid_attach(GTK_GRID(grid), label, 0, 2, 1, 1);

    sprintf(buffer, "Curso: %s", student->course);
    label = gtk_label_new(buffer);
    gtk_label_set_xalign(GTK_LABEL(label), 0);
    gtk_grid_attach(GTK_GRID(grid), label, 0, 3, 1, 1);

    sprintf(buffer, "Ano da matrícula: %d", student->registration_year);
    label = gtk_label_new(buffer);
    gtk_label_set_xalign(GTK_LABEL(label), 0);
    gtk_grid_attach(GTK_GRID(grid), label, 0, 4, 1, 1);

    GString *grades_str = g_string_new("Notas: ");
    for (int i = 0; i < 10; i++) {
        if (student->grades[i] != -1.0) {
            gchar *grade_str = g_strdup_printf("%.2f ", student->grades[i]);
            g_string_append(grades_str, grade_str);
            g_free(grade_str);
        }
    }

    label = gtk_label_new(grades_str->str);
    printf("Grades label: %s\n", gtk_label_get_text(GTK_LABEL(label)));
    gtk_label_set_xalign(GTK_LABEL(label), 0);
    gtk_grid_attach(GTK_GRID(grid), label, 0, 5, 1, 1);

    close_button = gtk_button_new_with_label("Close");
    g_signal_connect_swapped(close_button, "clicked", G_CALLBACK(gtk_widget_destroy), viewStudentWindow);
    gtk_grid_attach(GTK_GRID(grid), close_button, 0, 11, 1, 1);

    gtk_widget_show_all(viewStudentWindow);

}
