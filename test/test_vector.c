
#include "lib/vector.h"
#include <stdio.h>
#include <stdlib.h>

char *string1 = "hellow";
char *string2 = "aarstarst";

int main(){
    vector_t * vector = malloc(sizeof(vector_t));
    vector_init(vector);
    vector_push(vector, string1);
    vector_push(vector, string2);

    int i=0;
    void *item;
    vector_each(*vector, i, item){
        printf("%s\n", item);
    }

}