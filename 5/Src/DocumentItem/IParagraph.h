//
// Created by thehedgeh0g on 22.10.24.
//

#ifndef IPARAGRAPH_H
#define IPARAGRAPH_H
#include <string>

namespace DocumentItem
{
    class IParagraph
    {
    public:
        virtual ~IParagraph() = default;

        [[nodiscard]] virtual std::string GetText() const = 0;

        virtual void SetText(const std::string &text) = 0;
    };
}
#endif IPARAGRAPH_H
