#include <stdio.h>
#include "../src/collections/ccollections.h"


typedef struct
{
    u32 a;
    clist_head list;
} test_clist_t;

void test_clist()
{
    test_clist_t test[10];
    test_clist_t *it;
    clist_head *pos, *n;

    for (u32 i = 0; i < 10; ++i)
    {
        test[i].a = i;
        clist_init(&test[i].list);
    }
    
    clist_add(&test[3].list, &test[0].list);
    clist_add(&test[6].list, &test[3].list);
    clist_add(&test[9].list, &test[6].list);
    clist_del(&test[6].list);
    
    printf("Test 1:\n");
    CLIST_FOR_EACH_ENTRY(it, &test[0].list, list)
    {
        printf("%d, ", it->a);
    }
    printf("\n");

    printf("Test 2:\n");
    CLIST_FOR_EACH_ENTRY_REVERSE(it, &test[0].list, list)
    {
        printf("%d, ", it->a);
    }
    printf("\n");

    clist_add(&test[8].list, &test[9].list);
    
    printf("Test 3:\n");
    CLIST_FOR_EACH(pos, &test[0].list)
    {
        it = CLIST_ENTRY(pos, test_clist_t, list);
        printf("%d, ", it->a);
    }
    printf("\n");

    printf("Test 4:\n");
    CLIST_FOR_EACH_REVERSE_SAFE(pos, n, &test[0].list)
    {
        it = CLIST_ENTRY(pos, test_clist_t, list);
        clist_add(&test[1].list, pos);
        clist_erase(pos);
        printf("%d, ", it->a);
    }
    printf("\n");

    printf("Test 5:\n");
    CLIST_FOR_EACH_REVERSE_SAFE(pos, n, &test[0].list)
    {
        it = CLIST_ENTRY(pos, test_clist_t, list);
        printf("%d, ", it->a);
    }
    printf("\n");

}

int main()
{
    test_clist();
    return 0;
}