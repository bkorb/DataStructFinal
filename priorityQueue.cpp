
#include <iostream>
#include <string>
#include "priorityQueue.hpp"

using namespace std;

PriorityQueue :: PriorityQueue(int queueSize)
{
  maxQueueSize = queueSize;
  currentQueueSize = 0;
  priorityQueue = new GroupNode[queueSize];
}

PriorityQueue :: ~PriorityQueue()
{
  delete[] priorityQueue;
}

void PriorityQueue :: enqueue(string _groupName, int _groupSize, int _month, int _day)
{
  if(!isFull())
  {
    if(isEmpty())
    {
      priorityQueue[0].groupName = _groupName;
      priorityQueue[0].groupSize = _groupSize;
      priorityQueue[0].month = _month;
      priorityQueue[0].day = _day;
      currentQueueSize++;
      return;
    }
    else
    {
      priorityQueue[currentQueueSize].groupName = _groupName;
      priorityQueue[currentQueueSize].groupSize = _groupSize;
      priorityQueue[currentQueueSize].month = _month;
      priorityQueue[currentQueueSize].day = _day;
      repairUpward(currentQueueSize);
      currentQueueSize++;
      return;
    }
  }
  else
  {
    cout << "Heap full, cannot enqueue" << endl;
    return;
  }
}

void PriorityQueue :: dequeue()
{
  if(!isEmpty())
  {
    currentQueueSize--;
    priorityQueue[0] = priorityQueue[currentQueueSize];
    repairDownward(0);
    return;
  }
  else
  {
    cout << "Queue empty, cannot dequeue" << endl;
    return;
  }
}

GroupNode PriorityQueue :: peek()
{
  if(!isEmpty())
  {
    return priorityQueue[0];
  }
  else
  {
    cout << "Heap empty, nothing to peek" << endl;
    return priorityQueue[0];
  }
}

bool PriorityQueue :: isFull()
{
  if(currentQueueSize == maxQueueSize) return true;
  else return false;
}

bool PriorityQueue :: isEmpty()
{
 if(currentQueueSize == 0) return true;
 else return false;
}

void PriorityQueue :: repairUpward(int nodeIndex)
{
  GroupNode temp;
  while(priorityQueue[nodeIndex].month <= priorityQueue[nodeIndex - 1].month && nodeIndex != 0)
  {
      temp = priorityQueue[nodeIndex - 1];
      priorityQueue[nodeIndex - 1] = priorityQueue[nodeIndex];
      priorityQueue[nodeIndex] = temp;
      nodeIndex--;
  }
  int i = 0;
  while(i != currentQueueSize - 1)
  {
    if(priorityQueue[i].month == priorityQueue[i + 1].month)
    {
      if(priorityQueue[i].day > priorityQueue[i + 1].day)
      {
        temp = priorityQueue[i + 1];
        priorityQueue[i + 1] = priorityQueue[i];
        priorityQueue[i] = temp;
      }
    }
    i++;
  }
  i = 0;
  while(i != currentQueueSize - 1)
  {
    if(priorityQueue[i].month == priorityQueue[i + 1].month && priorityQueue[i].day == priorityQueue[i + 1].day)
    {
      if(priorityQueue[i].groupSize > priorityQueue[i + 1].groupSize)
      {
        temp = priorityQueue[i + 1];
        priorityQueue[i + 1] = priorityQueue[i];
        priorityQueue[i] = temp;
      }
    }
    i++;
  }
  return;
}

void PriorityQueue :: repairDownward(int nodeIndex)
{
  GroupNode temp;
  while(priorityQueue[nodeIndex].month > priorityQueue[nodeIndex + 1].month && nodeIndex != currentQueueSize)
  {
    temp = priorityQueue[nodeIndex + 1];
    priorityQueue[nodeIndex + 1] = priorityQueue[nodeIndex];
    priorityQueue[nodeIndex] = temp;
    nodeIndex++;
  }
  if(currentQueueSize == 2)
  {
    return;
  }
  int i = 0;
  while(i != currentQueueSize)
  {
    if(priorityQueue[i].month == priorityQueue[i + 1].month)
    {
      if(priorityQueue[i].day > priorityQueue[i + 1].day)
      {
        temp = priorityQueue[i + 1];
        priorityQueue[i + 1] = priorityQueue[i];
        priorityQueue[i] = temp;
      }
    }
    i++;
  }
  i = 0;
  while(i != currentQueueSize)
  {
    if(priorityQueue[i].month == priorityQueue[i + 1].month && priorityQueue[i].day == priorityQueue[i + 1].day)
    {
      if(priorityQueue[i].groupSize > priorityQueue[i + 1].groupSize)
      {
        temp = priorityQueue[i + 1];
        priorityQueue[i + 1] = priorityQueue[i];
        priorityQueue[i] = temp;
      }
    }
    i++;
  }
  return;
}

