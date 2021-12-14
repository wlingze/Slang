
#ifndef OBJECT_OBJECT 

struct object;
struct class;

#define OBJECT_HEADER       \
    struct object *next;    \
    struct class *class;    \
    int flag;

typedef struct object {
    OBJECT_HEADER
} object_t;

#define OBJECT_OBJECT 
#endif 