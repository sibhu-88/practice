#include "header.h"

void apply_css_from_file(const gchar *file_path)
{
    GtkCssProvider *provider = gtk_css_provider_new();  
    gtk_css_provider_load_from_path(provider, file_path, NULL);
    
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(), 
        GTK_STYLE_PROVIDER(provider), 
        GTK_STYLE_PROVIDER_PRIORITY_USER);  
    g_object_unref(provider);
}


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

void on_button_click(GtkWidget *button, gpointer user_data)
{
    GtkWidget **widget = user_data;
    gboolean success = check_login(widget[0], widget[1], widget[2]);

    if (success)
    {

        clear_container(widget[3]);
        desktop(widget[3]);

        gtk_widget_show_all(widget[3]);
    }
}

void on_activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Student DataBase");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 650);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    apply_css_from_file("style.css");

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_widget_set_margin_top(grid, 100);
    gtk_widget_set_margin_start(grid, 50);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER); // center horizontally
    gtk_widget_set_hexpand(grid, TRUE);            // allow horizontal expansion
    gtk_widget_set_vexpand(grid, TRUE);            // allow vertical expansion

   // gtk_box_pack_start(GTK_BOX(box), grid, FALSE, TRUE, 10);

    GtkWidget *username = gtk_label_new("User Name:");
    GtkWidget *password = gtk_label_new("Password:");
    GtkWidget *entry_user = gtk_entry_new();
    GtkWidget *entry_pass = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entry_pass), FALSE);
    GtkWidget *login = gtk_button_new_with_label("Login");
    GtkStyleContext *context = gtk_widget_get_style_context(login);
    gtk_style_context_add_class(context, "default-button");
    GtkWidget *status = gtk_label_new("");

    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_user), "Enter your username");
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_pass), "Enter your password");


    gtk_grid_attach(GTK_GRID(grid), status, 0, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), username, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_user, 1, 1, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), password, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_pass, 1, 2, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), login, 1, 3, 1, 1);

    GtkWidget **widget = g_new(GtkWidget *, 4);
    widget[0] = entry_user;
    widget[1] = entry_pass;
    widget[2] = status;
    widget[3] = box;
    desktop(box);
   // g_signal_connect(login, "clicked", G_CALLBACK(on_button_click), widget);
    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
    GtkApplication *app = gtk_application_new("com.example.GTK3App", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
