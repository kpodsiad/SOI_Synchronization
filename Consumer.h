//
// Created by kamil on 12/24/18.
//

#ifndef MONITORS_CONSUMER_H
#define MONITORS_CONSUMER_H

#include <iostream>
#include "MyThreadClass.h"
#include "Buffer.h"
#include "Counter.h"

extern bool finished;

class Consumer : public MyThreadClass
{
private:
	static int ID;
	int myID = ID;
	Buffer *buffer = nullptr;
	Counter *counter = nullptr;

protected:
	void InternalThreadEntry() override
	{
		//sleep(4);
		while( buffer[myID].consume() )
		{
			sleep(1);
			counter->decreaseAddedCount();
			counter->wakeUpProducer();
		}
	}

public:
	Consumer(Buffer *buffer, Counter *counter) : buffer(buffer), counter(counter)
	{
		++Consumer::ID;
	}

	Consumer(Buffer *buffer) : buffer(buffer)
	{
		++Consumer::ID;
	}

	Consumer() : myID(Consumer::ID)
	{
		++Consumer::ID;
	}

	void setBuffer(Buffer *buffer)
	{
		Consumer::buffer = buffer;
	}

	void setCounter(Counter *counter)
	{
		Consumer::counter = counter;
	}

	void start()
	{
		StartInternalThread();
	}

	void join()
	{
		WaitForInternalThreadToExit();
	}
};

#endif //MONITORS_CONSUMER_H
