#include "DataInterface.h"

DataInterface::DataInterface()
{
	_drinkManage = new DrinkManage();
	_moneyManage = new MoneyManage();
}

DataInterface::~DataInterface()
{
	delete _drinkManage;
	delete _moneyManage;
}