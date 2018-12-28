//
// Created by kamil on 12/24/18.
//

#ifndef MONITORS_PRODUCER_H
#define MONITORS_PRODUCER_H

#include <pthread.h>
#include "Buffer.h"
#include "ItemCounter.h"
#include "MyThreadClass.h"

extern bool finished;

class Producer : public MyThreadClass
{
private:
	Buffer *buffer;
	Counter *counter;

	void InternalThreadEntry() override
	{
		for (int i = 0; i < 10; ++i)
		{
			buffer->add(i);
		}
	}

public:
	Producer(Buffer *buffer, Counter *counter) : buffer(buffer), counter(counter)
	{}

	Producer(Buffer *buffer) : buffer(buffer)
	{}

	void start()
	{
		StartInternalThread();
	}

	void join()
	{
		WaitForInternalThreadToExit();
	}

};

#endif //MONITORS_PRODUCER_H


//
//	void *producerFunction(void)
//	{
//		for (int i = 0; i < 10; ++i)
//		{
//			buffer.tryAdd(i);
//			usleep(100);
//		}
//	}
//
//	static void *p(void *context)
//	{
//		return ((Producer *)context)->producerFunction();
//	}

//	static void *hello_helper(void *context)
//	{
//		return ((Producer *)context)->hello();
//	}
//	void *hello(void)
//	{
//		std::cout << "Hello, world!" << std::endl;
//		int x=6;
//		buffer.tryAdd(x);
//		return 0;
//	}