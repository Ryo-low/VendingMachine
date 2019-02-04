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
//	[�T�v] �X���b�g����
//	[����] �Ȃ�
//	[�ߒl] ����(TRUE:������,FALSE:�͂���)
//	[�T�v] �擪3���͓����l��p����
//         ���X�g1�����ŏ��͌Œ�ōő���ŏ�+�m����`�l-1�ŋ��߁A
//         ���͈̔͂ŗ��������B
//         ����āA���I�m����1/�m����`�l�ƂȂ�B
//////////////////////////////////////////////////////////////////
RESULT Slot::start_slot()
{
	RESULT result = FALSE;

	int farstNum	= get_randomNumberOfDecideRange( SLOT_RANGE_MIN, SLOT_RANGE_MAX );
	int endNumMax	= farstNum + HIT_PROBABILITY - ADJUST_NUM;
	int endNum		= get_randomNumberOfDecideRange( farstNum, endNumMax );
	int endIndex	= (int)endNum % MOD_NUM;		// �\��������0~9�̂���10�Ŋ������]����g�p
	// 1�����ڏ���
	vector<string> output = _allNumber.at( farstNum );
	Monitor::outputVec( output );
	Sleep( SLOT_WAY_SLEEP );
	Monitor::clear();

	// 2�����ڏ���
	vector<string> nextNumber = _allNumber.at( farstNum );			// 2���ڂ̐���
	output = combine_digitalNumber( output, nextNumber );
	Monitor::outputVec( output );
	Sleep( SLOT_WAY_SLEEP );
	Monitor::clear();
	// 3�����ڏ���
	output = combine_digitalNumber( output, nextNumber );
	Monitor::outputVec( output );
	Sleep( SLOT_WAY_SLEEP );
	Monitor::clear();
	// �����菈��
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
		// �͂��ꏈ��
		nextNumber = _allNumber.at( farstNum + INTEGER_ONE );
		output = combine_digitalNumber( output, nextNumber );
		Monitor::outputVec( output );
		Sleep( SLOT_DISPLAY_TIME );
		Monitor::clear();
	}
	return result;
}

//////////////////////////////////////////////////////////////////
//	[�T�v] �f�W�^���ԍ�����
//	[����] ���̔ԍ�,�E�̔ԍ�
//	[�ߒl] ������
//////////////////////////////////////////////////////////////////
vector<string> Slot::combine_digitalNumber(vector<string> left, vector<string> right)
{
	vector<string> result;
	for( unsigned char numberIndex = INTEGER_ZERO; numberIndex < LINE_NUM; ++numberIndex ){
		result.push_back( left.at(numberIndex) + right.at(numberIndex) );
	}
	return result;
}