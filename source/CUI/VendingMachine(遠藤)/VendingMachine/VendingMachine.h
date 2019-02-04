#pragma once
#include	"UtilityUnit\Calculator.h"
#include	"UtilityUnit\Monitor.h"
#include	"UtilityUnit\Input.h"
#include	"DataUnit\DataInterface.h"
#include	"Common.h"
#include	"UtilityUnit\Slot.h"

#define					SEPARATE_CHAR				":"

// �����̔��@�̏��
enum STATE_ENUM
{
	UNDEFIND_STATE		=-1,						// �������p
	FIRST_STATE,									// ���� or �W�v		���
	SECOND_STATE,									// �w�� or �ނ�o��	���
	THIRD_STATE										// �v���O�����I��
};

/* ���j���[�n�� */
// �\������
#define					PAYMENT_MESSAGE				"����������"
#define					BUY_MESSAGE					"�w��"
#define					TAKE_CHANGE_MESSAGE			"���ނ���o��"
#define					AGGREGATE_MESSAGE			"�W�v"
#define					SELECT_MESSAGE				"���j���[��I��"

#define					SELECT_COIN_TYPE_MESSAGE	"�������邨���̎�ނ����"
#define					SELECT_COIN_NUM_MESSAGE		"�������邨���̖��������"

#define					SELECT_DRINK_TYPE_MESSAGE_1	"�w��������ݕ��̎�ނ�I��"
#define					SELECT_DRINK_TYPE_MESSAGE_2	"���ݕ��̎�ނ�I��"
#define					BUY_AFTER_MESSAGE			">>>Thanks for the purchase<<<"
#define					GET_DRINK_MESSAGE			"You did get a drink"

#define					VENDING_CHANGE_MESSAGE		"���̋@�����K�݌�"
#define					USER_CHANGE_MESSAGE			"���ނ�"
#define					MONEY_OUTPUT_MESSAGE_1		"�~��"
#define					MONEY_OUTPUT_MESSAGE_2		"��"
#define					DRINK_STOCK_MESSAGE			"���ݕ��݌�"
#define					DRINK_OUTPUT_MESSAGE_1		"��"
#define					DRINK_OUTPUT_MESSAGE_2		"�{"

#define					FINISH_MESSAGE				"�������͂��ďI��"

// ����ꗗ
enum MENU_TYPE_ENUM{
	MENU_UNDEFIND		= -1,						// �������p
	PAYMENT,										// ����������
	BUY,											// �w��
	TAKE_CHANGE,									// ���ނ���o��
	AGGREGATE,										// �W�v
	MENU_NUM
};
// �\�������p
struct MENU_MESSAGE{
	string				message;					// �\�����b�Z�[�W
};

class VendingMachine
{
public:

	VendingMachine();
	~VendingMachine();

	RESULT	interface();


private:
	// �N���X�|�C���^
	DataInterface*	_dataInterface;
	// ���j���[�I�������b�Z�[�W
	MENU_MESSAGE	_menuMessage[MENU_NUM];

	// ���ꂼ��̏�Ԃ̏���
	MENU_TYPE_ENUM	process_firstState();
	MENU_TYPE_ENUM	process_secondState();

	// ����Ǘ�
	STATE_ENUM	manager(MENU_TYPE_ENUM menuType);

	// ��������
	STATE_ENUM	input_money();

	// �w������
	STATE_ENUM	buy_drink(RESULT* result);

	// ���ނ���o��
	STATE_ENUM	output_change();

	// �W�v����
	STATE_ENUM	do_aggregate();

	// �X���b�g����
	void do_slot();
	RESULT do_slotHit();

	// ���ݕ��I��
	DRINK_TYPE_ENUM select_drink();

	RESULT check_drinkStock(DRINK_TYPE_ENUM	selectDrinkType);
};