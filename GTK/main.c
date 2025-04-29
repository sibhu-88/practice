#include <gtk/gtk.h>

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

static void on_login_clicked(GtkButton *button, gpointer user_data) {
    GtkEntry **entries = (GtkEntry **)user_data;
    const gchar *username = gtk_entry_get_text(entries[0]);
    const gchar *password = gtk_entry_get_text(entries[1]);

    g_print("Username: %s\n", username);
    g_print("Password: %s\n", password);
}

GtkWidget *login(){
    GtkWidget *box,*grid;

    box = gtk_box_new (GTK_ORIENTATION_VERTICAL ,10);    
    grid = gtk_grid_new();
    gtk_widget_set_name(box, "login-box");
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);

   gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

    GtkWidget *username_label = gtk_label_new("Username:");
    GtkWidget *password_label = gtk_label_new("Password:");

    gtk_widget_set_margin_top(grid, 20);
    gtk_widget_set_margin_bottom(grid, 20);
    gtk_widget_set_margin_start(grid, 20);
    gtk_widget_set_margin_end(grid, 20);


    GtkWidget *username_entry = gtk_entry_new();
    GtkWidget *password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(password_entry), '*');

    GtkWidget *login_button = gtk_button_new_with_label("Login");
    gtk_widget_set_name(login_button, "login-button");

    GtkEntry **entries = g_new(GtkEntry*, 2);
    entries[0] = GTK_ENTRY(username_entry);
    entries[1] = GTK_ENTRY(password_entry);
    
    gtk_grid_attach(GTK_GRID(grid), username_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), username_entry, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), password_label, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), password_entry, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), login_button, 0, 2, 2, 1);
    
    g_signal_connect(login_button, "clicked", G_CALLBACK(on_login_clicked), entries);
    gtk_container_add(GTK_CONTAINER(box), grid);
    return box;
}

void on_activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Student DataBase");

    GdkScreen *screen = gdk_screen_get_default();
    int width = gdk_screen_get_width(screen);
    int height = gdk_screen_get_height(screen);

    gtk_window_set_default_size(GTK_WINDOW(window), width, 1000);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    apply_css_from_file("style.css");

    GtkWidget *login_window = login();
    gtk_container_add(GTK_CONTAINER(window), login_window);
    
    gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
    GtkApplication *app = gtk_application_new("com.example.GTK3App", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
