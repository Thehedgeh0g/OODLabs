//
// Created by flipd on 24.12.2024.
//

#ifndef IUSECASE_H
#define IUSECASE_H

namespace App {
    class IUseCase {
        public:
            virtual ~IUseCase() = default;

            virtual void Execute() = 0;

    };
}

#endif //IUSECASE_H
