//
// Created by flipd on 25.12.2024.
//

#ifndef VSHAPE_H
#define VSHAPE_H
#include <memory>
#include <string>
#include "./../ShapeStrategies/IFigure.h"
#include "./../ICanvas.h"


namespace view {

    class VShape {
    public:
        VShape(std::string id, const uint32_t &color, std::unique_ptr<IFigure> figure)
            : m_id(std::move(id)),
              m_color(color),
              m_figure(std::move(figure)) {
        }


        [[nodiscard]] std::string GetId() const {
            return m_id;
        }

        void SetId(const std::string &id) {
            m_id = id;
        }

        [[nodiscard]] uint32_t GetColor() const {
            return m_color;
        }

        void SetColor(uint32_t color) {
            m_color = color;
        }

        [[nodiscard]] IFigure &GetFigure(){
            return *m_figure;
        }

        void SetFigure(std::unique_ptr<IFigure> figure) {
            this->m_figure = move(figure);
        }

        void Draw(std::unique_ptr<ICanvas>& canvas) const {
            try {
                m_figure->Draw(0x000000FF, canvas);
            }
            catch (const std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        }

    private:
        std::string m_id;
        uint32_t m_color;
        std::unique_ptr<IFigure> m_figure;
    };
}
#endif //VSHAPE_H
