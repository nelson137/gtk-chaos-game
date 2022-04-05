#ifndef _MODEL_H
#define _MODEL_H

#include <sys/time.h>

#include "gtk/gtk.h"

typedef struct _Model
{
    GtkDrawingArea *drawing_area;
    gboolean cursor_in_draw;
    int draw_cursor_x;
    int draw_cursor_y;
    struct timeval last_draw_click;
    gboolean valid_draw_click;
    int point_count;
} Model;

Model *model_new();

void model_free(Model **model);

#endif
