/* Shravani Patil - 39
   Supriya Pimparkar-40 */
/* Smart Public Transport Reservation System */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5
#define NAME_SIZE 50
#define ROUTE_SIZE 50

//Reservation Structure

struct Reservation
{
    int reservationID;
    char passengerName[NAME_SIZE];
    char busRoute[ROUTE_SIZE];
};

//STAGE 1 - Linear queue
//Passenger Reservation Booking
struct Reservation queue[MAX];

int front = -1;
int rear = -1;

//Cancelled Reservation Logs
struct Reservation stack[MAX];

int top = -1;

//Linked List-Passenger Travel Records
struct TravelRecord
{
    int reservationID;
    char passengerName[NAME_SIZE];
    char busRoute[ROUTE_SIZE];

    struct TravelRecord *next;
};

struct TravelRecord *head = NULL;

//Bus Route Structure
struct BusRoute
{
    int routeID;
    char routeName[ROUTE_SIZE];
};

// STAGE 2 - Circular Queue
//Bus Route Rotation

struct BusRoute routeQueue[MAX];

int routeFront = -1;
int routeRear = -1;


// STAGE 3 - BST
//Bus Route Hierarchy
struct BSTNode
{
    int routeID;
    char routeName[ROUTE_SIZE];

    struct BSTNode *left;
    struct BSTNode *right;
};

struct BSTNode *root = NULL;

// STAGE 3 - Binary Search

struct BusRoute binarySearchList[MAX];
int routeCount = 0;

//FUNCTION PROTOTYPES

// Queue 
void enqueue(struct Reservation reservation);
void dequeue();
void displayQueue();

// Stack 
void push(struct Reservation reservation);
void pop();
void displayStack();

// Linked List 
void addTravelRecordFromReservation(struct Reservation reservation);
void displayTravelRecords();
void deleteTravelRecord();

// Circular Queue 
void addBusRoute();
void rotateBusRoute();
void displayBusRoutes();

// BST 
struct BSTNode *createBSTNode(int routeID,char routeName[]);

struct BSTNode *insertBST(struct BSTNode *root,int routeID,
    char routeName[]);

void inorderBST(struct BSTNode *root);
void displayBST();

// Binary Search 
void sortRoutes();
void binarySearchRoute();
void displayBinarySearchRoutes();

// QUEUE - Add reservation
 
void enqueue(struct Reservation reservation)
{
    if (rear == MAX - 1)
    {
        printf("\nQueue Overflow! Reservation queue is full.\n");
        return;
    }

    if (front == -1)
    {
        front = 0;
    }

    rear++;

    queue[rear] = reservation;

    printf("\nReservation added to queue successfully.\n");
}

 /*QUEUE - Process Reservation
  Automatically adds passenger to Linked List*/
   
void dequeue()
{
    struct Reservation processedReservation;

    if (front == -1 || front > rear)
    {
        printf("\nQueue Underflow! No reservation requests available.\n");
        return;
    }

// Store reservation before removing it 
    processedReservation = queue[front];

    printf("\n------- RESERVATION PROCESSED -------\n");

    printf("Reservation ID : %d\n",processedReservation.reservationID);

    printf("Passenger Name : %s\n",processedReservation.passengerName);

    printf("Bus Route      : %s\n",processedReservation.busRoute);

// Add processed passenger to Linked List 
    addTravelRecordFromReservation(processedReservation);

    front++;

// Reset queue when empty 
    if (front > rear)
    {
        front = -1;
        rear = -1;
    }
}

//QUEUE - Display
void displayQueue()
{
    int i;

    if (front == -1)
    {
        printf("\nReservation Queue is empty.\n");
        return;
    }

    printf("\n--------- RESERVATION QUEUE ---------\n");

    for (i = front; i <= rear; i++)
    {
        printf("\nReservation ID : %d",queue[i].reservationID);

        printf("\nPassenger Name : %s",queue[i].passengerName);

        printf("\nBus Route      : %s\n",queue[i].busRoute);
    }
}

