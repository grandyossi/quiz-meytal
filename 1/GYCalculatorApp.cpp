#ifdef _WIN32
#include<conio.h> //MS SPECIFIC
#define gy_get_char _getche
#else
#include<iostream>
#define gy_get_char getchar
#endif //WIN
#include"GYCalculatorApp.h"
using namespace GYQuizMeytalCalculator;
using std::queue;
using std::stack;


namespace {
	//an empty queue of aritmetic chars.
	//usage : ONLY as default arg (primary/main method invocation)
	queue<char> fifoAritmeticzGlobal;
} //anonymous [hidden] namespace


//The current stack is about to return.
//@returns calculations according to current queues
static __int64 getStackNumbersArtimetics(queue<__int64>& inNumbers,
					 queue<char>& inAritmetics)
{//TO_DO *1* : assert `n` numbers , `n-1` aritmetics ?
	__int64 x, y, tempCalc = 0;
	//inNumbers is a queue -> can't push tempCalcz to the queue!
	bool isCalcMade = false;//++
	//TO_DO *1* : assert NONZERO sized aritmeticz container
	while (inNumbers.size() > 1 || isCalcMade)
	{
		if (isCalcMade)
		{
			x = tempCalc;//current x is the previous calc result
			isCalcMade = false;
		}
		else
		{
			x = inNumbers.front();
			inNumbers.pop();
		}
		y = inNumbers.front();
		inNumbers.pop();
		switch (inAritmetics.front())
		{
		case '+':
			tempCalc = x + y; break;
		case '-':
			tempCalc = x - y; break;
		case '/':
			tempCalc = x / y; break; //TO_DO *3* : divide by zero ?
		case '*':
			tempCalc = x * y; break;
		case '^':
			tempCalc = (__int64)pow(x, y); break;
		}
		inAritmetics.pop();
		if (inNumbers.size() == 0) break;//++
		isCalcMade = true;//++
		//org : inNumbers.push(tempCalc);
	}
	return (inNumbers.size() == 0) ? tempCalc : inNumbers.front();
}


//-------------------------------------------------------------------------
//recursive input of end-user chars via a static method
//@returns current stack's calculation
//-------------------------------------------------------------------------
static	__int64 getCalculation(queue<char>& inFifoPrevAritmicz = fifoAritmeticzGlobal)
{
	char			anInput = 0;
	//true once `fifoDigitz` has elements
	bool			isNumberInput = false;//number may be zero
	__int64			theSign = 1, aVal = 0, tempNumber = 0;
	//queue of aritmetic chars
	queue<char>		fifoAritmeticCharz;
	//the digits inputted now form numbers :
	//2 1 (two and one) != 21 (twenty one)
	queue<__int64>	fifoNumbers;
	//
	while (anInput != '\r' && anInput != '\n' && anInput != ')')
	{
		anInput = gy_get_char();
		if ('(' == anInput)
			fifoNumbers.push(
				getCalculation(fifoAritmeticCharz)); //<- RECURSIVE
		else
		{//current stack / input queue
			if ((aVal = getCharAsDigit(anInput)) != GY_NOT_A_DIGIT)
			{
				if (tempNumber == 0)
				{
					isNumberInput = true;
					tempNumber = aVal;
				}
				else
				{
					tempNumber *= 10;
					tempNumber += aVal;
				}
				////////////fifoDigitz.push(aVal);
			}//numeric
			else
			{//NAN
				if (getIsCharArtimetic(anInput))
				{
					fifoAritmeticCharz.push(anInput);
					anInput = ' ';//disruptive
				}
				if (' ' == anInput || '\r' == anInput ||
					'\n' == anInput || ')' == anInput)
				{//white space signifies a gap between NUMBERS
				 //TO_DO *4*  read  : std::ws
				 //ignore leading junk spaces <-> size > 0
					////////REM : not O(n)
					////////if (fifoDigitz.size() > 0)
					////////{
					////////	isNumberInput = true;//the digits may build a number
					////////	aVal = 0;
					////////}
					////////while (fifoDigitz.size() > 0)
					////////{//c++ power is... pow (not ^)
					////////	aVal += fifoDigitz.front() *
					////////		static_cast<__int64>(
					////////			pow(10, fifoDigitz.size() - 1));
					////////	fifoDigitz.pop();
					////////}
					if (isNumberInput)
					{
						fifoNumbers.push(theSign * tempNumber);
						theSign = 1;//resets :
						isNumberInput = false;
						tempNumber = 0;
					}
				}
				else if ('m' == anInput) theSign = -1;//TO_DO *4* : "mmmmX"?
			}//nan
		}//within current stack
	}//while
	return getStackNumbersArtimetics(
		fifoNumbers,
		(fifoAritmeticCharz.size() != 0)/*no aritmetic input in parenz?*/
		? fifoAritmeticCharz : inFifoPrevAritmicz);
} //getCalculation


__int64 GYCalculatorApp::execute()
{
	return getCalculation();
}
