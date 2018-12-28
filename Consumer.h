//
// Created by kamil on 12/24/18.
//

#ifndef MONITORS_CONSUMER_H
#define MONITORS_CONSUMER_H

#include <iostream>
#include "MyThreadClass.h"
#include "Buffer.h"
#include "ItemCounter.h"

extern bool finished;

class Consumer : public MyThreadClass
{
private:
	static int ID;
	int myID = ID;
	Buffer *buffer;
	Counter *counter;

protected:
	void InternalThreadEntry() override
	{
		for (int i = 0; i < 10; ++i)
		{
			buffer->consume();
		}
	}

public:
	Consumer(Buffer *buffer, Counter *counter) : buffer(buffer), counter(counter)
	{
		++ID;
	}

	Consumer(Buffer *buffer) : buffer(buffer)
	{}

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
