#include <iostream>
#include <pthread.h>
const int SIZE = 3;
const int N = 5;

#include "Producer.h"
#include "Consumer.h"

int Buffer::ID = 0;
int Consumer::ID = 0;




int main()
{
	Buffer buffer[N];
	Counter counter;

	Producer producer{buffer, &counter};
	Consumer consumer[N];

	for(auto &i : consumer)
	{
		i.setBuffer(buffer);
		i.setCounter(&counter);
	}

	producer.start();
	sleep(5);
	for(auto &i : consumer)
	{
		i.start();
	}



	producer.join();
	for(auto &i : consumer)
	{
		i.join();
	}

	return 0;
}
