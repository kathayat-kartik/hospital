#include<stdio.h>
#include<stdlib.h>
struct patient
{
	int id;
	int age;
	char name[50];
    struct patient*next;
};
struct patient* front=NULL;
struct patient* rear=NULL;
int currentId=0;
void addPatient()
{	
	struct patient*newNode=(struct patient*)malloc(sizeof(struct patient));
	if(newNode==NULL)
	{
		printf("Memory allocation failed!\n");
		return;
	}
	currentId++;
	newNode->id=currentId;
	printf("ENTER PATIENT DETAILS:\n");
	printf("Name:");
	scanf("%s",newNode->name);
	printf("Age:");
	scanf("%d",&newNode->age);
	newNode->next=NULL;
	if(front==NULL && rear==NULL)
	{
		front=rear=newNode;
	}
	else
	{
		rear->next=newNode;
		rear=newNode;
	}
	
}
void displayQueue()
{
	if(front==NULL)
	{
		printf("Queue is empty!");
		return;
	}
	struct patient* temp = front ;
	printf("\n---Patients in Queue---\n");
	while(temp!=NULL)
	{
		printf("ID:%d  Name:%s  Age:%d \n",temp->id,temp->name,temp->age);
	    temp=temp->next;
	}	
}
void servePatient()
{
	if(front==NULL)
	{
		printf("Queue is empty!\n");
		return ;
	}
	struct patient*temp=front;
	printf("Serving patient: %s (ID:%d)\n", temp->name, temp->id);
	front=front->next;
	free(temp);
	if(front==NULL)
	{
		rear=NULL;
	}
}
int main()
{
	int choice;
	int running=1;
	while (running==1) 
	{
		printf("\n--- Hospital Queue Menu ---\n");
        printf("1. Add Patient\n");
        printf("2. Display Patients\n");
        printf("3. Serve Patient\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addPatient();
                break;
            case 2:
                displayQueue();
                break;
            case 3:
                servePatient();
                break;
            case 4:
                printf("Exiting program...\n");
                running=0;
				break;
            default:
                printf("Invalid choice! Try again.\n");
        }
	}
}
