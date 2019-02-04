#include "Drink.h"

Drink::Drink()
{
	_drinkState[TEA].stock		= TEA_STOCK;
	_drinkState[TEA].value		= DRINK_VALUE_TEA;
	_drinkState[COFFEE].stock	= COFFEE_STOCK;
	_drinkState[COFFEE].value	= DRINK_VALUE_COFFEE;
	_drinkState[WATER].stock	= WATER_STOCK;
	_drinkState[WATER].value	= DRINK_VALUE_WATER;
}

Drink::~Drink()
{

}

//////////////////////////////////////////
//	[�T�v] �݌ɂ����邩�`�F�b�N
//	[����] ���ݕ��̎��
//	[�ߒl] ����
//////////////////////////////////////////
RESULT Drink::exist_drink(DRINK_TYPE_ENUM drinkType)
{
	RESULT result = FALSE;
	if( Calculator::equalBigger(_drinkState[drinkType].stock, INTEGER_ONE) == TRUE ){
		result = TRUE;
	}
	return result;
}

//////////////////////////////////////////
//	[�T�v] �w��̈��ݕ������炷
//	[����] ���ݕ��̎��
//	[�ߒl] �Ȃ�
//////////////////////////////////////////
void Drink::reduce_drink(DRINK_TYPE_ENUM drinkType)
{
	--_drinkState[drinkType].stock;
}

//////////////////////////////////////////
//	[�T�v] �w���ʂ̈��ݕ��̏�Ԃ��擾
//	[����] ���ݕ��̎��,�i�[�ϐ�
//	[�ߒl] �Ȃ�
//////////////////////////////////////////
void Drink::get_drinkState(DRINK_TYPE_ENUM drinkType, THINGS_STATE (&drink)[DRINK_TYPENUM])
{
	if( drinkType != ALL_DRINK_TYPE ){
		drink[drinkType] = _drinkState[drinkType];
		return;
	}
	for( unsigned char drinkIndex = INTEGER_ZERO; drinkIndex < DRINK_TYPENUM; ++drinkIndex ){
		drink[drinkIndex] = _drinkState[drinkIndex];
	}
}

//////////////////////////////////////////
//	[�T�v] ���ݕ���ʂ��疼�O��Ԃ�
//	[����] ���ݕ��̎��
//	[�ߒl] ���ݕ��̖��O
//////////////////////////////////////////
DRINK_NAME Drink::get_nameToTypeNum(DRINK_TYPE_ENUM drinkType)
{
	DRINK_NAME result;
	switch( drinkType ){
	case( TEA ):
		result.name = TEA_NAME;
		break;
	case( COFFEE ):
		result.name = COFFEE_NAME;
		break;
	case( WATER ):
		result.name = WATER_NAME;
		break;
	default:
		break;
	}
	return result;
}