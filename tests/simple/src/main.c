#include <stdlib.h>
#include <stdio.h>
#include "bdd-for-c.h"
#include "counter.h"


typedef struct {
    CS_SLOT(counter_changed);

    counter_t *counter;

    int counter_changed_invokations;
} application_t;


int app_counter_changed(application_t *app, counter_t *counter, int value) {
    app->counter_changed_invokations++;
    return 0;
}


application_t *application_new(void) {
    application_t *app = malloc(sizeof(application_t));

    CS_SLOT_INIT(app, counter_changed);
    app->counter = counter_new();
    app->counter_changed_invokations = 0;

    CS_CONNECT(app->counter, value_changed, app, counter_changed);

    return app;
}

void application_free(application_t *app) {
    counter_free(app->counter);
    free(app);
}


spec("simple") {
    // create the demo app
    static application_t *app;

    before_each() {
        app = application_new();
    }

    after_each() {
        application_free(app);
    }

    // update the counter a few times
    describe("counter") {
        it("should provide working atomic methods") {
            counter_set(app->counter, 10);
            expect(app->counter->value) to_be(10);

            counter_increase(app->counter);
            expect(app->counter->value) to_be(11);

            counter_reset(app->counter);
            expect(app->counter->value) to_be(0);
        }

        it("should emit a changed signal") {
            counter_increase(app->counter);
            expect(app->counter_changed_invokations) to_be(1);

            counter_reset(app->counter);
            counter_reset(app->counter); // second reset should NOT invoke another callback
            expect(app->counter_changed_invokations) to_be(2);
        }
    }
}
