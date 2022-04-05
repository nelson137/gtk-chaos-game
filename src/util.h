#ifndef _UTIL_H
#define _UTIL_H

#include <sys/time.h>

#include "glib.h"

typedef struct _Point
{
    double x, y;
} Point;

double dbl_abs(double x);

gboolean dbl_approx_eq(double a, double b);

double elapsed_ms(struct timeval *a, struct timeval *b);

gboolean point_in_triangle(Point *p, Point *t1, Point *t2, Point *t3);

double triangle_area(Point *p1, Point *p2, Point *p3);

#endif
