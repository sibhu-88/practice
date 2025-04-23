#ifndef HEADER_H
#define HEADER_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct sdb
{
    int rollno;
    char name[50];
    float percentage;
    struct sdb *next;
} SDB;

void on_add_clicked(GtkMenuItem *menuitem, gpointer user_data);
void on_list_clicked(GtkMenuItem *menuitem, gpointer user_data);
void on_modify_clicked(GtkMenuItem *menuitem, gpointer user_data);
void on_sort_clicked(GtkMenuItem *menuitem, gpointer user_data);
void on_save_clicked(GtkMenuItem *menuitem, gpointer user_data);
void on_submit_click(GtkWidget *button, gpointer user_data);
void on_submit_more_click(GtkWidget *button, gpointer user_data);

void apply_css(const gchar *css_data);
gboolean clear_status_label(gpointer user_data);
void clear_container(GtkWidget *container);
gboolean check_login(GtkWidget *entry_user, GtkWidget *entry_pass, GtkWidget *status_label);
gboolean check_data(GtkWidget *entry_name, GtkWidget *entry_per, GtkWidget *status_label);

void add_new_record(SDB **ptr, const gchar *name, float percentage);

#endif
