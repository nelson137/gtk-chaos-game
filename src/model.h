#ifndef _MODEL_H
#define _MODEL_H

#include "gtk/gtk.h"

typedef struct _Model
{
    GtkDrawingArea *drawing_area;
    int point_count;
} Model;

Model *model_new();

void model_free(Model **model);

void model_flush(Model *model);

#endif
