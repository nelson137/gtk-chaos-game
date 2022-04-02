#include <stdlib.h>
#include <sys/time.h>

#include "gtk/gtk.h"

static const char *APP_ID = "com.nelsonearle.ChaosGame";
static const gchar *APP_TITLE = "Chaos Game";

#define WIDTH 800
#define HEIGHT 600

void activate(GtkApplication *app, gpointer arg)
{
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);

    gtk_window_set_default_size(GTK_WINDOW(window), WIDTH, HEIGHT);

    gtk_widget_show(window);
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    GtkApplication *app = gtk_application_new(
        APP_ID,
        G_APPLICATION_FLAGS_NONE);

    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
