#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP

#include <string>
#include <cstring>

using namespace std;

template <class T>
class PriorityQueue
{
		public:

		//Purpose: perform all operations necessary to instantiate a class object
		PriorityQueue(int queueSize);

		PriorityQueue();

		// Purpose: free all resources that the object has acquired
		~PriorityQueue();

		// Purpose: enqueue new group into priority queue; call other
		void enqueue (T node);

		//Purpose: remove the group (allocate the table) at the front of the priority queue from
		void dequeue();

		// return: groupID of the group at the front of the priority queue
		T peek();

		//return: true if queue is full, false otherwise
		bool isFull();

		// return: true if queue is empty, false otherwise
		bool isEmpty();

		int monthConverter(string _month); //changes calender values into single digit rankings

		string rankingConverter(int _ranking); // reverses the changes in monthConverter()

		void deleteReservation(T res); // removes a node in the queue from anywhere

		private:
		//Purpose: maintain heap properties by swapping node with parent if necessary
		void repairUpward(int nodeIndex);

		// Purpose: maintain heap properties by swapping node with child if necessary
		void repairDownward(int nodeIndex);

		T* priorityQueue; //pointer to the array used to implement priority queue
		int currentQueueSize; //number of skis currently in the priority queue
		int maxQueueSize; //maximum capacity of priority queue
};

template <class T>
PriorityQueue<T> :: PriorityQueue(int queueSize)
{
	maxQueueSize = queueSize;
	currentQueueSize = 0;
	priorityQueue = new T[queueSize];
}

template <class T>
PriorityQueue<T> :: PriorityQueue()
{
	maxQueueSize = 1000;
	currentQueueSize = 0;
	priorityQueue = new T[1000];
}

template <class T>
PriorityQueue<T> :: ~PriorityQueue()
{
	delete[] priorityQueue;
}

template <class T>
void PriorityQueue<T> :: enqueue(T node)
{
	if(!isFull())
	{
		if(isEmpty())
		{
			priorityQueue[0] = node;
			currentQueueSize++;
			return;
		}
		else
		{
			priorityQueue[currentQueueSize] = node;
			repairUpward(currentQueueSize);
			currentQueueSize++;
			return;
		}
	}
	else
	{
		return;
	}
}

template <class T>
void PriorityQueue<T> :: dequeue()
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
		return;
	}
}

template <class T>
T PriorityQueue<T> :: peek()
{
		return priorityQueue[0];
}

template <class T>
bool PriorityQueue<T> :: isFull()
{
		return (currentQueueSize == maxQueueSize);
}

template <class T>
bool PriorityQueue<T> :: isEmpty()
{
		return (currentQueueSize == 0);
}

template <class T>
void PriorityQueue<T> :: repairUpward(int nodeIndex)
{
	T temp;
	while(priorityQueue[nodeIndex] < priorityQueue[nodeIndex - 1] && nodeIndex != 0)
	{
			temp = priorityQueue[nodeIndex - 1];
			priorityQueue[nodeIndex - 1] = priorityQueue[nodeIndex];
			priorityQueue[nodeIndex] = temp;
			nodeIndex--;
	}
}

template <class T>
void PriorityQueue<T> :: repairDownward(int nodeIndex)
{
	T temp;
	while(priorityQueue[nodeIndex] > priorityQueue[nodeIndex + 1] && nodeIndex != currentQueueSize)
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
}

template <class T>
int PriorityQueue<T> :: monthConverter(string _month)
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
		return -1;
	}
}

template <class T>
string PriorityQueue<T> :: rankingConverter(int _ranking)
{
	if(_ranking == 1)
	{
		return "September";
	}
	if(_ranking == 2)
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
		return "error";
	}
}

template <class T>
void PriorityQueue<T> :: deleteReservation(T res)
{
	int place = -1;
	for(int i = 0; i < currentQueueSize; i++)
	{
		if(priorityQueue[i] == res)
		{
			place = i;
			break;
		}
	}
	if(place==-1){
		return;
	}
	else
	{
		for(int t = place; t < currentQueueSize-1; t++)
		{
			priorityQueue[t] = priorityQueue[t+1];
		}
		currentQueueSize--;
	}
}

#endif
