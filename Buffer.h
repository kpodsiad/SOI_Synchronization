//
// Created by kamil on 12/23/18.
//

#ifndef MONITORS_BUFFER_H
#define MONITORS_BUFFER_H

extern const int SIZE;

#include "monitor.h"
#include <queue>
#include <iostream>

class Buffer : public Monitor
{
private:
	Condition empty, full;
	int size = SIZE;
	static int ID;
	int bufferID = ID;
	std::queue<int> q;
	bool finished = false;

public:
	Buffer() : Monitor()
	{
		++Buffer::ID;
	}

	bool add(int &item)
	{
		if(!canAdd())
			return false;

		enter();
		q.push(item);
		std::cout<<"added item: "<<item<<" to buffer nr: "<<bufferID<<"\n";

		if(q.size() == 1)
			signal(empty);

		leave();
		return true;
	}

	bool consume()
	{
		enter();

		if(q.empty())
			wait(empty);

		if( finished && q.empty() )
			return false;

		auto x = q.front();
		std::cout<<"Consumer nr: "<<bufferID<<" ";
		std::cout<<"consume: "<<x<<"\n";
		q.pop();

		if(q.size() == size -1)
			signal(full);

		leave();
		return true;
	}

	bool canAdd()
	{
		enter();
		bool canAdd = (q.size() < size);
		leave();
		return canAdd;
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

};

#endif //MONITORS_BUFFER_H
