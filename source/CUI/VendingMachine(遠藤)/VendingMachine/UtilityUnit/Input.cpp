#include "Input.h"

Input::Input()
{
}

Input::~Input()
{
}

//////////////////////////////////////
//	[�T�v] �����Ȃ�int�̓���
//	[����] �Ȃ�
//	[�ߒl] ���͒l
//////////////////////////////////////
INPUT_NUM Input::input_uIntNum()
{
	INPUT_NUM	result;
	string		input;
	RESULT		inputJudge = FALSE;
	while( inputJudge == FALSE ){
		input.clear();
		cout << "����>" << endl;
		cin >> input;
		if( std::all_of(input.cbegin(), input.cend(), iswdigit) ){
			inputJudge = TRUE;
			break;
		}
		cout << "�ē���" << endl;
	}
	result.number = stoi( input );
	return result;
}

//////////////////////////////////////
//	[�T�v] ���͂��͈͓���
//	[����] ����,�ő�l,�ŏ��l
//	[�ߒl] ����
//////////////////////////////////////
RESULT Input::is_trueNumber(INPUT_NUM input, int max, int min)
{
	RESULT result = TRUE;
	result = Calculator::equalBigger( (unsigned long)max, (unsigned long)input.number );
	if( result == FALSE ){
		return result;
	}
	result = Calculator::equalBigger( (unsigned long)input.number, (unsigned long)min );
	return result;
}