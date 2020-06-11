#include <iostream>
using namespace std;

class set {
public:
	int x;
	int y;
};

class QueueNode
{
	set element;
	QueueNode* next;
	QueueNode(set element, QueueNode* next);
	friend class Queue;
};

class Queue
{
public:
	QueueNode* front;
	QueueNode* rear;
	Queue();
	~Queue();

	void add(set item);
	set poll();
	set peek() const;
	bool is_Empty()const;
	void clear();

};