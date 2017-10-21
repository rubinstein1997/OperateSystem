#include <stdio.h>
#include <malloc.h>

#define EMPTY_LIST_SIZE 40



typedef struct node {
    char name;
    int number;
    int status;
    int task;
    int parent;
    int sub;

    struct node* next;
}node;

//for create a empty list that every node has a number to identify
node* create (int number) {
    node* new_node = (node*)malloc(sizeof(node));

    if(new_node == NULL) {
        printf("Error creating a new node.\n");
        exit(0);
    }
    new_node->number = number;
    new_node->next = NULL;

    return new_node;
}


node* Init_Empty_List(node* head) {


    head = create(0);
    printf("PCB number: %d\n",head->number);
    node* cursor = head;
    for(int i = 1; i < EMPTY_LIST_SIZE; i ++) {
        /* create a new node */
        node* new_node = create(i);
        cursor->next = new_node;
        cursor = new_node;
        printf("PCB number: %d\n",new_node->number);
    }
    return head;
}

void traverse(node* head) {
    node* cursor = head;
    printf("***************************************\n");
    printf("totally hava %d process \n",cursor->number);
    cursor = cursor->next;
    while(cursor != NULL) {
        printf("name:%c  number:%d status:%d task:%d \n",cursor->name,cursor->number,cursor->status,cursor->task);
        cursor = cursor->next;
    }
}

void emptytraverse(node* head) {
    node* cursor = head;
    while(cursor != NULL) {
        printf("%d ",cursor->number);
        cursor = cursor->next;
    }

}


int count(node *head) {
    node *cursor = head;
    int c = 0;
    while(cursor != NULL) {
        c ++;
        cursor = cursor->next;
    }
    return c;
}

void menu() {
    printf("Init EmptyList success\n");
    printf("**********************************\n");
    printf("1.create process\n");
    printf("2.show all process information\n");
    printf("3.into process\n");
}



node* Create_Process(node* EmptyListHead, node* ReadyListHead) {
    node* empty_cursor;
    node* ready_cursor = ReadyListHead->next;
    empty_cursor = EmptyListHead->next;

    char name;
    int task = 0;
    int status = 0;

    printf("please enter process name status task in order: ");
    scanf("%c %d %d",&name,&status,&task);
    fflush(stdin);
    EmptyListHead->name = name;
    EmptyListHead->status = status;
    EmptyListHead->task = task;
    printf("name:%c  number:%d status:%d task:%d\n",EmptyListHead->name,EmptyListHead->number,EmptyListHead->status,EmptyListHead->task);

    ReadyListHead->next = EmptyListHead;
    (ReadyListHead->next)->next = ready_cursor;
    //the number of ReadyListHead element ++
    ReadyListHead->number ++;

    EmptyListHead = empty_cursor;

    return EmptyListHead;

}



int main() {
    int command = 0;

    node* EmptyListHead = NULL;
    node* ReadyListHead = NULL;

    ReadyListHead = create(0);

    /*Init EmptyList*/
    EmptyListHead = Init_Empty_List(EmptyListHead);

    menu();

    while(1) {
        printf("***************************************\n");
        printf("\nEnter a command(0-10,-1 to quit):");
        scanf("%d", &command);
        fflush(stdin);
        if (command == -1)
            break;
        switch (command) {
            case 0:
                menu();
                break;
            case 1:
                EmptyListHead = Create_Process(EmptyListHead,ReadyListHead);
                printf("create process success\n");
                break;
            case 2:
                if(ReadyListHead != NULL)
                    traverse(ReadyListHead);
                break;
            case 3:
                emptytraverse(EmptyListHead);
                break;

        }
    }
    return 0;
}