
#include "lib/gift.h"
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>

gift_t * gift_init(char *name, u_int64_t item){
    gift_t *this = malloc(sizeof(gift_t));
    this->name = name;
    this->item = item;
}