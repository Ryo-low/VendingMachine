#include "VendingMachine.h"

// �R���X�g���N�^
VendingMachine::VendingMachine()
{
	_dataInterface						= new DataInterface;

	// ���j���[�ݒ�
	_menuMessage[PAYMENT].message		= PAYMENT_MESSAGE;
	_menuMessage[BUY].message			= BUY_MESSAGE;
	_menuMessage[TAKE_CHANGE].message	= TAKE_CHANGE_MESSAGE;
	_menuMessage[AGGREGATE].message		= AGGREGATE_MESSAGE;
}
// �f�X�g���N�^
VendingMachine::~VendingMachine()
{
	delete	_dataInterface;
}

///////////////////////////////////////
//	[�T�v] ��Ԃ��Ƃ̑�����Ǘ�
//	[�ߒl] ����
///////////////////////////////////////
RESULT VendingMachine::interface()
{
	STATE_ENUM		nowState	= FIRST_STATE;
	MENU_TYPE_ENUM	menuType	= MENU_UNDEFIND;

	while( nowState != THIRD_STATE ){
		Monitor::output( SELECT_MESSAGE );
		// ���ꂼ��̏�Ԃ̏������s��
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
//	[�T�v] ���1�̏������s��
//	[����] ���j���[���
//	[�ߒl] �\�����b�Z�[�W
///////////////////////////////////////
MENU_TYPE_ENUM VendingMachine::process_firstState()
{
	MENU_TYPE_ENUM	result = MENU_UNDEFIND;
	vector<string>	messageVector;
	string			displayMessage;
	// �\�������Z�b�g
	displayMessage	= to_string( (int)messageVector.size() );
	displayMessage	= displayMessage + SEPARATE_CHAR + PAYMENT_MESSAGE;
	messageVector.push_back( displayMessage );
	displayMessage.clear();
	displayMessage	= to_string( (int)messageVector.size() );
	displayMessage	= displayMessage + SEPARATE_CHAR + AGGREGATE_MESSAGE;
	messageVector.push_back( displayMessage );
	// �I�����\��
	Monitor::outputVec( messageVector );
	// ���͎�t,���f
	RESULT		inputResult = FALSE;
	INPUT_NUM	input;
	while( inputResult == FALSE ){
		input		= Input::input_uIntNum();
		inputResult	= Input::is_trueNumber( input, (int)messageVector.size() - ADJUST_NUM, INTEGER_ZERO );
	}
	// �I�𓮍�ϊ�
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
//	[�T�v] ���2�̏������s��
//	[����] ���j���[���
//	[�ߒl] �\�����b�Z�[�W
///////////////////////////////////////
MENU_TYPE_ENUM VendingMachine::process_secondState()
{
	MENU_TYPE_ENUM	result = MENU_UNDEFIND;
	vector<string>	messageVector;
	string			displayMessage;
	// �\�������Z�b�g
	displayMessage	= to_string( (int)messageVector.size() );
	displayMessage	= displayMessage + SEPARATE_CHAR + BUY_MESSAGE;
	messageVector.push_back( displayMessage );
	displayMessage.clear();
	displayMessage	= to_string( (int)messageVector.size() );
	displayMessage	= displayMessage + SEPARATE_CHAR + TAKE_CHANGE_MESSAGE;
	messageVector.push_back( displayMessage );
	// �I�����\��
	Monitor::outputVec( messageVector );
	// ���͎�t
	RESULT		inputResult = FALSE;
	INPUT_NUM	input;
	while( inputResult == FALSE ){
		input		= Input::input_uIntNum();
		inputResult	= Input::is_trueNumber(input, ((int)messageVector.size() - ADJUST_NUM), INTEGER_ZERO);
	}

	// �I�𓮍�ϊ�
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
//	[�T�v] ������Ǘ�����
//	[����] ���j���[���
//	[�ߒl] ���̏��
///////////////////////////////////////
STATE_ENUM VendingMachine::manager(MENU_TYPE_ENUM menuType)
{
	// �I�����ꂽ���������s���A���̏�ԑJ�ڂ��󂯎��
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
			// �w���������X���b�g�J�n
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
//	[�T�v] �������
//	[����] ����
//	[�ߒl] ���̏��
//////////////////////////////////////
STATE_ENUM VendingMachine::input_money()
{
	// �������̎�ޓ���
	Monitor::output( SELECT_COIN_TYPE_MESSAGE );
	RESULT			inputResult	= FALSE;	
	INPUT_NUM		moneyType;				// ���͎󂯎��
	THINGS_STATE	money;					// �Z�b�g���邨��
	while( inputResult == FALSE ){
		moneyType	= Input::input_uIntNum();
		money.value	= (unsigned short)moneyType.number;
		inputResult	= _dataInterface->is_money( money );
		if( inputResult == FALSE ){
			Monitor::output( MONEY_TYPE_IS_NO );
		}
	}

	// �������̖�������
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
	// ���z����
	_dataInterface->set_userMoney( money );
	return SECOND_STATE;
}

//////////////////////////////////////////////////////
//	[�T�v] �w������
//	[����] ����
//	[�ߒl] ���̏��(���2)
//////////////////////////////////////////////////////
STATE_ENUM VendingMachine::buy_drink(RESULT* result){
	// �I�����\��
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

	// �w�������I��
	DRINK_TYPE_ENUM	selectDrinkType;
	selectDrinkType = select_drink();

	// �݌Ƀ`�F�b�N
	if( check_drinkStock(selectDrinkType) == FALSE ){
		return SECOND_STATE;
	}
	// �������`�F�b�N
	unsigned long moneyStock = _dataInterface->get_allMoneyValue( USER_STOCKER ).value;
	unsigned long drinkValue = _dataInterface->get_value( selectDrinkType ).value;
	if( Calculator::equalBigger(moneyStock, drinkValue) == FALSE ){
		Monitor::output( USER_MONEY_NONE );
		return SECOND_STATE;
	}
	// ���ނ�`�F�b�N
	THINGS_STATE change;
	change.value = (unsigned short)(moneyStock - drinkValue);
	if( Calculator::bigger(moneyStock, drinkValue) == TRUE){
		if( _dataInterface->check_changeOutput(change) != TRUE ){
			Monitor::output( CHANGE_NONE );
			return SECOND_STATE;
		}
	}
	// �����܂Ń`�F�b�N���ʂ邱�Ƃōw���\
	_dataInterface->reduce_drink( selectDrinkType );
	// ����������
	_dataInterface->set_buyAfterMoneyState( change );
	Monitor::output( BUY_AFTER_MESSAGE );
	Monitor::output_messageToUnique( BUY_AFTER_MESSAGE );
	*result = TRUE;
	return SECOND_STATE;
}

//////////////////////////////////////////////////////
//	[�T�v] ��K����
//	[����] ����
//	[�ߒl] ���̏��(���1�F����or�W�v)
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
//	[�T�v] �W�v����
//	[����] ����
//	[�ߒl] ���̏��(���3�F�I��)
//////////////////////////////////////////////////////
STATE_ENUM VendingMachine::do_aggregate()
{
	vector<string> stockOutput;
	stockOutput.clear();
	string oneLine;
	// ���ݕ��݌�
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
		
	// ���̋@�݌ɋ��z
	stockOutput.clear();
	THINGS_STATE stockMoneyState[MONEY_TYPENUM];
	_dataInterface->get_moneyState( VENDING_STOCER, ALL_MONEY_TYPE, stockMoneyState );
	// �g�p�Ҏc��
	vector<string> userOutput;
	userOutput.clear();
	THINGS_STATE userMoneyState[MONEY_TYPENUM];
	_dataInterface->get_moneyState( USER_STOCKER, ALL_MONEY_TYPE, userMoneyState );
	for( unsigned char stockIndex = INTEGER_ZERO; stockIndex < MONEY_TYPENUM; ++stockIndex ){
		// �݌ɃZ�b�g
		oneLine.clear();
		oneLine	 = to_string( stockMoneyState[stockIndex].value ) + MONEY_OUTPUT_MESSAGE_1;
		oneLine	+= to_string( stockMoneyState[stockIndex].stock ) + MONEY_OUTPUT_MESSAGE_2;
		stockOutput.push_back( oneLine );
		// �g�p�҃Z�b�g
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
//	[�T�v] �X���b�g����
//	[����] ����
//	[�ߒl] ����
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
//	[�T�v] �X���b�g�����莞����
//	[����] ����
//	[�ߒl] �I���X�e�[�^�X
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
//	[�T�v] ���ݕ��I���֐�
//	[����] ����
//	[�ߒl] ���ݕ��̎��
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
//	[�T�v] �݌Ɋm�F
//	[����] ���ݕ��̎��
//	[�ߒl] ����
//////////////////////////////////////////////////////
RESULT VendingMachine::check_drinkStock(DRINK_TYPE_ENUM	selectDrinkType)
{
	if( _dataInterface->exist_drink(selectDrinkType) == FALSE ){
		Monitor::output( DRINK_STOCK_NONE );
		return FALSE;
	}
	return TRUE;
}