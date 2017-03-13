/*
 * Copyright 2014 Andrew Gregory <andrew.gregory.8@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Project URL: http://github.com/andrewgregory/mHashTable.c
 */

#ifndef MHASHTABLE_H
#define MHASHTABLE_H

#define MHT_DEFAULT_SIZE 128

typedef size_t (*mht_hashfn_t)(const char *key);
typedef int (*mht_cmpfn_t)(const char *key1, const char *key2);

typedef struct mht_item_t { 
    size_t hash;
    const char *key;
    const void *value;
    struct mht_item_t *next;
} mht_item_t;

typedef struct mht_t {
    mht_hashfn_t hashfn;
    mht_cmpfn_t cmpfn;
    size_t size;
    mht_item_t **buckets;
} mht_t;

size_t mht_hashfn_sdbm(const char *key);
mht_t *mht_new(size_t buckets);
mht_item_t *mht_next_item(mht_t *table, mht_item_t *item);
void mht_free(mht_t *mht);
mht_item_t *mht_get_item(mht_t *mht, const char *key);
int mht_delete_item(mht_t *mht, const char *key);
int mht_set_value(mht_t *mht, const char *key, const void *value);
void *mht_get_value(mht_t *mht, const char *key);
int mht_contains(mht_t *mht, const char *key);

#endif /* MHASHTABLE_H */
