#include"GYReverseSemaphore.h"
using namespace GYQuizMeytalThreading;


GYReverseSemaphore::GYReverseSemaphore(const __int64& inDesiredLocksTH)
:m_locksThreshold(inDesiredLocksTH)
{
}


std::function<void()> GYReverseSemaphore::getWaitFunction()
{
	mf_setLockedCount();
	//the wait is encapsulated (via lambda) back to the caller.
	//the lambda captures (by ref) members of its enclosing scope (this)
	return [&]
	{//notice: the actual WAIT is on a `unique_lock`. not wrapped in block.
		std::unique_lock<mutex> lockUntil(m_countThreads_mutex);
		//n invokers will wait for this member sync thread to finish
		m_blockUntilTHReached.wait(
								lockUntil,
								[&] { return m_isTHReached; });
	};
}//n times
void GYReverseSemaphore::mf_setLockedCount()
{
	{//notice : notifier's `lock_guard` is within a block
		std::lock_guard<mutex>	lock(m_countThreads_mutex);//<- locks
		if (m_countThreads == 0)
			m_isTHReached = false;
		++m_countThreads;
		if (m_locksThreshold == m_countThreads)
			//only ONE thread will reach here (THE actual notifier)
			m_isTHReached = true;
	}//critical section
	if (m_locksThreshold == m_countThreads)
	{
		//paradigm : one notifier -> many listeners
		m_blockUntilTHReached.notify_all();
		m_countThreads = 0;//reset
		//http://en.cppreference.com/w/cpp/thread/condition_variable/notify_all
	}
}//n times. lock is released on return
