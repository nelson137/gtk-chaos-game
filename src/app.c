#include <stdlib.h>

#include "cairo.h"
#include "gtk/gtk.h"

#include "model.h"
#include "util.h"

#include "app.h"

#define POINT_RADIUS 1.0

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

gboolean point_in_big_triangle(double x, double y)
{
    Point p;
    p.x = x;
    p.y = y;
    return point_in_triangle(
        &p, big_triangle, big_triangle + 1, big_triangle + 2);
}

void set_initial_point(double x, double y)
{
    points[0].x = x;
    points[0].y = y;
}

void generate_points()
{
    for (int i = 1; i < NUM_POINTS; i++)
    {
        int big_tri_i = 3 * ((double)rand() / RAND_MAX);
        Point *jitter = big_triangle + big_tri_i;
        points[i].x = (jitter->x - points[i - 1].x) / 2 + points[i - 1].x;
        points[i].y = (jitter->y - points[i - 1].y) / 2 + points[i - 1].y;
    }
}

gboolean on_drawing_area_tick(
    GtkWidget *self,
    GdkFrameClock *clock,
    gpointer data)
{
    gtk_widget_queue_draw(self);
    return G_SOURCE_CONTINUE;
}

void on_motion_enter(
    GtkEventControllerMotion *self,
    gdouble x,
    gdouble y,
    gpointer data)
{
    Model *model = (Model *)data;
    model->cursor_in_draw = TRUE;
    model->draw_cursor_x = (int)x;
    model->draw_cursor_y = (int)y;
}

void on_motion_update(
    GtkEventControllerMotion *self,
    gdouble x,
    gdouble y,
    gpointer data)
{
    Model *model = (Model *)data;
    model->draw_cursor_x = (int)x;
    model->draw_cursor_y = (int)y;
}

void on_motion_leave(GtkEventControllerMotion *self, gpointer data)
{
    Model *model = (Model *)data;
    model->cursor_in_draw = FALSE;
}

void on_drawing_area_click_released(
    GtkGestureClick *self,
    gint n_press,
    gdouble x,
    gdouble y,
    gpointer data)
{
    Model *model = (Model *)data;
    gettimeofday(&model->last_draw_click, NULL);
    if ((model->valid_draw_click = point_in_big_triangle(x, y)))
    {
        set_initial_point(x, y);
        generate_points();
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

    struct timeval now;
    gettimeofday(&now, NULL);
    double ms_since_invalid_click =
        elapsed_ms(&model->last_draw_click, &now);

    if (!model->valid_draw_click && ms_since_invalid_click < 2000.0)
    {
        cairo_font_extents_t extents;
        cairo_font_extents(cr, &extents);

        static double text_margin = 8.0;
        double text_x = text_margin;
        double text_y = extents.height + text_margin;
        cairo_move_to(cr, text_x, text_y);
        cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
        cairo_show_text(
            cr, "Error: New initial point must be inside of the triangle");
        cairo_stroke(cr);

        if (ms_since_invalid_click < 175.0 ||
            (350.0 <= ms_since_invalid_click && ms_since_invalid_click < 525.0))
        {
            cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 0.5);
            static double dashes[] = {12.0};
            cairo_set_dash(cr, dashes, 1, 0.0);
            cairo_move_to(cr, big_triangle[2].x, big_triangle[2].y);
            cairo_line_to(cr, big_triangle[0].x, big_triangle[0].y);
            cairo_line_to(cr, big_triangle[1].x, big_triangle[1].y);
            cairo_line_to(cr, big_triangle[2].x, big_triangle[2].y);
            cairo_stroke(cr);
        }
    }

    if (model->cursor_in_draw)
    {
        static double text_margin = 6.0;
        double text_x = text_margin;
        double text_y = (double)height - text_margin;
        cairo_move_to(cr, text_x, text_y);

        cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);

        gchar *cursor_pos_text = g_strdup_printf(
            "x=%d, y=%d", model->draw_cursor_x, model->draw_cursor_y);
        cairo_show_text(cr, cursor_pos_text);
        cairo_stroke(cr);
        g_free(cursor_pos_text);
    }
}
