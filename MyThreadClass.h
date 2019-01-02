//
// Created by kamil on 12/24/18.
//

#ifndef MONITORS_MYTHREADCLASS_H
#define MONITORS_MYTHREADCLASS_H

#include "pthread.h"
#include <iostream>

class MyThreadClass
{
public:
	MyThreadClass()
	{}

	virtual ~MyThreadClass()
	{}

	/** Returns true if the thread was successfully started, false if there was an error starting the thread */
	bool StartInternalThread()
	{
		return (pthread_create(&thread, NULL, InternalThreadEntryFunc, this) == 0);
	}

	/** Will not return until the internal thread has exited. */
	void WaitForInternalThreadToExit()
	{
		(void) pthread_join(thread, NULL);
		std::cout << "Thread dead\n";
	}

protected:
	/** Implement this method in your subclass with the code you want your thread to run. */
	virtual void InternalThreadEntry() = 0;

private:
	static void *InternalThreadEntryFunc(void *This)
	{
		((MyThreadClass *) This)->InternalThreadEntry();
		return NULL;
	}

	pthread_t thread;
};


#endif //MONITORS_MYTHREADCLASS_H
