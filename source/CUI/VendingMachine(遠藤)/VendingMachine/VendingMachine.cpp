#include "VendingMachine.h"

// コンストラクタ
VendingMachine::VendingMachine()
{
	_dataInterface						= new DataInterface;

	// メニュー設定
	_menuMessage[PAYMENT].message		= PAYMENT_MESSAGE;
	_menuMessage[BUY].message			= BUY_MESSAGE;
	_menuMessage[TAKE_CHANGE].message	= TAKE_CHANGE_MESSAGE;
	_menuMessage[AGGREGATE].message		= AGGREGATE_MESSAGE;
}
// デストラクタ
VendingMachine::~VendingMachine()
{
	delete	_dataInterface;
}

///////////////////////////////////////
//	[概要] 状態ごとの操作を管理
//	[戻値] 結果
///////////////////////////////////////
RESULT VendingMachine::interface()
{
	STATE_ENUM		nowState	= FIRST_STATE;
	MENU_TYPE_ENUM	menuType	= MENU_UNDEFIND;

	while( nowState != THIRD_STATE ){
		Monitor::output( SELECT_MESSAGE );
		// それぞれの状態の処理を行う
		switch( nowState )
		{
		case FIRST_STATE:
			menuType = process_firstState();
			break;
		case SECOND_STATE:
			menuType = process_secondState();
			break;
		case THIRD_STATE:
			return TRUE;
			break;
		default:
			return FALSE;
			break;
		}
		nowState = manager( menuType );
	}
	Monitor::output( FINISH_MESSAGE );
	string a;
	cin >> a;
	return TRUE;
}

///////////////////////////////////////
//	[概要] 状態1の処理を行う
//	[引数] メニュー種別
//	[戻値] 表示メッセージ
///////////////////////////////////////
MENU_TYPE_ENUM VendingMachine::process_firstState()
{
	MENU_TYPE_ENUM	result = MENU_UNDEFIND;
	vector<string>	messageVector;
	string			displayMessage;
	// 表示文字セット
	displayMessage	= to_string( (int)messageVector.size() );
	displayMessage	= displayMessage + SEPARATE_CHAR + PAYMENT_MESSAGE;
	messageVector.push_back( displayMessage );
	displayMessage.clear();
	displayMessage	= to_string( (int)messageVector.size() );
	displayMessage	= displayMessage + SEPARATE_CHAR + AGGREGATE_MESSAGE;
	messageVector.push_back( displayMessage );
	// 選択肢表示
	Monitor::outputVec( messageVector );
	// 入力受付,判断
	RESULT		inputResult = FALSE;
	INPUT_NUM	input;
	while( inputResult == FALSE ){
		input		= Input::input_uIntNum();
		inputResult	= Input::is_trueNumber( input, (int)messageVector.size() - ADJUST_NUM, INTEGER_ZERO );
	}
	// 選択動作変換
	switch( input.number ){
	case( INTEGER_ZERO ):
		result = PAYMENT;
		break;
	case( INTEGER_ONE ):
		result = AGGREGATE;
		break;
	default:
		break;
	}
	return result;
}

///////////////////////////////////////
//	[概要] 状態2の処理を行う
//	[引数] メニュー種別
//	[戻値] 表示メッセージ
///////////////////////////////////////
MENU_TYPE_ENUM VendingMachine::process_secondState()
{
	MENU_TYPE_ENUM	result = MENU_UNDEFIND;
	vector<string>	messageVector;
	string			displayMessage;
	// 表示文字セット
	displayMessage	= to_string( (int)messageVector.size() );
	displayMessage	= displayMessage + SEPARATE_CHAR + BUY_MESSAGE;
	messageVector.push_back( displayMessage );
	displayMessage.clear();
	displayMessage	= to_string( (int)messageVector.size() );
	displayMessage	= displayMessage + SEPARATE_CHAR + TAKE_CHANGE_MESSAGE;
	messageVector.push_back( displayMessage );
	// 選択肢表示
	Monitor::outputVec( messageVector );
	// 入力受付
	RESULT		inputResult = FALSE;
	INPUT_NUM	input;
	while( inputResult == FALSE ){
		input		= Input::input_uIntNum();
		inputResult	= Input::is_trueNumber(input, ((int)messageVector.size() - ADJUST_NUM), INTEGER_ZERO);
	}

	// 選択動作変換
	switch( input.number ){
	case( INTEGER_ZERO ):
		result = BUY;
		break;
	case( INTEGER_ONE ):
		result = TAKE_CHANGE;
		break;
	default:
		break;
	}
	return result;
}

