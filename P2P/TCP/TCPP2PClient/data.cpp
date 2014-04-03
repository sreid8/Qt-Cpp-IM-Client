#include "data.h"

Data::Data()
{
}

Data::Data(const Data &rhs)
{
    text = rhs.text;
    frame = rhs.frame;
}
