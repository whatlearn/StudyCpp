#include <iostream>
#include<vector>
#include <thread>
#include <mutex>
#include<condition_variable>
#include"BlockingQueue.h"


BlockingQueue<int> bq;

void function1()
{
	int counts = 100;
	while (true)
	{
		bq.push(counts);
		counts--;
		//cout << "counts " << counts << endl;
		cout << bq.size() << endl;
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}

void function2()
{
	int num;
	while (true)
	{
		num = bq.pop();
		cout << "pop " << num << endl;
		this_thread::sleep_for(chrono::seconds(1));
	}
	return;
}

void test()
{
	std::cout << "print" << std::endl;
}

int main()
{
	thread t1(&function1);
	thread t2(function2);

	cout << t1.hardware_concurrency() << endl;

	t1.join();
	t2.join();

	return 0;
}