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
    //Run while there is at least one node in the list
    while(head != NULL){
        //Start at the head
        struct node* temp = head;
        //Traverse the list
        while(temp != NULL){
            //If a node has a task burst time greater than the quantum
            if(temp->task->burst > QUANTUM){
                //Run the task for the Quantum then subtract that time from the task
                run(temp->task, QUANTUM);
                temp->task->burst -= 10;
                //Go to the next node
                temp = temp->next;
            }
            //If a node has less burst time then the quantum
            else{
                //We run and delete that task
                run(temp->task, temp->task->burst);
                struct node* del = temp;
                temp = temp->next;

                printf("Task %s is now finished\n", del->task->name); 
                delete(&head, del->task);
            }
        }
    }
}