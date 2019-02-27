#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "list.h"

static uint16_t values[256];

int main(void)
{
    printf("merge-sort\n");
    struct list_head testlist;
    struct listitem *item, *is = NULL;
    size_t i;

    random_shuffle_array(values, (uint16_t) ARRAY_SIZE(values));

    INIT_LIST_HEAD(&testlist);

    assert(list_empty(&testlist));

    /* Add values into array */
    for (i = 0; i < ARRAY_SIZE(values); i++) {
        item = (struct listitem *) malloc(sizeof(*item));
        item->i = values[i];
        list_add_tail(&item->list, &testlist);
    }

    /* merge sort */

    /* clean list */
    i = 0;
    list_for_each_entry_safe (item, is, &testlist, list) {
        list_del(&item->list);
        free(item);
        i++;
    }

    assert(i == ARRAY_SIZE(values));
    assert(list_empty(&testlist));
    return 0;
}
