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
	} //��Ұ� ó�����´ٸ� front�� �ش� ��Ҹ� ����������Ѵ�.
	else {
		rear->next = newNode;
		rear = newNode;
	}
}
set Queue::poll() {
	QueueNode* tmp = front;
	set removed = front->element;
	front = front->next; //front�� �� ��ҷ� �Ű��ش�. 
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