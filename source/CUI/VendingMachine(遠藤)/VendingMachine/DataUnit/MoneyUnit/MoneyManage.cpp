#include	"MoneyManage.h"

MoneyManage::MoneyManage()
{
	_stock	= new Money();
	_user	= new Money();
	// 対応金リスト作成
	_moneyTypeList[THOUSAND].value		= YEN_THOUSAND;
	_moneyTypeList[FIVEHOUNDRED].value	= YEN_FIVEHOUNDRED;
	_moneyTypeList[HOUNDRED].value		= YEN_HOUNDRED;
	_moneyTypeList[FIFTY].value			= YEN_FIFTY;
	_moneyTypeList[TEN].value			= YEN_TEN;
	// 初期在庫セット
	set_stock();
}

MoneyManage::~MoneyManage()
{
	delete _stock;
	delete _user;
}

//////////////////////////////////
//	[概要] 初期在庫をセットする
//	[引数] なし
//	[戻値] なし
/////////////////////////////////
void MoneyManage::set_stock()
{
	// 初期在庫セット
	THINGS_STATE setMoney;
	setMoney.stock = THOUSAND_STOCK;
	_stock->add_money( THOUSAND, setMoney );
	setMoney.stock = FIVEHOUNDRED_STOCK;
	_stock->add_money( FIVEHOUNDRED, setMoney );
	setMoney.stock = HOUNDRED_STOCK;
	_stock->add_money( HOUNDRED, setMoney );
	setMoney.stock = FIFTY_STOCK;
	_stock->add_money( FIFTY, setMoney );
	setMoney.stock = TEN_STOCK;
	_stock->add_money( TEN, setMoney );
}

///////////////////////////////////////
//	[概要] 対応しているお金かどうか
//	[引数] 物の価値
//	[戻値] 結果
///////////////////////////////////////
RESULT MoneyManage::is_money(THINGS_STATE money)
{
	RESULT result = FALSE;
	for( unsigned char index = INTEGER_ZERO; index < MONEY_TYPENUM; ++index ){
		if( _moneyTypeList[index].value == money.value ){
			result = TRUE;
			break;
		}
	}
	return result;
}

//////////////////////////////////////////////////
//	[概要] 投入枚数が制限値を超えていないか
//	[引数] 投入金の枚数
//	[戻値] 結果
//////////////////////////////////////////////////
RESULT MoneyManage::check_moneyStockLimit(THINGS_STATE money)
{
	// 指定金種の状態を取得
	MONEY_TYPE_ENUM	moneyType	= convert_thingsStateToMoneyType( money );
	THINGS_STATE	moneyState[MONEY_TYPENUM];
	_user->get_moneyState( moneyType, moneyState );
	// 制限値を設定
	unsigned long limitNum		= MONEY_STOCK_LIMIT - moneyState[moneyType].stock;
	RESULT result				= Calculator::equalBigger(limitNum, money.stock);
	
	return result;
}

//////////////////////////////////
//	[概要] 投入金をセットする
//	[引数] 投入金の状態
//	[戻値] なし
/////////////////////////////////
void MoneyManage::set_userMoney(THINGS_STATE money)
{
	MONEY_TYPE_ENUM moneyType = ALL_MONEY_TYPE;
	moneyType = convert_thingsStateToMoneyType( money );

	_user->add_money( moneyType, money );
}

//////////////////////////////////////////////////////
//	[概要] 種別毎にお金の状態を取得する
//	[引数] 取得先種別、指定金種別、お金の状態格納変数
//	[戻値] なし
//////////////////////////////////////////////////////
void MoneyManage::get_moneyState(STOCKER_TYPE_ENUM stockType, MONEY_TYPE_ENUM moneyType, THINGS_STATE (& moneyState)[MONEY_TYPENUM])
{
	if( stockType == VENDING_STOCER ){
		_stock->get_moneyState( moneyType, moneyState );
	}
	if( stockType == USER_STOCKER ){
		_user->get_moneyState( moneyType, moneyState );
	}
}

//////////////////////////////////////////////////////
//	[概要] 指定在庫種別の総額を取得する
//	[引数] 在庫種別
//	[戻値] 総額
//////////////////////////////////////////////////////
THINGS_STATE MoneyManage::get_allMoneyValue(STOCKER_TYPE_ENUM stocerType)
{
	THINGS_STATE result;
	result.stock = INTEGER_ONE;
	result.value = INTEGER_ZERO;
	THINGS_STATE moneyState[MONEY_TYPENUM];
	get_moneyState(stocerType, ALL_MONEY_TYPE, moneyState);
	for( unsigned char moneyIndex = INTEGER_ONE; moneyIndex <= MONEY_TYPENUM; ++moneyIndex ){
		result.value += moneyState[moneyIndex - ADJUST_NUM].value * moneyState[moneyIndex - ADJUST_NUM].stock;
	}

	return result;
}


