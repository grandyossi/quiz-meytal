#ifndef GY_MEYTAL_SEMAPHORE
#define GY_MEYTAL_SEMAPHORE    
#define BEGIN_GY_NS_MEYTAL_TH namespace GYQuizMeytalThreading {
#define END_GY_NS_MEYTAL_TH }
#include<mutex> //includes <functional>, 
using std::mutex;
//http://en.cppreference.com/w/cpp/thread/lock_guard
//http://en.cppreference.com/w/cpp/thread/condition_variable


BEGIN_GY_NS_MEYTAL_TH
//usage:
//A. known amount of DIFFERENT asynchronous tasks should meet at
//   a critical junction, where mutual synchronization is required.
//   This critical location is usually a "milestone",
//   which achievment is required prior to proceeding with
//   a whole "bigger/containing" task.
//	 (i.e : a [big] software's initialization milestone)
//B. when multiple instances of a principal "SAME thing"
//   should be "unleashed" simultaneously
//   while this specific "hell" properties are known only at runtime
//   (i.e : principal trading threads within a nice, little trading software)
class GYReverseSemaphore
{
public:
	//CTOR
	//@param the principal amount of working threads
	GYReverseSemaphore(const __int64&);


#pragma region GuardMechanism
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	//To be invoked in order to obtain a synchronization function.
	//The returned function must then be invoked 
	//in order to actually wait / block.
	//@returns a function to be invoked by the caller!
	std::function<void()> getWaitFunction();
	//i.e : obj.getWaitFunction()();
private:
	//private method : returns only once 
	void mf_setLockedCount();
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma endregion

	//private CTOR
	GYReverseSemaphore() = default;

	//signifies THE PRINCIPAL value from which execution is ignited
	const __int64				m_locksThreshold;
	//locks acquired count
	__int64						m_countThreads;
	//ye favorite synchronization primitive (can't be const : see `lock`)
	mutex						m_countThreads_mutex;
	//blocks until threshold value reached
	std::condition_variable		m_blockUntilTHReached = { };
	//Threashold sync object
	bool						m_isTHReached = false;
};
END_GY_NS_MEYTAL_TH
#endif
