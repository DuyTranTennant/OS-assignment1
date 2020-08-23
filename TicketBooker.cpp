/*
created by:Guanhua Wang, Duy Duc Tran
ID:a1709743,   a1739535(for undergraduate)
time:06.08.2020
Contact Email:
Include int main(int argc,char *argv[])
input: argv[1]
output: Screen

input sample:
ID arrival_time priority age total_tickets_required
for example: s1 3 1 0 50

output sample:
ID, arrival and termination times, ready time and durations of running and waiting
*/

#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <bitset>
#include <list>
#include <stdexcept>
#include <functional>
#include <utility>
#include <ctime>
#include <sstream>
using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////

//To hold output
class Customer_result
{
public:
    string name; //Initialized in initial()
    int arrival; //Initialized in initial()
    int end;
    int ready;
    int running; //Initialized in initial()
    int waiting;
};

//To hold input
class Customer
{
public:
    string customerID;
    int arrival_time;
    int priority;
    int age;
    int total_ticket;
    Customer *next = NULL;
    Customer_result *corresponding = new Customer_result(); //Everything is initialized in initial()
};

//To hold all inputs (unordered);
vector<Customer *> customer_in_queue1_vector;
vector<Customer *> customer_in_queue2_vector;

//To hold all outputs;
vector<Customer_result *> customer_result_vector;

//////////////////////////////////////////////////////////////////////////////////////////////

class Queue
{
public:
    Customer *header = NULL;
};

//These Queues are to hold sorted customers
Queue *queue1 = new Queue();
Queue *queue2 = new Queue();

//These Queues are for working on
Queue *working_queue1 = new Queue();
Queue *working_queue2 = new Queue();

//////////////////////////////////////////////////////////////////////////////////////////////

//Grab string from stdin , then turn it into Customer object and store in vector (unordered)
//Also , separate the object into 2 different vector due to their priority (priority <=3 will store into customer_in_queue1_vector)
void initial()
{
    string temp = "";
    stringstream ss;
    int i = 0;
    Customer *ptr = NULL;

    while (getline(cin, temp))
    {
        ptr = new Customer();
        while (i < 5)
        {
            ss << temp;
            switch (i)
            {
            case 0:
                ss >> ptr->customerID;
                break;
            case 1:
                ss >> ptr->arrival_time;
                break;
            case 2:
                ss >> ptr->priority;
                break;
            case 3:
                ss >> ptr->age;
                break;
            case 4:
                ss >> ptr->total_ticket;
                break;
            default:
                break;
            }
            i++;
        }
        ss.str(""); // <-- ss.clear() not working
        i = 0;

        //Put into the vector
        if (ptr->priority <= 3)
        {
            customer_in_queue1_vector.push_back(ptr);
        }
        else
        {
            customer_in_queue2_vector.push_back(ptr);
        }

        //Initialize corresponding as well (Customer_result object)
        ptr->corresponding->name = ptr->customerID;
        ptr->corresponding->arrival = ptr->arrival_time;
        ptr->corresponding->end = -1;
        ptr->corresponding->ready = -1;
        ptr->corresponding->running = 0;
        ptr->corresponding->waiting = 0;
    }
}

void printQueue(Customer *HeadQueue)
{
    while (HeadQueue != NULL)
    {
        cout << HeadQueue->customerID << endl;
        HeadQueue = HeadQueue->next;
    }
}
//Grab the Customer object from vector , then arrange the object into a queue list (ordered)
void setUpQueue(vector<Customer *> queue, Queue *queuePointer){
    Customer *ptr_queue1 = NULL;
    Customer *previous_customer = NULL;
    for (int i = 1; i < customer_in_queue1_vector.size(); i++)
    {
        //Reset back to header
        ptr_queue1 = queuePointer->header;
        previous_customer = NULL;

        while (ptr_queue1 != NULL)
        {
            if ((customer_in_queue1_vector[i]->arrival_time < ptr_queue1->arrival_time) || (customer_in_queue1_vector[i]->arrival_time == ptr_queue1->arrival_time && customer_in_queue1_vector[i]->priority < ptr_queue1->priority))
            {
                //Check if it is the header of queue1
                if (ptr_queue1 == queuePointer->header)
                {
                    queue1->header = customer_in_queue1_vector[i];
                    customer_in_queue1_vector[i]->next = ptr_queue1;
                    break;
                }
                else
                {
                    previous_customer->next = customer_in_queue1_vector[i];
                    customer_in_queue1_vector[i]->next = ptr_queue1;
                    break;
                }
            }
            else
            {
                previous_customer = ptr_queue1;
                ptr_queue1 = ptr_queue1->next;
            }
        }

        //Last customer
        if (ptr_queue1 == NULL)
        {
            previous_customer->next = customer_in_queue1_vector[i];
        }
    }
}
void input()
{
    Customer *ptr_queue1 = NULL;
    Customer *ptr_queue2 = NULL;
    Customer *previous_customer = NULL;
    Customer *temp = NULL;

    //Set queue1 and queue2 to the first customer
    queue1->header = customer_in_queue1_vector[0];
    queue2->header = customer_in_queue2_vector[0];

    //////////////////////////////////////////////////////////////////////////////////////////////
    //Set up queue1
    setUpQueue(customer_in_queue1_vector, queue1);
    //Set up queue2
    setUpQueue(customer_in_queue2_vector, queue2);
}

