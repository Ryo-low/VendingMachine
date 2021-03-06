#include "Calculator.h"

Calculator::Calculator(){

}

Calculator::~Calculator(){

}

//////////////////////////////////////////
//	[概要] 第1引数 / 第2引数 の結果整数部
//	[引数] 左辺,右辺
//	[戻値] 結果
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