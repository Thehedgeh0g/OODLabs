//
// Created by thehedgeh0g on 11.11.24.
//

#ifndef CLIENT_H
#define CLIENT_H
#include <istream>

#include "ShapeFactory/ShapeFactory.h"
#include "Slide/Slide.h"
#include "Slide/SlideBuilder.h"

class Client
{
public:
    explicit Client(SlideBuilder& slideService) : m_slideService(slideService)
    {
    }

    void HandleCommands(std::istream &inputData, const std::shared_ptr<ICanvas> &canvas)
    {
        m_slideService.CreateSlide(inputData);
    }

private:
SlideBuilder& m_slideService;
};
#endif //CLIENT_H
