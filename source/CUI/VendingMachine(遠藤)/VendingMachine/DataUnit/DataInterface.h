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

	/*�����֘A*/
	// �Ή����Ă��邨�����ǂ���
	RESULT is_money(THINGS_STATE money);

	// ���������߂��Ă��Ȃ���
	RESULT check_moneyStockLimit(THINGS_STATE moneyStock);

	// �������Z�b�g����
	void set_userMoney(THINGS_STATE money);
	
	// �w��݌Ɏ�ʂ̂����̏�Ԃ��擾
	void get_moneyState(STOCKER_TYPE_ENUM stockType, MONEY_TYPE_ENUM moneyType, THINGS_STATE (& moneyState)[MONEY_TYPENUM]);

	// �w��݌Ɏ�ʂ̑��z���擾
	THINGS_STATE get_allMoneyValue(STOCKER_TYPE_ENUM stocerType);

	// ���ނ���o���邩�`�F�b�N
	RESULT check_changeOutput(THINGS_STATE change);
	
	// �w�����K�ݒ�
	void set_buyAfterMoneyState(THINGS_STATE change);

	void move_userMoneyToStock(MONEY_TYPE_ENUM moneyType);

	/*���ݕ��֘A*/
	// �Ή����Ă�����ݕ����ǂ���
	RESULT is_drink(DRINK_TYPE_ENUM drinkType);

	// �w�肵�����̂����邩�ǂ���
	RESULT exist_drink(DRINK_TYPE_ENUM drinkType);

	// �w����ݕ��̉��i���擾
	THINGS_STATE get_value(DRINK_TYPE_ENUM drinkType);

	// �݌ɂ����炷
	void reduce_drink(DRINK_TYPE_ENUM drinkType);

	// ��Ԃ��擾
	void get_drinkState(DRINK_TYPE_ENUM drinkType, THINGS_STATE (&drink)[DRINK_TYPENUM]);

	// ���ݕ������擾
	DRINK_NAME get_drinkNameToTypeNum(DRINK_TYPE_ENUM drinkType);
 
private:
	DrinkManage* _drinkManage;
	MoneyManage* _moneyManage;
};

/*�����֘A*/
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
/*���ݕ��֘A*/
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