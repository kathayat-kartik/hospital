#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

// patient details
typedef struct patient
{
    int id;
    int age;
    char name[50];
    char disease[50];
    int emergency;
} patient;

typedef struct node
{
    patient pat;
    struct node *next;
} node;

// queue
typedef struct queue
{
    node *front, *rear;
} queue;

void intial_queue(queue *q)
{
    q->front = q->rear = NULL;
}

int empty_check(queue *q)
{
    return q->front == NULL;
}

void enqueue(queue *q, patient p)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->pat = p;
    new_node->next = NULL;

    if (q->rear == NULL)
    {
        q->front = q->rear = new_node;
    }
    else
    {
        q->rear->next = new_node;
        q->rear = new_node;
    }
    printf("Patient %s (ID=%d) added to normal queue.\n", p.name, p.id);
}

patient dequeue(queue *q)
{
    patient dummy = {-1, -1, "", "", 0};
    if (empty_check(q))
    {
        printf("Queue is empty.\n");
        return dummy;
    }
    node *temp = q->front;
    patient p = temp->pat;
    q->front = q->front->next;
    if (q->front == NULL)
    {
        q->rear = NULL;
    }
    free(temp);
    return p;
}

// emergency queue (heap)
typedef struct
{
    int size;
    patient pat[MAX];
} heap;

void intial_heap(heap *h)
{
    h->size = 0;
}

void swap_patient(patient *a, patient *b)
{
    patient t = *a;
    *a = *b;
    *b = t;
}

void insert_heap(heap *h, patient p)
{
    int i = h->size++;
    h->pat[i] = p;

    while (i > 0 && h->pat[(i - 1) / 2].age < h->pat[i].age)
    {
        swap_patient(&h->pat[(i - 1) / 2], &h->pat[i]);
        i = (i - 1) / 2;
    }
    printf("Emergency patient %s (ID=%d, age=%d) added.\n", p.name, p.id, p.age);
}

patient remove_heap(heap *h)
{
    patient dummy = {-1, -1, "", "", 0};
    if (h->size == 0)
        return dummy;

    patient p = h->pat[0];
    h->pat[0] = h->pat[h->size - 1];
    h->size--;

    int i = 0;
    while (1)
    {
        int left = 2 * i + 1, right = 2 * i + 2, largest = i;
        if (left < h->size && h->pat[left].age > h->pat[largest].age)
            largest = left;
        if (right < h->size && h->pat[right].age > h->pat[largest].age)
            largest = right;
        if (largest == i)
            break;
        swap_patient(&h->pat[i], &h->pat[largest]);
        i = largest;
    }
    return p;
}

// viewing queues
void view_queue(queue *normal_q, heap *emergency_q)
{
    // emergency queue
    if (emergency_q->size == 0)
    {
        printf("No patient in emergency queue.\n");
    }
    else
    {
        printf("\n---- Emergency Patients ----\n");
        for (int i = 0; i < emergency_q->size; i++)
        {
            printf("Patient[%d] | Name:%s | ID:%d | Age:%d | Disease:%s\n",
                   i + 1,
                   emergency_q->pat[i].name,
                   emergency_q->pat[i].id,
                   emergency_q->pat[i].age,
                   emergency_q->pat[i].disease);
        }
    }

    // normal queue
    printf("\n---- Normal Queue ----\n");
    if (empty_check(normal_q))
    {
        printf("No patient in normal queue.\n");
    }
    else
    {
        int i = 0;
        node *temp = normal_q->front;
        while (temp)
        {
            printf("Patient[%d] | Name:%s | ID:%d | Age:%d | Disease:%s\n",
                   ++i,
                   temp->pat.name,
                   temp->pat.id,
                   temp->pat.age,
                   temp->pat.disease);
            temp = temp->next;
        }
    }
    printf("\n");
}

int main()
{
    queue normalQ;
    heap emergencyQ;
    intial_queue(&normalQ);
    intial_heap(&emergencyQ);

    // sample patients
    patient p1 = {2001, 19, "ABHISHEK", "ANEMIA", 0};
    patient p2 = {2005, 32, "KITE", "RICKETS", 1};
    patient p3 = {2003, 47, "KULLI", "CANCER", 0};
    patient p4 = {1992, 87, "TOLEX", "ASTHMA", 1};

    // add patients
    enqueue(&normalQ, p1);
    insert_heap(&emergencyQ, p2);
    enqueue(&normalQ, p3);
    insert_heap(&emergencyQ, p4);

    // view all
    view_queue(&normalQ, &emergencyQ);

    printf("\n--- Assigning Doctor ---\n");
    patient treated;

    if (emergencyQ.size > 0)
    {
        treated = remove_heap(&emergencyQ);
        printf("Doctor treating Emergency: %s (ID=%d)\n", treated.name, treated.id);
    }
    else if (!empty_check(&normalQ))
    {
        treated = dequeue(&normalQ);
        printf("Doctor treating Normal: %s (ID=%d)\n", treated.name, treated.id);
    }

    // view after treatment
    view_queue(&normalQ, &emergencyQ);

    return 0;
}
