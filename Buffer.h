//
// Created by kamil on 12/23/18.
//

#ifndef MONITORS_BUFFER_H
#define MONITORS_BUFFER_H


#include "monitor.h"
#include "Printer.h"
#include <deque>
#include <iostream>

class Buffer : public Monitor
{
private:
	Condition empty, full;
	Printer *printer = nullptr;
	int size = SIZE;
	static int ID;
	int bufferID = ID;
	std::deque<int> q;
	bool finished = false;

	bool canAdd()
	{
		enter();
		bool canAdd = (q.size() < size);
		leave();
		return canAdd;
	}

public:
	Buffer() : Monitor()
	{
		++Buffer::ID;
	}

	bool add(int &item)
	{
		if(!canAdd()) //if queue is full
			return false;

		enter();
		q.push_front(item);
//		std::cout<<"PRODUCER added item: "<<item<<" to buffer nr: "<<bufferID<<"\n";
//		print();
		printer->print(bufferID, q);

		if(q.size() == 1)
			signal(empty);

		leave();
		return true;
	}

	bool consume()
	{
		enter();

		if( finished && q.empty() )
			return false;

		if(q.empty()) //wait if the queue is empty
			wait(empty);

		if( finished && q.empty() )
			return false;

		q.pop_front();

		printer->print(bufferID, q);

		if(q.size() == size - 1)
			signal(full);

		leave();
		return true;
	}



	int getID()
	{
		return bufferID;
	}

	void setFinished(bool finished)
	{
		this->finished = finished;
	}

	void wakeUpCustomer()
	{
		signal(empty);
	}

	void setPrinter(Printer *printer)
	{
		Buffer::printer = printer;
	}
};

#endif //MONITORS_BUFFER_H
