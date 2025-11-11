#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// ---------- STRUCTURES ----------

struct pat;
struct doc;
static int doc_count = 30;

typedef struct pat
{
    int id;
    int age;
    char name[50];
    char disease[50];
    int emergency;
    int severity;
    float priority;
    struct doc* assigned;
} pat;

typedef struct node
{
    pat patient;
    struct node* next;
} node;

typedef struct queue
{
    node *front, *rear;
} queue;

typedef struct heap
{
    int size;
    pat pt[100];
} heap;

typedef struct doc
{
    int doc_id;
    char name[50];
    char special[50];
    int available;
    pat waiting[3];
    int count;
    int type;
} doc;

typedef struct
{
    char* disease;
    char* special;
} allocate;

// ---------- GLOBAL ALLOCATION TABLE ----------

allocate type[] =
{
    {"cough", "General Physician"},
    {"cold", "General Physician"},
    {"fever", "General Physician"},
    {"sore throat", "General Physician"},
    {"fracture", "Orthopedic"},
    {"joint pain", "Orthopedic"},
    {"chest pain", "Cardiologist"},
    {"heart pain", "Cardiologist"},
    {"rashes", "Dermatologist"},
    {"allergy", "Dermatologist"},
    {"stomach pain", "Gastroenterologist"},
    {"food poisoning", "Gastroenterologist"},
    {NULL, NULL}
};

// ---------- PRIORITY CALCULATION ----------

float check_priority(pat p)
{
    float pr = 0;
    pr += p.emergency * 0.50f;
    pr += p.severity * 0.30f;
    pr += 0.20f * ((float)p.age / 100);
    return pr;
}

// ---------- QUEUE FUNCTIONS ----------

void init_queue(queue *q)
{
    q->front = q->rear = NULL;
}

int checkq(queue *q)
{
    return q->front == NULL;
}

void enqueue(queue *q, pat p)
{
    node *new = (node*)malloc(sizeof(node));
    new->patient = p;
    new->next = NULL;

    if (q->front == NULL)
    {
        q->rear = q->front = new;
    }
    else
    {
        q->rear->next = new;
        q->rear = q->rear->next;
    }
    printf("PATIENT (ID=%d) added to [NORMAL QUEUE]\nPatient Name : %s\n", p.id, p.name);
}

pat dequeue(queue* q)
{
    pat dummy = {-1, -1, "", "", 0, 0, 0.0, NULL};
    if (checkq(q))
    {
        printf("(no patient in queue.)\n");
        return dummy;
    }
    node* temp = q->front;
    pat p = temp->patient;
    if (q->front == q->rear)
    {
        q->rear = q->front = NULL;
    }
    else
    {
        q->front = q->front->next;
    }
    free(temp);
    return p;
}

// ---------- HEAP FUNCTIONS ----------

void init_heap(heap* h)
{
    h->size = 0;
}

void swap(pat *a, pat *b)
{
    pat temp = *a;
    *a = *b;
    *b = temp;
}

void insert_heap(heap *h, pat p)
{
    if(h->size >= 100)
    {
        printf("\nHeap Full\n");
        return;
    }
    int i = h->size++;
    h->pt[i] = p;
    while (i > 0 && h->pt[(i - 1) / 2].priority < h->pt[i].priority)
    {
        swap(&h->pt[(i - 1) / 2], &h->pt[i]);
        i = (i - 1) / 2;
    }
    printf("EMERGENCY PATIENT (ID=%d) added to (EMERGENCY QUEUE)\nPatient Name : %s\n", p.id, p.name);
}

pat remove_heap(heap *h)
{
    pat dummy = {-1, -1, "", "", 0, 0, 0.0, NULL};
    if (h->size == 0)
    {
        return dummy;
    }
    pat p = h->pt[0];
    h->pt[0] = h->pt[h->size - 1];
    h->size--;

    int i = 0;
    while (1)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;
        if (left < h->size && h->pt[left].priority > h->pt[largest].priority)
            largest = left;
        if (right < h->size && h->pt[right].priority > h->pt[largest].priority)
            largest = right;
        if (largest == i)
            break;
        swap(&h->pt[i], &h->pt[largest]);
        i = largest;
    }
    return p;
}

int load_counter() {
    FILE *fp = fopen("counter.txt", "r");
    int counter = 0;
    if(!fp)
    {
        // no counter file yet
    }
    if (fp != NULL) {
        fscanf(fp, "%d", &counter);
        fclose(fp);
    }
    return counter;
}

