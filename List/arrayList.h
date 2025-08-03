#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int maxSize;
    int listSize;
    int curr;
    int *array;
    // declare variables you need
} arrayList;

void init(arrayList* list)
{
    // implement initialization
    list->curr = 0; list->listSize = 0; list->maxSize = 2;
    list->array = (int*)malloc(list->maxSize*sizeof(int));
    
}

void free_list(arrayList* list)
{
    // implement destruction of list
    free(list->array);
}

void increase_capacity(arrayList* list)
{
    // implement capacity increase
    int prev_size = list->maxSize;
    list->maxSize *=2;
    list->array = (int*)realloc(list->array, list->maxSize*sizeof(int));
    printf("Capacity increased from %d to %d\n", prev_size, list->maxSize);
}

void decrease_capacity(arrayList* list)
{
    // implement capacity decrease
    int prev_size = list->maxSize;
    list->maxSize /=2;
    list->array = (int*)realloc(list->array,list->maxSize * sizeof(int));
    printf("Capacity decreased from %d to %d\n", prev_size, list->maxSize);
}

void print(arrayList* list)
{
    // implement list printing
    if(list->listSize == 0){
        printf("[ . ]\n");
        return;
    }
    printf("[ ");
    for(int i = 0; i<list->listSize; i++){
        if(i==list->curr-1)printf("%d| ", list->array[i]);
        else printf("%d ", list->array[i]);
    }
    printf("]\n");
}

void insert(int item, arrayList* list)
{
    // implement insert function
    if(list->listSize+1>(list->maxSize)/2){
        increase_capacity(list);
    }int i = list->listSize;
    for(; i>list->curr; i--){
        list->array[i]= list->array[i-1];
    }
    list->array[list->curr] = item;
    list->listSize++;
    list->curr++;
    print(list);
}

int delete_cur(arrayList* list)
{
    // implement deletion of current index function
    if (list->listSize == 0) {
        return -1;
    }
    int answer = list->array[list->curr - 1];
    for(int i = list->curr-1; i<list->listSize-1; i++){
        list->array[i]= list->array[i+1];
    }
    if(list->listSize-1 < (list->maxSize)/4){
        decrease_capacity(list);
    }
    if(list->curr==list->listSize)list->curr--;
    list->listSize--;
    //list->curr;
    print(list);
    return answer;
}

void append(int item, arrayList* list)
{
    // implement append function
    if(list->listSize+1>(list->maxSize)/2){
        increase_capacity(list);
    }
    list->array[list->listSize] = item;
    if(list->listSize == 0)list->curr++;
    list->listSize++;
    print(list);
}

int size(arrayList* list)
{
    // implement size function
    return list->listSize;
}

void prev(int n, arrayList* list)
{
    // implement prev function
    if(list->curr-n <0)list->curr = 0;
    else list->curr -= n;
    print(list);
}

void next(int n, arrayList* list)
{
    // implement next function
    if(list->curr+n >=list->listSize)list->curr = list->listSize;
    else list->curr += n;
    print(list);
}

int is_present(int n, arrayList* list)
{
    // implement presence checking function
    for(int i = 0; i<list->listSize; i++){
        if(list->array[i]==n){
            return 1; 
        }
    }
    return 0;
}

void clear(arrayList* list)
{
    // implement list clearing function
    list->array = (int*)realloc( list->array, 2*sizeof(int));
    list->curr = 0; list->maxSize = 2; list->listSize =0;
    print(list);
}

void delete_item(int item, arrayList* list)
{
    // implement item deletion function
    int index = -1;
    for(int i = 0; i<list->listSize; i++){
        if(list->array[i]==item){index = i; break;}
    }

    if(index==-1){
        printf("%d not found\n", item);
    }else{
        for(int i = index; i<list->listSize-1; i++){
            list->array[i]= list->array[i+1];
        }
        if(list->listSize-1 < (list->maxSize)/4){
            decrease_capacity(list);
        }
        list->listSize--;
        //list->curr--;
        if(list->curr>list->listSize)list->curr = list->listSize;
        print(list);
    }
}

void swap_ind(int ind1, int ind2, arrayList* list)
{
    // implement swap function
    if (ind1 < 0 || ind1 >= list->listSize || ind2 < 0 || ind2 >= list->listSize) {
        printf("Invalid indices\n");
        return;
    }
    int temp = list->array[ind1];
    list->array[ind1] = list->array[ind2];
    list->array[ind2] = temp;
    print(list);
}

// you can define helper functions you need