#include "findStudentPresentation.h"

#include "infra/gtk/gtk.h"
#include "modules/student/entities/student.h"
#include "modules/student/presentation/viewStudentPresentation/viewStudentPresentation.h"
#include "modules/student/useCases/findStudent/findStudent.h"

void on_cpf_entry_changed(GtkEditable *editable, gpointer user_data) {
    const gchar *cpf = gtk_entry_get_text(GTK_ENTRY(editable));
    GtkWidget *ok_button = GTK_WIDGET(user_data);

    if (strlen(cpf) == 11) {
        gtk_widget_set_sensitive(ok_button, TRUE);
    } else {
        gtk_widget_set_sensitive(ok_button, FALSE);
    }
}

void on_ok_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *cpf_entry = GTK_WIDGET(user_data);
    GtkWidget *window = gtk_widget_get_toplevel(cpf_entry);

    gchar *cpf = g_strdup(gtk_entry_get_text(GTK_ENTRY(cpf_entry)));

    if (cpf != NULL) {
        if (strlen(cpf) != 11 || !g_regex_match_simple("^[0-9]*$", cpf, 0, 0)) {
           show_validation_alert(gtk_widget_get_toplevel(window),"CPF inválido. Deve ter exatamente 11 números.");
            return;
        }

        Student *student = findStudent(cpf);

        if (student != NULL) {
            viewStudentPresentation(student);
            free(student);
        } else {
            show_alert(window, "Nenhum aluno encontrado com o CPF informado.");
        }

        g_free(cpf);
    }
}

void findUserByCpfPresentation() {
    GtkWidget *findStudentWindow, *label, *box, *button_box, *cpf_entry, *ok_button, *cancel_button;

    findStudentWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(findStudentWindow), "Buscar estudante");
    gtk_window_set_position(GTK_WINDOW(findStudentWindow), GTK_WIN_POS_CENTER);

    gtk_window_set_modal(GTK_WINDOW(findStudentWindow), TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(findStudentWindow), GTK_WINDOW(window));

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(box), 10);
    gtk_container_add(GTK_CONTAINER(findStudentWindow), box);

    label = gtk_label_new("Digite o CPF do estudante:");
    gtk_label_set_xalign(GTK_LABEL(label), 0);
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);

    cpf_entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(cpf_entry ), 11);
    gtk_box_pack_start(GTK_BOX(box), cpf_entry, FALSE, FALSE, 0);

    button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_button_box_set_layout(GTK_BUTTON_BOX(button_box), GTK_BUTTONBOX_END);
    gtk_box_set_spacing(GTK_BOX(button_box), 10);
    gtk_box_pack_start(GTK_BOX(box), button_box, FALSE, FALSE, 0);

    cancel_button = gtk_button_new_with_label("Cancelar");
    gtk_container_add(GTK_CONTAINER(button_box), cancel_button);
    ok_button = gtk_button_new_with_label("Buscar");
    gtk_widget_set_sensitive(ok_button, FALSE);
    gtk_container_add(GTK_CONTAINER(button_box), ok_button);

    g_signal_connect(cpf_entry, "changed", G_CALLBACK(on_cpf_entry_changed), ok_button);
    g_signal_connect(ok_button, "clicked", G_CALLBACK(on_ok_button_clicked), cpf_entry);
    g_signal_connect_swapped(cancel_button, "clicked", G_CALLBACK(gtk_widget_destroy), findStudentWindow);

    gtk_widget_show_all(findStudentWindow);

    gtk_main();
}