void save_counter(int counter) {
    FILE *fp = fopen("counter.txt", "w");
    if (fp != NULL) {
        fprintf(fp, "%d", counter);
        fclose(fp);
    }
}

int latest_id;

// ----------- INPUT, VIEW PATIENT -----------

pat input_patient()
{
    pat p;
    p.assigned = NULL;
    p.id = latest_id;
    latest_id++;

    printf("==========================================\n");
    printf("| Patient ID           : %d\n", p.id);
    printf("==========================================\n");

    printf("| Enter Patient Name   : ");
    scanf(" %49[^\n]", p.name);
    getchar();

    printf("| Enter Age            : ");
    scanf("%d", &p.age);
    getchar();

    printf("| Enter Disease        : ");
    scanf(" %49[^\n]", p.disease);
    getchar();

    printf("| Emergency Case (1/0) : ");
    scanf("%d", &p.emergency);

    printf("| Severity Level (1-10): ");
    scanf("%d", &p.severity);
    printf("==========================================\n");

    p.priority = check_priority(p);
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    printf("               Patient Registered Successfully!                \n");
    printf("---------------------------------------------------------------\n");
    printf("| %-15s : %-40d |\n", "Patient ID", p.id);
    printf("| %-15s : %-40s |\n", "Patient Name", p.name);
    printf("| %-15s : %-40s |\n", "Disease", p.disease);
    printf("| %-15s : %-40s |\n", "Emergency", (p.emergency ? "YES" : "NO"));
    printf("| %-15s : %-40d |\n", "Severity", p.severity);
    printf("| %-15s : %-40.2f |\n", "Priority", p.priority);
    printf("---------------------------------------------------------------\n");

    return p;
}

void view_normal_patient(queue* q)
{
    if (checkq(q))
    {
        printf("\n=========================================\n");
        printf("         NO PATIENTS IN QUEUE\n");
        printf("=========================================\n");
        return;
    }

    node* temp = q->front;
    printf("\n================ NORMAL QUEUE ================\n");

    while (temp != NULL)
    {
        printf("=============================================\n");
        printf("| Patient ID   : %-28d |\n", temp->patient.id);
        printf("| Name          : %-28s |\n", temp->patient.name);
        printf("| Disease       : %-28s |\n", temp->patient.disease);
        printf("| Age           : %-28d |\n", temp->patient.age);
        printf("| Emergency     : %-28s |\n", temp->patient.emergency ? "YES" : "NO");
        printf("| Severity      : %-28d |\n", temp->patient.severity);
        printf("| Priority      : %-28.2f |\n", temp->patient.priority);
        printf("=============================================\n\n");
        temp = temp->next;
    }

    printf("=============== END OF LIST =================\n");
}

void view_emergency_queue(heap* h)
{
    if (h->size == 0)
    {
        printf("\nNO PATIENT");
        return;
    }

    printf("\n=================== EMERGENCY QUEUE ===================\n\n");

    for (int i = 0; i < h->size; i++)
    {
        printf("=============================================\n");
        printf("| Patient ID    : %-27d |\n", h->pt[i].id);
        printf("| Name          : %-27s |\n", h->pt[i].name);
        printf("| Disease       : %-27s |\n", h->pt[i].disease);
        printf("| Age           : %-27d |\n", h->pt[i].age);
        printf("| Emergency     : %-27s |\n", h->pt[i].emergency ? "YES" : "NO");
        printf("| Severity      : %-27d |\n", h->pt[i].severity);
        printf("| Priority      : %-27.2f |\n", h->pt[i].priority);
        printf("=============================================\n\n");
    }

    printf("========================================================\n");
}

// -------- RE-ENQUEUE --------

void re_enequeue(queue* q, pat p)
{
    node* temp = (node*)malloc(sizeof(node));
    if (!temp) return;
    temp->patient = p;
    temp->next = NULL;

    if(checkq(q))
    {
        q->front = q->rear = temp;
    }
    else
    {
        temp->next = q->front->next;
        q->front->next = temp;
    }
}

// ---------------------- FILL ARRAY ----------------------

void fill_array(doc *d, pat *p)
{
    d->waiting[d->count] = *p;
    d->waiting[d->count].assigned = d;
    d->count++;

    printf("\n------------------------------------------------------------\n");
    printf("| Patient %-20s (ID=%-5d) assigned to Dr. %-15s |\n", 
           p->name, p->id, d->name);
    printf("------------------------------------------------------------\n");
}


// ---------------------- ASSIGN FUNCTION ----------------------

