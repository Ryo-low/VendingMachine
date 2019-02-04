#include "main.h"

int main()
{
	RESULT result = TRUE;
	VendingMachine* vendingMachine = new VendingMachine();

	result = vendingMachine->interface();
	delete vendingMachine;


	return result;
}