///////////////////////////////////////
//	[概要] 流れを管理する
//	[引数] メニュー種別
//	[戻値] 次の状態
///////////////////////////////////////
STATE_ENUM VendingMachine::manager(MENU_TYPE_ENUM menuType)
{
	// 選択された処理を実行し、次の状態遷移を受け取る
	STATE_ENUM nextState = UNDEFIND_STATE;
	RESULT result = FALSE;
	switch( menuType )
	{
	case PAYMENT:
		nextState = input_money();
		break;
	case BUY:
		nextState = buy_drink( &result );
		if( result == TRUE ){
			// 購入成功時スロット開始
			do_slot();
		}
		break;
	case TAKE_CHANGE:
		nextState = output_change();
		break;
	case AGGREGATE:
		nextState = do_aggregate();
		break;
	default:
		break;
	}
	return nextState;
}

//////////////////////////////////////
//	[概要] 入金作業
//	[引数] 無し
//	[戻値] 次の状態
//////////////////////////////////////
STATE_ENUM VendingMachine::input_money()
{
	// 投入金の種類入力
	Monitor::output( SELECT_COIN_TYPE_MESSAGE );
	RESULT			inputResult	= FALSE;	
	INPUT_NUM		moneyType;				// 入力受け取り
	THINGS_STATE	money;					// セットするお金
	while( inputResult == FALSE ){
		moneyType	= Input::input_uIntNum();
		money.value	= (unsigned short)moneyType.number;
		inputResult	= _dataInterface->is_money( money );
		if( inputResult == FALSE ){
			Monitor::output( MONEY_TYPE_IS_NO );
		}
	}

	// 投入金の枚数入力
	Monitor::output( SELECT_COIN_NUM_MESSAGE );

	inputResult	= FALSE;
	INPUT_NUM	moneyStock;
	string errorMessage;
	while( inputResult == FALSE ){
		errorMessage.clear();
		errorMessage	= to_string(MONEY_STOCK_LIMIT) + MONEY_STOCK_LIMIT_OVER;
		Monitor::output( errorMessage );
		moneyStock		= Input::input_uIntNum();
		money.stock		= (unsigned char)moneyStock.number;
		inputResult		= _dataInterface->check_moneyStockLimit( money );
	}
	// 金額投入
	_dataInterface->set_userMoney( money );
	return SECOND_STATE;
}

