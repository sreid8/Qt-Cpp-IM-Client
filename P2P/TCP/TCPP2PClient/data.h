#ifndef DATA_H
#define DATA_H
#include <QString>
class Data
{
public:
    Data();
    Data(const Data& rhs);
    QString text;
    int frame;
};

#endif // DATA_H
