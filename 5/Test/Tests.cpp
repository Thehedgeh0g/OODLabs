//
// Created by thehedgeh0g on 29.10.24.
//

#include <gtest/gtest.h>
#include "./../Src/Document/Document.h"
#include "./../Src/Command/InsertParagraphCommand.h"
#include "./../Src/Client/Client.h"


TEST(DocumentTests, InsertParagraph) {
    std::istringstream inputData("InsertParagraph end testParagraph\nInsertParagraph 0 testParagraph2\nList\nUndo\nList\nRedo\nList\nexit");
    std::ostringstream outputData;
    auto client = Client(std::make_unique<Document::Document>());
    client.Run(inputData, outputData);
    std::string output = outputData.str();

    ASSERT_EQ(output, "Title: title\n1. Paragrpah: testParagraph2\n2. Paragrpah: testParagraph\nTitle: title\nTitle: title\n1. Paragrpah: testParagraph2\n2. Paragrpah: testParagraph\n");
}

TEST(DocumentTests, InsertImage) {
    std::istringstream inputData("InsertImage end 100 100 ./image1.png\nList\nUndo\nList\nexit");
    std::ostringstream outputData;
    auto client = Client(std::make_unique<Document::Document>());
    client.Run(inputData, outputData);
    std::string output = outputData.str();

    ASSERT_EQ(output, "Title: title\n1. Image: 100 100 ./image1.png\nTitle: title\n");
}

TEST(DocumentTests, SetTitle) {
    std::istringstream inputData("SetTitle test\nList\nUndo\nList\nexit");
    std::ostringstream outputData;
    auto client = Client(std::make_unique<Document::Document>());
    client.Run(inputData, outputData);
    std::string output = outputData.str();

    ASSERT_EQ(output, "Title: test\nTitle: title\n");
}

TEST(DocumentTests, ReplaceText) {
    std::istringstream inputData("InsertParagraph end testParagraph\nInsertParagraph 0 testParagraph2\nReplaceText 0 newText\nList\nUndo\nList\nexit");
    std::ostringstream outputData;
    auto client = Client(std::make_unique<Document::Document>());
    client.Run(inputData, outputData);
    std::string output = outputData.str();

    ASSERT_EQ(output, "Title: title\n1. Paragrpah: newText\n2. Paragrpah: testParagraph\nTitle: title\n1. Paragrpah: testParagraph2\n2. Paragrpah: testParagraph\n");
}

TEST(DocumentTests, ResizeImage) {
    std::istringstream inputData("InsertImage end 100 100 ./image1.png\nResizeImage 0 150 150\nList\nexit");
    std::ostringstream outputData;
    auto client = Client(std::make_unique<Document::Document>());
    client.Run(inputData, outputData);
    std::string output = outputData.str();

    ASSERT_EQ(output, "Title: title\n1. Image: 150 150 ./image1.png\n");
}

TEST(DocumentTests, DeleteItem) {
    std::istringstream inputData("InsertImage end 100 100 ./image1.png\nDeleteItem 0\nList\nexit");
    std::ostringstream outputData;
    auto client = Client(std::make_unique<Document::Document>());
    client.Run(inputData, outputData);
    std::string output = outputData.str();

    ASSERT_EQ(output, "Title: title\n");
}

TEST(DocumentTests, Undo) {
    std::istringstream inputData("InsertImage end 100 100 ./image1.png\nDeleteItem 0\nUndo\nList\nexit");
    std::ostringstream outputData;
    auto client = Client(std::make_unique<Document::Document>());
    client.Run(inputData, outputData);
    std::string output = outputData.str();

    ASSERT_EQ(output, "Title: title\n1. Image: 100 100 ./image1.png\n");
}

TEST(DocumentTests, Redo) {
    std::istringstream inputData("InsertImage end 100 100 ./image1.png\nDeleteItem 0\nUndo\nRedo\nList\nexit");
    std::ostringstream outputData;
    auto client = Client(std::make_unique<Document::Document>());
    client.Run(inputData, outputData);
    std::string output = outputData.str();

    ASSERT_EQ(output, "Title: title\n");
}

TEST(DocumentTests, CantUndo) {
    std::istringstream inputData("Undo\nexit");
    std::ostringstream outputData;
    auto client = Client(std::make_unique<Document::Document>());
    client.Run(inputData, outputData);
    std::string output = outputData.str();

    ASSERT_EQ(output, "Can't undo\n");
}

TEST(DocumentTests, CantRedo) {
    std::istringstream inputData("InsertImage end 100 100 ./image1.png\nDeleteItem 0\nUndo\nResizeImage 0 150 150\nRedo\nList\nexit");
    std::ostringstream outputData;
    auto client = Client(std::make_unique<Document::Document>());
    client.Run(inputData, outputData);
    std::string output = outputData.str();

    ASSERT_EQ(output, "Can't redo\nTitle: title\n1. Image: 150 150 ./image1.png\n");
}

TEST(DocumentTests, TryUseUnexistingCommand) {
    std::istringstream inputData("abc\nexit");
    std::ostringstream outputData;
    auto client = Client(std::make_unique<Document::Document>());
    client.Run(inputData, outputData);
    std::string output = outputData.str();

    ASSERT_EQ(output, "Unknown command\n");
}

