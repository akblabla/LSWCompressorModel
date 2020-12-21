#pragma once
#include <queue>
#include <mutex>
template <typename T>
class PopFrontQueue :
	private std::queue<T>
{
public:
	bool empty() const;
	void push(const T& val);
	T pop_front();
private:
	std::mutex _mutex;
};

template<typename T>
inline bool PopFrontQueue<T>::empty() const
{
	return std::queue<T>::empty();
}

template<typename T>
inline void PopFrontQueue<T>::push(const T& val)
{
	_mutex.lock();
	std::queue<T>::push(val);
	_mutex.unlock();
}

template<typename T>
inline T PopFrontQueue<T>::pop_front()
{
	_mutex.lock();
	T val = std::queue<T>::front();
	std::queue<T>::pop();
	_mutex.unlock();
	return val;
}
