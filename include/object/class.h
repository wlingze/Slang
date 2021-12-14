
#ifndef OBJECT_CLASS
#include "object/object.h"

typedef struct class {
    OBJECT_HEADER;
    char * name;
    void (*gc_free)(object_t *);
    void (*gc_mark)(object_t *);
} class_t;



#define OBJECT_CLASS
#endif // OBJECT_CLASS