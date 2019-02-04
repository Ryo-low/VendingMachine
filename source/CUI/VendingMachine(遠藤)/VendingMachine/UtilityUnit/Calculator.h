#pragma once
#pragma once
#include "..\Common.h"

class Calculator
{
public:
	Calculator();

	~Calculator();
	// a‚ªbˆÈã‚©
	static RESULT equalBigger(long seemsBigger, long seemsSmaller);

	// a‚ªb‚æ‚è‘å‚«‚¢‚©
	static RESULT bigger(long seemsBigger, long seemsSmaller);

	// a/b‚Ì®”•”‚ðŒvŽZ
	static unsigned long unsignedDivision(unsigned long divNumLeft, unsigned long divNumRight);

private:
};

//////////////////////////////////////
//	[ŠT—v] ‘æ1ˆø”>=‘æ2ˆø”‚©
//	[ˆø”] ‘å‚«‚¢‚Ù‚¤,‚»‚êˆÈ‰º
//	[–ß’l] Œ‹‰Ê
//////////////////////////////////////
inline RESULT Calculator::equalBigger( long seemsBigger, long seemsSmaller ){
	RESULT result = FALSE;
	if( seemsBigger >= seemsSmaller ){
		result = TRUE;
	}
	return result;
}

//////////////////////////////////////
//	[ŠT—v] ‘æ1ˆø”>‘æ2ˆø”‚©
//	[ˆø”] ‘å‚«‚¢‚Ù‚¤,‚»‚ê–¢–ž
//	[–ß’l] Œ‹‰Ê
//////////////////////////////////////
inline RESULT Calculator::bigger( long seemsBigger, long seemsSmaller ){
	RESULT result = FALSE;
	if( seemsBigger > seemsSmaller ){
		result = TRUE;
	}
	return result;
}