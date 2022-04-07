#include <stdlib.h>

#include "cairo.h"
#include "gtk/gtk.h"

#include "model.h"

#include "app.h"

#define POINT_RADIUS 1.0

typedef struct _Point
{
    double x, y;
} Point;

typedef struct _Rgb
{
    double r, g, b;
} Rgb;

static Rgb point_color = {1.0, 0.0, 0.0};

static Point big_triangle[] = {
    {300.0000, 083.4936}, // top middle
    {050.0000, 516.5064}, // bottom left
    {550.0000, 516.5064}, // bottom right
};

static Point points[NUM_POINTS];

void generate_points()
{
    points[0].x = 330.0;
    points[0].y = 250.0;
    for (int i = 1; i < NUM_POINTS; i++)
    {
        int big_tri_i = 3 * ((double)rand() / RAND_MAX);
        Point *jitter = big_triangle + big_tri_i;
        points[i].x = (jitter->x - points[i - 1].x) / 2 + points[i - 1].x;
        points[i].y = (jitter->y - points[i - 1].y) / 2 + points[i - 1].y;
    }
}

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

void _draw_point(cairo_t *cr, Point *p)
{
    cairo_arc(cr, p->x, p->y, POINT_RADIUS, 0.0, 2 * G_PI);
    cairo_stroke(cr);
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

    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_paint(cr);

    cairo_set_source_rgb(cr, point_color.r, point_color.g, point_color.b);

    for (int i = 0; i < 3; i++)
        _draw_point(cr, big_triangle + i);

    for (int i = 0; i < slider_value; i++)
        _draw_point(cr, points + i);
}
