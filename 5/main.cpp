//
// Created by thehedgeh0g on 22.10.24.
//

#include "Src/Document/Document.h"
#include "Src/Client/Client.h"

int main()
{
    auto client = Client(std::make_unique<Document::Document>());
    client.Run(std::cin, std::cout);
    return 0;
}
