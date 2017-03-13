#include "tap.c/tap.c"

#include "mhashtable.c"

/* build, loop through, and destroy a large hash to catch significant
 * performance hits */

int main(void) {
    size_t i, limit = 100000;
    mht_t *h = mht_new(limit / 4);
    mht_item_t *it = NULL;

    tap_plan(1);

    for(i = 0; i < limit; i++) {
        char buf[10], *c;
        sprintf(buf, "%zd", i);
        c = strdup(buf);
        mht_set_value(h, c, c);
    }

    for(i = 0; i < limit; i++) {
        char buf[10];
        sprintf(buf, "%zd", i);
        if(!mht_get_value(h, buf)) { break; }
    }
    tap_ok(i == limit, "%zd", i);

    while((it = mht_next_item(h, it))) {
        free((char*) it->key);
    }

    mht_free(h);

    return 0;
}
