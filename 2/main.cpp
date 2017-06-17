#include<thread>
#include"GYReverseSemaphore.h"
using std::thread;
using namespace GYQuizMeytalThreading;


GYReverseSemaphore appReadySync(5);


void thProc(const __int64& zzzleepForMs)
{
	//do x ...
	//
	//do y ...
	std::this_thread::sleep_for(std::chrono::milliseconds(zzzleepForMs));
	//do z ...
	//
	//until:
	appReadySync.getWaitFunction()();//will wait here for sync!
	//
	//do good...
	//
	//do evil...
}


//========================================
int main()
{
	thread t1(thProc, 1200);
	thread t2(thProc, 1800);
	thread t3(thProc, 3000);//ye oldie
	thread t4(thProc, 500);
	thread t5(thProc, 1800);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	return 0;//after 3 seconds
}
