#include "header.h"

void ListRecord(GtkButton *button, SDB *list)
{
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));

    if (list == NULL)
    {
        GtkWidget *dialog = gtk_dialog_new_with_buttons("No Records",
                                                        GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(window))),
                                                        GTK_DIALOG_MODAL,
                                                        "_OK",
                                                        GTK_RESPONSE_OK,
                                                        NULL);

        GtkWidget *message_label = gtk_label_new("No student records available.");
        GtkWidget *ok_button = gtk_dialog_get_widget_for_response(GTK_DIALOG(dialog), GTK_RESPONSE_OK);
        gtk_style_context_add_class(gtk_widget_get_style_context(ok_button), "ok-button");
        gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(dialog))), message_label, TRUE, TRUE, 0);

        gtk_widget_show_all(dialog);

        g_signal_connect(dialog, "response", G_CALLBACK(gtk_widget_destroy), NULL);
        return;
    }

    GList *children = gtk_container_get_children(GTK_CONTAINER(window));
    for (GList *iter = children; iter; iter = g_list_next(iter))
    {
        GtkWidget *child = GTK_WIDGET(iter->data);
        gtk_container_remove(GTK_CONTAINER(window), child);
        gtk_widget_destroy(child); // Ensure widget is destroyed
    }
    g_list_free(children);

    GtkWidget *listrecord = ListRecordTable(list);

    gtk_container_add(GTK_CONTAINER(window), listrecord);
    gtk_widget_show_all(window);
}

GtkWidget *ListRecordTable(SDB *node) {
    g_print("ListRecordTable: node=%p\n", (void *)node);

    // Create main vertical box
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(main_box), 10);

    // Add header bar
    GtkWidget *header = create_header_bar();
    gtk_box_pack_start(GTK_BOX(main_box), header, FALSE, FALSE, 0);

    // Add blinking title label
    GtkWidget *title_label = gtk_label_new("STUDENT DATABASE PROJECT");
    gtk_label_set_markup(GTK_LABEL(title_label), "<b>STUDENT DATABASE PROJECT</b>");
    gtk_widget_set_halign(title_label, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(main_box), title_label, FALSE, FALSE, 10);

    // Create inner vertical box for centering
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(box, GTK_ALIGN_CENTER);

    // Create grid
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_container_set_border_width(GTK_CONTAINER(grid), 10);

    // Create header labels
    GtkWidget *header_rollno = gtk_label_new("Roll No");
    GtkWidget *header_name = gtk_label_new("Name");
    GtkWidget *header_mark = gtk_label_new("Mark");

    // Make headers bold
    gtk_label_set_markup(GTK_LABEL(header_rollno), "<b>Roll No</b>");
    gtk_label_set_markup(GTK_LABEL(header_name), "<b>Name</b>");
    gtk_label_set_markup(GTK_LABEL(header_mark), "<b>Mark</b>");

    // Attach headers to grid (row 0)
    gtk_grid_attach(GTK_GRID(grid), header_rollno, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), header_name, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), header_mark, 2, 0, 1, 1);

    // Iterate through the linked list
    SDB *current = node;
    int row = 1;
    while (current != NULL) {
        // Convert rollno and mark to strings
        char rollno_str[10];
        char mark_str[10];
        snprintf(rollno_str, sizeof(rollno_str), "%d", current->rollno);
        snprintf(mark_str, sizeof(mark_str), "%d", current->mark);

        // Create labels for each field
        GtkWidget *rollno_label = gtk_label_new(rollno_str);
        GtkWidget *name_label = gtk_label_new(current->name);
        GtkWidget *mark_label = gtk_label_new(mark_str);

        // Left-align labels
        gtk_label_set_xalign(GTK_LABEL(rollno_label), 0.0);
        gtk_label_set_xalign(GTK_LABEL(name_label), 0.0);
        gtk_label_set_xalign(GTK_LABEL(mark_label), 0.0);

        // Attach labels to grid
        gtk_grid_attach(GTK_GRID(grid), rollno_label, 0, row, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), name_label, 1, row, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), mark_label, 2, row, 1, 1);

        current = current->next;
        row++;
    }

    // Create button box for "Back" button
    GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_halign(button_box, GTK_ALIGN_CENTER);

    GtkWidget *back_button = gtk_button_new_with_label("Back");
    gtk_box_pack_start(GTK_BOX(button_box), back_button, FALSE, FALSE, 0);
    g_signal_connect(back_button, "clicked", G_CALLBACK(homepage), NULL);

    // Pack widgets into boxes
    gtk_box_pack_start(GTK_BOX(box), grid, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(main_box), box, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(main_box), button_box, FALSE, FALSE, 10);

    return main_box;
}
/*
{ 


    // Tree view
  GtkWidget *tree_view = gtk_tree_view_new();
  gtk_style_context_add_class(gtk_widget_get_style_context(tree_view), "record-table");
  gtk_widget_set_name(tree_view, "student-list");
  gtk_container_add(GTK_CONTAINER(box), tree_view);

    // List store
    GtkListStore *store = gtk_list_store_new(3,
                                             G_TYPE_INT,    // Roll No
                                             G_TYPE_STRING, // Name
                                             G_TYPE_INT);   // Mark
    GtkTreeIter iter;
    SDB *current = node;
    while (current)
    {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, current->rollno,
                           1, current->name,
                           2, current->mark,
                           -1);
        g_print("Added record to list: rollno=%d, name=%s, mark=%d\n",
                current->rollno, current->name, current->mark);
        current = current->next;
    }

    // Columns
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    renderer = gtk_cell_renderer_text_new();
    g_object_set(renderer, "weight", PANGO_WEIGHT_BOLD, "xalign", 0.5, NULL); // Bold header
    column = gtk_tree_view_column_new_with_attributes("Roll No", renderer,
                                                      "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    gtk_tree_view_column_set_resizable(column, TRUE);

    renderer = gtk_cell_renderer_text_new();
    g_object_set(renderer, "weight", PANGO_WEIGHT_BOLD, "xalign", 0.5, NULL); // Bold header
    column = gtk_tree_view_column_new_with_attributes("Name", renderer,
                                                      "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    gtk_tree_view_column_set_resizable(column, TRUE);

    renderer = gtk_cell_renderer_text_new();
    g_object_set(renderer, "weight", PANGO_WEIGHT_BOLD, "xalign", 0.5, NULL); // Bold header
    column = gtk_tree_view_column_new_with_attributes("Mark", renderer,
                                                      "text", 2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    gtk_tree_view_column_set_resizable(column, TRUE);

    gtk_tree_view_set_model(GTK_TREE_VIEW(tree_view), GTK_TREE_MODEL(store));
    g_object_unref(store);
}
*/

