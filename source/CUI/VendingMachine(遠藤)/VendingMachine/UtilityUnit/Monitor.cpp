#include "Monitor.h"
#include <Windows.h>

Monitor::Monitor()
{

}

Monitor::~Monitor()
{

}

//////////////////////////////////////
//	[概要] 1文出力
//	[引数] 出力文字
//	[戻値] なし
//////////////////////////////////////
void Monitor::output(string message)
{
	cout << message << endl;
}

//////////////////////////////////////
//	[概要] 複数文出力
//	[引数] 出力文字
//	[戻値] なし
//////////////////////////////////////
void Monitor::outputVec(vector<string> messaga)
{
	for( vector<string>::iterator it = messaga.begin(); it != messaga.end(); ++it ){
		cout << *it << endl;
	}
}

//////////////////////////////////////
//	[概要] 1文出力
//	[引数] 出力文字
//	[戻値] なし
//////////////////////////////////////
void Monitor::output_messageToUnique(string message)
{
	system("cls");
	for( unsigned char spaceNum = INTEGER_ZERO; spaceNum <= SPACE_COUNT * 0.5; ++spaceNum){
		for( unsigned char firstCount = INTEGER_ZERO; firstCount < spaceNum; ++firstCount ){
			cout<< SPACE;
		}
		cout << FIRST_STRING;
		for( unsigned char endCount	= spaceNum + spaceNum; endCount <= SPACE_COUNT; ++endCount ){
			cout<< SPACE;
		}
		cout << END_STRING << endl;
		Sleep( SLEEP_TIME );
		system("cls");
	}
	cout << message << endl;
	Sleep( LEAVE_TIME );
	system("cls");
}