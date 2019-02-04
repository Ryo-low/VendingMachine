#pragma once
#include "Calculator.h"
#include "..\Common.h"
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
using namespace std;

struct INPUT_NUM{
	int number;
};

class Input
{
public:
	Input();

	~Input();

	// 数値のみの入力を受け付ける
	static INPUT_NUM input_uIntNum();

	// 入力値が指定範囲内か
	static RESULT is_trueNumber(INPUT_NUM input, int max, int min);
};