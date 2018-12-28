//
// Created by kamil on 12/23/18.
//

#ifndef MONITORS_BUFFER_H
#define MONITORS_BUFFER_H

extern const int SIZE;

#include "monitor.h"
#include <queue>
#include <iostream>
extern bool finished;

class Buffer : public Monitor
{
private:
	Condition empty, full;
	int size = SIZE;
	static int ID;
	int bufferID = ID;
	std::queue<int> q;

public:
	Buffer() : Monitor()
	{
		++ID;
	}

	bool add(int &item)
	{
		if(!canAdd())
			wait(full);

		enter();
		q.push(item);
		std::cout<<"added item: "<<item<<" to buffer nr: "<<bufferID<<"\n";

		if(q.size() == 1)
			signal(empty);

		leave();
		return true;
	}

	void consume()
	{
		enter();

		if(q.empty())
			wait(empty);

		auto x = q.front();
		std::cout<<"Consumer nr: "<<bufferID<<" ";
		std::cout<<"consume: "<<x<<"\n";
		q.pop();

		if(q.size() == size -1)
			signal(full);

		leave();
	}

	bool canAdd()
	{
		enter();
		bool canAdd = (q.size() < size);
		leave();
		return canAdd;
	}

	int getQueueSize() const
	{
		return static_cast<int>(q.size());
	}

	int getID()
	{
		return bufferID;
	}

	const Condition &getEmpty() const
	{
		return empty;
	}

	const Condition &getFull() const
	{
		return full;
	}
};

#endif //MONITORS_BUFFER_H