//////////////////////////////////////////////////////
//	[概要] 購入動作
//	[引数] 無し
//	[戻値] 次の状態(状態2)
//////////////////////////////////////////////////////
STATE_ENUM VendingMachine::buy_drink(RESULT* result){
	// 選択肢表示
	*result = FALSE;
	Monitor::output( SELECT_DRINK_TYPE_MESSAGE_1 );
	vector<string>	messageVector;
	string			displayMessage;
	displayMessage	= to_string( TEA );
	displayMessage	= displayMessage + SEPARATE_CHAR + TEA_NAME;
	messageVector.push_back( displayMessage );
	displayMessage.clear();
	displayMessage	= to_string( COFFEE );
	displayMessage	= displayMessage + SEPARATE_CHAR + COFFEE_NAME;
	messageVector.push_back( displayMessage );
	displayMessage.clear();
	displayMessage	= to_string( WATER );
	displayMessage	= displayMessage + SEPARATE_CHAR + WATER_NAME;
	messageVector.push_back( displayMessage );
	Monitor::outputVec( messageVector );

	// 購入飲料選択
	DRINK_TYPE_ENUM	selectDrinkType;
	selectDrinkType = select_drink();

	// 在庫チェック
	if( check_drinkStock(selectDrinkType) == FALSE ){
		return SECOND_STATE;
	}
	// 投入金チェック
	unsigned long moneyStock = _dataInterface->get_allMoneyValue( USER_STOCKER ).value;
	unsigned long drinkValue = _dataInterface->get_value( selectDrinkType ).value;
	if( Calculator::equalBigger(moneyStock, drinkValue) == FALSE ){
		Monitor::output( USER_MONEY_NONE );
		return SECOND_STATE;
	}
	// お釣りチェック
	THINGS_STATE change;
	change.value = (unsigned short)(moneyStock - drinkValue);
	if( Calculator::bigger(moneyStock, drinkValue) == TRUE){
		if( _dataInterface->check_changeOutput(change) != TRUE ){
			Monitor::output( CHANGE_NONE );
			return SECOND_STATE;
		}
	}
	// ここまでチェックが通ることで購入可能
	_dataInterface->reduce_drink( selectDrinkType );
	// 投入金操作
	_dataInterface->set_buyAfterMoneyState( change );
	Monitor::output( BUY_AFTER_MESSAGE );
	Monitor::output_messageToUnique( BUY_AFTER_MESSAGE );
	*result = TRUE;
	return SECOND_STATE;
}

//////////////////////////////////////////////////////
//	[概要] つり銭だし
//	[引数] 無し
//	[戻値] 次の状態(状態1：入金or集計)
//////////////////////////////////////////////////////
STATE_ENUM VendingMachine::output_change()
{
	string			message;
	vector<string>	changeMessage;
	THINGS_STATE	userMoneyState[MONEY_TYPENUM];
	_dataInterface->get_moneyState( USER_STOCKER, ALL_MONEY_TYPE, userMoneyState );
	for( unsigned char stateIndex = INTEGER_ZERO; stateIndex < MONEY_TYPENUM; ++stateIndex ){
		message.clear();
		message = to_string( userMoneyState[stateIndex].value ) + MONEY_OUTPUT_MESSAGE_1;
		message = message + to_string( userMoneyState[stateIndex].stock )+ MONEY_OUTPUT_MESSAGE_2;

		changeMessage.push_back( message );
		_dataInterface->move_userMoneyToStock( (MONEY_TYPE_ENUM)stateIndex );
	}
	
	Monitor::outputVec( changeMessage );
	return FIRST_STATE;
}

//////////////////////////////////////////////////////
//	[概要] 集計動作
//	[引数] 無し
//	[戻値] 次の状態(状態3：終了)
//////////////////////////////////////////////////////
STATE_ENUM VendingMachine::do_aggregate()
{
	vector<string> stockOutput;
	stockOutput.clear();
	string oneLine;
	// 飲み物在庫
	THINGS_STATE drinkState[DRINK_TYPENUM];
	_dataInterface->get_drinkState( ALL_DRINK_TYPE, drinkState );
	DRINK_NAME drink;
	for( unsigned char drinkIndex = INTEGER_ZERO; drinkIndex < DRINK_TYPENUM; ++drinkIndex ){
		oneLine.clear();
		drink	 = _dataInterface->get_drinkNameToTypeNum( (DRINK_TYPE_ENUM)drinkIndex );
		oneLine	 = drink.name									+ DRINK_OUTPUT_MESSAGE_1;
		oneLine	+= to_string( drinkState[drinkIndex].stock )	+ DRINK_OUTPUT_MESSAGE_2;
		stockOutput.push_back( oneLine );
	}
	Monitor::output( DRINK_STOCK_MESSAGE );
	Monitor::outputVec( stockOutput );
		
	// 自販機在庫金額
	stockOutput.clear();
	THINGS_STATE stockMoneyState[MONEY_TYPENUM];
	_dataInterface->get_moneyState( VENDING_STOCER, ALL_MONEY_TYPE, stockMoneyState );
	// 使用者残金
	vector<string> userOutput;
	userOutput.clear();
	THINGS_STATE userMoneyState[MONEY_TYPENUM];
	_dataInterface->get_moneyState( USER_STOCKER, ALL_MONEY_TYPE, userMoneyState );
	for( unsigned char stockIndex = INTEGER_ZERO; stockIndex < MONEY_TYPENUM; ++stockIndex ){
		// 在庫セット
		oneLine.clear();
		oneLine	 = to_string( stockMoneyState[stockIndex].value ) + MONEY_OUTPUT_MESSAGE_1;
		oneLine	+= to_string( stockMoneyState[stockIndex].stock ) + MONEY_OUTPUT_MESSAGE_2;
		stockOutput.push_back( oneLine );
		// 使用者セット
		oneLine.clear();
		oneLine	 = to_string( userMoneyState[stockIndex].value ) + MONEY_OUTPUT_MESSAGE_1;
		oneLine	+= to_string( userMoneyState[stockIndex].stock ) + MONEY_OUTPUT_MESSAGE_2;
		userOutput.push_back( oneLine );
	}
	Monitor::output( VENDING_CHANGE_MESSAGE );
	Monitor::outputVec( stockOutput );

	Monitor::output( USER_CHANGE_MESSAGE );
	Monitor::outputVec( userOutput );

	return THIRD_STATE;
}

