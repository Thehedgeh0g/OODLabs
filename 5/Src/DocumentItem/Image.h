//
// Created by thehedgeh0g on 22.10.24.
//

#ifndef IMAGE_H
#define IMAGE_H
#include <utility>

#include "IImage.h"

namespace DocumentItem
{
    class Image : public IImage
    {
    public:
        Image(std::string  path, const int width, const int height)
        : m_path(std::move(path)), m_width(width), m_height(height) {}

        [[nodiscard]] std::string GetPath() const override
        {
            return m_path;
        }

        [[nodiscard]] int GetWidth() const override
        {
            return m_width;
        }

        [[nodiscard]] int GetHeight() const override
        {
            return m_height;
        }

        void Resize(const int width, const int height) override
        {
            m_width = width;
            m_height = height;
        }
    private:
        int m_width = 0;
        int m_height = 0;
        std::string m_path;
    };
}
#endif //IMAGE_H
