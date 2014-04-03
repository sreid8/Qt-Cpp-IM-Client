#include "User.h"


User::User(void)
{
}


User::~User(void)
{
}

User& User::operator=(const User& rhs)
{
	ip = rhs.ip;
	return *this;
}

User::User(const User& other)
{
	ip = other.ip;
}
