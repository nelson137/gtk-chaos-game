#include <stdlib.h>

#include "gtk/gtk.h"

#include "model.h"

Model *model_new()
{
    Model *model = malloc(sizeof(Model));
    model->drawing_area = NULL;
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

void model_flush(Model *model)
{
    gtk_widget_queue_draw(GTK_WIDGET(model->drawing_area));
}