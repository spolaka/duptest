#include <iostream>
#include "..\interface\dupcounter.h"

dupcounter dummydupCounter;

void printValues() {
	std::cout << "dup count " << dummydupCounter.GetDupCount() << std::endl;
	std::cout << "non-dup count " << dummydupCounter.GetNonDupCount() << std::endl;
	for(auto str : dummydupCounter.GetInvalidLines())
		std::cout << "Invalid Lines " << str.c_str() << std::endl;
	for (auto val : dummydupCounter.GetFrequentGroup())
		std::cout << "frequent group " << val << std::endl;
}

int main() {

	printValues();
	dummydupCounter.AddLine("1,2,3,4");
	printValues();
	dummydupCounter.AddLine("1, 2, 3, 4");
	printValues();
	dummydupCounter.AddLine("1, 2, 3");
	printValues();
	dummydupCounter.AddLine("1, 2, 4");
	printValues();
	dummydupCounter.AddLine("1, 2, 3");
	printValues();
	dummydupCounter.AddLine(", , ,");
	printValues();
	dummydupCounter.AddLine("-----");
	printValues();
	dummydupCounter.AddLine("-----");
	printValues();
}