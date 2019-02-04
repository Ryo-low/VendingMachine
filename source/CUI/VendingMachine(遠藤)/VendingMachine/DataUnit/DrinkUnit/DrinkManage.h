#pragma once
#include	"Drink.h"

/* 飲み物データ管理クラス */
class DrinkManage
{
public:
	DrinkManage();
	~DrinkManage();
	// 飲み物の種類として存在するか
	RESULT is_drink(DRINK_TYPE_ENUM drinkType);

	// 指定飲み物の在庫があるか
	RESULT exist_drink(DRINK_TYPE_ENUM drinkType);

	// 指定飲み物の価値取得
	THINGS_STATE get_value(DRINK_TYPE_ENUM drinkType);

	// 在庫を減らす
	void reduce_drink(DRINK_TYPE_ENUM drinkType);

	// 飲み物の状態取得
	void get_drinkState(DRINK_TYPE_ENUM drinkType, THINGS_STATE (&drink)[DRINK_TYPENUM]);

	// 飲み物名を取得
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