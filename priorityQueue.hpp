#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP

#include <string>
#include <cstring>

// a struct to store customers group information
struct GroupNode
{
  std::string groupName;
  int groupSize;
  int month;
  int day;
  int cost;
  int numRepairs;
  //array for query choices
};


class PriorityQueue
{
    public:

    //Purpose: perform all operations necessary to instantiate a class object
    PriorityQueue(int queueSize);

    // Purpose: free all resources that the object has acquired
    ~PriorityQueue();

    // Purpose: enqueue new group into priority queue; call other
    void enqueue (std::string _groupName, int _groupSize, int _month, int _day);

    //Purpose: remove the group (allocate the table) at the front of the priority queue from
    void dequeue();

    // return: groupID of the group at the front of the priority queue
    GroupNode peek();

    //return: true if queue is full, false otherwise
    bool isFull();

    // return: true if queue is empty, false otherwise
    bool isEmpty();

    int monthConverter(std::string _month); //changes calender values into single digit rankings

    std::string rankingConverter(int _ranking); // reverses the changes in monthConverter()

    void deleteReservation(std::string groupName, int month, int day); // removes a node in the queue from anywhere

    private:
    //Purpose: maintain heap properties by swapping node with parent if necessary
    void repairUpward(int nodeIndex);

    // Purpose: maintain heap properties by swapping node with child if necessary
    void repairDownward(int nodeIndex);

    GroupNode* priorityQueue; //pointer to the array used to implement priority queue
    GroupNode* returnQueue;
    int currentQueueSize; //number of skis currently in the priority queue
    int currentReturnSize;
    int maxQueueSize; //maximum capacity of priority queue
};

#endif