//Do queue1 and queue2 , then combine them into multilevel queue
void works()
{

    //1) Promotion

    //2) Reposition first customer in Queue1

    //3)Take all Customers from Queue1 and Queue2

    //4)Rearrange Queue1 (in Priority) and Queue2 (in Shortest Remaining)
}

//Print the output from Customer_result vector
void output()
{
    int i;
    int k = 0;
    int digit_counter = 1;
    int temp = 0;
    string spacing = "          ";

    cout << "name   arrival   end   ready   running   waiting" << endl;
    for (i = 0; i < customer_result_vector.size(); i++) // every result
    {
        cout << customer_result_vector[i]->name;
        while (k < 5)
        {
            switch (k)
            {
            case 0:
                temp = customer_result_vector[i]->arrival;
                break;
            case 1:
                temp = customer_result_vector[i]->end;
                break;
            case 2:
                temp = customer_result_vector[i]->ready;
                break;
            case 3:
                temp = customer_result_vector[i]->running;
                break;
            case 4:
                temp = customer_result_vector[i]->waiting;
                break;
            default:
                break;
            }

            //Find digit
            while (temp >= 10)
            {
                temp = temp / 10;
                digit_counter++;
            }

            //Set indentation
            switch (k)
            {
            case 0:
                cout << spacing.substr(0, 10 - digit_counter) << customer_result_vector[i]->arrival;
                break;
            case 1:
                cout << spacing.substr(0, 10 - digit_counter) << customer_result_vector[i]->end;
                break;
            case 2:
                cout << spacing.substr(0, 10 - digit_counter) << customer_result_vector[i]->ready;
                break;
            case 3:
                cout << spacing.substr(0, 10 - digit_counter) << customer_result_vector[i]->running;
                break;
            case 4:
                cout << spacing.substr(0, 10 - digit_counter) << customer_result_vector[i]->waiting;
                break;
            default:
                break;
            }

            //Reset
            k++;
            digit_counter = 1;
            temp = 0;
        }
        cout << endl;
        k = 0;
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    int i, j, k;
    freopen(argv[1], "r", stdin);

    initial(); // initial data

    cout << "Queue 1" << endl;
    for (int i = 0; i < customer_in_queue1_vector.size(); i++)
    {
        cout << customer_in_queue1_vector[i]->customerID << " " << customer_in_queue1_vector[i]->arrival_time << " " << customer_in_queue1_vector[i]->priority << " " << customer_in_queue1_vector[i]->age << " " << customer_in_queue1_vector[i]->total_ticket << endl;
    }
    cout << "Queue 2" << endl;
    for (int i = 0; i < customer_in_queue2_vector.size(); i++)
    {
        cout << customer_in_queue2_vector[i]->customerID << " " << customer_in_queue2_vector[i]->arrival_time << " " << customer_in_queue2_vector[i]->priority << " " << customer_in_queue2_vector[i]->age << " " << customer_in_queue2_vector[i]->total_ticket << endl;
    }

    input(); // input data
    cout << "Sorted Queue1" << endl;
    printQueue(queue1->header);
    cout << "Sorted Queue2" << endl;
    printQueue(queue2->header);
    //works();          // process data
    //output();         // output result
    return 0;
}
