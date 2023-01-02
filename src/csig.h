#include <stdio.h>
#include "csig.h"


#define _STRINGIFY(x) #x
#define STRINGIFY(x) _STRINGIFY(x)


CS_SIGNAL_DEFINE(midi_recv, int a, int b);


typedef struct {
    CS_SIGNAL(midi_recv);
} midi_t;



typedef struct {
    CS_SLOT(midi_recv);
} user_t;



int user_midi_recv(user_t *user, midi_t *midi, int a, int b) {
    printf("user_midi_recv called!\n");
    return a + b;
}



int main() {
    midi_t midi_obj;
    user_t user_obj;
    
    midi_t *midi = &midi_obj;
    user_t *user = &user_obj;


    // init signal
    CS_SIGNAL_INIT(midi, midi_recv);


    // connect slot
    CS_CONNECT(midi, midi_recv, user, midi_recv);


    // emit signal
    int result = CS_EMIT(midi, midi_recv, 1, 2);
    printf("result: %d\n", result);

    return 0;
}


