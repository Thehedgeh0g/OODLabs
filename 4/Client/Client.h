//
// Created by thehedgeh0g on 16.10.24.
//

#ifndef CLIENT_H
#define CLIENT_H
#include <algorithm>
#include <memory>

#include "../Designer/IDesigner.h"
#include "../Draft/ICanvas.h"
#include "../Painter/IPainter.h"

class Client
{
public:
    Client(
        std::unique_ptr<Designer::IDesigner>&& designer,
        std::unique_ptr<Painter::IPainter>&& painter,
        std::unique_ptr<draft::ICanvas>&& canvas
    ):
        m_canvas(std::move(canvas)),
        m_designer(std::move(designer)),
        m_painter(std::move(painter))
    {
    };

    void Run(std::istream &input, std::ostream &output) const
    {
        auto draft = m_designer->CreateDraft(input);
        output << "Rendering Picture..." << std::endl;
        m_painter->DrawPicture(draft, *m_canvas);
        output << "Picture has been painted" << std::endl;

        std::string exit;
        std::getline(input, exit);
    }

private:
    std::unique_ptr<draft::ICanvas> m_canvas;
    std::unique_ptr<Designer::IDesigner> m_designer;
    std::unique_ptr<Painter::IPainter> m_painter;
};

#endif //CLIENT_H
