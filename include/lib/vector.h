
#ifndef LIB_VECTOR
#define LIB_VECTOR

#define VECTOR_INIT_SIZE 0x20
#include <stddef.h>


#define vector_each(this, i, item) \
    for ((i); ((i) < (this).count) ? ((item) = (this).data[(i)], 1) : 0; (i)++)


#define vector_template(data_t, vector)     \
    struct {                                \
        unsigned int count;                 \
        unsigned int capacity;              \
        data_t *data;                       \
    } vector

#define vector_init(this)                                           \
    do {                                                            \
        (this)->count = 0;                                          \
        (this)->capacity = 0;                                       \
        (this)->data = NULL;                                        \
    } while (0)

#define vector_get(this, index)                             \
    ({                                                      \
        assert((index) >= 0);                               \
        assert((index) < (this).count);                    \
        (this).data[(index)];                              \
    }) 

#define vector_set(this, index, item)                             \
    ({                                                      \
        assert((index) >= 0);                               \
        assert((index) < (this)->count);                    \
        (this)->data[(index)] = (item);                              \
    }) 

#define vector_push_back(this, item)                                \
    do {                                                            \
        int item_size = sizeof((this)->data[0]);                    \
        int vector_size;                                            \
        if ((this)->capacity == 0) {                                \
            (this)->capacity = 2;                                   \
            vector_size = (this)->capacity * item_size;             \
            (this)->data = malloc(vector_size);                     \
        }                                                           \
        if ((this)->count >= (this)->capacity) {                    \
            (this)->capacity *= 2;                                  \
            vector_size = (this)->capacity * item_size;             \
            (this)->data = realloc((this)->data, vector_size);      \
        }                                                           \
        (this)->data[(this)->count] = (item);                       \
        (this)->count++;                                            \
    } while (0)

#endif // LIB_VECTOR