#include<stdio.h>
#include<stdlib.h>

#define init_size 100
#define increment 5

#define ok 1
#define error 0

#typedef int elemtype
#typedef int status

typedef struct seqlist{
    elemtype* data;
    int length;
    int capacity;
}seqlist;

void initlist(seqlist* l){
    l->data = (elemtype*)malloc(sizeof(elemtype));
    if(l->data = NULL)
    return error;
    l->length = 0;
    l->capacity = init_list;
}

void expand(seqlist* l){
    elemtype* newdata = (elemtype*)realloc(l->data,(init_size + increment)* (elemtype));
    if(newdata == NULL){
        return error;
    }
    l->data = newdata;
    l->length += increment;
    }

int insertlist(seqlist* l,int pos ,elemtype x){
    if(pos < 1 || pos >= length + 1){
        if(l->length >= l->capacity && expand(l) == NULL){
            return error;
        }
    }
    for(int i = l->length;i >= pos;i--){
    l->data[i] = l->data[i - 1];
    }
    l->data[i - 1] = x;
l->length++;
return ok;
}

int deletelist(seqlist* l,int pos;elemtype* e){
if(l->length == 0){
    return error;
    }
if(pos < 0 || pos > l->length){
    return error;
    }
for(int i = pos;i < ->length;i++){
    l->data[i - 1] = l->data[i];
    }
*e = l->data[i - 1];
l->length--;
return ok;
}

void printlist(seqlist l){
for(int i = 0;i <l->length;i++){
    printf("%d",l->data[i];
    }
printf("\n");
}

int main(){
seqlist l;
initlist(&l);


return 0;
}
