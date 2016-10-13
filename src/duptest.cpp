#include "..\include\duptest.h"


bool dupcheck::operator==(dupcheck const & rhs) const
{
	return (rhs.kv == this->kv);
}

dupcheck::dupcheck(const std::map<int, int>& ip):kv(ip)
{
}

int dupcheck::IncrementAndGetCount()
{
	count += 1;
	return count;
}

bucket::bucket(int tot, int cnt):total(tot) , count(cnt)
{
}

bool bucket::operator==(bucket const & rhs) const
{
	return (rhs.total == this->total && rhs.count == this->count);
}

int bucket::AddGroup(const std::map<int, int>& ipgroup)
{
	auto it = std::find(dupchecks.begin(), dupchecks.end(), ipgroup);
	if (it == dupchecks.end())
	{
		dupchecks.push_back(dupcheck(ipgroup));
		it = std::find(dupchecks.begin(), dupchecks.end(), ipgroup);
	}
	return (*it).IncrementAndGetCount();
}
