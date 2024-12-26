//
// Created by flipd on 25.12.2024.
//

#ifndef PSHAPE_H
#define PSHAPE_H
#include <memory>
#include <regex>

#include "IPresentor.h"
#include "../App/DraftFacade.h"

namespace view {
    class VWindow;
}

namespace Presenter {
    class PShape : public IPresentor {
    public:
        PShape(
            std::unique_ptr<App::DraftFacade> &draftFacade,
            std::unique_ptr<App::DraftContainer> &draftContainer
        ): m_draftFacade(draftFacade), m_draftContainer(draftContainer) {
        };

        ~PShape() override = default;

        void HandleEvent(std::unique_ptr<Presenter::IInteractionEvent> event) override {
            std::cout << event->GetEventData().data << std::endl;
            std::string target, action;
            size_t last_space = event->GetEventData().data.find_last_of(' ');
            target = event->GetEventData().data.substr(last_space + 1);
            std::istringstream iss(event->GetEventData().data);
            iss >> action;
            if (action == "MousePressed" && ((target == "Triangle") || (target == "Circle") || (target == "Rectangle"))
                && (CountOfParams(event->GetEventData().data) == 2)) {
                std::cout << "Creating" << std::endl;
                Create(target + " 400 200 50 50 0x0000000FF");
                return;
            }
            if (action == "MousePressed" && target != "Triangle" || target == "Circle" || target == "Rectangle" && (
                    CountOfParams(event->GetEventData().data) == 2)) {
                std::cout << "Selecting " + target << std::endl;
                Select(target);
                return;
            }
            if (action == "MouseMoved" && !(target == "Triangle") || (target == "Circle") || (target == "Rectangle") &&
                (CountOfParams(event->GetEventData().data) == 6)) {
                std::cout << "Moving " + target << std::endl;
                double xFrom, yFrom, xTo, yTo;
                iss >> xFrom >> yFrom >> xTo >> yTo;
                Update("Move " + std::to_string(xTo - xFrom) + " " + std::to_string(yTo - yFrom));
                return;
            }
        }

    private:
        void Create(const std::string &createData) {
            m_draftFacade->InsertNewShape(createData);
        }

        void Update(const std::string &updateData) {
            m_draftFacade->UpdateSelectedShapes(updateData);
        }

        void Select(const std::string &selectData) {
            m_draftFacade->SelectShape(selectData);
        }

        void Delete() {
            m_draftFacade->DeleteSelectedShapes();
        }

        static int CountOfParams(const std::string &str) {
            std::regex wordRegex("\\S+");
            return std::distance(
                std::sregex_iterator(str.begin(), str.end(), wordRegex),
                std::sregex_iterator()
            );
        }


        std::unique_ptr<App::DraftFacade> &m_draftFacade;
        std::unique_ptr<App::DraftContainer> &m_draftContainer;
    };
}
#endif //PSHAPE_H
