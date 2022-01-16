#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
    int value;
    struct node* next;
} node;

typedef struct stack {
    int key;
    struct stack* next;
} stack;

typedef struct queue {
    node* front;
    node* rear;
} queue;

typedef struct bst {
    int key;
    struct bst *left;
    struct bst *right;
} bst;

/*  BİLİNEN SORUNLAR
    Binary Search Tree print edilince 0 çıkıyor bir tane.
    cmd de kod print edilmiyor ama ubuntu replit onlinegdb hepsinde ediliyor.
*/

struct bst* insert(struct bst* bst_, int key)
{
    if(bst_ == NULL)
    {
        struct bst* temp;
        temp = (bst*) malloc(sizeof(bst));
        temp->key = key;
        temp->left = temp->right = NULL;
        return temp;
    }
    if(key < bst_->key)
        bst_->left = insert(bst_->left, key);
    else if(key > bst_->key)
        bst_->right = insert(bst_->right, key);
    return bst_;
}

void inorder(bst *root) 
{
    if (root != NULL)
    { 
        inorder(root->left); 
        printf("%d ", root->key);
        inorder(root->right);
    }
}

void descending_order_bst(bst *root)
{
    if(root != NULL)
    {
        descending_order_bst(root->right);
        printf("%d ", root->key);
        descending_order_bst(root->left);
    }
}


void fill_structures(stack ** stack_, queue ** queue_, bst ** bst_, int data[20])
{
    double stack_fill_time=0.0, queue_fill_time=0.0, bst_fill_time=0.0;
    int i;
    stack *temp, *current;
    clock_t start, end;
    bst* bst_current;
    *stack_ = (stack*) malloc(sizeof(stack));
    *queue_ = (queue*) malloc(sizeof(queue));
    *bst_ = (bst*) malloc(sizeof(bst));

    // FILL STACK
    start = clock();
    for(i=0; i<20; i++)
    {
        temp = (stack*) malloc(sizeof(stack));
        temp->key = data[i];
        temp->next = NULL;
        if(stack_ != NULL)
            temp->next = *stack_;
        *stack_ = temp;
    }
    end = clock();
    stack_fill_time += ((double) (end - start)) / CLOCKS_PER_SEC * 1000;

    // FILL QUEUE
    start = clock();
    (*queue_)->front = NULL;
    (*queue_)->rear = NULL;
    for(i=0; i<20; i++)
    {
        node* queue_node;
        queue_node = (node*) malloc(sizeof(node));
        
        queue_node->value = data[i];
        queue_node->next = NULL;
        if((*queue_)->front == NULL)
        {
            (*queue_)->front = queue_node;
            (*queue_)->rear = queue_node;
        }
        else
        {
            (*queue_)->rear->next = queue_node;
            (*queue_)->rear = queue_node;
        }
    }
    end = clock();
    queue_fill_time += ((double) (end - start)) / CLOCKS_PER_SEC * 1000;

    // FILL BINARY SEARCH TREE
    start = clock();
    for(i=0; i<20; i++)
    {
        insert(*bst_, data[i]);
    }
    end = clock();
    bst_fill_time += ((double) (end - start)) / CLOCKS_PER_SEC * 1000;

    printf("PART 1: FILLING DATA STRUCTURES\nStructures\tStack\tQueue\tBST\nExec. Time\t%.3lf\t%.3lf\t%.3lf\n",stack_fill_time, queue_fill_time, bst_fill_time);
    
}

    

    /*print stack content
    for(current = stack_; current->next != NULL ; current = current -> next)
        printf("%d ", current->key);
        */
    /*
    // print queue
    struct node* current_;

    for(current_=(*queue_)->front; current_!=NULL; current_=current_->next)
    {
        printf("%d ", current_->value);
    }*/

    /* print binary search Tree
    inorder(*bst_);
    */