//STACK - Push
void push(struct Reservation reservation)
{
    if (top == MAX - 1)
    {
        printf("\nStack Overflow! Cancellation stack is full.\n");
        return;
    }

    top++;

    stack[top] = reservation;

    printf("\nReservation cancelled and added to stack successfully.\n");
}

 // STACK - Pop
void pop()
{
    if (top == -1)
    {
        printf("\nStack Underflow! No cancelled reservations available.\n");
        return;
    }

    printf("\n------- CANCELLED RESERVATION REMOVED -------\n");

    printf("Reservation ID : %d\n",stack[top].reservationID);

    printf("Passenger Name : %s\n",stack[top].passengerName);

    printf("Bus Route      : %s\n",stack[top].busRoute);

    top--;
}

// STACK - Display
void displayStack()
{
    int i;

    if (top == -1)
    {
        printf("\nCancellation Stack is empty.\n");
        return;
    }

    printf("\n--------- CANCELLATION STACK ---------\n");

    for (i = top; i >= 0; i--)
    {
        printf("\nReservation ID : %d",stack[i].reservationID);

        printf("\nPassenger Name : %s",stack[i].passengerName);

        printf("\nBus Route      : %s\n",stack[i].busRoute);
    }
}

 //LINKED LIST - ADD
void addTravelRecordFromReservation(struct Reservation reservation)
{
    struct TravelRecord *newNode;
    struct TravelRecord *temp;

    newNode = (struct TravelRecord *)malloc(sizeof(struct TravelRecord));

    if (newNode == NULL)
    {
        printf("\nMemory allocation failed!\n");
        return;
    }

    newNode->reservationID = reservation.reservationID;

    strcpy(newNode->passengerName,reservation.passengerName);

    strcpy(newNode->busRoute,reservation.busRoute);

    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        temp = head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }

    printf("\nPassenger travel record added to Linked List.\n");
}

// LINKED LIST - Display
void displayTravelRecords()
{
    struct TravelRecord *temp;

    if (head == NULL)
    {
        printf("\nNo passenger travel records available.\n");
        return;
    }

    printf("\n--------- PASSENGER TRAVEL RECORDS ---------\n");

    temp = head;

    while (temp != NULL)
    {
        printf("\nReservation ID : %d",temp->reservationID);

        printf("\nPassenger Name : %s",temp->passengerName);

        printf("\nBus Route      : %s\n",temp->busRoute);

        temp = temp->next;
    }
}

 //LINKED LIST - Delete
void deleteTravelRecord()
{
    struct TravelRecord *temp;

    if (head == NULL)
    {
        printf("\nLinked List is empty. No record to delete.\n");
        return;
    }

    temp = head;

    head = head->next;

    printf("\nTravel record removed successfully.\n");

    printf("Reservation ID : %d\n",temp->reservationID);

    printf("Passenger Name : %s\n",temp->passengerName);

    printf("Bus Route      : %s\n",temp->busRoute);

    free(temp);
}

//BST - Create Node
struct BSTNode *createBSTNode(int routeID,char routeName[])
{
    struct BSTNode *newNode;

    newNode = (struct BSTNode *)malloc(sizeof(struct BSTNode));

    if (newNode == NULL)
    {
        printf("\nMemory allocation failed!\n");
        return NULL;
    }

    newNode->routeID = routeID;

