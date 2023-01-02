#include <stdlib.h>
#include <stdio.h>
#include "counter.h"


typedef struct {
    CS_SLOT(counter_changed);

    counter_t *counter;
} application_t;


application_t *app;


int app_counter_changed(application_t *app, counter_t *counter, int value) {
    printf("Counter value changed to %d\n", value);
    return 0;
}


application_t *application_new(void) {
    application_t *app = malloc(sizeof(application_t));

    app->counter = counter_new();

    CS_CONNECT(app->counter, value_changed, app, counter_changed);

    return app;
}

void application_free(application_t *app) {
    counter_free(app->counter);
    free(app);
}


int main(int argc, char **argv) {
    // create the demo app
    app = application_new();

    // update the counter a few times
    counter_set(app->counter, NULL, 10);
    counter_reset(app->counter, NULL);
    counter_increase(app->counter, NULL);

    return 0;
}
