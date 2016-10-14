#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include "..\interface\dupcounter.h"

void printValues(const dupcounter& dummydupCounter) {
	std::cout << "dup count " << dummydupCounter.GetDupCount() << std::endl;
	std::cout << "non-dup count " << dummydupCounter.GetNonDupCount() << std::endl;
	std::cout << "frequent group ";
	for (auto val : dummydupCounter.GetFrequentGroup())
		std::cout << val << " ";
	std::cout << std::endl;
	std::cout << "Invalid Lines Start" << std::endl;
	for(auto str : dummydupCounter.GetInvalidLines())
		std::cout << str.c_str() << std::endl;
	std::cout << "Invalid Lines End" << std::endl;
	
}

void PrintAndassertValues(const dupcounter& dummydupCounter , const int& dupCount , const int& nondupCount , 
					const std::vector<int>& freqGroup , const  std::vector<std::string>&  invalidLines ) {
	printValues(dummydupCounter);
	assert(dummydupCounter.GetDupCount() == dupCount);
	assert(dummydupCounter.GetNonDupCount() == nondupCount);
	assert(dummydupCounter.GetFrequentGroup() == freqGroup);
	assert(dummydupCounter.GetInvalidLines() == invalidLines);
}

void TestBasic() {	
	
	dupcounter dummydupCounter;
	PrintAndassertValues(dummydupCounter, 0, 0, {}, {});
	dummydupCounter.AddLine("1,2,3,4");
	PrintAndassertValues(dummydupCounter, 0, 1, {1,2,3,4}, {});
	dummydupCounter.AddLine("1, 2, 3, 4");
	PrintAndassertValues(dummydupCounter, 2, 0, {1,2,3,4}, {});
	dummydupCounter.AddLine("1, 2, 3");
	PrintAndassertValues(dummydupCounter, 2, 1, { 1,2,3,4 }, {});
	dummydupCounter.AddLine("1, 2, 4");
	PrintAndassertValues(dummydupCounter, 2, 2, { 1,2,3,4 }, {});
	dummydupCounter.AddLine("1, 2, 3");
	PrintAndassertValues(dummydupCounter, 4, 1, { 1,2,3,4 }, {});
	dummydupCounter.AddLine(", , ,");
	PrintAndassertValues(dummydupCounter, 4, 1, { 1,2,3,4 }, {", , ,"});
	dummydupCounter.AddLine("-----");
	PrintAndassertValues(dummydupCounter, 4, 1, { 1,2,3,4 }, { ", , ," , "-----" });
	dummydupCounter.AddLine("-----");
	PrintAndassertValues(dummydupCounter, 4, 1, { 1,2,3,4 }, { ", , ," , "-----" , "-----"});
	dummydupCounter.AddLine("4 ,3 , 3 , 0");
	PrintAndassertValues(dummydupCounter, 4, 2, { 1,2,3,4 }, { ", , ," , "-----" , "-----" });
	dummydupCounter.AddLine("3, 1, 2");
	PrintAndassertValues(dummydupCounter, 5, 2, { 1,2,3 }, { ", , ," , "-----" , "-----" });

}

void TestFileRead(const std::string& filePath){
	dupcounter dummydupCounter;

	std::ifstream infile(filePath);
	std::string line;
	while (std::getline(infile, line))
	{	
		dummydupCounter.AddLine(line);
	}
	printValues(dummydupCounter);
}

int main() {
//	TestBasic();
	TestFileRead("E:/input.txt");
}