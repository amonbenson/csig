#include "counter.h"
#include <stdlib.h>


counter_t *counter_new(void) {
    counter_t *counter = malloc(sizeof(counter_t));

    CS_SIGNAL_INIT(counter, value_changed);
    CS_SLOT_INIT_ANON(counter, set);
    CS_SLOT_INIT_ANON(counter, increase);
    CS_SLOT_INIT_ANON(counter, reset);
    counter->value = 0;

    return counter;
}

void counter_free(counter_t *counter) {
    free(counter);
}


int counter_set(counter_t *counter, int value) {
    if (counter->value == value) return 0;

    counter->value = value;
    return (
        {
            int _ret = 0;
            __cs_slot_t *_slot = (counter)->__CS_SIGNAL_MEMBER(value_changed)._rootslot;
            while (_slot)
            {
                if (_slot->_anon)
                {
                    _ret = ((__CS_CALLBACK_TYPE_ANON(value_changed))_slot->_callback)(_slot->_target, value);
                }
                else
                {
                    _ret = ((__CS_CALLBACK_TYPE(value_changed))_slot->_callback)(_slot->_target, counter, value);
                }
                if (_ret != 0)
                    break;
                _slot = _slot->_next;
            }
            _ret;
        });
    //return CS_EMIT(counter, value_changed, value);
}

int counter_increase(counter_t *counter) {
    return counter_set(counter, counter->value + 1);
}

int counter_reset(counter_t *counter) {
    return counter_set(counter, 0);
}
