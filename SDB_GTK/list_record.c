#include"header.h"
void on_list_clicked(GtkMenuItem *menuitem, gpointer user_data)
{
    GtkWidget *content_area = GTK_WIDGET(user_data);
    clear_container(content_area);

    // Check if the linked list is empty
    if (hptr == NULL)
    {
        // Create a dialog to inform the user
        GtkWidget *dialog = gtk_dialog_new_with_buttons("No Records",
                                                        GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(menuitem))),
                                                        GTK_DIALOG_MODAL,
                                                        "_OK",
                                                        GTK_RESPONSE_OK,
                                                        NULL);

        // Create a label with the message
        GtkWidget *message_label = gtk_label_new("No student records available.");
        gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(dialog))), message_label, TRUE, TRUE, 0);

        // Show the dialog
        gtk_widget_show_all(dialog);

        // Connect the response signal to destroy the dialog
        g_signal_connect(dialog, "response", G_CALLBACK(gtk_widget_destroy), NULL);
        return;
    }

    GtkWidget *frame = gtk_frame_new(NULL);
    gtk_container_set_border_width(GTK_CONTAINER(frame), 10);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_widget_set_margin_top(grid, 10);
    gtk_widget_set_margin_start(grid, 10);
    gtk_widget_set_margin_end(grid, 10);
    gtk_widget_set_margin_bottom(grid, 10);

    gtk_container_add(GTK_CONTAINER(frame), grid);

    // Table Headers (bold)
    GtkWidget *header_id = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(header_id), "<b>ID</b>");
    GtkWidget *header_name = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(header_name), "<b>Name</b>");
    GtkWidget *header_per = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(header_per), "<b>Percentage</b>");

    gtk_grid_attach(GTK_GRID(grid), header_id, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), header_name, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), header_per, 2, 0, 1, 1);

    // Student Records
    SDB *temp = hptr;
    int row = 1;
    while (temp != NULL)
    {
        gchar id_str[10], per_str[10];
        sprintf(id_str, "%d", temp->rollno);
        sprintf(per_str, "%.2f", temp->percentage);

        GtkWidget *id_label = gtk_label_new(id_str);
        GtkWidget *name_label = gtk_label_new(temp->name);
        GtkWidget *per_label = gtk_label_new(per_str);

        gtk_widget_set_margin_top(id_label, 5);
        gtk_widget_set_margin_top(name_label, 5);
        gtk_widget_set_margin_top(per_label, 5);

        gtk_grid_attach(GTK_GRID(grid), id_label, 0, row, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), name_label, 1, row, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), per_label, 2, row, 1, 1);

        row++;
        temp = temp->next;
    }

    gtk_box_pack_start(GTK_BOX(content_area), frame, FALSE, TRUE, 0);
    gtk_widget_show_all(content_area);
}
