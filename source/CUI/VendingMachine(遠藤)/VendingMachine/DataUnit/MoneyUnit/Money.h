#pragma once
#include	"../../Common.h"

// お金の種類
enum MONEY_TYPE_ENUM{
	ALL_MONEY_TYPE				= INTEGER_MINUS_ONE,
	THOUSAND,
	FIVEHOUNDRED,
	HOUNDRED,
	FIFTY,
	TEN,
	MONEY_TYPENUM
};
// お金の価値
enum MONEY_VALUE_ENUM{
	MONEY_VALUE_THOUSAND		= 1000,
	MONEY_VALUE_FIVEHOUNDRED	= 500,
	MONEY_VALUE_HOUNDRED		= 100,
	MONEY_VALUE_FIFTY			= 50,
	MONEY_VALUE_TEN				= 10
};

/* お金のデータ保持クラス */
class Money
{
public:
	Money();
	~Money();
	// お金の追加,セット
	void add_money(MONEY_TYPE_ENUM moneyType, THINGS_STATE money);
	void set_money(MONEY_TYPE_ENUM moneyType, THINGS_STATE money);
	void reduce_money(MONEY_TYPE_ENUM moneyType, THINGS_STATE money);

	// 指定金種が存在するか
	RESULT exist_money(MONEY_TYPE_ENUM moneyType);

	// お金の状態を取得
	void get_moneyState(MONEY_TYPE_ENUM moneyType, THINGS_STATE(& moneyState)[MONEY_TYPENUM]);

private:
	THINGS_STATE _moneyState[MONEY_TYPENUM];
};

inline void Money::add_money(MONEY_TYPE_ENUM moneyType, THINGS_STATE money)
{
	_moneyState[moneyType].stock += money.stock;
}

inline void Money::set_money(MONEY_TYPE_ENUM moneyType, THINGS_STATE money)
{
	_moneyState[moneyType].stock = money.stock;
}

inline void Money::reduce_money(MONEY_TYPE_ENUM moneyType, THINGS_STATE money)
{
	_moneyState[moneyType].stock -= money.stock;
}

inline RESULT Money::exist_money(MONEY_TYPE_ENUM moneyType)
{
	RESULT result = FALSE;
	if( _moneyState[moneyType].stock != INTEGER_ZERO ){
		result = TRUE;
	}
	return result;
}