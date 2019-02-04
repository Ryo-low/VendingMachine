#pragma once
#include "../Common.h"
#include "Monitor.h"

#include <random>

// 出現番地最小数、最大数
#define		SLOT_RANGE_MIN		0
#define		SLOT_RANGE_MAX		9

// 当選確率 1/下記定義値で当選
#define		HIT_PROBABILITY		2
#define		ADJUSTMENT_NUM		1
// 先頭3桁固定
#define		FIX_NUM				3

// 1つ目の値+当選確率%10 で表示値を決める
#define		MOD_NUM				10

// デジタル数字群
// 文字列の被りもあるが、
// 使いまわしは可読性を下げるため
// その数字にあった名称で定義する
#define		LINE_NUM			3				// 3行に渡って表示

#define		ZERO_ON				"  |￣|"
#define		ZERO_MIDDELE		"  |　|"
#define		ZERO_UNDER			"  |__|"

#define		ONE_ALL				"     |"
// 同じ文字を3つ繋げれば良いため"     |"
// 1つでよい					"     |"

#define		TWO_ON				"   ￣|"
#define		TWO_MIDDELE			"   ― "
#define		TWO_UNDER			"  |__ "

#define		THREE_ON			"   ￣|"
#define		THREE_MIDDELE		"   ―|"
#define		THREE_UNDER			"   __|"

#define		FOUR_ON				"  |  |"
#define		FOUR_MIDDELE		"   ―|"
#define		FOUR_UNDER			"     |"

#define		FIVE_ON				"  |￣ "
#define		FIVE_MIDDELE		"   ― "
#define		FIVE_UNDER			"   __|"

#define		SIX_ON				"  |   "
#define		SIX_MIDDELE			"  |― "
#define		SIX_UNDER			"  |__|"

#define		SEVEN_ON			"  |￣|"
#define		SEVEN_MIDDELE		"     |"
#define		SEVEN_UNDER			"     |"

#define		EIGHT_ON			"  |￣|"
#define		EIGHT_MIDDELE		"  |―|"
#define		EIGHT_UNDER			"  |__|"

#define		NINE_ON				"  |￣|"
#define		NINE_MIDDELE		"   ―|"
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
	// x.at(y-1)でyのデジタル表示を取り出す(縦:3行)
	vector<vector<string>> _allNumber;

	// デジタル表示文字列結合
	vector<string> combine_digitalNumber(vector<string> left, vector<string> right);
};

inline int Slot::get_randomNumberOfDecideRange(int min, int max){
    // 乱数生成器
    static std::mt19937_64 mt64( INTEGER_ZERO );

    // min~max の一様分布整数 (int) の分布生成器
    std::uniform_int_distribution<int> gen_rand_uni_int( min, max );

    // 乱数を生成
    return (int)gen_rand_uni_int( mt64 );
}