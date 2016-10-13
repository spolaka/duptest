#pragma once
#include <vector>
#include "..\include\duptest.h"

class dupcounter {

public:
	bool AddLine(const std::string& oneLine);
	int GetDupCount() const;
	int GetNonDupCount() const;
	const std::vector<int>& GetFrequentGroup() const;
	const std::vector<std::string>& GetInvalidLines() const;
private :

	bool GetLineAsIntMap(std::map<int, int>& ipMap, std::vector<int>& iplist, int& total, int& count, const std::string& oneLine);

	std::vector<bucket> buckets;
	std::vector<std::string> invalidIps;
	int dupgroups = 0;
	int nondupgroups = 0;
	std::vector<int> freqGroup;
	int freqGroupCount = 0;
};
