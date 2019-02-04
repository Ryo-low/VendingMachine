#pragma once
#include	"../../Common.h"

// �����̎��
enum MONEY_TYPE_ENUM{
	ALL_MONEY_TYPE				= INTEGER_MINUS_ONE,
	THOUSAND,
	FIVEHOUNDRED,
	HOUNDRED,
	FIFTY,
	TEN,
	MONEY_TYPENUM
};
// �����̉��l
enum MONEY_VALUE_ENUM{
	MONEY_VALUE_THOUSAND		= 1000,
	MONEY_VALUE_FIVEHOUNDRED	= 500,
	MONEY_VALUE_HOUNDRED		= 100,
	MONEY_VALUE_FIFTY			= 50,
	MONEY_VALUE_TEN				= 10
};

/* �����̃f�[�^�ێ��N���X */
class Money
{
public:
	Money();
	~Money();
	// �����̒ǉ�,�Z�b�g
	void add_money(MONEY_TYPE_ENUM moneyType, THINGS_STATE money);
	void set_money(MONEY_TYPE_ENUM moneyType, THINGS_STATE money);
	void reduce_money(MONEY_TYPE_ENUM moneyType, THINGS_STATE money);

	// �w����킪���݂��邩
	RESULT exist_money(MONEY_TYPE_ENUM moneyType);

	// �����̏�Ԃ��擾
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