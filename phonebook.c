#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
struct Contact{
    unsigned long number;
    char *firstname;
    char *lastname;
    struct Contact *left;
    struct Contact *right;
    struct Contact *parent;
};
struct Phonebook{
    struct Contact* head;
};
void add(unsigned long number, char *firstname, char* lastname, struct Phonebook* phonebook){
    struct Contact *new = malloc(sizeof(struct Contact));
    new->firstname = calloc(strlen(firstname), sizeof(char));
    new->lastname = calloc(strlen(lastname), sizeof(char));
    new->number = number;
      if(phonebook->head == NULL){
        new->parent = NULL;
        phonebook->head->left = new;
    }else{
        struct Contact* temp = phonebook->head;
        struct Contact* tempN = NULL;
        while(temp){
            if(temp->number> number){
                tempN = temp;
                temp = temp->left;
            }else if(temp->number< number){
                tempN = temp;
                temp = temp->right;
            }
        }
        if(tempN->number> number){
            tempN->left = new;
            new ->parent = tempN;
        }else if(tempN->number< number){
            tempN->right = number;
            new->parent = tempN;
        }
    }
}
void display(struct Contact* head){
    if(head == NULL) return;
    display(head->left);
    printf("%s %s: %lu\n", head->firstname, head->lastname, head->number);
    display(head->right);
}
struct Phonebook* createPhonebook(){
    struct Phonebook* newPhonebook = malloc(sizeof(struct Phonebook));
    newPhonebook->head = NULL;
    return newPhonebook;
}
int main(){
    char answer;
    char *firstname;
    char *lastname;
    unsigned long number;
    char operation;
    struct Phonebook *newPh = createPhonebook();
    printf("Welcome, do you want to: \n");
    printf("Create new contact\t c\n Display contacts\t d \n");
    scanf("%c", &answer);
    if(answer == 'c'){
        scanf("%lu, %s, %s", &number, &firstname, &lastname);
        add(number, firstname, lastname, newPh);
    }
    if(answer == 'd'){
        display(newPh);
    }
    return 0;
}