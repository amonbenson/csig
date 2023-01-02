#pragma once


#ifndef CS_DEFAULT_CALLBACK
    #define CS_DEFAULT_CALLBACK(owner, slot) owner ## _ ## slot
#endif


#ifndef NULL
    #define NULL ((void *) 0)
#endif


#define __CONCATENATE_IMPL(a, b) a ## b
#define __CONCATENATE(a, b) __CONCATENATE_IMPL(a, b)


typedef struct __cs_slot_t {
    void *_target;
    int _anon;
    int (*_callback)();
    struct __cs_slot_t *_next;
} __cs_slot_t;

typedef struct {
    __cs_slot_t *_rootslot;
} __cs_signal_t;


#define __CS_CALLBACK_TYPE(name) __cs_callback_ ## name ## _t
#define __CS_CALLBACK_TYPE_ANON(name) __cs_callback_ ## name ## _anon_t

#define CS_SIGNAL_DEFINE(name, args...) \
    typedef int (*__CS_CALLBACK_TYPE(name))(void *target, void *emitter, ## args); \
    typedef int (*__CS_CALLBACK_TYPE_ANON(name))(void *target, ## args)

#define __CS_SIGNAL_MEMBER(name) __cs_signal_ ## name

#define CS_SIGNAL(name) \
    __cs_signal_t __CS_SIGNAL_MEMBER(name);

#define CS_SIGNAL_INIT(owner, name) do { \
    (owner)->__CS_SIGNAL_MEMBER(name)._rootslot = NULL; \
} while (0)


#define __CS_SLOT_MEMBER(name) __cs_slot_ ## name

#define CS_SLOT(name) \
    __cs_slot_t __CS_SLOT_MEMBER(name);

#define __CS_SLOT_INIT(owner, name, anon, callback, ...) do { \
    (owner)->__CS_SLOT_MEMBER(name)._target = owner; \
    (owner)->__CS_SLOT_MEMBER(name)._anon = anon; \
    (owner)->__CS_SLOT_MEMBER(name)._callback = (int (*)()) (callback); \
    (owner)->__CS_SLOT_MEMBER(name)._next = NULL; \
} while (0)
#define CS_SLOT_INIT(owner, name, callback...) \
    __CS_SLOT_INIT(owner, name, 0, ## callback, CS_DEFAULT_CALLBACK(owner, name))
#define CS_SLOT_INIT_ANON(owner, name, callback...) \
    __CS_SLOT_INIT(owner, name, 1, ## callback, CS_DEFAULT_CALLBACK(owner, name))


#define __CS_CONNECT(head, add) do { \
    __cs_slot_t *_tmp; \
    (add)->_next = NULL; \
    if (head) { \
        _tmp = (head); \
        while (_tmp->_next) _tmp = _tmp->_next; \
        _tmp->_next = (add); \
    } else { \
        (head) = (add); \
    } \
} while (0);
#define CS_CONNECT(emitter, signal, target, slot) \
    __CS_CONNECT((emitter)->__CS_SIGNAL_MEMBER(signal)._rootslot, &(target)->__CS_SLOT_MEMBER(slot))



#define CS_EMIT(emitter, signal, args...) ({ \
    int _ret = 0; \
    __cs_slot_t *_slot = (emitter)->__CS_SIGNAL_MEMBER(signal)._rootslot; \
    while (_slot) { \
        if (_slot->_anon) { \
            _ret = ((__CS_CALLBACK_TYPE_ANON(signal)) _slot->_callback)(_slot->_target, ## args); \
        } else { \
            _ret = ((__CS_CALLBACK_TYPE(signal)) _slot->_callback)(_slot->_target, emitter, ## args); \
        } \
        if (_ret != 0) break; \
        _slot = _slot->_next; \
    } \
    _ret; \
})
