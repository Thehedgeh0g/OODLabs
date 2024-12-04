#include "Menu/Menu.h"
#include "Menu/Commands/EjectCoinsCommand.h"
#include "Menu/Commands/ExitCommand.h"
#include "Menu/Commands/InsertCoinCommand.h"
#include "Menu/Commands/RefillCommand.h"
#include "Menu/Commands/TurnCrankCommand.h"

int main()
{
    multiGumballMachine::MultiGumballMachine machine(10);
    menu::Menu menu;

    menu.addCommand("1", "Добавить монету", std::make_shared<menu::InsertCoinCommand>(machine));
    menu.addCommand("2", "Повернуть рычаг", std::make_shared<menu::TurnCrankCommand>(machine));
    menu.addCommand("3", "Пополнить жвачки", std::make_shared<menu::RefillCommand>(machine, 5));
    menu.addCommand("4", "Вернуть неизрасходованные монеты", std::make_shared<menu::EjectCoinsCommand>(machine));
    menu.addCommand("0", "Выход", std::make_shared<menu::ExitCommand>());

    while (true)
    {
        std::cout << "-----------Данные Об Автомате-----------" << machine.ToString() <<
                "----------------------------------------" << std::endl;
        menu.show();
        std::cout << "Выберите действие: ";
        std::string choice;
        std::cin >> choice;
        if (menu.execute(choice))
        {
            break;
        };
        std::cout << std::endl;
    }

    return 0;
}
