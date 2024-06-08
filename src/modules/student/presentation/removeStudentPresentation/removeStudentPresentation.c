#include "infra/gtk/gtk.h"

#include "modules/student/useCases/removeStudent/removeStudent.h"
#include "modules/student/useCases/updateStudentList/updateStudentList.h"

void remove_student_and_refresh_list(GtkButton *button, gpointer id_ptr) {
    int id = GPOINTER_TO_INT(id_ptr);
    removeStudent(id);
    updateStudentList();
    gtk_widget_destroy(gtk_widget_get_toplevel(GTK_WIDGET(button)));
}


void removeStudentPresentation(GtkButton *button) {
    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));

    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        int id;
        gtk_tree_model_get(model, &iter, 0, &id, -1);

        GtkWidget *dialog_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(dialog_window), "Confirmação");
        gtk_window_set_default_size(GTK_WINDOW(dialog_window), 300, 150);
        gtk_window_set_position(GTK_WINDOW(dialog_window), GTK_WIN_POS_CENTER);
        gtk_window_set_decorated(GTK_WINDOW(dialog_window), TRUE);
        gtk_container_set_border_width(GTK_CONTAINER(dialog_window), 10);

        gtk_window_set_modal(GTK_WINDOW(dialog_window), TRUE);

        gtk_window_set_transient_for(GTK_WINDOW(dialog_window), GTK_WINDOW(window));

        GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        gtk_container_add(GTK_CONTAINER(dialog_window), vbox);

        GtkWidget *label = gtk_label_new("Tem certeza de que deseja remover este aluno?");
        gtk_label_set_line_wrap(GTK_LABEL(label), TRUE);
        gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 5);

        GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
        gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 5);

        GtkWidget *yes_button = gtk_button_new_with_label("Sim");
        gtk_widget_set_name(yes_button, "yes_button");
        gtk_box_pack_start(GTK_BOX(hbox), yes_button, TRUE, TRUE, 5);
        g_signal_connect(yes_button, "clicked", G_CALLBACK(remove_student_and_refresh_list), GINT_TO_POINTER(id));

        GtkWidget *no_button = gtk_button_new_with_label("Não");
        gtk_widget_set_name(no_button, "no_button");
        gtk_box_pack_start(GTK_BOX(hbox), no_button, TRUE, TRUE, 5);
        g_signal_connect_swapped(no_button, "clicked", G_CALLBACK(gtk_widget_destroy), dialog_window);

        gtk_widget_show_all(dialog_window);
    }
}
