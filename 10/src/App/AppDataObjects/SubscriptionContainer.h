//
// Created by flipd on 26.12.2024.
//

#ifndef SUBSCRIPTIONCONTAINER_H
#define SUBSCRIPTIONCONTAINER_H
#include <map>
#include <string>
#include <boost/signals2/connection.hpp>

#include "ShapeSelection.h"
#include "../../Domain/Draft.h"
#include "./../../Domain/Shape.h"

namespace App {
    class SubscriptionContainer {
    public:
        explicit SubscriptionContainer(const std::unique_ptr<Draft> &draft) {
            SubscribeOnShapeDeleted(draft, [this](const std::string &id) {
                this->DoOnShapeDeleted(id);
            });
        }

        ~SubscriptionContainer() {
            m_shapeModifiedSubscriptions.clear();
        }

        void SubscribeOnShape(
            const std::unique_ptr<Draft> &draft,
            const std::string &id,
            const std::function<void(
                const RectD &,
                const std::string &
            )> &handler
        ) {
            m_shapeModifiedSubscriptions.insert({id, draft->FindShapeById(id)->DoOnShapeChanged(handler)});
        }

        void UnsubscribeOnShape(const std::shared_ptr<Shape> &shape) {
            m_shapeModifiedSubscriptions.erase(shape->GetId());
        }

        void SubscribeOnShapeCreated(
            const std::unique_ptr<Draft> &draft,
            const std::function<void(
                const RectD &,
                const std::string &,
                const uint32_t &,
                const ShapeType &
            )> &handler
        ) {
            m_shapeCreatedSubscription = draft->DoOnShapeCreated(handler);
        }

        void SubscribeOnShapeDeleted(
            const std::unique_ptr<Draft> &draft,
            const std::function<void(
                const std::string&
            )> &handler
        ) {
            m_shapeDeletedSubscription = draft->DoOnShapeDeleted(handler);
        }

        void DoOnShapeDeleted(const std::string &id) {
            m_shapeModifiedSubscriptions[id].disconnect();
        }

        void SubscribeOnSelectionChanged(ShapeSelection &selection, const std::function<void(const std::string &)> &handler) {
            m_shapeSelectionSubscription = selection.DoOnSelectionChanged(handler);
        }

    private:
        boost::signals2::scoped_connection m_shapeCreatedSubscription;
        boost::signals2::scoped_connection m_shapeDeletedSubscription;
        boost::signals2::scoped_connection m_shapeSelectionSubscription;
        std::map<std::string, boost::signals2::scoped_connection> m_shapeModifiedSubscriptions;
    };
}

#endif //SUBSCRIPTIONCONTAINER_H
