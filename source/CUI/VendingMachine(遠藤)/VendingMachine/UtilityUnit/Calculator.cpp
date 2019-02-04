#include "Calculator.h"

Calculator::Calculator(){

}

Calculator::~Calculator(){

}

//////////////////////////////////////////
//	[ŠT—v] ‘æ1ˆø” / ‘æ2ˆø” ‚ÌŒ‹‰Ê®”•”
//	[ˆø”] ¶•Ó,‰E•Ó
//	[–ß’l] Œ‹‰Ê
//////////////////////////////////////////
unsigned long Calculator::unsignedDivision(unsigned long divNumLeft, unsigned long divNumRight)
{
	unsigned long result = INTEGER_ZERO;
	if( (divNumLeft == INTEGER_ZERO) || (divNumRight == INTEGER_ZERO) ){
		return result;
	}
	while( equalBigger(divNumLeft, divNumRight) == TRUE ){
		divNumLeft -= divNumRight;
		++result;
	}
	return result;
}