#pragma once
#include	"Money.h"
#include	"..\../Common.h"
#include	"../../UtilityUnit/Calculator.h"

// 初期在庫
#define		THOUSAND_STOCK		  8
#define		FIVEHOUNDRED_STOCK	  1
#define		HOUNDRED_STOCK		 10
#define		FIFTY_STOCK			  2
#define		TEN_STOCK			100

enum STOCKER_TYPE_ENUM{
	ALL_STOCKER					= INTEGER_MINUS_ONE,
	VENDING_STOCER,										// 自動販売機在庫
	USER_STOCKER										// 使用者在庫
};

/* お金データ管理クラス */
class MoneyManage
{
public:
	MoneyManage();
	~MoneyManage();
	
	// 受け取った値が対応しているお金かどうか
	RESULT is_money(THINGS_STATE money);

	// ある種の投入金枚数が制限を超えていないか
	RESULT check_moneyStockLimit(THINGS_STATE money);

	// お金をセットする
	void set_userMoney(THINGS_STATE money);

	// お金の状態を取得する
	void get_moneyState(STOCKER_TYPE_ENUM stockType, MONEY_TYPE_ENUM moneyType, THINGS_STATE (& moneyState)[MONEY_TYPENUM]);

	// 総額を取得する
	THINGS_STATE get_allMoneyValue(STOCKER_TYPE_ENUM stocerType);

	// お釣りを出せるかチェック
	RESULT check_changeOutput(THINGS_STATE change);
	// 指定在庫でお釣りが出せるかチェック
	THINGS_STATE check_changeOutputDecideStocker(THINGS_STATE change, const THINGS_STATE (&stock)[MONEY_TYPENUM]);

	// 購入後金額操作
	void set_buyAfterMoneyState(THINGS_STATE change);

	// 使用者のお金を金庫に入れる
	void move_userMoneyToStock(MONEY_TYPE_ENUM moneyType);

private:
	// 在庫と投入金
	Money*	_stock;
	Money*	_user;
	// 対応しているお金のリスト
	THINGS_STATE _moneyTypeList[MONEY_TYPENUM];

	// 初期在庫セット
	void	set_stock();


	// 価値から添え字に変換する
	MONEY_TYPE_ENUM convert_thingsStateToMoneyType(THINGS_STATE money);
};