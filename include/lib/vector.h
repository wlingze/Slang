
#ifndef LIB_VECTOR

typedef struct vector {
    unsigned int count;
    unsigned int capacity;
    void **data;
} vector_t;

#define VECTOR_INIT_SIZE 0x20

extern void vector_init(vector_t *this);
extern void vector_destruction(vector_t *this);

extern void vector_push(vector_t *this, void *item);
extern void *vector_pop(vector_t *this);

extern void *vector_get(vector_t *this, unsigned int idx);
extern void vector_set(vector_t *this, unsigned int idx, void *item);

#define vector_each(this, i, item) \
    for (i; (i < (this).count) ? (item = (this).data[i], 1) : 0; i++)


#define vector_template(data_t, vector)     \
    struct {                                \
        unsigned int count;                 \
        unsigned int capacity;              \
        data_t **data;                       \
    } vector

#define LIB_VECTOR
#endif // LIB_VECTOR