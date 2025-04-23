#include "header.h"

SDB *hptr = NULL;

gboolean clear_status_label(gpointer user_data)
{
    GtkWidget **widget = (GtkWidget **)user_data;
    gtk_entry_set_text(GTK_ENTRY(widget[0]), "");
    gtk_entry_set_text(GTK_ENTRY(widget[1]), "");
    gtk_label_set_text(GTK_LABEL(widget[2]), "");

    g_free(widget); // Free the allocated memory
    return G_SOURCE_REMOVE;
}

void clear_container(GtkWidget *container)
{
    GList *children, *iter;

    children = gtk_container_get_children(GTK_CONTAINER(container));
    for (iter = children; iter != NULL; iter = g_list_next(iter))
    {
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    }
    g_list_free(children);
}

gboolean check_login(GtkWidget *entry_user, GtkWidget *entry_pass, GtkWidget *status_label)
{
    GtkWidget **widget = g_new(GtkWidget *, 3);
    widget[0] = entry_user;
    widget[1] = entry_pass;
    widget[2] = status_label;
    
    const gchar *username = gtk_entry_get_text(GTK_ENTRY(entry_user));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(entry_pass));
    GtkStyleContext *context = gtk_widget_get_style_context(status_label);

    if (g_strcmp0(username, "") == 0 || g_strcmp0(password, "") == 0)
    {
        gtk_label_set_text(GTK_LABEL(status_label), "Please fill all fields.");
        gtk_style_context_remove_class(context, "success-label");
        gtk_style_context_add_class(context, "error-label");
    }
    else if (strcmp(username, "vector") == 0 && strcmp(password, "123") == 0)
    {
        gtk_label_set_text(GTK_LABEL(status_label), "Login Successful!");
        gtk_style_context_remove_class(context, "error-label");
        gtk_style_context_add_class(context, "success-label");
        return TRUE;
    }
    else
    {
        gtk_label_set_text(GTK_LABEL(status_label), "Invalid username or password");
        gtk_style_context_remove_class(context, "success-label");
        gtk_style_context_add_class(context, "error-label");
    }

    g_timeout_add_seconds(1, clear_status_label, widget);
    return FALSE;
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