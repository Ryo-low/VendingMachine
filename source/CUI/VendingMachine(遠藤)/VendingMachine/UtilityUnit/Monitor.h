#pragma once
#include "../Common.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define				SPACE_COUNT		20
#define				SPACE			" "
#define				FIRST_STRING	">"
#define				END_STRING		"<"
#define				LEFT_STRING		">>>>>"
#define				RIGHT_STRING	"<<<<<"
#define				SLEEP_TIME		35
#define				LEAVE_TIME		1100

class Monitor
{
public:
	Monitor();
	~Monitor();
	// 1文の出力
	static void output(string message);

	// 複数行の出力
	static void outputVec(vector<string> message);

	// 1文出力
	static void output_messageToUnique(string message);

	static void clear();
};

inline void Monitor::clear()
{
	system("cls");
}