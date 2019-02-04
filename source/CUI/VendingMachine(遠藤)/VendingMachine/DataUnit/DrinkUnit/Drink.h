#pragma once
#include	"../../Common.h"
#include	"../../UtilityUnit/Calculator.h"


// 飲み物の種類
#define		TEA_NAME			"お茶"
#define		COFFEE_NAME			"コーヒー"
#define		WATER_NAME			"水"

// 初期在庫
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

// 飲み物の価値
enum DRINK_VALUE_ENUM{
	DRINK_VALUE_TEA				= 150,
	DRINK_VALUE_COFFEE			= 110,
	DRINK_VALUE_WATER			=  90
};

struct DRINK_NAME {
	string name;
};

/* 飲み物データ保持クラス */
class Drink
{
public:
	Drink();
	~Drink();
	
	// 飲み物があるか
	RESULT exist_drink(DRINK_TYPE_ENUM drinkType);

	// 飲み物の価値を取得
	THINGS_STATE get_value(DRINK_TYPE_ENUM drinkType);

	// 在庫を減らす
	void reduce_drink(DRINK_TYPE_ENUM drinkType);

	// 状態取得
	void get_drinkState(DRINK_TYPE_ENUM drinkType, THINGS_STATE (&drink)[DRINK_TYPENUM]);

	// 飲み物名を取得
	DRINK_NAME get_nameToTypeNum(DRINK_TYPE_ENUM drinkType);

private:
	THINGS_STATE	_drinkState[DRINK_TYPENUM];
};


inline THINGS_STATE Drink::get_value(DRINK_TYPE_ENUM drinkType)
{
	return _drinkState[drinkType];
}
