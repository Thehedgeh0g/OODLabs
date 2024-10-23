//
// Created by thehedgeh0g on 22.10.24.
//

#include "Src/Document/Document.h"
#include "Src/Client/Client.h"

int main() {

  auto document = std::make_unique<Document>;
  auto client = Client(document);
  return 0;
}
