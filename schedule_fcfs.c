/**
 * FCFS scheduling
 */
 
#include <stdlib.h>
#include <stdio.h>

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
    //read list in reverse
    while(head != NULL){
        struct node* temp = head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        run(temp->task, temp->task->burst);
        delete(&head, temp->task);
    }
}