#include "cairo.h"
#include "gtk/gtk.h"

#include "model.h"

char *format_point_count_value(GtkScale *scale, double value, gpointer data)
{
    return g_strdup_printf("%d", (int)value);
}

void on_point_count_change(GtkRange *self, gpointer data)
{
    Model *model = (Model *)data;
    int value = (int)gtk_range_get_value(self);
    model->point_count = value;
    model_flush(model);
}

void on_draw(
    GtkDrawingArea *w,
    cairo_t *cr,
    int width,
    int height,
    gpointer data)
{
    Model *model = (Model *)data;

    int slider_value = model->point_count;
    double b = (double)slider_value / 1000.0;

    cairo_set_source_rgb(cr, 1.0, 0.0, b);
    cairo_paint(cr);
}
