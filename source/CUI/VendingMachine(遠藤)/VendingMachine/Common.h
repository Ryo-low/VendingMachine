#pragma once
#include <stdio.h>
 #include <conio.h>

 /* define const */
 #define ESC "\x1b" //�G�X�P�[�v����(ESC:0x1B)�̒�`
#include <string>
using namespace std;
#define				INTEGER_MINUS_ONE		-1
#define				INTEGER_ZERO			0
#define				INTEGER_ONE				1
#define				ADJUST_NUM				1		// �z�񒲐��l

#define				MONEY_STOCK_LIMIT		20		// �d�ݓ����\��

// �G���[�n
#define				MONEY_TYPE_IS_NO		"�Ή����Ă��Ȃ��d�݂̎�ނł�"
#define				MONEY_STOCK_LIMIT_OVER	"���܂ł��������ł��܂���"
#define				DRINK_STOCK_NONE		"�݌ɂ�����܂���"
#define				USER_MONEY_NONE			"������������܂���"
#define				CHANGE_NONE				"���ނ肪����܂���"


// �֐�����
typedef int RESULT;
#ifdef		TRUE
#undef		TRUE
#endif
#define		TRUE    1

#ifdef		FALSE
#undef		FALSE
#endif
#define		FALSE	0

struct THINGS_STATE{
	unsigned short	value;				// ���l
	unsigned short	stock;				// ��
};
// �����̉��l
#define	YEN_THOUSAND		1000
#define	YEN_FIVEHOUNDRED	 500
#define	YEN_HOUNDRED		 100
#define	YEN_FIFTY			  50
#define	YEN_TEN				  10


class Common
{
public:
	Common();
	~Common();

	
};