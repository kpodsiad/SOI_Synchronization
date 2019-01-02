//
// Created by kamil on 12/24/18.
//

#ifndef MONITORS_PRODUCER_H
#define MONITORS_PRODUCER_H

#include <pthread.h>
#include "Buffer.h"
#include "Counter.h"
#include "MyThreadClass.h"

class Producer : public MyThreadClass
{
private:
	Buffer *buffer;
	Counter *counter;

	void InternalThreadEntry() override
	{

		for (int j = 0; j < 15 ; ++j)
		{
			counter->checkIfCanAdd();
			int item = rand()%100;
			int id = j%N;
			buffer[id].add(item);
			counter->increaseAddedCount();
		}

		for (int i = 0; i < 10; ++i)
		{
			counter->checkIfCanAdd();
			int item = rand()%100;

			int id = rand()%N;

			while (!buffer[id].add(item))
				int id = rand()%N;

			counter->increaseAddedCount();
		}

		signalCustomers();
	}

	void signalCustomers() const
	{
		for(int i=0; i < N; ++i)
		{
			buffer[i].setFinished(true);
			buffer[i].wakeUpCustomer();
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