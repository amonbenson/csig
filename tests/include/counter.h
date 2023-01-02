#pragma once

#include "csig.h"


CS_SIGNAL_DEFINE(value_changed, int);


typedef struct {
    CS_SIGNAL(value_changed);

    CS_SLOT(set);
    CS_SLOT(increase);
    CS_SLOT(reset);

    int value;
} counter_t;


counter_t *counter_new(void);
void counter_free(counter_t *counter);

int counter_set(counter_t *counter, void *emitter, int value);
int counter_increase(counter_t *counter, void *emitter);
int counter_reset(counter_t *counter, void *emitter);
