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
    //Malloc task
    Task* task = malloc(sizeof(Task));
    //Fill out task properties
    task->name = name;
    task->tid = tid++;
    task->priority = priority;
    task->burst = burst;
    //Insert into list
    insert(&head, task);
}

void schedule(){
    //delete from list highest priority first
    //While there is still a node in the list
    while(head != NULL){
        //We track the current temporary node
        struct node* temp = head;
        //We track the next node to be ran by the cpu
        struct node* next = head;
        //We traverse the list
        while(temp != NULL){
            //If a the temp node has higher priority then the next node
            if(temp->task->priority > next->task->priority){
                //Make the next node the current temp node
                next = temp;
            }
            //Go to the next node
            temp = temp->next;
        }
        //Run and delete the next task
        run(next->task, next->task->burst);
        delete(&head, next->task);
    }
}