#include"skip_list.h"

int main() {
    skip_list_t l;
    init_list(&l);
    insert_update(&l, 2, 12);
    insert_update(&l, 6, 32);
    insert_update(&l, 4, 72);
    insert_update(&l, 3, 42);
    print(&l);
    destroy(&l);
    return 0;
}