    strcpy(newNode->routeName,routeName);

    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

//BST - Insert
struct BSTNode *insertBST(struct BSTNode *root,int routeID,
    char routeName[])
{
    if (root == NULL)
    {
        return createBSTNode(routeID,routeName);
    }

    if (routeID < root->routeID)
    {
        root->left = insertBST(root->left,routeID, routeName);
    }
    else if (routeID > root->routeID)
    {
        root->right = insertBST(root->right,routeID,routeName);
    }
    return root;
}

//BST - Inorder Traversal
void inorderBST(struct BSTNode *root)
{
    if (root != NULL)
    {
        inorderBST(root->left);

        printf("Route ID : %d | Bus Route : %s\n",
               root->routeID,root->routeName);

        inorderBST(root->right);
    }
}

// BST - Display Heirarchy
void displayBST()
{
    if (root == NULL)
    {
        printf("\nBus Route Hierarchy is empty.\n");
        return;
    }

    printf("\n--------- BUS ROUTE HIERARCHY - BST ---------\n");

    inorderBST(root);
}

/* ADD BUS ROUTE
   Automatically adds route to:
   1. Circular Queue
   2. BST
   3. Binary Search Array */
void addBusRoute()
{
    int routeID;
    char routeName[ROUTE_SIZE];
    int i;

    if (routeCount == MAX)
    {
        printf("\nMaximum number of bus routes reached.\n");
        return;
    }

    printf("\nEnter Route ID: ");
    scanf("%d", &routeID);

    if (routeID <= 0)
    {
        printf("\nInvalid Route ID!\n");
        return;
    }

// Check duplicate Route ID 
    for (i = 0; i < routeCount; i++)
    {
        if (binarySearchList[i].routeID == routeID)
        {
            printf("\nRoute ID already exists!\n");
            return;
        }
    }
    printf("Enter Bus Route: ");
    scanf(" %[^\n]", routeName);

//CIRCULAR QUEUE
    if (routeFront == -1)
    {
        routeFront = 0;
        routeRear = 0;
    }
    else
    {
        routeRear = (routeRear + 1) % MAX;
    }

    routeQueue[routeRear].routeID = routeID;

    strcpy(routeQueue[routeRear].routeName,routeName);

//BST
    root = insertBST(root,routeID,routeName);

// Binary Search Array
    binarySearchList[routeCount].routeID = routeID;

    strcpy(binarySearchList[routeCount].routeName,routeName);

    routeCount++;

    printf("\nBus route added successfully!\n");

    printf("Route ID  : %d\n",routeID);

    printf("Bus Route : %s\n",routeName);
}

//CIRCULAR QUEUE - Rotate
void rotateBusRoute()
{
    struct BusRoute temp;

    if (routeFront == -1)
    {
        printf("\nCircular Queue is empty.\n");
        return;
    }

 //Store the first route.
    temp = routeQueue[routeFront];

//Move front forward.

    routeFront = (routeFront + 1) % MAX;

//Move rear forward.

    routeRear = (routeRear + 1) % MAX;

//Put old first route at rear.
    routeQueue[routeRear] = temp;

    printf("\nBus route rotated successfully.\n");

    displayBusRoutes();
}

//CIRCULAR QUEUE - Display

void displayBusRoutes()
{
    int i;

    if (routeFront == -1)
    {
        printf("\nCircular Queue is empty.\n");
        return;
    }

    printf("\n--------- Bus Route ---------\n");

    i = routeFront;

    while (1)
    {
        printf("Route ID : %d | Bus Route : %s\n",routeQueue[i].routeID,
               routeQueue[i].routeName);
               
        if (i == routeRear)
        {
            break;
        }

        i = (i + 1) % MAX;
    }
}

//Binary Search - Sort
void sortRoutes()
{
    int i;
    int j;

    struct BusRoute temp;
    for (i = 0;i < routeCount - 1;i++)
    {
        for (j = 0;j < routeCount - i - 1;j++)
        {
            if (binarySearchList[j].routeID>binarySearchList[j + 1].routeID)
            {
                temp = binarySearchList[j];

                binarySearchList[j] = binarySearchList[j + 1];

                binarySearchList[j + 1] = temp;
            }
        }
    }
}

//Binary Search
//Search Bus by Route ID
void binarySearchRoute()
{
    int key;

    int low = 0;
    int high;

    int mid;

    int found = 0;

    if (routeCount == 0)
    {
        printf("\nNo bus routes available for searching.\n");
        return;
    }

 //Binary Search requires sorted data.
    sortRoutes();

    printf("\nEnter Route ID to search: ");
    scanf("%d", &key);

    high = routeCount - 1;

    while (low <= high)
    {
        mid = (low + high) / 2;

        if (binarySearchList[mid].routeID == key)
        {
            printf("\n--------- BUS FOUND ---------\n");

            printf("Route ID  : %d\n",binarySearchList[mid].routeID);

            printf("Bus Route : %s\n",binarySearchList[mid].routeName);

            found = 1;

            break;
        }

        if (key < binarySearchList[mid].routeID)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    if (found == 0)
    {
        printf("\nBus route with Route ID %d not found.\n",key);
    }
}

//Display Binary Search Data

void displayBinarySearchRoutes()
{
    int i;

    if (routeCount == 0)
    {
        printf("\nNo bus routes available.\n");
        return;
    }

    sortRoutes();

    printf("\n--------- ROUTES FOR BINARY SEARCH ---------\n");

    for (i = 0;i < routeCount;i++)
    {
        printf("Route ID : %d | Bus Route : %s\n",binarySearchList[i].routeID,
               binarySearchList[i].routeName);
    }
}

//MAIN FUNCTION
int main()
{
    int choice;

    struct Reservation reservation;

    while (1)
    {
        printf("\n\n****************************************************");
        printf("\n       SMART PUBLIC TRANSPORT RESERVATION");
        printf("\n****************************************************");

        printf("\n\n--- Stage 1 Functions ---");

        printf("\n1. Add Passenger Reservation");
        printf("\n2. Process Passenger Reservation");
        printf("\n3. Display Reservation Queue");

        printf("\n4. Cancel Reservation");
        printf("\n5. Remove Cancelled Reservation");
        printf("\n6. Display Cancellation Stack");

        printf("\n\n--- Stage 2 Functions ---");

        printf("\n7. Add Bus Route");
        printf("\n8. Rotate Bus Route");
        printf("\n9. Display Bus Routes");

        printf("\n10. Display Passenger Travel Records");
        printf("\n11. Delete Passenger Travel Record");

        printf("\n\n--- Stage 3 Functions ---");

        printf("\n12. Display Bus Route Hierarchy - BST");
        printf("\n13. Search Bus by Route ID - Binary Search");
        printf("\n14. Display Routes for Binary Search");

        printf("\n15. Exit");

        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            //QUEUE
            case 1:
                printf("\nEnter Reservation ID: ");

                scanf("%d",&reservation.reservationID);

                if (reservation.reservationID <= 0)
                {
                    printf("\nInvalid Reservation ID!\n");
                    break;
                }

                printf("Enter Passenger Name: ");

                scanf(" %[^\n]",reservation.passengerName);

                printf("Enter Bus Route: ");

                scanf(" %[^\n]",reservation.busRoute);

                enqueue(reservation);
                break;

            case 2:
                  //Processing the passenger automatically
                  //adds the passenger to the Linked List.
                dequeue();
                break;

            case 3:
                displayQueue();
                break;
            
            
               //STACK
            case 4:
                printf("\nEnter Reservation ID: ");

                scanf("%d",&reservation.reservationID);

                if (reservation.reservationID <= 0)
                {
                    printf("\nInvalid Reservation ID!\n");
                    break;
                }

                printf("Enter Passenger Name: ");

                scanf(" %[^\n]",reservation.passengerName);

                printf("Enter Bus Route: ");

                scanf(" %[^\n]",reservation.busRoute);

                push(reservation);
                break;

            case 5:
                pop();
                break;

            case 6:
                displayStack();
                break;


              // STAGE 2 - CIRCULAR QUEUE
            case 7:
                addBusRoute();
                break;

            case 8:
                rotateBusRoute();
                break;

            case 9:
                displayBusRoutes();
                break;

               //STAGE 2 - LINKED LIST
            case 10:
                displayTravelRecords();
                break;

            case 11:
                deleteTravelRecord();
                break;

               //STAGE 3 - BST
            case 12:
                displayBST();
                break;

               //STAGE 3 - BINARY SEARCH
            case 13:
                binarySearchRoute();
                break;

            case 14:
                displayBinarySearchRoutes();
                break;

               //EXIT
            case 15:

                printf("\nThank you for using Smart Public "
                       "Transport Reservation System!\n");
                exit(0);

            default:

                printf("\nInvalid choice! Please enter "
                       "a number from 1 to 15.\n");
        }
    }
    return 0;
}