//
// Created by kamil on 12/23/18.
//

#ifndef MONITORS_ITEMCOUNTER_H
#define MONITORS_ITEMCOUNTER_H

#include <iostream>
#include "monitor.h"

extern const int SIZE;
extern const int N;


class Counter : Monitor
{
private:
	int addedCount = 0;
	int qCapacity = SIZE;
	int qAmount = N;
	Condition full;

public:
	Counter() : Monitor()
	{}

	void checkIfCanAdd()
	{
		enter();

		if(addedCount >= qCapacity*qAmount)
		{
			std::cout<<"Producer is waiting\n";
			leave();
			wait(full);
		}
		else
			leave();
	}

	void wakeUpProducer()
	{
		signal(full);
	}

	void increaseAddedCount()
	{
		++addedCount;
	}

	void decreaseAddedCount()
	{
		--addedCount;
	}
};

#endif //MONITORS_ITEMCOUNTER_H
