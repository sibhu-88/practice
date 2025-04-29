#include "header.h"

GtkWidget *create_header_bar()
{
    GtkWidget *header = gtk_header_bar_new();

    GtkWidget *logo_image = gtk_image_new_from_file("logo.png");
    gtk_header_bar_pack_start(GTK_HEADER_BAR(header), logo_image);

    const char *button_icons[] = {
        "document-save-symbolic",
        "view-sort-ascending-symbolic",
        "document-edit-symbolic",
        "view-list-symbolic",
        "list-add-symbolic"};

    const char *button_labels[] = {"Save", "Sort", "Modify", "List", "Add"};

    GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    for (int i = 0; i < 5; i++)
    {
        GtkWidget *btn = gtk_button_new_from_icon_name(button_icons[i], GTK_ICON_SIZE_BUTTON);

        gtk_widget_set_tooltip_text(btn, button_labels[i]);
        g_signal_connect(btn, "clicked", G_CALLBACK(on_menu_button_clicked), (gpointer)button_labels[i]);

        gtk_box_pack_end(GTK_BOX(button_box), btn, FALSE, FALSE, 0);
    }

    // Add Profile Section
    GtkWidget *profile_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_widget_set_margin_start(profile_box, 15); // Space between buttons and profile

    GtkWidget *profile_btn = gtk_button_new_from_icon_name("avatar-default-symbolic", GTK_ICON_SIZE_BUTTON);
    gtk_widget_set_tooltip_text(profile_btn, "User Profile");
    gtk_box_pack_end(GTK_BOX(profile_box), profile_btn, FALSE, FALSE, 0);

    g_signal_connect(profile_btn, "clicked", G_CALLBACK(on_profile_clicked), NULL);

    gtk_header_bar_pack_end(GTK_HEADER_BAR(header), profile_box);
    gtk_header_bar_pack_end(GTK_HEADER_BAR(header), button_box);

    return header;
}

// Profile Click Handler (New Function)
void on_profile_clicked(GtkButton *button, gpointer user_data)
{
    g_print("Profile button clicked!\n");

    // Create profile menu
    GtkWidget *menu = gtk_menu_new();

    GtkWidget *menu_item1 = gtk_menu_item_new_with_label("Edit Profile");
    GtkWidget *menu_item2 = gtk_menu_item_new_with_label("Change Password");
    GtkWidget *menu_item3 = gtk_menu_item_new_with_label("Logout");

    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item1);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item2);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item3);

    // Connect menu actions
    g_signal_connect(menu_item1, "activate", G_CALLBACK(edit_profile), NULL);
    g_signal_connect(menu_item2, "activate", G_CALLBACK(change_password), NULL);
    g_signal_connect(menu_item3, "activate", G_CALLBACK(logout_user), NULL);

    gtk_widget_show_all(menu);

    // Show menu at button position
    gtk_menu_popup_at_widget(
        GTK_MENU(menu),
        GTK_WIDGET(button),
        GDK_GRAVITY_SOUTH_WEST,
        GDK_GRAVITY_NORTH_WEST,
        NULL);
}

// Connect profile button in create_header_bar (add this line)
// g_signal_connect(profile_btn, "clicked", G_CALLBACK(on_profile_clicked), NULL);

void on_menu_button_clicked(GtkButton *button, gpointer user_data)
{
    const char *button_label = (const char *)user_data;
    g_print("Clicked: %s\n", button_label);

    if (strcmp(button_label, "Add") == 0)
    {
        // Handle Add action
    }
    else if (strcmp(button_label, "List") == 0)
    {
        // Handle List action
    }
    else if (strcmp(button_label, "Modify") == 0)
    {
        // Handle Modify action
    }
    else if (strcmp(button_label, "Sort") == 0)
    {
        // Handle Sort action
    }
    else if (strcmp(button_label, "Save") == 0)
    {
        // Handle Save action
    }
}

// Add these stubs for menu actions
void edit_profile(GtkMenuItem *item, gpointer data)
{
    g_print("Edit Profile selected\n");
}

void change_password(GtkMenuItem *item, gpointer data)
{
    g_print("Change Password selected\n");
}

void logout_user(GtkMenuItem *item, gpointer data)
{
    g_print("Logout selected\n");
    gtk_main_quit();
}
