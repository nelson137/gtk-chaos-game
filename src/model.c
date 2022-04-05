#include <stdlib.h>

#include "gtk/gtk.h"

#include "model.h"

Model *model_new()
{
    Model *model = malloc(sizeof(Model));
    model->drawing_area = NULL;
    model->cursor_in_draw = FALSE;
    model->draw_cursor_x = 0;
    model->draw_cursor_y = 0;
    model->point_count = 0;
    return model;
}

void model_free(Model **model)
{
    if (model == NULL || *model == NULL)
        return;
    free(*model);
    *model = NULL;
}
