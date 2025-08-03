#include <stdio.h>
#include <stdlib.h>

typedef struct node //  important
{
    int element;
    struct node* next;
    struct node* prev;
} node;

typedef struct 
{
    // declare head, tail, cur and other variables you need
    node *head;
    node *tail;
    node *curr;
    int list_size;

} linkedList;

void init(linkedList* list)
{
    // implement initialization
    list->head = NULL; 
    list->curr = NULL;
    list->tail = NULL;
    list->list_size = 0;
}

void free_list(linkedList* list)
{
    // implement destruction of list
    node *temp;
    while(list->curr!=NULL){
        temp = list->curr;
        list->curr = list->curr->prev;
        free(temp);
    }
}

void print(linkedList* list)
{
    // implement list printing
    if(list->list_size==0){
        printf("[ . ]\n");
        return;
    }else if(list->list_size==1){
        printf("[ %d| ]\n", list->head->element);
        return;
    }
    node *temp;
    temp = list->head;
    printf("[ ");
    while(temp!=NULL){
        if(temp==list->curr) printf("%d| ", temp->element);
        else printf("%d ", temp->element);
        temp = temp->next;
    }
    printf("]\n");
}

void insert(int item, linkedList* list)
    {// implement insert function
    node *newNode = (node*)malloc(sizeof(node)); 
    newNode->element = item;
    newNode->next = NULL, newNode->prev = NULL;
    if(list->curr!=NULL){
        if(list->curr==list->tail){
            list->tail = newNode;
            list->curr->next = list->tail;
            list->tail->prev = list->curr;
            list->curr = list->tail;
        }else{
            node* curr_next = list->curr->next;
            newNode->next = curr_next;
            curr_next->prev = newNode;
            list->curr->next = newNode;
            newNode->prev = list->curr;
            list->curr = newNode;
        }
    }else{
        if(list->head==NULL){
            list->head = newNode;
            list->tail = newNode;
        }else{
            list->tail = newNode;
            list->head->next = list->tail;
            list->tail->prev = list->head;
            list->curr = newNode;
        }
    }
    list->list_size++;
    print(list);
}

int delete_cur(linkedList* list)
{
    // implement deletion of current index function
    int item ;
    if(list->curr == list->head){
        node* temp = list->head;
        node* second_one = list->head->next;
        list->head = second_one;
        list->curr = second_one;
        if(second_one!=NULL)second_one->prev = NULL;
        else list->tail = NULL;
        item = temp->element;
        list->list_size--;
        free(temp);
        print(list);
        return item;
    }else if(list->curr ==list->tail){
        node *temp = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        item = temp->element;
        list->curr = list->tail;
        list->list_size--;
        free(temp);
        print(list);
        return item;

    }
    else{
        node* temp = list->curr;
        node* prev_curr = list->curr->prev;
        node* post_curr = list->curr->next;
        prev_curr->next = post_curr;
        post_curr->prev = prev_curr;
        list->curr = post_curr;
        list->list_size--;
        item = temp->element;
        free(temp);
        print(list);
        return item;
    }
}

void append(int item, linkedList* list)
{
    // implement append function
    node* temp = (node*)malloc(sizeof(node));
    temp->element = item;
    if(list->tail==NULL && list->head==NULL){
        list->head = temp;
        list->tail = temp;
        list->curr = temp;
        list->list_size++;
        print(list);
        return;
    }
    list->tail->next = temp;
    temp->prev = list->tail;
    list->tail = temp;
    temp->next = NULL;
    list->list_size++;
    print(list);
}

int size(linkedList* list)
{
    // implement size function
    return list->list_size;
}

void prev(int n, linkedList* list)
{
    // implement prev function
    while(n-- && list->curr!=list->head){
        list->curr = list->curr->prev;
    }
    print(list);
}

void next(int n, linkedList* list)
{
    // implement next function
    while(n-- && list->curr!=list->tail){
        list->curr = list->curr->next;
    }
    print(list);
}

int is_present(int n, linkedList* list)
{
    // implement presence checking function
    node* temp = list->head;
    while(temp!=NULL){
        if(temp->element ==n){
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void clear(linkedList* list)
{
    // implement list clearing function
    
    while(list->tail!=NULL){
        node* temp = list->tail;
        list->tail = list->tail->prev;
        free(temp);
    }
    list->curr = NULL;
    list->head = NULL;
    list->list_size = 0;
    list->tail = NULL;
    print(list);
}

void delete_item(int item, linkedList* list)
{
    // implement item deletion function
    node* temp = list->head;
    while(temp!=NULL){
        if(temp->element==item)break;
        temp = temp->next;
    }
    if(temp!=NULL){
        if(temp==list->tail){
            list->tail= list->tail->prev;
            list->tail->next = NULL;
            free(temp);
            list->list_size--;
            if(temp==list->curr)list->curr = list->tail;
            print(list);
            return;
        }
        node* prev_node = temp->prev;
        node* next_node = temp->next;
        prev_node->next = next_node;
        next_node->prev = prev_node;
        if(temp==list->curr){
            list->curr = temp->next;
        }
        free(temp);
        list->list_size--;
        print(list);
    }else{
        printf("%d not found\n", item);
    }
}

void swap_ind(int ind1, int ind2, linkedList* list)
{
    // implement swap function
    if (ind1 < 0 || ind1 >= list->list_size || ind2 < 0 || ind2 >= list->list_size) {
        printf("Invalid indices\n");
        return;
    }
    node* node1, *node2;
    node* temp = list->head;
    int index = 0;
    while(temp!=NULL){
        if(index==ind1){
            node1 = temp;
        }
        if(index==ind2){
            node2 = temp;
        }
        index++;
        temp = temp->next;
    }
    int tempo_val = node1->element;
    node1->element = node2->element;
    node2->element = tempo_val;
    print(list);
}

// you can define helper functions you need