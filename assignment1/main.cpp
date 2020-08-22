#include <iostream>
#include <string>
using namespace std;
class priorityQueue
{
public:
    string id;
    int priority;
    int arriveTime;
    int age;
    int ticketRequire;
    priorityQueue *next;
    priorityQueue();
    priorityQueue(string idP, int priorityP, int arriveTimeP, int ageP, int ticketRequireP, priorityQueue *nextP)
    {
        id = idP;
        priority = priorityP;
        arriveTime = arriveTimeP;
        age = ageP;
        ticketRequire = ticketRequireP;
        next = nextP;
    }
};

void printQueue(priorityQueue *root)
{

    while (root != NULL)
    {
        cout << root->id << "\t arri: " << root->arriveTime << '\t' << root->ticketRequire << "\t Prio: " << root->priority << '\t' << root->age << '\t' << root->ticketRequire << '\n';
        root = root->next;
    }
}

priorityQueue *pop(priorityQueue *head)
{
    priorityQueue *temp;
    temp = head->next;
    free(head);
    return temp;
}

priorityQueue *push_back(priorityQueue *root, priorityQueue *newNode ){
    while (root != NULL)
    {
        root = root->next;
    }
    root = newNode;
}

priorityQueue *push(priorityQueue *root, string idP, int priorityP, int arriveTimeP, int ageP, int ticketRequireP, priorityQueue *nextP)
{
    priorityQueue *newNode = new priorityQueue(idP, priorityP, arriveTimeP, ageP, ticketRequireP, NULL);
    if(root == NULL){
        return newNode;
    }
    if (root->priority > newNode->priority)
    {
        newNode->next = root;
        return newNode;
    }
    priorityQueue *res;
    res = root;
    while (root->next != NULL && root->next->arriveTime < newNode->arriveTime)
    {
        if (root->arriveTime != newNode->arriveTime){
            root = root->next;
        }
    }
    if (root->arriveTime == newNode->arriveTime){
        priorityQueue *temp;
        // temp = root->next;

        // newNode->next = temp;
        // root->next = newNode;
    }
    newNode->next = root->next;
    root->next = newNode;
    return res;
}

int main()
{
   // cout << "name \t" << "arrival_time \t" <<  "tickets_required \t" <<  "running \t" <<  "priority_number \t" << "age/runs\n";
    priorityQueue *queue1 = NULL;
    priorityQueue *queue2;
    queue1 = push(queue1, "a0", 2, 2, 0, 2, NULL);
    queue1 = push(queue1, "a1",2, 6, 0, 18, NULL);
    queue1 = push(queue1, "a2",1, 2, 0, 2, NULL);
    // printQueue(queue1);
    // cout << queue1 << endl;
    // queue1 = pop(queue1);
    // printQueue(queue1);
    int time = 0;
    while(queue1 != NULL){
        time+= queue1->arriveTime;
        cout << time << endl;
        cout << queue1->id << "\t arri: " << queue1->arriveTime << '\t' << queue1->ticketRequire << "\t Prio: " << queue1->priority << '\t' << queue1->age << '\t' << queue1->ticketRequire << '\n';
        queue1 = pop(queue1);
    }
}