//
// Created by thehedgeh0g on 22.10.24.
//

#ifndef IDOCUMENT_H
#define IDOCUMENT_H
#include <memory>
#include <optional>
#include "./../DocumentItem/DocumentItem.h"


namespace Document
{
    /*
    Интерфейс документа
    */
    class IDocument
    {
    public:
        // Вставляет параграф текста в указанную позицию (сдвигая последующие элементы)
        // Если параметр position не указан, вставка происходит в конец документа
        virtual void InsertParagraph(const std::string &text,
                                     std::optional<size_t> position = std::nullopt) = 0;

        virtual void ReplaceText(const std::string &newText, size_t position) = 0;

        // Вставляет изображение в указанную позицию (сдвигая последующие элементы)
        // Параметр path задает путь к вставляемому изображению
        // При вставке изображение должно копироваться в подкаталог images
        // под автоматически сгенерированным именем
        virtual void InsertImage(const std::string &path, int width, int height,
                                 std::optional<size_t> position = std::nullopt) = 0;

        virtual void ResizeImage(int width, int height, size_t position) = 0;

        // Возвращает количество элементов в документе
        [[nodiscard]] virtual size_t GetItemsCount() const = 0;

        // Доступ к элементам изображения
        [[nodiscard]] virtual DocumentItem::ConstDocumentItem GetItem(size_t index) const = 0;

        virtual DocumentItem::DocumentItem GetItem(size_t index) = 0;

        // Удаляет элемент из документа
        virtual void DeleteItem(size_t index) = 0;

        // Возвращает заголовок документа
        [[nodiscard]] virtual std::string GetTitle() const = 0;

        // Изменяет заголовок документа
        virtual void SetTitle(const std::string &title) = 0;

        // Сообщает о доступности операции Undo
        [[nodiscard]] virtual bool CanUndo() const = 0;

        // Отменяет команду редактирования
        virtual void Undo() = 0;

        // Сообщает о доступности операции Redo
        [[nodiscard]] virtual bool CanRedo() const = 0;

        // Выполняет отмененную команду редактирования
        virtual void Redo() = 0;

        // Сохраняет документ в формате html. Изображения сохраняются в подкаталог images.
        // Пути к изображениям указываются относительно пути к сохраняемому HTML файлу
        virtual void Save(const std::string &path) const = 0;

        virtual ~IDocument() = default;
    };
}
#endif //IDOCUMENT_H
