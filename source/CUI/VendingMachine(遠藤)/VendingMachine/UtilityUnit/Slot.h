#pragma once
#include "../Common.h"
#include "Monitor.h"

#include <random>

// �o���Ԓn�ŏ����A�ő吔
#define		SLOT_RANGE_MIN		0
#define		SLOT_RANGE_MAX		9

// ���I�m�� 1/���L��`�l�œ��I
#define		HIT_PROBABILITY		2
#define		ADJUSTMENT_NUM		1
// �擪3���Œ�
#define		FIX_NUM				3

// 1�ڂ̒l+���I�m��%10 �ŕ\���l�����߂�
#define		MOD_NUM				10

// �f�W�^�������Q
// ������̔������邪�A
// �g���܂킵�͉ǐ��������邽��
// ���̐����ɂ��������̂Œ�`����
#define		LINE_NUM			3				// 3�s�ɓn���ĕ\��

#define		ZERO_ON				"  |�P|"
#define		ZERO_MIDDELE		"  |�@|"
#define		ZERO_UNDER			"  |__|"

#define		ONE_ALL				"     |"
// ����������3�q����Ηǂ�����"     |"
// 1�ł悢					"     |"

#define		TWO_ON				"   �P|"
#define		TWO_MIDDELE			"   �\ "
#define		TWO_UNDER			"  |__ "

#define		THREE_ON			"   �P|"
#define		THREE_MIDDELE		"   �\|"
#define		THREE_UNDER			"   __|"

#define		FOUR_ON				"  |  |"
#define		FOUR_MIDDELE		"   �\|"
#define		FOUR_UNDER			"     |"

#define		FIVE_ON				"  |�P "
#define		FIVE_MIDDELE		"   �\ "
#define		FIVE_UNDER			"   __|"

#define		SIX_ON				"  |   "
#define		SIX_MIDDELE			"  |�\ "
#define		SIX_UNDER			"  |__|"

#define		SEVEN_ON			"  |�P|"
#define		SEVEN_MIDDELE		"     |"
#define		SEVEN_UNDER			"     |"

#define		EIGHT_ON			"  |�P|"
#define		EIGHT_MIDDELE		"  |�\|"
#define		EIGHT_UNDER			"  |__|"

#define		NINE_ON				"  |�P|"
#define		NINE_MIDDELE		"   �\|"
#define		NINE_UNDER			"     |"


#define		SLOT_WAY_SLEEP		1000
#define		SLOT_FLASHING_TIME	 500
#define		SLOT_DISPLAY_TIME	1500

class Slot
{
public:
	Slot();
	~Slot();

	RESULT start_slot();

	int get_randomNumberOfDecideRange(int min, int max);

private:
	// x.at(y-1)��y�̃f�W�^���\�������o��(�c:3�s)
	vector<vector<string>> _allNumber;

	// �f�W�^���\�������񌋍�
	vector<string> combine_digitalNumber(vector<string> left, vector<string> right);
};

inline int Slot::get_randomNumberOfDecideRange(int min, int max){
    // ����������
    static std::mt19937_64 mt64( INTEGER_ZERO );

    // min~max �̈�l���z���� (int) �̕��z������
    std::uniform_int_distribution<int> gen_rand_uni_int( min, max );

    // �����𐶐�
    return (int)gen_rand_uni_int( mt64 );
}