void ordered_print(stack * stack_, queue * queue_, bst * bst_)
{
    int i, j, c=20;
    double stack_time=0.0, q_time=0.0, bst_time=0.0;
    clock_t start, end;

    printf("\nPART 2: ORDERING AND PRINTING");

    // ORDER STACK AND PRINT
    start = clock();
    stack *current, *next, temp_node;
    current = stack_;
    for(i=0; i < c-1; i++, current = current->next)
    {
        next = current->next;
        for(j=i+1; j < c; j++, next = next->next)
        {
            if(current->key < next->key) // descending order
            {
                // swap
                temp_node.key = current->key;
                current->key = next->key;
                next->key = temp_node.key;
            }
        }
    }
    
    printf("\nStack: ");
    for(current = stack_; current->next != NULL; current = current->next)
    {
        printf("%d ", current->key);
    }
    end = clock();
    stack_time += ((double) (end - start)) / CLOCKS_PER_SEC * 1000;

    // ORDER QUEUE AND PRINT
    start = clock();
    node *q_current, *q_next, q_temp_node;
    
    for(q_current = queue_->front; q_current != queue_->rear; q_current = q_current->next)
    {
        
        for(q_next = q_current->next; q_next != queue_->rear->next; q_next = q_next->next)
        {
            if(q_current->value < q_next->value) // descending order
            {
                // swap nodes
                q_temp_node.value = q_current->value;
                q_current->value = q_next->value;
                q_next->value = q_temp_node.value;

                // update queue's front and rear
                if(q_temp_node.value == queue_->front->value)
                    queue_->front = q_current;
                if(q_temp_node.value == queue_->rear->value)
                    queue_->rear = q_next;
            }
        }
    }
    
    // Print Queue
    printf("\nQueue: ");
    for(q_current=queue_->front; q_current != queue_->rear->next; q_current = q_current->next)
    {
        printf("%d ", q_current->value);
    }
    printf("\nQueue's Front: %d, Queue's Rear: %d\n", queue_->front->value, queue_->rear->value);
    
    end = clock();
    q_time += ((double) (end - start)) / CLOCKS_PER_SEC * 1000;

    // Print BST in descending order
    start = clock();
    printf("Binary Search Tree: ");
    descending_order_bst(bst_);
    end = clock();
    bst_time += ((double) (end - start)) / CLOCKS_PER_SEC * 1000;

    printf("\nStructures\tStack\tQueue\tBST\nExec. Time\t%.3lf\t%.3lf\t%.3lf\n",stack_time, q_time, bst_time);

}

void search(stack * stack_, queue * queue_, bst * bst_, int val_to_search)
{
    int found_in_bst=0, found_in_queue=0, found_in_stack=0, stack_arr_index=0, step, queue_arr_index=0, i;
    int stack_results[20], queue_results[20];
    double stack_time=0.0, q_time=0.0, bst_time=0.0;
    clock_t start, end;
    stack *current;
    node *current_node;

    printf("\nPART 3: SEARCH\nSearch value: %d\n", val_to_search);

    
    // search in stack
    start = clock();
    step=0;
    printf("Stack: ");
    for(current = stack_; current->next != NULL; current = current->next)
    {
        if(current->key == val_to_search)
        {
            stack_results[stack_arr_index] = step;
            stack_arr_index++;
        }
        step++;
    }

    if(stack_arr_index == 0)
        printf("No results found in stack.");
    else
    {
        printf("%d results found on ", stack_arr_index);
        for(i=0; i<stack_arr_index; i++)
        {
            printf("%d. ", stack_results[i]+1);
        }
        printf("step(s).\n");
    }
    end = clock();
    stack_time += ((double) (end - start)) / CLOCKS_PER_SEC * 1000;

    // search in queue
    start = clock();
    step=0;
    printf("Queue: ");
    for(current_node = queue_->front; current_node != queue_->rear->next; current_node = current_node->next)
    {
        if(current_node->value == val_to_search)
        {
            queue_results[queue_arr_index] = step;
            queue_arr_index++;
        }
        step++;
    }
    if(queue_arr_index == 0)
        printf("No results found in queue.");
    else
    {
        printf("%d results found on ", queue_arr_index);
        for(i=0; i<queue_arr_index; i++)
        {
            printf("%d. ", queue_results[i]+1);
        }
        printf("step(s).\n");
    }
    end = clock();
    q_time += ((double) (end - start)) / CLOCKS_PER_SEC * 1000;

    printf("Structures\tStack\tQueue\tBST\nExec. Time\t%.3lf\t%.3lf\t%.3lf\n",stack_time, q_time, bst_time);


}

void special_traverse(stack * stack_, queue * queue_, bst * bst_)
{
    // code
}

int main(void) {
    int data[20]={5, 2, 7, 8, 11, 3, 21, 7, 6, 15, 19, 35, 24, 1, 8, 12, 17, 8, 23, 4};
    bst * bst_;
    queue * queue_;
    stack * stack_;
    fill_structures(&stack_, &queue_, &bst_, data);
    ordered_print(stack_, queue_, bst_);
    search(stack_, queue_, bst_, 5);
    special_traverse(stack_, queue_, bst_);
    return 0;
}