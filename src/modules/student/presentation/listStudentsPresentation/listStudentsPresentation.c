#include "listStudentsPresentation.h"

#include "infra/gtk/gtk.h"
#include "infra/storage/storage.h"
#include "modules/student/studentsModule.h"
#include "modules/student/useCases/updateStudentList/updateStudentList.h"
#include "modules/student/presentation/createStudentPresentation/createStudentPresentation.h"
#include "modules/student/presentation/updateStudentPresentation/updateStudentPresentation.h"
#include "modules/student/presentation/removeStudentPresentation/removeStudentPresentation.h"
#include "shared/updateStudentId.h"
#include "modules/student/presentation/viewStudentPresentation/viewStudentPresentation.h"
#include "modules/student/presentation/findStudentPresentation/findStudentPresentation.h"

GtkWidget *window;

int is_file_empty() {
    FILE *file = getStorage();

    int ch = getc(file);
    fclose(file);

    return ch == EOF;
}

void on_selection_changed(GtkTreeSelection *selection, gpointer data) {
    GtkWidget **buttons = (GtkWidget **)data;
    GtkTreeIter iter;
    GtkTreeModel *model;

    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        gtk_widget_set_sensitive(buttons[0], TRUE);
        gtk_widget_set_sensitive(buttons[1], TRUE);
        gtk_widget_set_sensitive(buttons[2], TRUE);
    } else {
        gtk_widget_set_sensitive(buttons[0], FALSE);
        gtk_widget_set_sensitive(buttons[1], FALSE);
        gtk_widget_set_sensitive(buttons[2], FALSE);
    }
}


void get_selected_student(Student *student) {
    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));

    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        gchar *grades;
        gchar *full_name;
        gchar *cpf;
        gchar *course;
        gint id;
        gint registration_year;
        gtk_tree_model_get(model, &iter, 0, &id, 1, &full_name, 2, &cpf, 3, &course, 4, &registration_year, 5, &grades, -1);

        updateStudentId = id;

        student->id = id;
        strncpy(student->full_name, full_name, sizeof(student->full_name) - 1);
        student->full_name[sizeof(student->full_name) - 1] = '\0';
        strncpy(student->cpf, cpf, sizeof(student->cpf) - 1);
        student->cpf[sizeof(student->cpf) - 1] = '\0';
        strncpy(student->course, course, sizeof(student->course) - 1);
        student->course[sizeof(student->course) - 1] = '\0';
        student->registration_year = registration_year;

        g_free(full_name);
        g_free(cpf);
        g_free(course);

        g_strchomp(grades);

        gchar **grades_tokens = g_strsplit(grades, " ", -1);
        int i = 0;
        while (grades_tokens[i] != NULL && i < 10) {
            student->grades[i] = g_ascii_strtod(grades_tokens[i], NULL);
            i++;
        }

        while (i < 10) {
            student->grades[i++] = -1.0;
        }

        g_strfreev(grades_tokens);
        g_free(grades);
    }
}

void on_row_activated(GtkTreeView *tree_view, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data) {
    GtkTreeModel *model = gtk_tree_view_get_model(tree_view);
    GtkTreeIter iter;

    if (gtk_tree_model_get_iter(model, &iter, path)) {
        Student *student = malloc(sizeof(Student));
        get_selected_student(student);

        viewStudentPresentation(student);

        free(student);
    }
}


void on_update_button_clicked(GtkWidget *widget, gpointer data) {
    Student *selected_student = malloc(sizeof(Student));
    GtkWidget **buttons = (GtkWidget **)g_object_get_data(G_OBJECT(widget), "buttons");

    get_selected_student(selected_student);

    updateStudentPresentation(selected_student, buttons);

    free(selected_student);
}



void listStudentsPresentation() {
    GtkWidget *scrolled_window;
    GtkWidget *button_box;
    GtkWidget *new_student_button;
    GtkWidget *update_student_button;
    GtkWidget *remove_student_button;
    GtkWidget *find_student_button;
    GtkWidget *exit_button;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Sistema de registro de estudantes");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 370, 480);

    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scrolled_window), list);

    button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_button_box_set_layout(GTK_BUTTON_BOX(button_box), GTK_BUTTONBOX_SPREAD);
    gtk_container_set_border_width(GTK_CONTAINER(button_box), 10);

    new_student_button = gtk_button_new_with_label("Novo estudante");
    update_student_button = gtk_button_new_with_label("Atualizar estudante");
    remove_student_button = gtk_button_new_with_label("Remover estudante");
    find_student_button = gtk_button_new_with_label("Buscar estudante");
    exit_button = gtk_button_new_with_label("Sair");

    gtk_container_add(GTK_CONTAINER(button_box), new_student_button);
    gtk_container_add(GTK_CONTAINER(button_box), update_student_button);
    gtk_container_add(GTK_CONTAINER(button_box), remove_student_button);
    gtk_container_add(GTK_CONTAINER(button_box), find_student_button);
    gtk_container_add(GTK_CONTAINER(button_box), exit_button);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), button_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_widget_set_size_request(GTK_WIDGET(scrolled_window), 900, -1);

    updateStudentList();

    GtkTreeViewColumn *column;
    GtkCellRenderer *renderer;

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Nome completo", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("CPF", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Curso", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Ano", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Notas", renderer, "text", 5, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

    gtk_widget_show_all(window);

    gtk_window_present(GTK_WINDOW(window));
    gtk_window_set_focus_on_map(GTK_WINDOW(window), TRUE);


    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));

    GtkWidget **buttons = malloc(3 * sizeof(GtkWidget *));
    buttons[0] = update_student_button;
    buttons[1] = remove_student_button;
    buttons[2] = find_student_button;

    g_signal_connect(selection, "changed", G_CALLBACK(on_selection_changed), buttons);

    on_selection_changed(selection, buttons);

    if (is_file_empty()) {
        gtk_widget_set_sensitive(update_student_button, FALSE);
        gtk_widget_set_sensitive(remove_student_button, FALSE);
        gtk_widget_set_sensitive(find_student_button, FALSE);
    }

    g_signal_connect(new_student_button, "clicked", G_CALLBACK(createStudentPresentation), buttons);
    g_signal_connect(update_student_button, "clicked", G_CALLBACK(on_update_button_clicked), buttons);
    g_signal_connect(remove_student_button, "clicked", G_CALLBACK(removeStudentPresentation), list);
    g_signal_connect(find_student_button, "clicked", G_CALLBACK(findUserByCpfPresentation), list);
    g_signal_connect(exit_button, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(list, "row-activated", G_CALLBACK(on_row_activated), NULL);



    g_object_set_data(G_OBJECT(update_student_button), "list", list);
}
