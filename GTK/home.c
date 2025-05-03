#include "header.h"

gboolean redirect_to_homepage(gpointer user_data)
{
    GtkButton *button = GTK_BUTTON(user_data);
    if (!button || !GTK_IS_BUTTON(button))
    {
        fprintf(stderr, "Error: Invalid or null button in redirect_to_homepage\n");
        return FALSE;
    }
    g_print("redirect_to_homepage: button=%p\n", (void *)button);
    homepage(button);
    return FALSE; // Run once

    
}

gboolean blink_label(gpointer data) {
    GtkWidget *label = GTK_WIDGET(data);
    gdouble opacity = gtk_widget_get_opacity(label);
    gtk_widget_set_opacity(label, opacity == 1.0 ? 0.3 : 1.0); // Toggle between opaque and semi-transparent
    return G_SOURCE_CONTINUE;
}

void homepage(GtkButton *button)
{
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    if (!gtk_widget_is_toplevel(window))
    {
        g_warning("Cannot show homepage: not a top-level window");
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

    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    GtkWidget *header = create_header_bar();
    gtk_box_pack_start(GTK_BOX(main_box), header, FALSE, FALSE, 0);

    GtkWidget *content_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_halign(content_box, GTK_ALIGN_START );
    gtk_widget_set_valign(content_box, GTK_ALIGN_CENTER);
    gtk_widget_set_hexpand(content_box, TRUE);
    gtk_widget_set_vexpand(content_box, TRUE);

    GtkWidget *project_label = gtk_label_new("STUDENT DATABASE PROJECT");
    GtkWidget *image = gtk_image_new_from_file("logo.png");
    GtkWidget *label = gtk_label_new("VECTOR Institute - One of the Best Embedded Systems Training Institutes in Chennai, Hyderabad & Bangalore.");
   
    // Add a timeout to blink the label every 500 milliseconds
    gtk_widget_set_opacity(project_label, 1.0);
    g_timeout_add(300, blink_label, project_label);

    gtk_style_context_add_class(gtk_widget_get_style_context(project_label), "project_label");
    gtk_style_context_add_class(gtk_widget_get_style_context(image), "header_image");
    gtk_style_context_add_class(gtk_widget_get_style_context(label), "header_label");

    gtk_label_set_line_wrap(GTK_LABEL(label), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(label), PANGO_WRAP_WORD);
    gtk_widget_set_hexpand(label, TRUE);

    gtk_box_pack_start(GTK_BOX(content_box), project_label, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(content_box), image, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(content_box), label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(main_box), content_box, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), main_box);
    gtk_widget_show_all(window);
}