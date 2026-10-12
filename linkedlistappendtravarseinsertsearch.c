
#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node *head = NULL;


// Append Node at End
void append(int value)
{
    struct Node *newNode, *temp;

    newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->data = value;
    newNode->next = NULL;

    if(head == NULL)
    {
        head = newNode;
    }
    else
    {
        temp = head;

        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}


// Insert at Specific Position
void insert(int value, int position)
{
    struct Node *newNode, *temp;
    int i;

    newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->data = value;

    if(position == 1)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        temp = head;

        for(i=1; i<position-1; i++)
        {
            temp = temp->next;
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }
}


// Traverse Linked List
void traverse()
{
    struct Node *temp = head;

    while(temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n");
}


// Search Node
void search(int key)
{
    struct Node *temp = head;
    int position = 1;

    while(temp != NULL)
    {
        if(temp->data == key)
        {
            printf("%d, found at position %d\n", key, position);
            return;
        }

        temp = temp->next;
        position++;
    }

    printf("%d is not found\n", key);
}


int main()
{
    int n, value, i;
    int insertValue, position, key;

    printf("Enter number of nodes: ");
    scanf("%d",&n);


    // Append using user input
    for(i=1; i<=n; i++)
    {
        printf("Enter value for node %d: ",i);
        scanf("%d",&value);

        append(value);
    }


    printf("\nAfter Append: ");
    traverse();


    printf("\nEnter value to insert: ");
    scanf("%d",&insertValue);

    printf("Enter position: ");
    scanf("%d",&position);

    insert(insertValue, position);


    printf("After Insert: ");
    traverse();


    printf("\nEnter value to search: ");
    scanf("%d",&key);

    search(key);


    return 0;
}
