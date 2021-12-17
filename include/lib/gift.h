
#ifndef LIB_GIFT_H
#define LIB_GIFT_H

#include <sys/types.h>
typedef struct gift {
    char *name;
    u_int64_t item;
} gift_t;

gift_t * gift_init(char *name, u_int64_t item);

#endif 