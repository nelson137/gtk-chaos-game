#ifndef _APP_H
#define _APP_H

#include "cairo.h"

#include "gtk/gtk.h"

#define NUM_POINTS 4096

void generate_points();

char *format_point_count_value(GtkScale *scale, double value, gpointer data);

void on_point_count_change(GtkRange *self, gpointer data);

void on_draw(
    GtkDrawingArea *w,
    cairo_t *cr,
    int width,
    int height,
    gpointer data);

#endif
