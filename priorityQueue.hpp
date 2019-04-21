#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP

#include <string>
#include <cstring>

// a struct to store info
struct GroupNode
{
  std::string groupName;
  int groupSize;
  int month;
  int day;
  int cost;
  //array for query choices
};


class PriorityQueue
{
    public:

    PriorityQueue(int queueSize);

    ~PriorityQueue();

    int rentalCost();

    int salesCost();

    void enqueue (std::string _groupName, int _groupSize, int _month, int _day, int _cost);

    //remove the group add group to return queue
    void dequeue();

    void returnEnqueue(std::string _groupName, int _groupSize, int _month, int _day, int _cost);

    void returnDequeue();

    GroupNode peek();

    GroupNode returnPeek();

    bool isFull();

    bool isEmpty();

    bool isReturnFull();

    bool isReturnEmpty();

    int monthConverter(std::string _month); //changes calender values into single digit rankings

    std::string rankingConverter(int _ranking); // reverses the changes in monthConverter()

    void deleteReservation(std::string groupName, int month, int day); // removes a node in the queue from anywhere

    private:
    //maintain heap properties
    void repairUpward(int nodeIndex);

    void repairUpwardReturn(int nodeIndex);

    // maintain heap properties
    void repairDownward(int nodeIndex);

    void repairDownwardReturn(int nodeIndex);

    GroupNode* priorityQueue; //pointer to the array used to implement priority queue
    GroupNode* returnQueue;
    int currentQueueSize; //number of skis currently in the priority queue
    int currentReturnSize;
    int maxQueueSize; //maximum capacity of priority queue
};

#endif
