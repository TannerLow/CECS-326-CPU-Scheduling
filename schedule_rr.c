/**
 * Round-robin scheduling
 */

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "task.h"
#include "list.h"
#include "cpu.h"


int tid = 1;
struct node* head = NULL;

//Your code and design here
void add(char *name, int priority, int burst){
    Task* task = malloc(sizeof(Task));
    task->name = name;
    task->tid = tid++;
    task->priority = priority;
    task->burst = burst;
    insert(&head, task);
}

void schedule(){
    while(head != NULL){
        struct node* temp = head;
        while(temp != NULL){
            if(temp->task->burst > QUANTUM){
                run(temp->task, QUANTUM);
                temp->task->burst -= 10;
                temp = temp->next;
            }
            else{
                run(temp->task, temp->task->burst);
                struct node* del = temp;
                temp = temp->next;
                printf("Task %s is now finished\n", del->task->name); 
                delete(&head, del->task);
            }
        }
    }
}