#pragma once
#pragma once
#include "..\Common.h"

class Calculator
{
public:
	Calculator();

	~Calculator();
	// a��b�ȏォ
	static RESULT equalBigger(long seemsBigger, long seemsSmaller);

	// a��b���傫����
	static RESULT bigger(long seemsBigger, long seemsSmaller);

	// a/b�̐��������v�Z
	static unsigned long unsignedDivision(unsigned long divNumLeft, unsigned long divNumRight);

private:
};

//////////////////////////////////////
//	[�T�v] ��1����>=��2������
//	[����] �傫���ق�,����ȉ�
//	[�ߒl] ����
//////////////////////////////////////
inline RESULT Calculator::equalBigger( long seemsBigger, long seemsSmaller ){
	RESULT result = FALSE;
	if( seemsBigger >= seemsSmaller ){
		result = TRUE;
	}
	return result;
}

//////////////////////////////////////
//	[�T�v] ��1����>��2������
//	[����] �傫���ق�,���ꖢ��
//	[�ߒl] ����
//////////////////////////////////////
inline RESULT Calculator::bigger( long seemsBigger, long seemsSmaller ){
	RESULT result = FALSE;
	if( seemsBigger > seemsSmaller ){
		result = TRUE;
	}
	return result;
}