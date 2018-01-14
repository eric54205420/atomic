﻿#include <stdio.h>
#include <assert.h>

#include "atom.h"

//
// winds 为 stdatomic.h 写的项目 
//
int main(int argc, char * argv[]) {
    char * some_ptr = "Hello, 世界";
    atomic_p_t atomic_ptr_to_int;
    atomic_store_p(&atomic_ptr_to_int, some_ptr, ATOMIC_RELAXED);
    char * prev_value = atomic_exchange_p(&atomic_ptr_to_int, NULL, ATOMIC_ACQ_REL);
    assert(some_ptr == prev_value);
    
    printf("%s\n", prev_value);

    // 自旋锁测试
    atom_t o = 0;
    printf("atom_t o -> %ld\n", o);

    if (atom_trylock(o)) {
        printf("atom_trylock get lock o = %ld\n", o);
        atom_unlock(o);
    } else {
        printf("atom_trylock no get lock o = %ld\n", o);
    }

    printf("atom_t o -> %ld\n", o);

    return 0;
}