//////////////////////////////////////////////////////
//	[概要] お釣りが出せるかチェック
//	[引数] お釣り
//	[戻値] 結果
//////////////////////////////////////////////////////
RESULT MoneyManage::check_changeOutput(THINGS_STATE change)
{
	THINGS_STATE userMoneyState[MONEY_TYPENUM];
	THINGS_STATE stockMoneyState[MONEY_TYPENUM];
	_user->get_moneyState( ALL_MONEY_TYPE, userMoneyState );
	_stock->get_moneyState( ALL_MONEY_TYPE, stockMoneyState );
	for( unsigned char stateIndex = INTEGER_ZERO; stateIndex < MONEY_TYPENUM; ++stateIndex ){
		stockMoneyState[stateIndex].stock += userMoneyState[stateIndex].stock;
	}

	change = check_changeOutputDecideStocker(change, stockMoneyState);
	if( change.value == INTEGER_ZERO ){
		return TRUE;
	}
	return FALSE;
}

//////////////////////////////////////////////////////
//	[概要] 指定在庫状態からお釣りが出せるかチェック
//	[引数] お釣り,指定在庫
//	[戻値] お釣り(value=0:釣出可能)
//////////////////////////////////////////////////////
THINGS_STATE MoneyManage::check_changeOutputDecideStocker(THINGS_STATE change, const THINGS_STATE (&stock)[MONEY_TYPENUM])
{
	for( unsigned char stockIndex = INTEGER_ZERO;
		(stockIndex < MONEY_TYPENUM) && (change.value != INTEGER_ZERO); ++stockIndex ){
		// 対象金種別のお釣りが必要かチェック
		unsigned long outputNum = INTEGER_ZERO;
		outputNum = Calculator::unsignedDivision( change.value, stock[stockIndex].value );
		if( outputNum == INTEGER_ZERO ){
			continue;
		}
		// 対象金種別が存在するかチェック
		if( stock[stockIndex].stock == INTEGER_ZERO ){
			continue;
		}
		// 出力お釣り枚数調整
		if( Calculator::bigger(outputNum, stock[stockIndex].stock) ){
			outputNum = stock[stockIndex].stock;
		}
		change.value -= (unsigned short)(stock[stockIndex].value * outputNum);
	}
	return change;
}

/////////////////////////////////////////////
//	[概要] 使用者のお金をつり銭と同等にする
//	[引数] つり銭
//	[戻値] なし
/////////////////////////////////////////////
void MoneyManage::set_buyAfterMoneyState(THINGS_STATE change)
{
	THINGS_STATE	userMoneyState[MONEY_TYPENUM];
	THINGS_STATE	stockMoneyState[MONEY_TYPENUM];
	THINGS_STATE	setMoneyState;
	MONEY_TYPE_ENUM	nowType = ALL_MONEY_TYPE;
	_user->get_moneyState( ALL_MONEY_TYPE, userMoneyState );
	for( unsigned char moneyIndex = INTEGER_ZERO; moneyIndex < MONEY_TYPENUM; ++moneyIndex ){
		unsigned long divNum	= INTEGER_ZERO;
		setMoneyState.stock		= INTEGER_ZERO;
		nowType = (MONEY_TYPE_ENUM)moneyIndex;
		move_userMoneyToStock( nowType );
		_stock->get_moneyState( nowType, stockMoneyState );
		divNum = Calculator::unsignedDivision(change.value, stockMoneyState[moneyIndex].value );
		// 在庫と最大枚数(商の整数部)どちらが大きいか
		// 最終枚数が0の場合はこの種類での出力は不可能
		if( Calculator::bigger(divNum, stockMoneyState[moneyIndex].stock) ){
			divNum = stockMoneyState[moneyIndex].stock;
		}
		if( divNum == INTEGER_ZERO ){
			continue;
		}
		setMoneyState.stock	= (unsigned short)divNum;
		_stock->reduce_money( nowType, setMoneyState );
		_user->set_money( nowType, setMoneyState );
		change.value -= stockMoneyState[moneyIndex].value * (unsigned short)divNum;
	}
}

//////////////////////////////////////////
//	[概要] 指定種別の金を使用者→在庫する
//	[引数] お金の種別
//	[戻値] なし
//////////////////////////////////////////
void MoneyManage::move_userMoneyToStock(MONEY_TYPE_ENUM moneyType)
{
	THINGS_STATE setMoney;
	setMoney.stock = INTEGER_ZERO;

	if( moneyType != ALL_MONEY_TYPE ){
		THINGS_STATE moneyState[MONEY_TYPENUM];
		_user->get_moneyState(moneyType, moneyState);
		_stock->add_money( moneyType, moneyState[moneyType] );
		_user->set_money( moneyType, setMoney );
		return;
	}
}

//////////////////////////////////////////
//	[概要] 価値からお金の種類に変換する
//	[引数] お金の状態
//	[戻値] お金の種類(列挙型)
//////////////////////////////////////////
MONEY_TYPE_ENUM MoneyManage::convert_thingsStateToMoneyType(THINGS_STATE money)
{
	 MONEY_TYPE_ENUM moneyType = ALL_MONEY_TYPE;
	 for( unsigned char checkIndex = INTEGER_ZERO; checkIndex < MONEY_TYPENUM; ++checkIndex ){
		if( _moneyTypeList[checkIndex].value == money.value ){
			moneyType = (MONEY_TYPE_ENUM)checkIndex;
			break;
		}
	}
	return moneyType;
}