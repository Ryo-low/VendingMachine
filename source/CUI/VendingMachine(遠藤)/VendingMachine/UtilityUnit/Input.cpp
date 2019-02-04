#include "Input.h"

Input::Input()
{
}

Input::~Input()
{
}

//////////////////////////////////////
//	[概要] 符号なしintの入力
//	[引数] なし
//	[戻値] 入力値
//////////////////////////////////////
INPUT_NUM Input::input_uIntNum()
{
	INPUT_NUM	result;
	string		input;
	RESULT		inputJudge = FALSE;
	while( inputJudge == FALSE ){
		input.clear();
		cout << "入力>" << endl;
		cin >> input;
		if( std::all_of(input.cbegin(), input.cend(), iswdigit) ){
			inputJudge = TRUE;
			break;
		}
		cout << "再入力" << endl;
	}
	result.number = stoi( input );
	return result;
}

//////////////////////////////////////
//	[概要] 入力が範囲内か
//	[引数] 入力,最大値,最小値
//	[戻値] 結果
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