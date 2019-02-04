#pragma once
#include <stdio.h>
 #include <conio.h>

 /* define const */
 #define ESC "\x1b" //エスケープ文字(ESC:0x1B)の定義
#include <string>
using namespace std;
#define				INTEGER_MINUS_ONE		-1
#define				INTEGER_ZERO			0
#define				INTEGER_ONE				1
#define				ADJUST_NUM				1		// 配列調整値

#define				MONEY_STOCK_LIMIT		20		// 硬貨投入可能数

// エラー系
#define				MONEY_TYPE_IS_NO		"対応していない硬貨の種類です"
#define				MONEY_STOCK_LIMIT_OVER	"枚までしか投入できません"
#define				DRINK_STOCK_NONE		"在庫がありません"
#define				USER_MONEY_NONE			"投入金が足りません"
#define				CHANGE_NONE				"お釣りが足りません"


// 関数結果
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
	unsigned short	value;				// 価値
	unsigned short	stock;				// 個数
};
// お金の価値
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