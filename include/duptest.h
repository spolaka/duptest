#pragma once
#include <map>
#include <vector>

class dupcheck {
public :
	bool operator ==(dupcheck const &rhs) const;
	dupcheck(const std::map<int, int>& ip);
	int IncrementAndGetCount();
private:
	std::map<int, int> kv;
	int count = 0;
};

class bucket {
public :	
	bucket(int tot, int cnt);
	bool operator ==(bucket const &rhs) const;
	int AddGroup(const std::map<int, int>& ipgroup);
private:
	int total;
	int count;
	std::vector<dupcheck> dupchecks;
};

