#include "Slot.h"
#include <Windows.h>

Slot::Slot()
{
	vector<string> oneNumber;
	oneNumber.push_back( ZERO_ON );
	oneNumber.push_back( ZERO_MIDDELE );
	oneNumber.push_back( ZERO_UNDER );
	_allNumber.push_back( oneNumber );
	
	oneNumber.clear();
	oneNumber.push_back( ONE_ALL );
	oneNumber.push_back( ONE_ALL );
	oneNumber.push_back( ONE_ALL );
	_allNumber.push_back( oneNumber );

	oneNumber.clear();
	oneNumber.push_back( TWO_ON );
	oneNumber.push_back( TWO_MIDDELE );
	oneNumber.push_back( TWO_UNDER );
	_allNumber.push_back( oneNumber );

	oneNumber.clear();
	oneNumber.push_back( THREE_ON );
	oneNumber.push_back( THREE_MIDDELE );
	oneNumber.push_back( THREE_UNDER );
	_allNumber.push_back( oneNumber );

	oneNumber.clear();
	oneNumber.push_back( FOUR_ON );
	oneNumber.push_back( FOUR_MIDDELE );
	oneNumber.push_back( FOUR_UNDER );
	_allNumber.push_back( oneNumber );

	oneNumber.clear();
	oneNumber.push_back( FIVE_ON );
	oneNumber.push_back( FIVE_MIDDELE );
	oneNumber.push_back( FIVE_UNDER );
	_allNumber.push_back( oneNumber );

	oneNumber.clear();
	oneNumber.push_back( SIX_ON );
	oneNumber.push_back( SIX_MIDDELE );
	oneNumber.push_back( SIX_UNDER );
	_allNumber.push_back( oneNumber );

	oneNumber.clear();
	oneNumber.push_back( SEVEN_ON );
	oneNumber.push_back( SEVEN_MIDDELE );
	oneNumber.push_back( SEVEN_UNDER );
	_allNumber.push_back( oneNumber );

	oneNumber.clear();
	oneNumber.push_back( EIGHT_ON );
	oneNumber.push_back( EIGHT_MIDDELE );
	oneNumber.push_back( EIGHT_UNDER );
	_allNumber.push_back( oneNumber );

	oneNumber.clear();
	oneNumber.push_back( NINE_ON );
	oneNumber.push_back( NINE_MIDDELE );
	oneNumber.push_back( NINE_UNDER );
	_allNumber.push_back( oneNumber );
}

Slot::~Slot()
{
	_allNumber.clear();
	_allNumber.shrink_to_fit() ;
}

//////////////////////////////////////////////////////////////////
//	[概要] スロット処理
//	[引数] なし
//	[戻値] 結果(TRUE:当たり,FALSE:はずれ)
//	[概要] 先頭3桁は同じ値を用いる
//         ラスト1桁を最小は固定で最大を最小+確率定義値-1で求め、
//         その範囲で乱数を取る。
//         よって、当選確率は1/確率定義値となる。
//////////////////////////////////////////////////////////////////
RESULT Slot::start_slot()
{
	RESULT result = FALSE;

	int farstNum	= get_randomNumberOfDecideRange( SLOT_RANGE_MIN, SLOT_RANGE_MAX );
	int endNumMax	= farstNum + HIT_PROBABILITY - ADJUST_NUM;
	int endNum		= get_randomNumberOfDecideRange( farstNum, endNumMax );
	int endIndex	= (int)endNum % MOD_NUM;		// 表示文字は0~9のため10で割った余りを使用
	// 1文字目処理
	vector<string> output = _allNumber.at( farstNum );
	Monitor::outputVec( output );
	Sleep( SLOT_WAY_SLEEP );
	Monitor::clear();

	// 2文字目処理
	vector<string> nextNumber = _allNumber.at( farstNum );			// 2桁目の数字
	output = combine_digitalNumber( output, nextNumber );
	Monitor::outputVec( output );
	Sleep( SLOT_WAY_SLEEP );
	Monitor::clear();
	// 3文字目処理
	output = combine_digitalNumber( output, nextNumber );
	Monitor::outputVec( output );
	Sleep( SLOT_WAY_SLEEP );
	Monitor::clear();
	// 当たり処理
	if( farstNum == endNum ){
		result = TRUE;
		nextNumber = _allNumber.at( endIndex );
		output = combine_digitalNumber( output, nextNumber );
		Monitor::outputVec( output );
		Sleep( SLOT_WAY_SLEEP );
		Monitor::clear();
		Sleep( SLOT_FLASHING_TIME );
		Monitor::outputVec( output );
		Sleep( SLOT_WAY_SLEEP );
		Monitor::clear();
		Sleep( SLOT_FLASHING_TIME );
		Monitor::outputVec( output );
		Sleep( SLOT_WAY_SLEEP );
		Monitor::clear();
		Sleep( SLOT_FLASHING_TIME );
		Monitor::outputVec( output );
		Sleep( SLOT_WAY_SLEEP );
		Monitor::clear();
	}
	else{
		// はずれ処理
		nextNumber = _allNumber.at( farstNum + INTEGER_ONE );
		output = combine_digitalNumber( output, nextNumber );
		Monitor::outputVec( output );
		Sleep( SLOT_DISPLAY_TIME );
		Monitor::clear();
	}
	return result;
}

//////////////////////////////////////////////////////////////////
//	[概要] デジタル番号結合
//	[引数] 左の番号,右の番号
//	[戻値] 結合後
//////////////////////////////////////////////////////////////////
vector<string> Slot::combine_digitalNumber(vector<string> left, vector<string> right)
{
	vector<string> result;
	for( unsigned char numberIndex = INTEGER_ZERO; numberIndex < LINE_NUM; ++numberIndex ){
		result.push_back( left.at(numberIndex) + right.at(numberIndex) );
	}
	return result;
}