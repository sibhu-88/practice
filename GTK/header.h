#ifndef HEADER_H
#define HEADER_H

#include <gtk/gtk.h>
#include <pango/pango.h>

GtkWidget *login();
gboolean check_login(GtkWidget *entry_user, GtkWidget *entry_pass, GtkWidget *status_label);
gboolean clear_status_label(gpointer user_data);
void homepage(GtkButton *);
GtkWidget* create_header_bar();
void on_menu_button_clicked(GtkButton *button, gpointer user_data);
void on_profile_clicked(GtkButton *button, gpointer user_data);
void edit_profile(GtkMenuItem *item, gpointer data);
void change_password(GtkMenuItem *item, gpointer data);
void logout_user(GtkMenuItem *item, gpointer data);

#endif