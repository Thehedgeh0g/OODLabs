//
// Created by thehedgeh0g on 10.11.24.
//

#ifndef IGROUPSTYLE_H
#define IGROUPSTYLE_H
#include <limits>

#include "IStyle.h"

namespace style
{
class IGroupStyle : public IStyle
{
public:
    virtual void InsertStyle(IStyle & style, size_t position = std::numeric_limits<size_t>::max()) = 0;
    virtual void RemoveStyleAtIndex(size_t index) = 0;
};
}
#endif //IGROUPSTYLE_H
