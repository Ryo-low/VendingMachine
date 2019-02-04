#include	"MoneyManage.h"

MoneyManage::MoneyManage()
{
	_stock	= new Money();
	_user	= new Money();
	// �Ή������X�g�쐬
	_moneyTypeList[THOUSAND].value		= YEN_THOUSAND;
	_moneyTypeList[FIVEHOUNDRED].value	= YEN_FIVEHOUNDRED;
	_moneyTypeList[HOUNDRED].value		= YEN_HOUNDRED;
	_moneyTypeList[FIFTY].value			= YEN_FIFTY;
	_moneyTypeList[TEN].value			= YEN_TEN;
	// �����݌ɃZ�b�g
	set_stock();
}

MoneyManage::~MoneyManage()
{
	delete _stock;
	delete _user;
}

//////////////////////////////////
//	[�T�v] �����݌ɂ��Z�b�g����
//	[����] �Ȃ�
//	[�ߒl] �Ȃ�
/////////////////////////////////
void MoneyManage::set_stock()
{
	// �����݌ɃZ�b�g
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
//	[�T�v] �Ή����Ă��邨�����ǂ���
//	[����] ���̉��l
//	[�ߒl] ����
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
//	[�T�v] ���������������l�𒴂��Ă��Ȃ���
//	[����] �������̖���
//	[�ߒl] ����
//////////////////////////////////////////////////
RESULT MoneyManage::check_moneyStockLimit(THINGS_STATE money)
{
	// �w�����̏�Ԃ��擾
	MONEY_TYPE_ENUM	moneyType	= convert_thingsStateToMoneyType( money );
	THINGS_STATE	moneyState[MONEY_TYPENUM];
	_user->get_moneyState( moneyType, moneyState );
	// �����l��ݒ�
	unsigned long limitNum		= MONEY_STOCK_LIMIT - moneyState[moneyType].stock;
	RESULT result				= Calculator::equalBigger(limitNum, money.stock);
	
	return result;
}

//////////////////////////////////
//	[�T�v] ���������Z�b�g����
//	[����] �������̏��
//	[�ߒl] �Ȃ�
/////////////////////////////////
void MoneyManage::set_userMoney(THINGS_STATE money)
{
	MONEY_TYPE_ENUM moneyType = ALL_MONEY_TYPE;
	moneyType = convert_thingsStateToMoneyType( money );

	_user->add_money( moneyType, money );
}

//////////////////////////////////////////////////////
//	[�T�v] ��ʖ��ɂ����̏�Ԃ��擾����
//	[����] �擾���ʁA�w�����ʁA�����̏�Ԋi�[�ϐ�
//	[�ߒl] �Ȃ�
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
//	[�T�v] �w��݌Ɏ�ʂ̑��z���擾����
//	[����] �݌Ɏ��
//	[�ߒl] ���z
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
//	[�T�v] ���ނ肪�o���邩�`�F�b�N
//	[����] ���ނ�
//	[�ߒl] ����
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
//	[�T�v] �w��݌ɏ�Ԃ��炨�ނ肪�o���邩�`�F�b�N
//	[����] ���ނ�,�w��݌�
//	[�ߒl] ���ނ�(value=0:�ޏo�\)
//////////////////////////////////////////////////////
THINGS_STATE MoneyManage::check_changeOutputDecideStocker(THINGS_STATE change, const THINGS_STATE (&stock)[MONEY_TYPENUM])
{
	for( unsigned char stockIndex = INTEGER_ZERO;
		(stockIndex < MONEY_TYPENUM) && (change.value != INTEGER_ZERO); ++stockIndex ){
		// �Ώۋ���ʂ̂��ނ肪�K�v���`�F�b�N
		unsigned long outputNum = INTEGER_ZERO;
		outputNum = Calculator::unsignedDivision( change.value, stock[stockIndex].value );
		if( outputNum == INTEGER_ZERO ){
			continue;
		}
		// �Ώۋ���ʂ����݂��邩�`�F�b�N
		if( stock[stockIndex].stock == INTEGER_ZERO ){
			continue;
		}
		// �o�͂��ނ薇������
		if( Calculator::bigger(outputNum, stock[stockIndex].stock) ){
			outputNum = stock[stockIndex].stock;
		}
		change.value -= (unsigned short)(stock[stockIndex].value * outputNum);
	}
	return change;
}

/////////////////////////////////////////////
//	[�T�v] �g�p�҂̂�������K�Ɠ����ɂ���
//	[����] ��K
//	[�ߒl] �Ȃ�
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
		// �݌ɂƍő喇��(���̐�����)�ǂ��炪�傫����
		// �ŏI������0�̏ꍇ�͂��̎�ނł̏o�͕͂s�\
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
//	[�T�v] �w���ʂ̋����g�p�ҁ��݌ɂ���
//	[����] �����̎��
//	[�ߒl] �Ȃ�
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
//	[�T�v] ���l���炨���̎�ނɕϊ�����
//	[����] �����̏��
//	[�ߒl] �����̎��(�񋓌^)
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