#include "queue.h"
QueueNode::QueueNode(set element, QueueNode* next)
{
	this->element = element;
	this->next = next;
}
Queue::Queue() {
	front = NULL;
	rear = NULL;
}
Queue::~Queue() {
	clear();
}

void Queue::clear() {
	QueueNode* tmp = front;
	while (tmp != NULL) {
		tmp = tmp->next;
		delete front;
		front = tmp;
	}
}
void Queue::add(set item) {
	QueueNode* newNode = new QueueNode(item, NULL);

	if (is_Empty()) {
		front = newNode;
		rear = newNode;
	} //요소가 처음들어온다면 front도 해당 요소를 가리켜줘야한다.
	else {
		rear->next = newNode;
		rear = newNode;
	}
}
set Queue::poll() {
	QueueNode* tmp = front;
	set removed = front->element;
	front = front->next; //front를 앞 요소로 옮겨준다. 
	delete tmp;
	return removed;
}

set Queue::peek() const {
	return front->element;
}
bool Queue::is_Empty()const
{
	if (front == NULL) return true;
	return false;
}