#include <stdlib.h>
#include <sys/time.h>

#include "gtk/gtk.h"

#include "app.h"
#include "model.h"

static const char *APP_ID = "com.nelsonearle.ChaosGame";
static const gchar *APP_TITLE = "Chaos Game";

#define PROJ_ROOT "/Users/nelson/Projects/chaos-game"

#define WIDTH 800
#define HEIGHT 600

#define POINT_COUNT_MAX 1000.0

void activate(GtkApplication *app, gpointer data)
{
    Model *model = (Model *)data;

    GtkBuilder *builder = gtk_builder_new_from_file(PROJ_ROOT "/builder.ui");

    GObject *window = gtk_builder_get_object(builder, "window");
    gtk_window_set_application(GTK_WINDOW(window), app);
    gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
    gtk_window_set_default_size(GTK_WINDOW(window), WIDTH, HEIGHT);

    GObject *drawing_area = gtk_builder_get_object(builder, "drawing-area");
    model->drawing_area = GTK_DRAWING_AREA(drawing_area);
    gtk_drawing_area_set_draw_func(
        GTK_DRAWING_AREA(drawing_area), on_draw, model, NULL);

    GObject *slider = gtk_builder_get_object(builder, "slider");
    gtk_range_set_range(GTK_RANGE(slider), 0.0, POINT_COUNT_MAX);
    gtk_range_set_increments(GTK_RANGE(slider), 1.0, 10.0);
    gtk_scale_set_format_value_func(
        GTK_SCALE(slider), format_point_count_value, NULL, NULL);
    g_signal_connect(
        slider, "value-changed", G_CALLBACK(on_point_count_change), model);

    gtk_widget_show(GTK_WIDGET(window));

    g_object_unref(builder);
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    Model *model = model_new();

    GtkApplication *app = gtk_application_new(
        APP_ID,
        G_APPLICATION_FLAGS_NONE);

    g_signal_connect(app, "activate", G_CALLBACK(activate), model);

    int status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);
    model_free(&model);

    return status;
}
