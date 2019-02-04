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
//	[概要] 指定種別の飲み物が存在するか
//	[引数] 飲み物の種別
//	[戻値] 結果
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
//	[概要] 指定種別の飲み物の在庫があるか
//	[引数] 飲み物の種別
//	[戻値] 結果
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
//	[概要] 指定種別の飲み物の価値を取得
//	[引数] 飲み物の種別
//	[戻値] 状態
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
//	[概要] 指定種別の飲み物が存在するか
//	[引数] 飲み物の種別
//	[戻値] 結果
//////////////////////////////////////////
DRINK_NAME DrinkManage::get_nameToTypeNum(DRINK_TYPE_ENUM drinkType)
{
	DRINK_NAME result;
	if( is_drink(drinkType) == TRUE ){
		result = _drink->get_nameToTypeNum( drinkType );
	}
	return result;
}