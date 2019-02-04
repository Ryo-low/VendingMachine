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
//	[概要] 在庫があるかチェック
//	[引数] 飲み物の種別
//	[戻値] 結果
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
//	[概要] 指定の飲み物を減らす
//	[引数] 飲み物の種別
//	[戻値] なし
//////////////////////////////////////////
void Drink::reduce_drink(DRINK_TYPE_ENUM drinkType)
{
	--_drinkState[drinkType].stock;
}

//////////////////////////////////////////
//	[概要] 指定種別の飲み物の状態を取得
//	[引数] 飲み物の種別,格納変数
//	[戻値] なし
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
//	[概要] 飲み物種別から名前を返す
//	[引数] 飲み物の種別
//	[戻値] 飲み物の名前
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