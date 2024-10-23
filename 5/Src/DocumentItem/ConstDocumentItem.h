//
// Created by thehedgeh0g on 22.10.24.
//

#ifndef CONSTDOCUMENTITEM_H
#define CONSTDOCUMENTITEM_H
#include <memory>

#include "IImage.h"
#include "IParagraph.h"

namespace DocumentItem
{
    class ConstDocumentItem
    {
    public:
        // Конструктор, принимающий указатель на изображение
        explicit ConstDocumentItem(std::unique_ptr<const IImage> image) : m_image(std::move(image))
        {
        }

        // Конструктор, принимающий указатель на параграф
        explicit ConstDocumentItem(std::unique_ptr<const IParagraph> paragraph) : m_paragraph(std::move(paragraph))
        {
        }

        // Возвращает указатель на константное изображение, либо nullptr,
        // если элемент не является изображением
        [[nodiscard]] std::unique_ptr<const IImage> GetImage() const
        {
            return m_image;
        }

        // Возвращает указатель на константный параграф, либо nullptr,
        // если элемент не является параграфом
        [[nodiscard]] std::unique_ptr<const IParagraph> GetParagraph() const
        {
            return m_paragraph;
        }

        virtual ~ConstDocumentItem() = default;

    private:
        std::unique_ptr<const IImage> m_image;
        std::unique_ptr<const IParagraph> m_paragraph;
    };
}
#endif //CONSTDOCUMENTITEM_H
