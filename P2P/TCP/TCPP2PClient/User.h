#pragma once
#include <QHostAddress>
class User
{
public:
	User(void);
	~User(void);
	User(const User& other);
	User& operator=(const User& rhs);
	QHostAddress ip;

};

