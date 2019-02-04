#include "Calculator.h"

Calculator::Calculator(){

}

Calculator::~Calculator(){

}

//////////////////////////////////////////
//	[�T�v] ��1���� / ��2���� �̌��ʐ�����
//	[����] ����,�E��
//	[�ߒl] ����
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