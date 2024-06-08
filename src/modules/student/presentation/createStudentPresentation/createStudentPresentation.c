#include <math.h>

#include "infra/gtk/gtk.h"
#include "infra/storage/storage.h"
#include "modules/student/entities/student.h"
#include "modules/student/useCases/updateStudentList/updateStudentList.h"
#include "modules/student/useCases/createStudent/createStudent.h"
#include "modules/student/useCases/checkIfStudentExistsByCpf/checkIfStudentExistsByCpf.h"

#define MAX_GRADES 10

void on_create_clicked(GtkWidget *widget, gpointer data) {
    Student student;
    GtkWidget **entries = (GtkWidget **)data;

    const gchar *full_name = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const gchar *cpf = gtk_entry_get_text(GTK_ENTRY(entries[1]));
    const gchar *course = gtk_entry_get_text(GTK_ENTRY(entries[2]));
    const gchar *year = gtk_entry_get_text(GTK_ENTRY(entries[3]));
    const gchar *grades_str = gtk_entry_get_text(GTK_ENTRY(entries[4]));

    if (strlen(full_name) < 4 || !g_regex_match_simple("^[a-zA-Z ]*$", full_name, 0, 0)) {
        show_validation_alert(gtk_widget_get_toplevel(widget),"Nome completo inválido. Deve ter pelo menos 4 caracteres e conter apenas letras de a-z.");
        return;
    }

    if (strlen(cpf) != 11 || !g_regex_match_simple("^[0-9]*$", cpf, 0, 0)) {
        show_validation_alert(gtk_widget_get_toplevel(widget),"CPF inválido. Deve ter exatamente 11 números.");
        return;
    }

    if (strlen(course) < 3 || !g_regex_match_simple("^[a-zA-Z ]*$", course, 0, 0)) {
        show_validation_alert(gtk_widget_get_toplevel(widget),"Curso inválido. Deve ter pelo menos 3 caracteres e conter apenas letras de a-z.");
        return;
    }

    if (strlen(year) != 4 || !g_regex_match_simple("^[0-9]*$", year, 0, 0)) {
        show_validation_alert(gtk_widget_get_toplevel(widget),"Ano inválido. Deve ter exatamente 4 números.");
        return;
    }

    if (!g_regex_match_simple("^([0-9]*[,]?[0-9]+ )*[0-9]*[,]?[0-9]*$", grades_str, 0, 0)) {
        show_validation_alert(gtk_widget_get_toplevel(widget),"Notas inválidas. Deve conter apenas números, vírgulas para decimais e espaços para separar as notas.");
        return;
    }

    if (checkIfStudentExistsByCpf(cpf, -1)) {
        show_validation_alert(gtk_widget_get_toplevel(widget), "Um estudante com este CPF já existe.");
        return;
    }

    strncpy(student.full_name, gtk_entry_get_text(GTK_ENTRY(entries[0])), sizeof(student.full_name));
    strncpy(student.cpf, gtk_entry_get_text(GTK_ENTRY(entries[1])), sizeof(student.cpf));
    strncpy(student.course, gtk_entry_get_text(GTK_ENTRY(entries[2])), sizeof(student.course));
    student.registration_year = atoi(gtk_entry_get_text(GTK_ENTRY(entries[3])));

    if (grades_str != NULL && strlen(grades_str) > 0) {
        gchar **grades_tokens = g_strsplit(grades_str, " ", -1);
        int i = 0, j = 0;
        while (grades_tokens[i] != NULL) {
            char *endptr;
            double grade = strtod(grades_tokens[i], &endptr);

            if (*endptr == '\0' && (grade * 100) == floor(grade * 100)) {
                student.grades[j++] = grade;
            }
            i++;
        }
        while (j < MAX_GRADES) {
            student.grades[j++] = -1.0;
        }
        g_strfreev(grades_tokens);
    } else {
        for (int i = 0; i < MAX_GRADES; i++) {
            student.grades[i] = -1.0;
        }
    }

    createStudent(&student);

    updateStudentList();

    GtkWidget **buttons = (GtkWidget **)g_object_get_data(G_OBJECT(widget), "buttons");
    gtk_widget_set_sensitive(buttons[0], TRUE);
    gtk_widget_set_sensitive(buttons[1], TRUE);
    gtk_widget_set_sensitive(buttons[2], TRUE);

    GtkWidget *createUserWindow = gtk_widget_get_toplevel(widget);
    if (gtk_widget_is_toplevel(createUserWindow)) {
        gtk_widget_destroy(createUserWindow);
    }
}

