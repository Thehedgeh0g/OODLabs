//
// Created by thehedgeh0g on 22.10.24.
//

#ifndef DOCUMENTITEM_H
#define DOCUMENTITEM_H
#include <memory>

#include "ConstDocumentItem.h"

namespace DocumentItem
{
    class DocumentItem : public ConstDocumentItem
    {
    public:
        explicit DocumentItem(std::unique_ptr<IImage> image) : ConstDocumentItem(image), m_image(std::move(image))
        {
        }

        explicit DocumentItem(std::unique_ptr<IParagraph> paragraph) : ConstDocumentItem(paragraph),
                                                                       m_paragraph(std::move(paragraph))
        {
        }

        // Возвращает указатель на изображение, либо nullptr, если элемент не является изображением
        std::unique_ptr<IImage> GetImage()
        {
            return m_image;
        }

        // Возвращает указатель на параграф, либо nullptr, если элемент не является параграфом
        std::unique_ptr<IParagraph> GetParagraph()
        {
            return m_paragraph;
        }

    private:
        std::unique_ptr<IImage> m_image;
        std::unique_ptr<IParagraph> m_paragraph;
    };
}
#endif //DOCUMENTITEM_H
