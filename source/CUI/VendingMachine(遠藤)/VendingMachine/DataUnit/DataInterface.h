#pragma once
#pragma once
#include "DrinkUnit\DrinkManage.h"
#include "MoneyUnit\MoneyManage.h"
#include <iostream>
using namespace std;

class DataInterface
{
public:
	DataInterface();
	~DataInterface();

	/*お金関連*/
	// 対応しているお金かどうか
	RESULT is_money(THINGS_STATE money);

	// 枚数が超過していないか
	RESULT check_moneyStockLimit(THINGS_STATE moneyStock);

	// お金をセットする
	void set_userMoney(THINGS_STATE money);
	
	// 指定在庫種別のお金の状態を取得
	void get_moneyState(STOCKER_TYPE_ENUM stockType, MONEY_TYPE_ENUM moneyType, THINGS_STATE (& moneyState)[MONEY_TYPENUM]);

	// 指定在庫種別の総額を取得
	THINGS_STATE get_allMoneyValue(STOCKER_TYPE_ENUM stocerType);

	// お釣りを出せるかチェック
	RESULT check_changeOutput(THINGS_STATE change);
	
	// 購入後つり銭設定
	void set_buyAfterMoneyState(THINGS_STATE change);

	void move_userMoneyToStock(MONEY_TYPE_ENUM moneyType);

	/*飲み物関連*/
	// 対応している飲み物かどうか
	RESULT is_drink(DRINK_TYPE_ENUM drinkType);

	// 指定したものがあるかどうか
	RESULT exist_drink(DRINK_TYPE_ENUM drinkType);

	// 指定飲み物の価格を取得
	THINGS_STATE get_value(DRINK_TYPE_ENUM drinkType);

	// 在庫を減らす
	void reduce_drink(DRINK_TYPE_ENUM drinkType);

	// 状態を取得
	void get_drinkState(DRINK_TYPE_ENUM drinkType, THINGS_STATE (&drink)[DRINK_TYPENUM]);

	// 飲み物名を取得
	DRINK_NAME get_drinkNameToTypeNum(DRINK_TYPE_ENUM drinkType);
 
private:
	DrinkManage* _drinkManage;
	MoneyManage* _moneyManage;
};

/*お金関連*/
inline RESULT DataInterface::is_money(THINGS_STATE money)
{
	return _moneyManage->is_money( money );
}

inline RESULT DataInterface::check_moneyStockLimit(THINGS_STATE money)
{
	return _moneyManage->check_moneyStockLimit( money );
}

inline void DataInterface::set_userMoney(THINGS_STATE money)
{
	return _moneyManage->set_userMoney( money );
}

inline void DataInterface::get_moneyState(STOCKER_TYPE_ENUM stockType, MONEY_TYPE_ENUM moneyType, THINGS_STATE (& moneyState)[MONEY_TYPENUM])
{
	_moneyManage->get_moneyState( stockType, moneyType, moneyState );
}

inline THINGS_STATE DataInterface::get_allMoneyValue(STOCKER_TYPE_ENUM stocerType)
{
	return _moneyManage->get_allMoneyValue( stocerType );
}

inline RESULT DataInterface::check_changeOutput(THINGS_STATE change)
{
	return _moneyManage->check_changeOutput( change );
}

inline void DataInterface::set_buyAfterMoneyState(THINGS_STATE change)
{
	_moneyManage->set_buyAfterMoneyState( change );
}

inline void DataInterface::move_userMoneyToStock(MONEY_TYPE_ENUM moneyType)
{
	_moneyManage->move_userMoneyToStock( moneyType );
}
/*飲み物関連*/
inline RESULT DataInterface::is_drink(DRINK_TYPE_ENUM drinkType)
{
	return _drinkManage->is_drink( drinkType );
}

inline RESULT DataInterface::exist_drink(DRINK_TYPE_ENUM drinkType)
{
	return _drinkManage->exist_drink( drinkType );
}

inline THINGS_STATE DataInterface::get_value(DRINK_TYPE_ENUM drinkType)
{
	return _drinkManage->get_value( drinkType );
}

inline void DataInterface::reduce_drink(DRINK_TYPE_ENUM drinkType)
{
	cout << "a" <<endl;
	_drinkManage->reduce_drink( drinkType );
}

inline void DataInterface::get_drinkState(DRINK_TYPE_ENUM drinkType, THINGS_STATE (&drink)[DRINK_TYPENUM])
{
	_drinkManage->get_drinkState( drinkType, drink );
}

inline DRINK_NAME DataInterface::get_drinkNameToTypeNum(DRINK_TYPE_ENUM drinkType)
{
	return _drinkManage->get_nameToTypeNum( drinkType );
}