//
// Created by flipd on 25.12.2024.
//

#ifndef IPRESENTOR_H
#define IPRESENTOR_H
namespace Presenter {
    class IPresentor {
        public:
            virtual ~IPresentor() = default;

            virtual void HandleEvent(std::unique_ptr<Presenter::IInteractionEvent> event) = 0;
    };
}
#endif //IPRESENTOR_H
