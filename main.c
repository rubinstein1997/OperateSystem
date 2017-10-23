#include <stdio.h>
#include <malloc.h>

#define EMPTY_LIST_SIZE 40
#define TIME_SLICE 4



typedef struct node {
    char name;
    int id;
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
    new_node->id = number;
    new_node->next = NULL;

    return new_node;
}


void Init_Empty_List(node* head) {

    node* cursor = create(1);
    head->next = cursor;
    for(int i = 2; i <= EMPTY_LIST_SIZE; i ++) {
        /* create a new node */
        node* new_node = create(i);
        cursor->next = new_node;
        cursor = new_node;
        printf("PCB number: %d\n",new_node->id);
    }
}

void traverse(node* head) {
    node* cursor = head;
    printf("***************************************\n");
    printf("totally hava %d process \n",cursor->id);
    cursor = cursor->next;
    while(cursor != NULL) {
        printf("name:%c  number:%d status:%d task:%d \n",cursor->name,cursor->id,cursor->status,cursor->task);
        cursor = cursor->next;
    }
}

void emptytraverse(node* head) {
    node* cursor = head;
    while(cursor != NULL) {
        printf("%d ",cursor->id);
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

void Create_Process(node* EmptyListHead, node* ReadyListHead) {

    node* empty_cursor = EmptyListHead->next;
    node* ready_cursor = ReadyListHead->next;
    node* empty_point = (EmptyListHead->next)->next;

    char name;
    int task = 0;
    int status = 0;

    printf("please enter process name status task in order: ");
    scanf("%c %d %d",&name,&status,&task);
    fflush(stdin);
    empty_cursor->name = name;
    empty_cursor->status = status;
    empty_cursor->task = task;
    empty_cursor->next = NULL;
    printf("name:%c  number:%d status:%d task:%d\n",empty_cursor->name,empty_cursor->id,empty_cursor->status,empty_cursor->task);

    ReadyListHead->next = empty_cursor;
    (ReadyListHead->next)->next = ready_cursor;
    ReadyListHead->id ++;
    EmptyListHead->next = empty_point;
}


//dispatch process
void dispatch(node* EmptyListHead,node* ReadyListHead) {
    //time that all process already run
    int time = 0;

    node* empty_cursor = EmptyListHead->next;
    node* first_cursor = ReadyListHead->next;
    node* prefirst_cursor = ReadyListHead->next;

    //if ReadyListHead has element
    while(ReadyListHead->id > 0) {

        //task > TIME_SLICE ,continue
        if(first_cursor->task > 4) {
            first_cursor->task -= 4;
            time += 4;
            printf("id: %c time: %d task:%d\n",first_cursor->name,time,first_cursor->task);

            //if the element that first_cursor point is the last element
            if(first_cursor->next == NULL) {  //first_cursor and prefirst_cursor both point ReadyHead->next
                first_cursor = ReadyListHead->next;
                prefirst_cursor = ReadyListHead->next;
            } else {  //else both cursor point the next element
                prefirst_cursor = first_cursor;
                first_cursor = first_cursor->next;
            }
        }
        else{  //task <= TIME_SLICE, so the element that first_cursor point need to be transferred from the Ready_List to Empty_List
            time += first_cursor->task;
            printf("id: %c time: %d task:0\n",first_cursor->name,time);

            //
            if(first_cursor->next == NULL) {
                if(prefirst_cursor == first_cursor) {
                    ReadyListHead->next = NULL;
                    first_cursor->next = empty_cursor;
                    empty_cursor = first_cursor;
                    EmptyListHead->next = empty_cursor;
                }
                else{
                    prefirst_cursor->next = NULL;
                    first_cursor->next = empty_cursor;
                    empty_cursor = first_cursor;
                    EmptyListHead->next = empty_cursor;
                    first_cursor = ReadyListHead->next;
                    prefirst_cursor = ReadyListHead->next;
                }
            }else {
                if(prefirst_cursor == first_cursor) {
                    prefirst_cursor = first_cursor->next;
                    ReadyListHead->next = prefirst_cursor;
                    first_cursor->next = empty_cursor;
                    empty_cursor = first_cursor;
                    EmptyListHead->next = empty_cursor;
                    first_cursor = prefirst_cursor;
                }else{
                    prefirst_cursor->next = first_cursor->next;
                    first_cursor->next = empty_cursor;
                    empty_cursor = first_cursor;
                    EmptyListHead->next = empty_cursor;
                    first_cursor = prefirst_cursor->next;
                }
            }
            //count of the Ready_List --
            ReadyListHead->id --;

        }


    }
}


void menu() {
    printf("Init EmptyList success\n");
    printf("**********************************\n");
    printf("1.create process\n");
    printf("2.show all process information\n");
    printf("3.show empty_list\n");
    printf("4.dispatch process\n");
}

int main() {
    //menu variable
    int command = 0;

    node* EmptyListHead = NULL;
    node* ReadyListHead = NULL;

    //Init Empty_List
    EmptyListHead = create(0);
    Init_Empty_List(EmptyListHead);


    //Init Ready_List
    ReadyListHead = (node*)malloc(sizeof(node));
    ReadyListHead->id = 0;
    ReadyListHead->next = NULL;

    //show menu
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
                Create_Process(EmptyListHead,ReadyListHead);
                printf("create process success\n");
                break;
            case 2:
                if(ReadyListHead != NULL)
                    traverse(ReadyListHead);
                break;
            case 3:
                emptytraverse(EmptyListHead);
                break;
            case 4:
                dispatch(EmptyListHead,ReadyListHead);
                break;
//            default:
//                continue;
        }
    }
    return 0;
}