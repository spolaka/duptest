#include <sstream>
#include <utility>
#include <iterator>

#include "..\interface\dupcounter.h"

bool dupcounter::AddLine(const std::string& oneLine)
{
	bool retValue = true;
	std::map<int, int> ipMap;
	std::vector<int> iplist;
	int total = 0;
	int count = 0;
	if (!GetLineAsIntMap(ipMap, iplist , total , count , oneLine))
	{
		invalidIps.push_back(oneLine);
		return false;
	}
	auto it = std::find(buckets.begin(), buckets.end(), bucket(total, count));
	if (it == buckets.end())
	{
		buckets.push_back(bucket(total, count));
		it = std::find(buckets.begin(), buckets.end(), bucket(total, count));
	}

	int grpcount = (*it).AddGroup(ipMap);
	if (grpcount == 1){
		nondupgroups += 1;	
		retValue = false;
	}
	else if(grpcount == 2){
		nondupgroups -= 1;
		dupgroups += 2;
	}
	else{
		dupgroups += 1;
	}
	if (grpcount > freqGroupCount) {
		freqGroup = iplist;
		freqGroupCount = grpcount;
	}

	return retValue;
}

int dupcounter::GetDupCount() const
{
	return dupgroups;
}

int dupcounter::GetNonDupCount() const
{
	return nondupgroups;
}

const std::vector<int>& dupcounter::GetFrequentGroup() const
{
	return freqGroup;
}

const std::vector<std::string>& dupcounter::GetInvalidLines() const
{
	return invalidIps;
}

bool dupcounter::GetLineAsIntMap(std::map<int, int>& ipMap, std::vector<int>& iplist, int & total, int & count, const std::string & oneLine)
{
	std::stringstream this_line(oneLine);
	int i;
	while (!this_line.eof())
	{
		int c = this_line.peek();
		if (c == ',' || c == ' ') {
			this_line.ignore(1);
		}
		else if (c < '0' || c > '9'){			
			return false;
		}
		if (this_line >> i){
			iplist.push_back(i);
			std::map<int, int>::iterator it = ipMap.find(i);
			if (it != ipMap.end()) {
				(*it).second += 1;
			}
			else {
				ipMap[i] = 1;
			}
		}
	}
	return true;
}
