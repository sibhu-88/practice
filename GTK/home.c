#include "header.h"

void homepage(GtkButton *button)
{
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    
    // Remove existing content
    GList *children = gtk_container_get_children(GTK_CONTAINER(window));
    if(children) {
        gtk_container_remove(GTK_CONTAINER(window), GTK_WIDGET(children->data));
        g_list_free(children);
    }

    // Main vertical container
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    
    // Add custom header
    GtkWidget *header = create_header_bar();
    gtk_box_pack_start(GTK_BOX(main_box), header, FALSE, FALSE, 0);
    
    // Content area
    GtkWidget *content_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL , 0);
    gtk_widget_set_halign(content_box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(content_box, GTK_ALIGN_CENTER);
    gtk_widget_set_hexpand(content_box, TRUE);
    gtk_widget_set_vexpand(content_box, TRUE);
    
    // Add image and label
    GtkWidget *image = gtk_image_new_from_file("logo.png");
    GtkWidget *label = gtk_label_new("Welcome to Student Database!");
    
    gtk_box_pack_start(GTK_BOX(content_box), image, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(content_box), label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(main_box), content_box, TRUE, TRUE, 0);

    // Add to window
    gtk_container_add(GTK_CONTAINER(window), main_box);
    gtk_widget_show_all(window);
}
