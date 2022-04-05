#include <stdlib.h>
#include <sys/time.h>

#include "gtk/gtk.h"

#include "app.h"
#include "model.h"

#include "builder.ui.h"

static const char *APP_ID = "com.nelsonearle.ChaosGame";
static const gchar *APP_TITLE = "Chaos Game";

#define WIDTH 888
#define HEIGHT 600

void activate(GtkApplication *app, gpointer data)
{
    Model *model = (Model *)data;

    GtkBuilder *builder =
        gtk_builder_new_from_string((const char *)BUILDER_UI, BUILDER_UI_LEN);

    GObject *window = gtk_builder_get_object(builder, "window");
    gtk_window_set_application(GTK_WINDOW(window), app);
    gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
    gtk_window_set_default_size(GTK_WINDOW(window), WIDTH, HEIGHT);

    GObject *drawing_area = gtk_builder_get_object(builder, "drawing-area");
    model->drawing_area = GTK_DRAWING_AREA(drawing_area);
    gtk_drawing_area_set_draw_func(
        GTK_DRAWING_AREA(drawing_area), on_draw, model, NULL);
    GtkEventController *motion = gtk_event_controller_motion_new();
    gtk_widget_add_controller(
        GTK_WIDGET(drawing_area), GTK_EVENT_CONTROLLER(motion));
    g_signal_connect(motion, "enter", G_CALLBACK(on_motion_enter), model);
    g_signal_connect(motion, "motion", G_CALLBACK(on_motion_update), model);
    g_signal_connect(motion, "leave", G_CALLBACK(on_motion_leave), model);

    GObject *slider = gtk_builder_get_object(builder, "slider");
    gtk_range_set_range(GTK_RANGE(slider), 0.0, (double)NUM_POINTS);
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

    generate_points();

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
