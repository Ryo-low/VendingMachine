#include	"DrinkManage.h"

DrinkManage::DrinkManage()
{
	_drink	= new Drink;
	set_stock();
}

DrinkManage::~DrinkManage()
{
	delete _drink;
}

void DrinkManage::set_stock()
{

}

//////////////////////////////////////////
//	[�T�v] �w���ʂ̈��ݕ������݂��邩
//	[����] ���ݕ��̎��
//	[�ߒl] ����
//////////////////////////////////////////
RESULT DrinkManage::is_drink(DRINK_TYPE_ENUM drinkType)
{
	RESULT result = FALSE;
	if( (Calculator::bigger(drinkType, (long)ALL_DRINK_TYPE) == TRUE) 
	&&  (Calculator::bigger(DRINK_TYPENUM, drinkType) == TRUE) ){
		result = TRUE;
	}
	return result;
}

//////////////////////////////////////////
//	[�T�v] �w���ʂ̈��ݕ��̍݌ɂ����邩
//	[����] ���ݕ��̎��
//	[�ߒl] ����
//////////////////////////////////////////
RESULT DrinkManage::exist_drink(DRINK_TYPE_ENUM drinkType)
{
	RESULT result = FALSE;
	if( is_drink(drinkType) == TRUE ){
		result = _drink->exist_drink( drinkType );
	}
	return result;
}

//////////////////////////////////////////
//	[�T�v] �w���ʂ̈��ݕ��̉��l���擾
//	[����] ���ݕ��̎��
//	[�ߒl] ���
//////////////////////////////////////////
THINGS_STATE DrinkManage::get_value(DRINK_TYPE_ENUM drinkType)
{
	THINGS_STATE drinkValue;
	drinkValue.stock = INTEGER_ZERO;
	drinkValue.value = INTEGER_ZERO;
	if( is_drink(drinkType) == TRUE ){
		drinkValue = _drink->get_value( drinkType );
	}
	return drinkValue;
}

//////////////////////////////////////////
//	[�T�v] �w���ʂ̈��ݕ������݂��邩
//	[����] ���ݕ��̎��
//	[�ߒl] ����
//////////////////////////////////////////
DRINK_NAME DrinkManage::get_nameToTypeNum(DRINK_TYPE_ENUM drinkType)
{
	DRINK_NAME result;
	if( is_drink(drinkType) == TRUE ){
		result = _drink->get_nameToTypeNum( drinkType );
	}
	return result;
}