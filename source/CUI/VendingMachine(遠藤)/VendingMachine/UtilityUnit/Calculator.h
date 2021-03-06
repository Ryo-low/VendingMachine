#pragma once
#pragma once
#include "..\Common.h"

class Calculator
{
public:
	Calculator();

	~Calculator();
	// aがb以上か
	static RESULT equalBigger(long seemsBigger, long seemsSmaller);

	// aがbより大きいか
	static RESULT bigger(long seemsBigger, long seemsSmaller);

	// a/bの整数部を計算
	static unsigned long unsignedDivision(unsigned long divNumLeft, unsigned long divNumRight);

private:
};

//////////////////////////////////////
//	[概要] 第1引数>=第2引数か
//	[引数] 大きいほう,それ以下
//	[戻値] 結果
//////////////////////////////////////
inline RESULT Calculator::equalBigger( long seemsBigger, long seemsSmaller ){
	RESULT result = FALSE;
	if( seemsBigger >= seemsSmaller ){
		result = TRUE;
	}
	return result;
}

//////////////////////////////////////
//	[概要] 第1引数>第2引数か
//	[引数] 大きいほう,それ未満
//	[戻値] 結果
//////////////////////////////////////
inline RESULT Calculator::bigger( long seemsBigger, long seemsSmaller ){
	RESULT result = FALSE;
	if( seemsBigger > seemsSmaller ){
		result = TRUE;
	}
	return result;
}