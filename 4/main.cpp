#include<mutex>
#include<thread>
#include<vector>
#include<functional>
#include<iostream>
#include<atomic>
//#include"GYAtomicInt.h"
using std::thread;
using std::cout;


int g_i = 0;
std::timed_mutex g_i_mutex = {};
std::unique_lock<std::timed_mutex> g_i_mutex_lock = { g_i_mutex, std::defer_lock };
//sai = simple atomic int
std::atomic_int g_sai(0);
//-------------------------------------------------------------
//This method has an unresolved issue.
//TO_DO *0* : why crash (no matter where `.unlock()` is)
[[deprecated("This method has an unresolved issue")]]
void thProcTimedMutex()
{
	//shake things up via zzzleep and run:
	std::this_thread::sleep_for(std::chrono::milliseconds(180));
	if (g_i_mutex_lock.try_lock_for(std::chrono::milliseconds(18)))
	{
		//std::timed_mutex has non-recursive ownership semantics:
		//ONLY ONE lock can be acquired within the same thread
		//(that's why the lock is not within the loop)
		for (int k = 0; k < 10; ++k) ++g_i;
		//NOTICE : k MUST be declared WITHIN the `for`
		//g_i_mutex_lock.unlock();
	}//try lock
	if (g_i_mutex_lock.owns_lock()) g_i_mutex_lock.unlock();
}
void thProcAtomic()
{
	//shake things up, with style, via zzzleep and run:
	std::this_thread::sleep_for(std::chrono::milliseconds(18));
	for (int k = 0; k < 10; ++k) ++g_sai;
}
void thProc()
{
	//shake things up, with style, via zzzleep and run:
	std::this_thread::sleep_for(std::chrono::milliseconds(18));
	for (int k = 0; k < 10; ++k) ++g_i;
}
void doShakeThingzUp(std::function<void ()> inThreadProc)
{
	g_i = 0;
	g_sai = 0;
	std::vector<std::thread> vTh;
	for (int i = 0; i < 18; ++i)
		vTh.emplace_back(inThreadProc);
	for (auto& th : vTh)
		th.join();
	//ONE main thread rules here:
	cout << ((g_i > 0) ? "Unsafe" : "Atomic") << " increment :   ";
	cout << ((g_i > 0) ? g_i : g_sai) << "\n";
}
//============================================
int main()
{
	doShakeThingzUp(thProc);
	doShakeThingzUp(thProc);
	doShakeThingzUp(thProc);
	doShakeThingzUp(thProc);
	cout << "--------------------------\n";
	doShakeThingzUp(thProcAtomic);
	doShakeThingzUp(thProcAtomic);
	doShakeThingzUp(thProcAtomic);
	doShakeThingzUp(thProcAtomic);
	getchar();
	return 0;
}
