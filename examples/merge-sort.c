#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "list.h"

// origin is 256
static uint16_t values[256];

void print_list(struct list_head *head)
{
    struct listitem *item;
    list_for_each_entry (item, head, list) {
        printf("%d ", item->i);
    }
    printf("\n");
}

void devide_list(struct list_head *head,
                 struct list_head *left_h,
                 struct list_head *right_h,
                 uint16_t n)
{
    struct list_head *cur = head->next, *next = head->next->next;
    size_t i = 0;
    for (i = 0; i < n; i++) {
        list_move_tail(cur, left_h);
        cur = next;
        next = next->next;
    }
    list_splice_tail(head, right_h);
}


int sort_sigle_item(struct listitem *item_l,
                    struct list_head *head,
                    struct list_head *list_r)
{
    struct listitem *item_r, *is = NULL;

    list_for_each_entry_safe (item_r, is, list_r, list) {
        if (item_l->i > item_r->i) {
            list_del(&item_r->list);
            // printf("%d, ", item_r->i);
            list_move_tail(&item_r->list, head);
            // printf("right: ");
            // print_list(list_r);
        } else {
            return 1;
        }
    }
    return 0;
}

void sort_left_right(struct list_head *head,
                     struct list_head *list_l,
                     struct list_head *list_r)
{
    struct listitem *item_l, *is = NULL;

    list_for_each_entry_safe (item_l, is, list_l, list) {
        if (sort_sigle_item(item_l, head, list_r)) {
            list_del(&item_l->list);
            // printf("%d, ", item_l->i);
            list_move_tail(&item_l->list, head);
            // printf("left: ");
            // print_list(list_l);
        }
    }

    if (list_empty(list_l)) {
        list_splice_tail(list_r, head);
    }
    if (list_empty(list_r)) {
        list_splice_tail(list_l, head);
    }
    printf("\n");
    print_list(head);
}


void merge_sort(struct list_head *head, uint16_t n)
{
    struct list_head list_l, list_r;
    INIT_LIST_HEAD(&list_l);
    INIT_LIST_HEAD(&list_r);


    if (n < 2)
        return;

    // split into 2
    n = n / 2;
    devide_list(head, &list_l, &list_r, n);
    merge_sort(&list_l, n);
    merge_sort(&list_r, n);
    INIT_LIST_HEAD(head);
    printf("Ready to sort: \n");
    printf("left: ");
    print_list(&list_l);
    printf("right: ");
    print_list(&list_r);
    sort_left_right(head, &list_l, &list_r);
}

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
    print_list(&testlist);
    merge_sort(&testlist, ARRAY_SIZE(values));

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