int assign(doc d[], pat *p)
{
    int n = 0;

    while (type[n].disease != NULL)
    {
        if (strcasecmp(type[n].disease, p->disease) == 0)
            break;
        n++;
    }

    if (type[n].disease == NULL)
    {
        printf("\n============================================================\n");
        printf("| No specialist found for '%s'. Referring to General Physician. |\n", p->disease);
        printf("============================================================\n");

        for (int i = 0; i < doc_count; i++)
        {
            if (strcasecmp(d[i].special, "General Physician") == 0 &&
                d[i].available == 1 && d[i].count != 3)
            {
                fill_array(&d[i], p);
                return 1;
            }
        }

        printf("\n============================================================\n");
        printf("| All General Physicians are busy. Try again later.         |\n");
        printf("============================================================\n");
        return 0;
    }
    else
    {
        for (int i = 0; i < doc_count; i++)
        {
            if (strcasecmp(d[i].special, type[n].special) == 0 &&
                d[i].available == 1 && d[i].count != 3)
            {
                fill_array(&d[i], p);
                return 1;
            }
        }

        printf("\n============================================================\n");
        printf("| All doctors for '%s' are currently busy. Try again later. |\n", type[n].special);
        printf("============================================================\n");
        return 0;
    }
    return 0;
}



// ---------------------- ASSIGN_DOC FUNCTION ----------------------

static int turn = 0;

