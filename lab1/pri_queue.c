#include <stdlib.h>
#include <stdio.h>
#include "pri_queue.h"
/** @file pri_queue.c */
static Node_ptr_t head = NULL;
/**
 * Insert a Node into a priority queue.
 * @param priority
 * @param data
 * @author Hamza Iqbal
 */
void PQ_insert(int priority, char * data) {
    
    //Creating the new node
    Node_ptr_t newNode = (Node_ptr_t) malloc (sizeof(Node_t));
    newNode -> data = data;
    newNode -> priority = priority;
    newNode -> next = NULL;
    
    //If there is no head/ first number being inserted, OR if inserted input priority is greater than head priority,
    // then let its next become the head 
    // and let IT become the new head
    
    if (head == NULL||head ->priority< priority){
        newNode ->next = head;
        head = newNode;
    }
    
    //else if input priority is less than the head priority
    else {
        Node_ptr_t temp =  (Node_ptr_t) malloc (sizeof(Node_t));
        temp = head;
        
        // while the next value is not null and the temporary next's priority is bigger than the temporary's priority..
        while (temp->next != NULL && temp->next ->priority >= priority)
        {
            temp = temp -> next;
        }
        //assigning the new priority
        newNode ->next = temp -> next;
          temp ->next   =  newNode;
    }     
}
/**
 * Delete and return the node with the highest priority.
 * @return The highest priority Node.
 */
Node_ptr_t PQ_delete() {
    // While ensuring that the queue contains a head, assign the value of the head to the temp pointer in order to return highest priority
    // and let the head equal its next value (deleting)
    while (head != NULL){
        //Using a temp pointer for Node
        Node_ptr_t temp = (Node_ptr_t)malloc (sizeof(Node_ptr_t));
        temp = head;
        head = head ->next;
    // return temp which holds the highest priority 
    return temp;
    }
}

/**
 * Do NOT modify this function.
 * @return A pointer to the head of the list.  (NULL if list is empty.)
 */
Node_ptr_t PQ_get_head() {
    return head;
}

/**
 * Do NOT modify this function.
 * @return the number of items in the queue
 */
int PQ_get_size() {
    int size = 0;
    Node_ptr_t tmp;
    for(tmp = head; tmp != NULL; tmp = tmp->next, size++)
        ;
    return size;
}


