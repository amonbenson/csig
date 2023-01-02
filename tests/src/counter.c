#include "counter.h"
#include <stdlib.h>


counter_t *counter_new(void) {
    counter_t *counter = malloc(sizeof(counter_t));

    CS_SIGNAL_INIT(counter, value_changed);
    CS_SLOT_INIT(counter, set);
    CS_SLOT_INIT(counter, increase);
    CS_SLOT_INIT(counter, reset);
    counter->value = 0;

    return counter;
}

void counter_free(counter_t *counter) {
    free(counter);
}


int counter_set(counter_t *counter, void *emitter, int value) {
    if (counter->value == value) return 0;

    counter->value = value;
    return CS_EMIT(counter, value_changed, value);
}

int counter_increase(counter_t *counter, void *emitter) {
    return counter_set(counter, emitter, counter->value + 1);
}

int counter_reset(counter_t *counter, void *emitter) {
    return counter_set(counter, emitter, 0);
}
