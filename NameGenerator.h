#pragma once
#include "stdafx.h"
class NameGenerator
{
protected:
	std::string mPrefix;
	unsigned long long int mNext;
public:
	NameGenerator(const NameGenerator& rhs)
		: mPrefix(rhs.mPrefix), mNext(rhs.mNext) {}

	NameGenerator(const std::string& prefix) : mPrefix(prefix), mNext(1) {}

	/// Generate a new name
	std::string generate()
	{
		std::stringstream s;
		s << mPrefix << mNext++;
		return s.str();
	}

	/// Reset the internal counter
	void reset()
	{
		mNext = 1ULL;
	}

	/// Manually set the internal counter (use caution)
	void setNext(unsigned long long int val)
	{
		mNext = val;
	}

	/// Get the internal counter
	unsigned long long int getNext() const
	{
		// lock even on get because 64-bit may not be atomic read
		return mNext;
	}
};