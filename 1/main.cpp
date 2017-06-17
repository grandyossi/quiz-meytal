#include"GYCalculatorApp.h"
using namespace GYQuizMeytalCalculator;


int main()
{
	__int64 theCalculation;
	printf("Calculator | Input & Enter to calculate\n(QUIT = Zero result OR plain Enter)\n\n");
	do
	{
		theCalculation = GYCalculatorApp::execute();
		printf("\nResult is :    %lld\n\n", theCalculation);
	} while (theCalculation != 0);
	return 0;
}
