#ifndef _APP_H
#define _APP_H

#include "cairo.h"

#include "gtk/gtk.h"

#include "util.h"

#define NUM_POINTS 4096

void set_initial_point(double x, double y);
void generate_points();

gboolean on_drawing_area_tick(
    GtkWidget *self,
    GdkFrameClock *clock,
    gpointer data);

void on_motion_enter(
    GtkEventControllerMotion *self,
    gdouble x,
    gdouble y,
    gpointer data);

void on_motion_update(
    GtkEventControllerMotion *self,
    gdouble x,
    gdouble y,
    gpointer data);

void on_motion_leave(GtkEventControllerMotion *self, gpointer data);

void on_drawing_area_click_released(
    GtkGestureClick *self,
    gint n_press,
    gdouble x,
    gdouble y,
    gpointer data);

char *format_point_count_value(GtkScale *scale, double value, gpointer data);

void on_point_count_change(GtkRange *self, gpointer data);

void on_draw(
    GtkDrawingArea *w,
    cairo_t *cr,
    int width,
    int height,
    gpointer data);

#endif
