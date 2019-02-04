#include "Money.h"

Money::Money()
{
	for( unsigned char stateIndex = INTEGER_ZERO; stateIndex < MONEY_TYPENUM; ++stateIndex ){
		_moneyState[stateIndex].stock = INTEGER_ZERO;
	}
	_moneyState[THOUSAND].value = MONEY_VALUE_THOUSAND;
	_moneyState[FIVEHOUNDRED].value = MONEY_VALUE_FIVEHOUNDRED;
	_moneyState[HOUNDRED].value = MONEY_VALUE_HOUNDRED;
	_moneyState[FIFTY].value = MONEY_VALUE_FIFTY;
	_moneyState[TEN].value = MONEY_VALUE_TEN;
}

Money::~Money()
{
}

////////////////////////////////////////////
//	[�T�v] �����̏�Ԃ��i�[����
//	[����] �����̃^�C�v�A�����̏�Ԋi�[�ϐ�
//	[�ߒl] �Ȃ�
////////////////////////////////////////////
void Money::get_moneyState(MONEY_TYPE_ENUM moneyType, THINGS_STATE (& moneyState)[MONEY_TYPENUM])
{
	if( moneyType != ALL_MONEY_TYPE ){
		moneyState[moneyType] = _moneyState[moneyType];
		return;
	}
	for( unsigned char stateIndex = INTEGER_ZERO; stateIndex < MONEY_TYPENUM; ++stateIndex ){
		moneyState[stateIndex] = _moneyState[stateIndex];
	}
}