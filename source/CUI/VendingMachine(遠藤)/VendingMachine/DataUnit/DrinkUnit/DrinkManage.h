#pragma once
#include	"Drink.h"

/* ���ݕ��f�[�^�Ǘ��N���X */
class DrinkManage
{
public:
	DrinkManage();
	~DrinkManage();
	// ���ݕ��̎�ނƂ��đ��݂��邩
	RESULT is_drink(DRINK_TYPE_ENUM drinkType);

	// �w����ݕ��̍݌ɂ����邩
	RESULT exist_drink(DRINK_TYPE_ENUM drinkType);

	// �w����ݕ��̉��l�擾
	THINGS_STATE get_value(DRINK_TYPE_ENUM drinkType);

	// �݌ɂ����炷
	void reduce_drink(DRINK_TYPE_ENUM drinkType);

	// ���ݕ��̏�Ԏ擾
	void get_drinkState(DRINK_TYPE_ENUM drinkType, THINGS_STATE (&drink)[DRINK_TYPENUM]);

	// ���ݕ������擾
	DRINK_NAME get_nameToTypeNum(DRINK_TYPE_ENUM drinkType);
 
private:
	Drink*	_drink;

	void set_stock();
};

inline void DrinkManage::reduce_drink(DRINK_TYPE_ENUM drinkType)
{
	_drink->reduce_drink( drinkType );
}

inline void DrinkManage::get_drinkState(DRINK_TYPE_ENUM drinkType, THINGS_STATE (&drink)[DRINK_TYPENUM])
{
	_drink->get_drinkState( drinkType, drink );
}