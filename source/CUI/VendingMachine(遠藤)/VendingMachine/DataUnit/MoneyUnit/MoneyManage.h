#pragma once
#include	"Money.h"
#include	"..\../Common.h"
#include	"../../UtilityUnit/Calculator.h"

// �����݌�
#define		THOUSAND_STOCK		  8
#define		FIVEHOUNDRED_STOCK	  1
#define		HOUNDRED_STOCK		 10
#define		FIFTY_STOCK			  2
#define		TEN_STOCK			100

enum STOCKER_TYPE_ENUM{
	ALL_STOCKER					= INTEGER_MINUS_ONE,
	VENDING_STOCER,										// �����̔��@�݌�
	USER_STOCKER										// �g�p�ҍ݌�
};

/* �����f�[�^�Ǘ��N���X */
class MoneyManage
{
public:
	MoneyManage();
	~MoneyManage();
	
	// �󂯎�����l���Ή����Ă��邨�����ǂ���
	RESULT is_money(THINGS_STATE money);

	// �����̓����������������𒴂��Ă��Ȃ���
	RESULT check_moneyStockLimit(THINGS_STATE money);

	// �������Z�b�g����
	void set_userMoney(THINGS_STATE money);

	// �����̏�Ԃ��擾����
	void get_moneyState(STOCKER_TYPE_ENUM stockType, MONEY_TYPE_ENUM moneyType, THINGS_STATE (& moneyState)[MONEY_TYPENUM]);

	// ���z���擾����
	THINGS_STATE get_allMoneyValue(STOCKER_TYPE_ENUM stocerType);

	// ���ނ���o���邩�`�F�b�N
	RESULT check_changeOutput(THINGS_STATE change);
	// �w��݌ɂł��ނ肪�o���邩�`�F�b�N
	THINGS_STATE check_changeOutputDecideStocker(THINGS_STATE change, const THINGS_STATE (&stock)[MONEY_TYPENUM]);

	// �w������z����
	void set_buyAfterMoneyState(THINGS_STATE change);

	// �g�p�҂̂��������ɂɓ����
	void move_userMoneyToStock(MONEY_TYPE_ENUM moneyType);

private:
	// �݌ɂƓ�����
	Money*	_stock;
	Money*	_user;
	// �Ή����Ă��邨���̃��X�g
	THINGS_STATE _moneyTypeList[MONEY_TYPENUM];

	// �����݌ɃZ�b�g
	void	set_stock();


	// ���l����Y�����ɕϊ�����
	MONEY_TYPE_ENUM convert_thingsStateToMoneyType(THINGS_STATE money);
};