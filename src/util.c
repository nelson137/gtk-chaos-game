#include <sys/time.h>

#include "glib.h"

#include "util.h"

/**
 * Return the absolute value of `x`.
 */
double dbl_abs(double x)
{
    return x < 0 ? -1 * x : x;
}

/**
 * Return whether `a == b` within some epsilon value.
 */
gboolean dbl_approx_eq(double a, double b)
{
    return dbl_abs(a - b) < 0.0001;
}

/**
 * Return the difference between times `a` and `b` in milliseconds.
 */
double elapsed_ms(struct timeval *a, struct timeval *b)
{
    int elapsed = 1000.0 * ((double)b->tv_sec - (double)a->tv_sec);
    elapsed += 0.001 * ((double)b->tv_usec - (double)a->tv_usec);
    return elapsed;
}

/**
 * Return whether `p` is inside of a triangle with points `t1`, `t2`, and `t3`.
 */
gboolean point_in_triangle(Point *p, Point *t1, Point *t2, Point *t3)
{
    double t_area = triangle_area(t1, t2, t3);
    double area_p12 = triangle_area(p, t1, t2);
    double area_p23 = triangle_area(p, t2, t3);
    double area_p13 = triangle_area(p, t1, t3);
    return dbl_approx_eq(area_p12 + area_p23 + area_p13, t_area);
}

/**
 * Return the area of the triangle with points `p1`, `p2`, and `p3`.
 */
double triangle_area(Point *p1, Point *p2, Point *p3)
{
    double area_doubled =
        p1->x * (p2->y - p3->y) +
        p2->x * (p3->y - p1->y) +
        p3->x * (p1->y - p2->y);
    return dbl_abs(area_doubled / 2);
}
