//2017-06-16
//	LOGIC :
//	A.
//		AT LEAST ONE arithmetic char before ANY digit char
//		2017-06-19 : added fonctionality to enable `regular` input order.
//	B.
//		`n` numbers   <=>   `n-1` aritmetics
//		digit_chars_count - 1   =   aritmetic_chars_count
//	C.
//		no floating point values as inputs
//	D.
//		no exception handling. Principal logic only
//	E.
//		implemented via a class in order to encapsulate some stuff,
//		like an anonymous namespace which hides a global var...
//
#ifndef GY_MEYTAL_CALCULATOR
#define GY_MEYTAL_CALCULATOR  
#define BEGIN_GY_NS_MEYTAL_CALCULATOR namespace GYQuizMeytalCalculator {
#define END_GY_NS_MEYTAL_CALCULATOR }
#include<queue>
#include<stack>
BEGIN_GY_NS_MEYTAL_CALCULATOR
#define GY_NOT_A_DIGIT -1


//@returns true - once the char signifies an aritmetic op
inline bool getIsCharArtimetic(const char& inC)
{//Look, Mom, I made a prototype of a rocket out of... switch&cases
 //#despicable_me_1
	switch (inC)
	{
	case '+': case '-': case '/': case '*':	case '^': return true;
	}
	return false;
}

//, const __int64& theSign
//A digit is a non-signed value,
//thus a negative value means NAN.
//@returns char converted to its numeric value, or GY_NOT_A_DIGIT
inline __int64 getCharAsDigit(const char& inC)
{//'0' - '0' = 0  ,  '1' - '0' = 1  ,  ...
	if (inC >= '0' && inC <= '9') return (inC - '0');//(theSign) * 
	//
	return GY_NOT_A_DIGIT;
}


//Not a pure singleton, so let's call it an app :)
//Instantiating this class is impossible
struct GYCalculatorApp final 
{
	//Executes an app sequence : chars input, followed by final calculation
	static __int64 execute();
private:
	GYCalculatorApp() = default;
};
END_GY_NS_MEYTAL_CALCULATOR
#endif // !GY_MEYTAL_CALCULATOR
