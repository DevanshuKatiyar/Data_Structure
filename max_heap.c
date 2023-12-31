#include <stdio.h>
#include <stdlib.h>

// MAX-HEAP
typedef struct node 
{
    int data;
    struct node *left, *right;
} heap;

typedef struct 
{
    heap *data[20];
    int size;
} queue;
typedef queue stack;

void push(stack *s, struct node *val) 
{
    s->data[s->size] = val;
    s->size++;
}

heap *pop(stack *s) 
{
    heap *ret = s->data[s->size - 1];
    s->data[s->size] = NULL;
    s->size--;
    return ret;
}

void enqueue(queue *q, struct node *val)
{
    q->data[q->size] = val;
    q->size++;
}

heap *dequeue(queue *q) 
{
    heap *ret = q->data[0];

    for (int i = 0; i < q->size - 1; i++)
        q->data[i] = q->data[i + 1];

    q->size--;
    return ret;
}

heap *newnode(int value) 
{
    heap *ret = malloc(sizeof(heap));

    ret->data = value;
    ret->left = NULL;
    ret->right = NULL;

    return ret;
}


void swap(struct node *first, struct node *second) 
{
    int temp = first->data;
    first->data = second->data;
    second->data = temp;
}

heap* get_last_parent(heap *h)
{
    if(h == NULL) return NULL;

    queue q = {.size = 0};
    enqueue(&q, h);

    heap *current = NULL;
    heap *possible_parent = NULL;

    while(q.size)
    {
        current = dequeue(&q);
        if(current == NULL) return possible_parent;
        // the parent of last child has only one child or both child
        if(current->left == NULL && current->right == NULL)
            return possible_parent;
        // if current node has only one child then it is the parent of last child
        if((current->left != NULL && current->right == NULL) ||
           (current->left == NULL && current->right != NULL)){
            return current;
        }
        possible_parent = current;
        enqueue(&q, current->left);
        enqueue(&q, current->right);
    }

    return possible_parent;
}


void heapup(heap *h)

 {
    if (h == NULL) return;

    stack s = {.size = 0};
    push(&s, h);

    heap *current = h;
    heap *prev = NULL;

    do {

        while (current->left != NULL && current != prev) {
            push(&s, current);
            current = current->left;
        }

        current = pop(&s);

        if (current->left != NULL && current->data < current->left->data)
            swap(current, current->left);
        if (current->right != NULL && current->data < current->right->data)
            swap(current, current->right);


        if (current->right != NULL) {
            prev = current;
            current = current->right;
        }
        else
            prev = current;

    } while (s.size != 0);
}


void heapdown(heap *h) 
{
    if (h == NULL) return;

    heap *current = h;
    heap *next = NULL, *prev = NULL;

    while (current->left != NULL || current->right != NULL) {
        if (current->left != NULL && current->data < current->left->data) {
            swap(current, current->left);
            next = current->left;
        }

        if (current->right != NULL && current->data < current->right->data) {
            swap(current, current->right);
            next = current->right;
        }

        prev = current;
        current = next;

        if(current == NULL || current == prev) break;
    }
}


void levelbalance(heap *h)
{

    if (h != NULL && h->left == NULL && h->right == NULL) return;

    queue q = {.size = 0};
    enqueue(&q, h);

    heap *current = NULL;

    while (q.size) {
        current = dequeue(&q);
        if (!current) continue;
        if(current->left == NULL && current->right == NULL) continue;

        if (current->left && current->right && current->left->data < current->right->data)
            swap(current->left, current->right);

        enqueue(&q, current->left);
        enqueue(&q, current->right);
    }
}


void add(heap **root, int value)
{
    if (*root == NULL) {
        *root = newnode(value);
        return;
    }

    heap *current = NULL;
    queue q = {.size = 0};
    enqueue(&q, *root);

    while (q.size) {
        current = dequeue(&q);
        if (!current) continue;

        if (current->left == NULL) {
            current->left = newnode(value);
            break;
        }
        if (current->right == NULL) {
            current->right = newnode(value);
            break;
        }

        enqueue(&q, current->left);
        enqueue(&q, current->right);
    }

    heapup(*root);
    levelbalance(*root);
}


int flick(heap **h)
{
    heap *current = *h;

    if(current == NULL)
        return 1 << 31 - 1;
    int ret = current->data;

    // if both children of root are empty then delete root itself
    if(current->left == NULL && current->right == NULL){
        *h = NULL;
        goto end;

    }

    heap *last_parent = get_last_parent(current);

    if(last_parent->right != NULL){
        swap(current, last_parent->right);
        free(last_parent->right);
        last_parent->right = NULL;
    }

    else {
        swap(current, last_parent->left);
        free(last_parent->left);
        last_parent->left = NULL;
    }

    end:
    heapdown(current);
    levelbalance(current);

    return ret;
}

void main() 
{
    heap *h = NULL;
    int size, len;

    printf("Enter number of elements in array: ");
    scanf("%d", &size);
    len = size;

    int *arr = calloc(size, sizeof(int));
    for (int i = 0; i < size; i++) {
        printf("array[%d] = ", i);
        scanf("%d", &arr[i]);
        add(&h, arr[i]); // add that element into heap
    }


    while (len > 0)
    {
        arr[len - 1] = flick(&h);
        len--;
    }
    printf("\n");
    printf("Sorted array is: ");
    for (int i = 0; i < size; i++) 
    {
        printf("%d ", arr[i]);
    }
}