void createStudentPresentation(GtkWidget *widget, gpointer data) {
    GtkWidget *createStudentWindow;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *entry;

    gtk_init(NULL, NULL);

    createStudentWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(createStudentWindow), "Criar Estudante");
    gtk_window_set_position(GTK_WINDOW(createStudentWindow), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(createStudentWindow), 10);

    gtk_window_set_modal(GTK_WINDOW(createStudentWindow), TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(createStudentWindow), GTK_WINDOW(window));

    grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_START);
    gtk_widget_set_valign(grid, GTK_ALIGN_START);
    gtk_container_add(GTK_CONTAINER(createStudentWindow), grid);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 20);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);

    const char *labels[] = {"Nome completo", "CPF", "Curso", "Ano da matrícula", "Notas"};
    const char *tips[] = {"Apenas letras de a-z", "Apenas números sem pontos ou traços", "Apenas letras de a-z", "Apenas números, 4 caracteres", "Apenas números ou ponto para delimitar decimais, valores devem ser separados por espaço"};
    GtkWidget *entries[5];
    int max_lengths[] = {100, 11, 100, 4, 100};

    for (int i = 0; i < 5; i++) {
        GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        gtk_widget_set_hexpand(vbox, TRUE);
        gtk_widget_set_halign(vbox, GTK_ALIGN_START);
        gtk_grid_attach(GTK_GRID(grid), vbox, 0, i, 1, 1);

        label = gtk_label_new(labels[i]);
        gtk_label_set_xalign(GTK_LABEL(label), 0);
        gtk_widget_set_name(label, "label");
        gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

        entry = gtk_entry_new();
        gtk_entry_set_max_length(GTK_ENTRY(entry), max_lengths[i]);
        gtk_widget_set_name(entry, "entry");
        gtk_widget_set_hexpand(entry, TRUE);
        gtk_widget_set_size_request(entry, 600, -1);
        gtk_box_pack_start(GTK_BOX(vbox), entry, TRUE, TRUE, 0);
        entries[i] = entry;

        GtkWidget *tip = gtk_label_new(tips[i]);
        gtk_label_set_xalign(GTK_LABEL(tip), 0);
        gtk_widget_set_name(tip, "tip");
        gtk_box_pack_start(GTK_BOX(vbox), tip, FALSE, FALSE, 0);
    }

    GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_widget_set_hexpand(button_box, TRUE);
    gtk_grid_attach(GTK_GRID(grid), button_box, 0, 5, 2, 1);

    GtkWidget *cancelButton = gtk_button_new_with_label("Cancelar");
    gtk_widget_set_size_request(cancelButton, 150, 50);
    gtk_widget_set_name(cancelButton, "cancelButton");
    g_signal_connect_swapped(cancelButton, "clicked", G_CALLBACK(gtk_widget_destroy), createStudentWindow);
    gtk_box_pack_start(GTK_BOX(button_box), cancelButton, TRUE, TRUE, 0);

    GtkWidget *saveButton = gtk_button_new_with_label("Salvar");
    gtk_widget_set_size_request(saveButton, 150, 50);
    gtk_widget_set_name(saveButton, "saveButton");
    g_object_set_data(G_OBJECT(saveButton), "buttons", data);
    g_signal_connect(saveButton, "clicked", G_CALLBACK(on_create_clicked), entries);
    gtk_box_pack_start(GTK_BOX(button_box), saveButton, TRUE, TRUE, 0);

    g_signal_connect(createStudentWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(createStudentWindow);

    gtk_main();
}
