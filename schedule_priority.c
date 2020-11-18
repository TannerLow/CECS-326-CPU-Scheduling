/*
 * Priority scheduling
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
    //delete from list highest priority first
    while(head != NULL){
        struct node* temp = head;
        struct node* next = head;
        while(temp != NULL){
            if(temp->task->priority > next->task->priority){
                next = temp;
            }
            temp = temp->next;
        }
        run(next->task, next->task->burst);
        delete(&head, next->task);
    }
}