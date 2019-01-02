//
// Created by kamil on 1/2/19.
//

#ifndef MONITORS_PRINTER_H
#define MONITORS_PRINTER_H


#include "Buffer.h"
#include "deque"

class Printer : public Monitor
{
public:
	Printer()
	{}

	void print(const int ID, std::deque<int> &q)
	{
		enter();

		if(q.empty())
			std::cout<<"                                Queue nr "<<ID<<" is empty\n";
		else
		{
			auto x = q.size();
			std::cout<<"Queue nr "<<ID<<"| elements: ";
			for(auto elem : q)
				std::cout<<elem<<",";
			std::cout<<"\n";
		}

		leave();
	}
};



#endif //MONITORS_PRINTER_H



