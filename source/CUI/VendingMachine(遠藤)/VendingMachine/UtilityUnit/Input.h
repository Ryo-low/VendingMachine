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

	// ���l�݂̂̓��͂��󂯕t����
	static INPUT_NUM input_uIntNum();

	// ���͒l���w��͈͓���
	static RESULT is_trueNumber(INPUT_NUM input, int max, int min);
};