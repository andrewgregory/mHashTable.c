#include "tap.c/tap.c"

#include "mht.c"

int main(void) {
    mht_t *h = mht_new(1); /* force hash collision */

    tap_plan(18);

#define CHECK_INSERT(key, val) \
    tap_is_int(mht_set_value(h, key, val), 1, "set %s => %s", key, val)

#define CHECK_KEY(key, val) do { \
    mht_item_t *i = mht_get_item(h, key); \
    if(tap_ok(i != NULL, "fetch %s", key)) \
        { tap_is_str(i->value, val, "%s => %s", key, val); } \
    else \
        { tap_ok(0, "%s => %s", key, val); } \
} while (0)

    CHECK_INSERT("foo", "bar");
    CHECK_INSERT("bar", "baz");
    CHECK_INSERT("baz", "quux");
    CHECK_INSERT("quux", "foo");

    CHECK_KEY("foo", "bar");
    CHECK_KEY("bar", "baz");
    CHECK_KEY("baz", "quux");
    CHECK_KEY("quux", "foo");

    /* overwrite existing key */
    CHECK_INSERT("foo", "baz");
    CHECK_KEY("foo", "baz");

#undef CHECK_INSERT
#undef CHECK_KEY

    tap_ok(mht_delete_item(h, "baz"), "delete %s", "baz");
    tap_is_int(mht_contains(h, "baz"), 0, "fetch %s => NULL", "baz");
    tap_is_int(mht_delete_item(h, "baz"), 0, "delete %s", "baz");

    mht_free(h);

    return 0;
}
