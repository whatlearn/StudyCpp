#pragma once
#include<deque>
#include<mutex>
#include<condition_variable>

using namespace std;

template<typename T>
class BlockingQueue
{
public:
	BlockingQueue()
	{
	}
	~BlockingQueue()
	{
	}

public:
	void push(const T &val)
	{
		lock_guard<mutex> lock(m_mutex);
		queue.push_back(val);
		cond.notify_one();
	}

	T pop()
	{
		unique_lock<mutex> lock(m_mutex);
		while (queue.empty())
		{
			cond.wait(lock);
		}
		T value = queue.front();
		queue.pop_front();
		return value;
	}

	int size()
	{
		return queue.size();
	}

private:
	condition_variable cond;
	deque<T> queue;
	mutex m_mutex;
};

