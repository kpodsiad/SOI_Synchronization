#include <iostream>
#include <pthread.h>
const int SIZE = 5;
const int N = 2;

#include "Buffer.h"
#include "Producer.h"
#include "Consumer.h"

int Buffer::ID = 0;
int Consumer::ID = 0;
Buffer buffer;


void *producerFunction(void*)
{
	for (int i = 0; i < 10; ++i)
	{
		buffer.add(i);
	}
}
void *consumerFunction(void*)
{
	for (int i = 0; i < 10; ++i)
	{
		buffer.consume();
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

	Producer producer{&buffer};
	Consumer consumer{&buffer};
	producer.start();
	consumer.start();
	producer.join();
	consumer.join();

	return 0;
}
