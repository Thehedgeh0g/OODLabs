//
// Created by thehedgeh0g on 03.12.24.
//

#ifndef ICOMMAND_H
#define ICOMMAND_H
namespace menu
{
class Command {
public:
    virtual bool execute() = 0;
    virtual ~Command() = default;
};
}
#endif //ICOMMAND_H
