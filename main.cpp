#include <iostream>
#include <pthread.h>
const int SIZE = 5;
const int N = 2;

#include "Producer.h"
#include "Consumer.h"

int Buffer::ID = 0;
int Consumer::ID = 0;

Buffer buffer[2];
Counter counter;



void *producerFunction(void*)
{
	for (int i = 0; i < 10; ++i)
	{
		//buffer.add(i);
	}
}
void *consumerFunction(void*)
{
	for (int i = 0; i < 10; ++i)
	{
		//buffer.consume();
	}
}

int main()
{
//	pthread_t producer, consumer;
//	pthread_create(&producer, NULL, producerFunction, NULL);
//	pthread_create(&consumer, NULL, consumerFunction, NULL);
//
//	pthread_join(producer, NULL);
//	pthread_join(consumer, NULL);

	Producer producer{buffer, &counter};
	Consumer consumer0{buffer, &counter};
	Consumer consumer1{buffer, &counter};

	producer.start();
	consumer0.start();
	consumer1.start();

	producer.join();
	consumer0.join();
	consumer1.join();

	return 0;
}
