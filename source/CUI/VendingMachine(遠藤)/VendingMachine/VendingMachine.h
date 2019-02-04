#pragma once
#include	"UtilityUnit\Calculator.h"
#include	"UtilityUnit\Monitor.h"
#include	"UtilityUnit\Input.h"
#include	"DataUnit\DataInterface.h"
#include	"Common.h"
#include	"UtilityUnit\Slot.h"

#define					SEPARATE_CHAR				":"

// 自動販売機の状態
enum STATE_ENUM
{
	UNDEFIND_STATE		=-1,						// 初期化用
	FIRST_STATE,									// 入金 or 集計		状態
	SECOND_STATE,									// 購入 or 釣り出し	状態
	THIRD_STATE										// プログラム終了
};

/* メニュー系統 */
// 表示文字
#define					PAYMENT_MESSAGE				"お金を入れる"
#define					BUY_MESSAGE					"購入"
#define					TAKE_CHANGE_MESSAGE			"お釣りを出す"
#define					AGGREGATE_MESSAGE			"集計"
#define					SELECT_MESSAGE				"メニューを選択"

#define					SELECT_COIN_TYPE_MESSAGE	"投入するお金の種類を入力"
#define					SELECT_COIN_NUM_MESSAGE		"投入するお金の枚数を入力"

#define					SELECT_DRINK_TYPE_MESSAGE_1	"購入する飲み物の種類を選択"
#define					SELECT_DRINK_TYPE_MESSAGE_2	"飲み物の種類を選択"
#define					BUY_AFTER_MESSAGE			">>>Thanks for the purchase<<<"
#define					GET_DRINK_MESSAGE			"You did get a drink"

#define					VENDING_CHANGE_MESSAGE		"自販機内金銭在庫"
#define					USER_CHANGE_MESSAGE			"お釣り"
#define					MONEY_OUTPUT_MESSAGE_1		"円が"
#define					MONEY_OUTPUT_MESSAGE_2		"枚"
#define					DRINK_STOCK_MESSAGE			"飲み物在庫"
#define					DRINK_OUTPUT_MESSAGE_1		"が"
#define					DRINK_OUTPUT_MESSAGE_2		"本"

#define					FINISH_MESSAGE				"何か入力して終了"

// 動作一覧
enum MENU_TYPE_ENUM{
	MENU_UNDEFIND		= -1,						// 初期化用
	PAYMENT,										// お金を入れる
	BUY,											// 購入
	TAKE_CHANGE,									// お釣りを出す
	AGGREGATE,										// 集計
	MENU_NUM
};
// 表示文字用
struct MENU_MESSAGE{
	string				message;					// 表示メッセージ
};

class VendingMachine
{
public:

	VendingMachine();
	~VendingMachine();

	RESULT	interface();


private:
	// クラスポインタ
	DataInterface*	_dataInterface;
	// メニュー選択時メッセージ
	MENU_MESSAGE	_menuMessage[MENU_NUM];

	// それぞれの状態の処理
	MENU_TYPE_ENUM	process_firstState();
	MENU_TYPE_ENUM	process_secondState();

	// 動作管理
	STATE_ENUM	manager(MENU_TYPE_ENUM menuType);

	// 入金動作
	STATE_ENUM	input_money();

	// 購入動作
	STATE_ENUM	buy_drink(RESULT* result);

	// お釣りを出す
	STATE_ENUM	output_change();

	// 集計動作
	STATE_ENUM	do_aggregate();

	// スロット処理
	void do_slot();
	RESULT do_slotHit();

	// 飲み物選択
	DRINK_TYPE_ENUM select_drink();

	RESULT check_drinkStock(DRINK_TYPE_ENUM	selectDrinkType);
};