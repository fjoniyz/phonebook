#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 255

struct node{
    unsigned long number;
    struct node* next;
    char name[MAX_LENGTH];
    int prefix;
};
struct phonebook{
    struct node* head;
};
struct node* createNode(unsigned long number, char name[], int prefix){
    struct node* new = malloc(sizeof(struct node));
    strncpy(new->name, name, strlen(name));
    new->prefix = prefix;
    new->number = number;
    new->next = NULL;
    return new;
}
struct phonebook* createPhonebook(){
    struct phonebook* newPhonebook = malloc(sizeof(struct phonebook));
    newPhonebook->head = NULL;
    return newPhonebook;
}

void insertSorted(struct phonebook* phonebook, struct node* new_elem){
    if(phonebook->head == NULL){
        phonebook->head = new_elem;
        phonebook->head->next = NULL;
    }
    else if (phonebook->head->number > new_elem->number)
    {
        new_elem->next = phonebook->head;
    }
    else{
        struct node *tempNext = phonebook->head->next;
        struct node *temp = phonebook->head;
        while(tempNext!=NULL){
            if(temp->number < new_elem->number && tempNext->number < new_elem->number){
                temp = tempNext;
                tempNext = tempNext -> next;
            }
            else{
                break;
            }
        }
        temp -> next = new_elem;
        new_elem-> next = tempNext;
    }
}
void display(struct node* head){
    struct node* temp = head;
    if(head == NULL){
        printf("Phonebook is empty\n");
    }
    else{
        printf("Phonebook: \n");
        while(temp){
            printf("%s\t|\t %d %lu\n",temp->name, temp->prefix, temp->number);
            temp = temp->next;
        }
    }
}
void freeAll(struct phonebook* start){
    struct node* temp = start->head;
    struct node* prev;
    while(temp){
        prev = temp;
        temp = temp->next;
        free(prev);
    }
    free(start);
}
void startup(){
    printf("\nPhonebook is at the moment empty. You can do the following things:\n\n");
    printf("Add number to the phonebook: \t 1\n");
    printf("Show phonebook: \t 2\n");
    printf("Quit: \t any other number\n");
}
int main(){
    unsigned long number;
    int answer;
    int prefix;
    char name[MAX_LENGTH];
    struct phonebook* newPhonebook = createPhonebook();
    startup();
    printf("Enter operation: \n");
    scanf("%d", &answer);
    if(answer == 1)
    {
        while(answer == 1){
            printf("Enter prefix: \n");
            scanf("%d", &prefix);
            printf("Enter number: \n");
            scanf("%lu", &number);
            printf("Enter name: \n");
            scanf("%s", name);
            struct node* newNode = createNode(number, name, prefix);
            insertSorted(newPhonebook, newNode);
            display(newPhonebook->head);
            printf("Enter operation \n");
            scanf("%d", &answer);
        }
        if(answer == 2){
            display(newPhonebook->head);
        }
        else{
        printf("Quitting...\n");
        }
    }else if(answer == 2){
        display(newPhonebook->head);
    }
    else{
        printf("Quitting...\n");
    }
    freeAll(newPhonebook);
    return 0;
}