int PriorityQueue :: monthConverter(string _month)
{
  if(_month == "September")
  {
    return 1;
  }
  if(_month == "October")
  {
    return 2;
  }
  if(_month == "November")
  {
    return 3;
  }
  if(_month == "December")
  {
    return 4;
  }
  if(_month == "January")
  {
    return 5;
  }
  if(_month == "Febuary")
  {
    return 6;
  }
  if(_month == "March")
  {
    return 7;
  }
  if(_month == "April")
  {
    return 8;
  }
  if(_month == "May")
  {
    return 9;
  }
  else
  {
    cout << "invalid month entered, please enter a new month: ";
    cin >> _month;
    return monthConverter(_month);
  }
}

string PriorityQueue :: rankingConverter(int _ranking)
{
  if(_ranking == 1)
  {
    return "September";
  }
  if(_ranking == 3)
  {
    return "October";
  }
  if(_ranking == 3)
  {
    return "November";
  }
  if(_ranking == 4)
  {
    return "December";
  }
  if(_ranking == 5)
  {
    return "January";
  }
  if(_ranking == 6)
  {
    return "Febuary";
  }
  if(_ranking == 7)
  {
    return "March";
  }
  if(_ranking == 8)
  {
    return "April";
  }
  if(_ranking == 9)
  {
    return "May";
  }
  else
  {
    cout << "error in rankings" << endl;
    return "error";
  }
}

void PriorityQueue :: deleteReservation(string groupName, int month, int day)
{
  int test = 0, place = 0;
  for(int i = 0; i < currentQueueSize; i++)
  {
    if(priorityQueue[i].groupName == groupName && priorityQueue[i].month == month)
    {
      if(priorityQueue[i].day == day)
      {
        test = 1;
        place = i;
        break;
      }
    }
  }
  if(test == 0)
  {
    cout << "No matching parties in the queue" << endl;
    return;
  }
  else
  {
    for(int t = place; t < currentQueueSize-1; t++)
    {
        priorityQueue[t] = priorityQueue[t+1];
    }
    cout << "Reservation deleted" << endl;
    return;
  }
}

int main(int argc, char *argv[])
{
  PriorityQueue queue = PriorityQueue(stoi(argv[1]));
  string name, group, _month, _day;
  int l = 0, c = 0, month = 0;
  while(l == 0)
  {
    cout << "============Main Menu============" << endl;
    cout << "1. Get group information from Inventory" << endl;
    cout << "2. Add a group to Priority Queue" << endl;
    cout << "3. Show next group in the queue" << endl;
    cout << "4. Help Next group" << endl;
    cout << "5. Cancel Reservation" << endl;
    cout << "6. Quit" << endl;
    cin >> c;
    switch (c)
    {
      case 1:
      // use this as the interaction between inventory and queue, so there can be specific skis in the queue;
      // it will add all the information selected as a node in the queue
      break;

      case 2:
      cin.ignore();
      if(queue.isFull())
      {
        cout << "Queue full, cannot enqueue" << endl;
        break;
      }
      cout << "Enter Group Name: " ;
      getline(cin, name);
      cout << endl;
      cout << "Enter Group Size: " ;
      getline(cin, group);
      cout << endl;
      cout << "Enter Month not in numerical form: ";
      getline(cin, _month);
      cout << endl;
      month = queue.monthConverter(_month);
      cout << "Enter Day in numerical form: ";
      getline(cin, _day);
      cout << endl;
      queue.enqueue(name, stoi(group), month, stoi(_day));
      break;
      case 3:
      if(queue.isEmpty())
      {
        cout << "Queue empty, nothing to peek" << endl;
        break;
      }
      cout<<"Group Name: " <<queue.peek().groupName<<endl;
      cout<<"Group Size: " <<queue.peek().groupSize<<endl;
      cout<<"Month: "<< queue.rankingConverter(queue.peek().month) <<endl;
      cout<<"Day: " <<queue.peek().day<<endl;
      break;
      case 4:
      if(queue.isEmpty())
      {
        cout << "Queue empty, cannot dequeue" << endl;
        break;
      }
      cout<<"Group Name: "<<queue.peek().groupName <<endl;
      // will display what skis, and how many skis
      queue.dequeue();
      break;
      case 5:
      if(queue.isEmpty())
      {
        cout << "Queue empty, cannot delete a reservation" << endl;
        break;
      }
      else
      {
        cin.ignore();
        cout << "Enter Group Name: ";
        getline(cin, name);
        cout << endl;
        cout << "Enter Month not in numerical form: ";
        getline(cin, _month);
        cout << endl;
        month = queue.monthConverter(_month);
        cout << "Enter Day in numerical form: ";
        getline(cin, _day);
        cout << endl;
        queue.deleteReservation(name, month, stoi(_day));
        break;
      }
      case 6:
      cout << "Goodbye!" << endl;
      if(!queue.isEmpty())
      {
        queue.~PriorityQueue();
      }
      l++;
      break;
    }
  }
  return 0;
}
