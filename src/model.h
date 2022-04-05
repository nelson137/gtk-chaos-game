#ifndef _MODEL_H
#define _MODEL_H

#include "gtk/gtk.h"

typedef struct _Model
{
    GtkDrawingArea *drawing_area;
    gboolean cursor_in_draw;
    int draw_cursor_x;
    int draw_cursor_y;
    int point_count;
} Model;

Model *model_new();

void model_free(Model **model);

#endif
