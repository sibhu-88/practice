#include "header.h"

SDB *hptr = NULL;

void on_submit_click(GtkWidget *button, gpointer user_data) {
    GtkWidget **student_data = (GtkWidget **)user_data;
    const gchar *name = gtk_entry_get_text(GTK_ENTRY(student_data[0]));
    float per = atof(gtk_entry_get_text(GTK_ENTRY(student_data[1])));

    add_new_record(&hptr, name, per);
    gtk_label_set_text(GTK_LABEL(student_data[2]), "Student added successfully!");
}

// gboolean check_data(GtkWidget *entry_name, GtkWidget *entry_per, GtkWidget *status_label)
// {
//     const gchar *name = gtk_entry_get_text(GTK_ENTRY(entry_user));
//     const gchar *percentage = gtk_entry_get_text(GTK_ENTRY(entry_pass));
//     GtkStyleContext *context = gtk_widget_get_style_context(status_label);

//     if (g_strcmp0(name, "") == 0 || g_strcmp0(percentage, "") == 0)
//     {
//         gtk_label_set_text(GTK_LABEL(status_label), "Please fill all fields.");
//         gtk_style_context_remove_class(context, "success-label");
//         gtk_style_context_add_class(context, "error-label");
//         return FALSE;
//     }
//     else
//     {
//         gtk_label_set_text(GTK_LABEL(status_label), "Login Successful!");
//         gtk_style_context_remove_class(context, "error-label");
//         gtk_style_context_add_class(context, "success-label");
//         return TRUE;
//     }
// }

void on_add_clicked(GtkMenuItem *menuitem, gpointer user_data)
{
    GtkWidget *content_area = GTK_WIDGET(user_data);

    GtkWidget *add_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_widget_set_margin_top(grid, 100);
    gtk_widget_set_margin_start(grid, 50);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER); 

    gtk_box_pack_start(GTK_BOX(add_box), grid, FALSE, TRUE, 10);

    GtkWidget *name = gtk_label_new("Name : ");
    GtkWidget *percentage = gtk_label_new("Percentage :");
    GtkWidget *entry_name = gtk_entry_new();
    GtkWidget *entry_per = gtk_entry_new();
    GtkWidget *submit = gtk_button_new_with_label("Submit");
    GtkStyleContext *context1 = gtk_widget_get_style_context(submit);
    gtk_style_context_add_class(context1, "default-button");
    GtkWidget *status = gtk_label_new("");
    
    gtk_grid_attach(GTK_GRID(grid), status, 0, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), name, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_name, 1, 1, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), percentage, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_per, 1, 2, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), submit, 1, 3, 1, 1);

    GtkWidget **widget = g_new(GtkWidget *, 3);
    widget[0] = entry_name;
    widget[1] = entry_per;
    widget[2] = status;

    g_signal_connect(submit, "clicked", G_CALLBACK(on_submit_click), widget);

    gtk_box_pack_start(GTK_BOX(content_area), add_box, FALSE, TRUE, 0);

    gtk_widget_show_all(content_area);
}

void on_list_clicked(GtkMenuItem *menuitem, gpointer user_data) {
    GtkWidget *content_area = GTK_WIDGET(user_data);
    clear_container(content_area);

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
    while (temp != NULL) {
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

void on_modify_clicked(GtkMenuItem *menuitem, gpointer user_data)
{
    g_print("Modify clicked\n");
}

void on_sort_clicked(GtkMenuItem *menuitem, gpointer user_data)
{
    g_print("Sort clicked\n");
}

void on_save_clicked(GtkMenuItem *menuitem, gpointer user_data)
{
    g_print("Save clicked\n");
}
