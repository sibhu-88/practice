#include "header.h"

SDB *hptr = NULL;

gboolean check_data(gpointer user_data)
{
    GtkWidget **student_data = (GtkWidget **)user_data;

    // if (student_data == NULL || student_data[0] == NULL || student_data[1] == NULL || student_data[2] == NULL) {
    //     g_print("Error: One of the student data widgets is NULL\n");
    //     return FALSE; // Handle the error appropriately
    // }

    const gchar *name = gtk_entry_get_text(GTK_ENTRY(student_data[0]));
    const gchar *percentage_text = gtk_entry_get_text(GTK_ENTRY(student_data[1]));
    GtkStyleContext *context = gtk_widget_get_style_context(student_data[2]);

    // Convert percentage to float
    float percentage = atof(percentage_text);

    if (g_strcmp0(name, "") == 0 || g_strcmp0(percentage_text, "") == 0)
    {
        gtk_label_set_text(GTK_LABEL(student_data[2]), "Please fill all fields.");
        gtk_style_context_remove_class(context, "success-label");
        gtk_style_context_add_class(context, "error-label");
    }
    else if (percentage < 0 || percentage > 100)
    {
        gtk_label_set_text(GTK_LABEL(student_data[2]), "Percentage must be between 0 and 100.");
        gtk_style_context_remove_class(context, "success-label");
        gtk_style_context_add_class(context, "error-label");
    }
    else
    {
        gtk_label_set_text(GTK_LABEL(student_data[2]), "Student added successfully!");
        gtk_style_context_remove_class(context, "error-label");
        gtk_style_context_add_class(context, "success-label");
        g_timeout_add_seconds(1, clear_status_label, student_data);
        return TRUE;
    }

    g_timeout_add_seconds(1, clear_status_label, student_data);
    return FALSE;
}

void on_submit_click(GtkWidget *button, gpointer user_data)
{
    GtkWidget **student_data = (GtkWidget **)user_data;
    // if (student_data == NULL || student_data[0] == NULL || student_data[1] == NULL) {
    //     g_print("Error: student_data or its entries are NULL\n");
    //     return FALSE; // Handle the error appropriately
    // }
    
    // if (!GTK_IS_ENTRY(student_data[0]) || !GTK_IS_ENTRY(student_data[1])) {
    //     g_print("Error: One of the widgets is not a GtkEntry\n");
    //     return FALSE; // Handle the error appropriately
    // }

    const gchar *name = gtk_entry_get_text(GTK_ENTRY(student_data[0]));
    float per = atof(gtk_entry_get_text(GTK_ENTRY(student_data[1])));

    gboolean status = check_data(student_data);

    if (status) {
        add_new_record(&hptr, name, per);
    
        // Only clear on success
        GtkWidget **clear_data = g_new(GtkWidget *, 3);
        clear_data[0] = student_data[0];
        clear_data[1] = student_data[1];
        clear_data[2] = student_data[2];
        g_timeout_add_seconds(1, clear_status_label, clear_data);
    }
   
}

void on_add_clicked(GtkMenuItem *menuitem, gpointer user_data)
{
    GtkWidget *content_area = GTK_WIDGET(user_data);
    GtkWidget *add_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    clear_container(content_area);

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


void on_list_clicked(GtkMenuItem *menuitem, gpointer user_data)
{
    GtkWidget *content_area = GTK_WIDGET(user_data);
    clear_container(content_area); // Clear previous content

    // Check if there are any student records
    if (hptr == NULL)
    {
        GtkWidget *dialog = gtk_dialog_new_with_buttons("No Records",
                                                        GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(menuitem))),
                                                        GTK_DIALOG_MODAL,
                                                        "_OK",
                                                        GTK_RESPONSE_OK,
                                                        NULL);

        GtkWidget *message_label = gtk_label_new("No student records available.");
        gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(dialog))), message_label, TRUE, TRUE, 0);

        gtk_widget_show_all(dialog);
        g_signal_connect(dialog, "response", G_CALLBACK(gtk_widget_destroy), NULL);
        return;
    }

    // Create a ListStore to hold the student data
    GtkListStore *list_store = gtk_list_store_new(3, G_TYPE_INT, G_TYPE_STRING, G_TYPE_FLOAT);

    // Populate the ListStore with student data
    SDB *temp = hptr; // Assuming hptr is your head pointer to the student linked list
    while (temp != NULL)
    {
        gtk_list_store_insert_with_values(list_store, NULL, -1,
                                           0, temp->rollno,    // ID
                                           1, temp->name,       // Name
                                           2, temp->percentage,  // Percentage
                                           -1);
        temp = temp->next;
    }

    // Create a TreeView and set the model
    GtkWidget *tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(list_store));

    // Create a cell renderer for the text
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();

    // Create columns for the TreeView
    GtkTreeViewColumn *column_id = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column_id);

    GtkTreeViewColumn *column_name = gtk_tree_view_column_new_with_attributes("Name", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column_name);

    GtkTreeViewColumn *column_percentage = gtk_tree_view_column_new_with_attributes("Percentage", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column_percentage);

    // Create a frame to hold the TreeView
    GtkWidget *frame = gtk_frame_new("Student Records");
    gtk_container_set_border_width(GTK_CONTAINER(frame), 10);
    gtk_container_add(GTK_CONTAINER(frame), tree_view);

    // Set the alignment of the frame to center it
    gtk_widget_set_halign(frame, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(frame, GTK_ALIGN_CENTER);

    // Create a box to hold the frame
    GtkWidget *center_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(center_box), frame, TRUE, TRUE, 0);

    // Add the centered box to the content area
    gtk_box_pack_start(GTK_BOX(content_area), center_box, TRUE, TRUE, 0);

    // Show all widgets
    gtk_widget_show_all(content_area);
}

void desktop(GtkWidget *box)
{
    GtkWidget *menubar = gtk_menu_bar_new();
    gtk_style_context_add_class(gtk_widget_get_style_context(menubar), "custom-menubar");
    
    GtkWidget *add_item = gtk_menu_item_new_with_label("Add  ");
    GtkWidget *list_item = gtk_menu_item_new_with_label("List  ");
    GtkWidget *modify_item = gtk_menu_item_new_with_label("Modify  ");
    GtkWidget *sort_item = gtk_menu_item_new_with_label("Sort  ");
    GtkWidget *save_item = gtk_menu_item_new_with_label("Save  ");
    
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), add_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), list_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), modify_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), sort_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), save_item);
    
    gtk_box_pack_start(GTK_BOX(box), menubar, FALSE, FALSE, 0);

    GtkWidget *content_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(content_area, "content-area");

    gtk_box_pack_start(GTK_BOX(box), content_area, TRUE, TRUE, 0);
    
    g_signal_connect(add_item,    "activate", G_CALLBACK(on_add_clicked),    content_area);
    g_signal_connect(list_item,   "activate", G_CALLBACK(on_list_clicked),   content_area);
    g_signal_connect(modify_item, "activate", G_CALLBACK(on_modify_clicked), content_area);
    g_signal_connect(sort_item,   "activate", G_CALLBACK(on_sort_clicked),   content_area);
    g_signal_connect(save_item,   "activate", G_CALLBACK(on_save_clicked),   content_area);
}