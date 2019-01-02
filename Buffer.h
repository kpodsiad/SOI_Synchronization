//
// Created by kamil on 12/23/18.
//

#ifndef MONITORS_BUFFER_H
#define MONITORS_BUFFER_H

extern const int SIZE;

#include "monitor.h"
#include <deque>
#include <iostream>

class Buffer : public Monitor
{
private:
	Condition empty, full;
	int size = SIZE;
	static int ID;
	int bufferID = ID;
	std::deque<int> q;
	bool finished = false;

	bool checkIfProducerEnded()
	{
		if( finished && q.empty() )
			return false;
	}

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
		if(!canAdd())
			return false;

		enter();
		q.push_front(item);
		std::cout<<"PRODUCER added item: "<<item<<" to buffer nr: "<<bufferID<<"\n";
		print();

		if(q.size() == 3)
			signal(empty);

		leave();
		return true;
	}

	bool consume()
	{
		enter();

		if( finished && q.empty() )
			return false;

		if(q.empty())
			wait(empty);

		if( finished && q.empty() )
			return false;

		auto x = q.front();
		std::cout<<"CONSUMER nr: "<<bufferID<<" ";
		std::cout<<"consume: "<<x<<"\n";
		q.pop_front();
		print();

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

	void print()
	{
		if(q.empty())
			std::cout<<"Queue nr "<<bufferID<<" is empty\n";
		else
		{
			auto x = q.size();
			std::cout<<"                                    Queue nr "<<bufferID<<"| elements: ";
			for(auto elem : q)
				std::cout<<elem<<",";
			std::cout<<"\n";
		}
	}

};

#endif //MONITORS_BUFFER_H
