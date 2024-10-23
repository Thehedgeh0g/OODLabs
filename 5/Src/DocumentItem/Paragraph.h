//
// Created by thehedgeh0g on 22.10.24.
//

#ifndef PARAGRAPH_H
#define PARAGRAPH_H
#include <utility>

#include "IParagraph.h"

namespace DocumentItem
{
    class Paragraph : public IParagraph
    {
    public:
        explicit Paragraph(std::string text) : m_text(std::move(text))
        {
        }

        [[nodiscard]] std::string GetText() const override
        {
            return m_text;
        }

        void SetText(const std::string &text) override
        {
            m_text = text;
        }
    private:
        std::string m_text;
    };
}
#endif //PARAGRAPH_H
