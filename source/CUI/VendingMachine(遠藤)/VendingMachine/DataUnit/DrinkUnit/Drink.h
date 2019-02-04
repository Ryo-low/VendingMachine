#pragma once
#include	"../../Common.h"
#include	"../../UtilityUnit/Calculator.h"


// ���ݕ��̎��
#define		TEA_NAME			"����"
#define		COFFEE_NAME			"�R�[�q�["
#define		WATER_NAME			"��"

// �����݌�
#define		TEA_STOCK		10
#define		COFFEE_STOCK	 5
#define		WATER_STOCK		 0

enum DRINK_TYPE_ENUM{
	ALL_DRINK_TYPE				= INTEGER_MINUS_ONE,
	TEA,
	COFFEE,
	WATER,
	DRINK_TYPENUM
};

// ���ݕ��̉��l
enum DRINK_VALUE_ENUM{
	DRINK_VALUE_TEA				= 150,
	DRINK_VALUE_COFFEE			= 110,
	DRINK_VALUE_WATER			=  90
};

struct DRINK_NAME {
	string name;
};

/* ���ݕ��f�[�^�ێ��N���X */
class Drink
{
public:
	Drink();
	~Drink();
	
	// ���ݕ������邩
	RESULT exist_drink(DRINK_TYPE_ENUM drinkType);

	// ���ݕ��̉��l���擾
	THINGS_STATE get_value(DRINK_TYPE_ENUM drinkType);

	// �݌ɂ����炷
	void reduce_drink(DRINK_TYPE_ENUM drinkType);

	// ��Ԏ擾
	void get_drinkState(DRINK_TYPE_ENUM drinkType, THINGS_STATE (&drink)[DRINK_TYPENUM]);

	// ���ݕ������擾
	DRINK_NAME get_nameToTypeNum(DRINK_TYPE_ENUM drinkType);

private:
	THINGS_STATE	_drinkState[DRINK_TYPENUM];
};


inline THINGS_STATE Drink::get_value(DRINK_TYPE_ENUM drinkType)
{
	return _drinkState[drinkType];
}