void assign_doc(doc d[], queue *q, heap *h)
{
    pat hold[10];
    int hold_count = 0;
    int rounds = 5;

    while (rounds-- > 0 && (!checkq(q) || h->size > 0))
    {
        pat p;
        int success = 0;

        if (turn == 0 && h->size > 0)
        {
            p = remove_heap(h);
            success = assign(d, &p);

            if (!success)
            {
                hold[hold_count++] = p;
                printf("\n============================================================\n");
                printf("| Emergency patient %-20s put ON HOLD. |\n", p.name);
                printf("============================================================\n");
            }
            turn = 1;
        }
        else if (turn == 1 && !checkq(q))
        {
            p = dequeue(q);
            success = assign(d, &p);

            if (!success)
            {
                enqueue(q, p);
                printf("\n^^^^\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
                printf("| Normal patient %-20s reinserted into queue. |\n", p.name);
                printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
            }
            turn = 0;
        }
        else
        {
            turn = 1 - turn;
        }
    }

    for (int i = 0; i < hold_count; i++)
    {
        insert_heap(h, hold[i]);
        printf("\n^^^^\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
        printf("| Held emergency patient %-20s reinserted into heap. |\n", hold[i].name);
        printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    }

    printf("\n============================================================\n");
    printf("| Doctor assignment round completed successfully.           |\n");
    printf("============================================================\n");
}

// ---------------------- VIEW DOCTOR ----------------------
void view_doctor(doc d[])
{
    printf("\n================= DOCTOR LIST =================\n\n");
    printf("ID\t%-20s %-25s %s\n", "Name", "Specialization", "Available(0-No | 1-Yes)");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < doc_count; i++)
    {
        printf("%-3d\t%-20s %-25s %d\n",
               d[i].doc_id,
               d[i].name,
               d[i].special,
               d[i].available);
    }
    printf("=============================================================\n");
}



// ---------------------- DISCHARGE PATIENT ----------------------

void discharge_patient(doc d[])
{
    int id, found = 0;
    printf("\nEnter Patient ID to discharge: ");
    scanf("%d", &id);

    for (int i = 0; i < doc_count; i++)
    {
        for (int j = 0; j < d[i].count; j++)
        {
            if (d[i].waiting[j].id == id)
            {
                found = 1;
                printf("\nPatient %s (ID=%d) discharged from Dr.%s (%s)\n",
                       d[i].waiting[j].name,
                       d[i].waiting[j].id,
                       d[i].name,
                       d[i].special);
                for (int k = j; k < d[i].count - 1; k++)
                    d[i].waiting[k] = d[i].waiting[k + 1];
                d[i].count--;
                printf("\n Discharge successful!\n");
                return;
            }
        }
    }
    if (!found)
        printf("\n Patient with ID %d not found in any doctor's waiting list.\n", id);
}

// ---------------------- UPDATE PATIENT ----------------------
void update_patient(queue *q, heap *h)
{
    int id, found = 0;
    printf("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    printf("                 PATIENT UPDATE SECTION\n");
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    printf("\nEnter Patient ID to update: ");
    scanf("%d", &id);

    node *temp = q->front;
    while (temp != NULL)
    {
        if (temp->patient.id == id)
        {
            found = 1;
            printf("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
            printf("           PATIENT FOUND IN NORMAL QUEUE\n");
            printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
            printf("| Current Patient ID : %-28d |\n", temp->patient.id);
            printf("| Name               : %-28s |\n", temp->patient.name);
            printf("| Disease            : %-28s |\n", temp->patient.disease);
            printf("| Age                : %-28d |\n", temp->patient.age);
            printf("| Emergency          : %-28s |\n", temp->patient.emergency ? "YES" : "NO");
            printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
            printf("\nEnter new details below:\n");
            printf("---------------------------------------------\n");
            printf("Enter new name: ");
            scanf(" %49[^\n]", temp->patient.name);
            printf("Enter new disease: ");
            scanf(" %49[^\n]", temp->patient.disease);
            printf("Is it an emergency case (1 = Yes / 0 = No)? ");
            scanf("%d", &temp->patient.emergency);
            printf("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
            printf("   Patient details updated successfully!\n");
            printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
            return;
        }
        temp = temp->next;
    }

    for (int i = 0; i < h->size; i++)
    {
        if (h->pt[i].id == id)
        {
            found = 1;
            printf("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
            printf("           PATIENT FOUND IN EMERGENCY HEAP\n");
            printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
            printf("| Current Patient ID : %-28d |\n", h->pt[i].id);
            printf("| Name               : %-28s |\n", h->pt[i].name);
            printf("| Disease            : %-28s |\n", h->pt[i].disease);
            printf("| Age                : %-28d |\n", h->pt[i].age);
            printf("| Emergency          : %-28s |\n", h->pt[i].emergency ? "YES" : "NO");
            printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
            printf("\nEnter new details below:\n");
            printf("---------------------------------------------\n");
            printf("Enter new name: ");
            scanf(" %49[^\n]", h->pt[i].name);
            printf("Enter new disease: ");
            scanf(" %49[^\n]", h->pt[i].disease);
            printf("Is it an emergency case (1 = Yes / 0 = No)? ");
            scanf("%d", &h->pt[i].emergency);
            printf("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
            printf("   Patient details updated successfully!\n");
            printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
            return;
        }
    }

    if (!found)
    {
        printf("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
        printf("    Patient with ID %d not found in queue or heap.\n", id);
        printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    }
}

// ---------- FILE HANDLING FOR PATIENTS ----------

void append_patient(pat *p)
{
    FILE *fp = fopen("patients.txt", "a");
    if (!fp)
    {
        printf("\nError opening file for appending.\n");
        return;
    }
    fprintf(fp, "%d|%s|%d|%s|%d|%d|%.2f\n",
            p->id, p->name, p->age, p->disease,
            p->emergency, p->severity, p->priority);
    fclose(fp);
}

void save_all_patients(queue *normalq, heap *emergencyq)
{
    FILE *fp = fopen("patients.txt", "w");
    if (!fp)
    {
        printf("\nError opening file for writing.\n");
        return;
    }

    node *temp = normalq->front;
    while (temp != NULL)
    {
        pat p = temp->patient;
        fprintf(fp, "%d|%s|%d|%s|%d|%d|%.2f\n",
                p.id, p.name, p.age, p.disease,
                p.emergency, p.severity, p.priority);
        temp = temp->next;
    }

    for (int i = 0; i < emergencyq->size; i++)
    {
        pat p = emergencyq->pt[i];
        fprintf(fp, "%d|%s|%d|%s|%d|%d|%.2f\n",
                p.id, p.name, p.age, p.disease,
                p.emergency, p.severity, p.priority);
    }

    fclose(fp);
    printf("\nAll patients saved to file successfully!\n");
}

void load_all_patients(queue *normalq, heap *emergencyq)
{
    FILE *fp = fopen("patients.txt", "r");
    if (!fp)
    {
        printf("\nNo existing patient file found. Starting fresh.\n");
        return;
    }

    pat p;
    while (fscanf(fp, "%d|%49[^|]|%d|%49[^|]|%d|%d|%f",
                  &p.id, p.name, &p.age, p.disease,
                  &p.emergency, &p.severity, &p.priority) == 7)
    {
        if (p.emergency == 1)
            insert_heap(emergencyq, p);
        else
            enqueue(normalq, p);
    }

    fclose(fp);
    printf("\nPatients loaded from file successfully!\n");
}

// ---------- FILE HANDLING FOR DOCTORS ----------

void load_doctors(doc d[])
{
    FILE *fp = fopen("doctors.txt", "r");
    if (!fp)
    {
        printf("\nNo doctor file found\n");
        for (int i = 0; i < doc_count; i++) {
            d[i].doc_id = i;
            d[i].name[0] = '\0';
            d[i].special[0] = '\0';
            d[i].available = 0;
            d[i].count = 0;
            d[i].type = 0;
        }
        return;
    }
    int i = 0;
    while (fscanf(fp, "%d|%49[^|]|%49[^|]|%d|%d\n",
                  &d[i].doc_id,
                  d[i].name,
                  d[i].special,
                  &d[i].available,
                  &d[i].count) == 5)
    {
        i++;
        if (i >= doc_count) break;
    }
    fclose(fp);
    printf("\ndoctors loaded from file.\n");
}

void save_all_doctors(doc d[])
{
    FILE *fp = fopen("doctors.txt", "w");
    if (!fp)
    {
        printf("\nError opening doctor file for writing.\n");
        return;
    }

    for (int i = 0; i < doc_count; i++)
    {
        fprintf(fp, "%d|%s|%s|%d|%d\n",
                d[i].doc_id, d[i].name, d[i].special, d[i].available, d[i].count);
    }

    fclose(fp);
    printf("\nAll doctors saved to file successfully!\n");
}

void doc_available(doc d[])
{
q:
    printf("=============================");
    printf("\n  SET DOCTOR AVAILABILITY\n");
    printf("=============================\n");
    printf("\n ENTER DOC ID : ");
    int id;
    scanf("%d", &id);
    int found = 0;

    for (int i = 0; i < doc_count; i++)
    {
        if (d[i].doc_id == id)
        {
            found = 1;
            printf("\n+-------------------------------------------------+\n");
            printf("|                 DOCTOR DETAILS                     |\n");
            printf("+----------------------------------------------------+\n");
            printf("| %-15s : %-30d |\n", "Doctor ID", d[i].doc_id);
            printf("| %-15s : %-30s |\n", "Name", d[i].name);
            printf("| %-15s : %-30s |\n", "Specialization", d[i].special);
            printf("| %-15s : %-30s |\n", "Availability", d[i].available ? "YES" : "NO");
            printf("+----------------------------------------------------+\n");
            printf("\nDoctor found!\nSet availability (1-yes | 0-no): ");
            scanf("%d", &d[i].available);
            printf("Completed!\n");
            break;
        }
    }

    if (!found)
    {
        printf("\nNOT FOUND! ---- (RE-ENTER THE ID)\n");
        getchar(); getchar();
        system("cls");
        goto q;
    }
}

// ---------------------- MAIN FUNCTION ----------------------

int main()
{
    latest_id = load_counter();
    queue normalq;
    heap emergencyq;
    doc d[30];

    init_queue(&normalq);
    init_heap(&emergencyq);
    load_doctors(d);
    load_all_patients(&normalq, &emergencyq);

    int choice;
    while (1)
    {
        system("cls");
        printf("\n                               +++=============MEDI-ASSIST ===============+++\n");
        printf("|===========================|\n");
        printf("|1. Register New Patient    |\n");
        printf("|2. View Normal Queue       |\n");
        printf("|3. View Emergency Queue    |\n");
        printf("|4. Assign Doctor           |\n");
        printf("|5. View Doctors            |\n");
        printf("|6. Discharge Patient       |\n");
        printf("|7. Update Patient Info     |\n");
        printf("|8. Save All Data           |\n");
        printf("|9. SET DOC Avaialablity    |\n");
        printf("|10. Exit                   |\n");
        printf("|===========================|\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
            {
                pat p = input_patient();
                append_patient(&p);
                if (p.emergency == 1)
                    insert_heap(&emergencyq, p);
                else
                    enqueue(&normalq, p);
                save_counter(latest_id);
                break;
            }

            case 2: view_normal_patient(&normalq); break;
            case 3: view_emergency_queue(&emergencyq); break;
            case 4: assign_doc(d, &normalq, &emergencyq); break;
            case 5: view_doctor(d); break;
            case 6: discharge_patient(d); break;
            case 7: update_patient(&normalq, &emergencyq); break;

            case 8:
                save_all_patients(&normalq, &emergencyq);
                save_all_doctors(d);
                save_counter(latest_id);
                break;

            case 10:
                printf("\nExiting Program... Goodbye!\n");
                return 0;

            case 9: doc_available(d);
                    break;

            default:
                printf("\nInvalid Choice. Try again.\n");
        }
        printf("\npress enter to return to main menu....");
        getchar();
        getchar();
    }

    return 0;
}

