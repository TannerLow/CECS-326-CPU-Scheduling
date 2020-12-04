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
    //reads list in reverse
    //while their is a node still in the list
    while(head != NULL){
        //Start from the head of the list
        struct node* temp = head;
        //Traverse the list and grab the last node
        while(temp->next != NULL){
            temp = temp->next;
        }
        //Run and delete last task from list
        run(temp->task, temp->task->burst);
        delete(&head, temp->task);
    }
}