//////////////////////////////////////////////////////
//	[概要] スロット処理
//	[引数] 無し
//	[戻値] 無し
//////////////////////////////////////////////////////
void VendingMachine::do_slot()
{
	RESULT slotResult	= FALSE;
	Slot slot			= Slot();
	slotResult			= slot.start_slot();

	if( slotResult == FALSE ){
		return;
	}

	RESULT result = FALSE;
	while( result == FALSE ){
		result = do_slotHit();
	}
}

//////////////////////////////////////////////////////
//	[概要] スロット当たり時処理
//	[引数] 無し
//	[戻値] 終了ステータス
//////////////////////////////////////////////////////
RESULT VendingMachine::do_slotHit()
{
	Monitor::output( SELECT_DRINK_TYPE_MESSAGE_2 );
	vector<string>	messageVector;
	string			displayMessage;
	displayMessage	= to_string( TEA );
	displayMessage	= displayMessage + SEPARATE_CHAR + TEA_NAME;
	messageVector.push_back( displayMessage );
	displayMessage.clear();
	displayMessage	= to_string( COFFEE );
	displayMessage	= displayMessage + SEPARATE_CHAR + COFFEE_NAME;
	messageVector.push_back( displayMessage );
	displayMessage.clear();
	displayMessage	= to_string( WATER );
	displayMessage	= displayMessage + SEPARATE_CHAR + WATER_NAME;
	messageVector.push_back( displayMessage );
	Monitor::outputVec( messageVector );

	DRINK_TYPE_ENUM selectDrinkType;
	selectDrinkType = select_drink();

	if(  check_drinkStock(selectDrinkType) == FALSE ){
		return FALSE;
	}
	_dataInterface->reduce_drink( selectDrinkType );
	Monitor::output( GET_DRINK_MESSAGE );
	return TRUE;
}

//////////////////////////////////////////////////////
//	[概要] 飲み物選択関数
//	[引数] 無し
//	[戻値] 飲み物の種類
//////////////////////////////////////////////////////
DRINK_TYPE_ENUM VendingMachine::select_drink()
{
	DRINK_TYPE_ENUM result;
	INPUT_NUM		selectDrinkNum;
	do{
		selectDrinkNum	= Input::input_uIntNum();
		result = (DRINK_TYPE_ENUM)selectDrinkNum.number;
	}
	while( _dataInterface->is_drink(result) != TRUE );

	return result;
}

//////////////////////////////////////////////////////
//	[概要] 在庫確認
//	[引数] 飲み物の種類
//	[戻値] 結果
//////////////////////////////////////////////////////
RESULT VendingMachine::check_drinkStock(DRINK_TYPE_ENUM	selectDrinkType)
{
	if( _dataInterface->exist_drink(selectDrinkType) == FALSE ){
		Monitor::output( DRINK_STOCK_NONE );
		return FALSE;
	}
	return TRUE;
}