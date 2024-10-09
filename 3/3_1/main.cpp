#include "Beverages.h"
#include "Condiments.h"

#include <iostream>
#include <string>
#include <functional>

using namespace std;

/*
Функция, возвращающая функцию, создающую коричную добавку
*/
function<IBeveragePtr(IBeveragePtr &&)> MakeCinnamon()
{
    return [](IBeveragePtr &&b) {
        return make_unique<CCinnamon>(move(b));
    };
}

/*
Возвращает функцию, декорирующую напиток определенной добавкой

Параметры шаблона:
	Condiment - класс добавки, конструктор которого в качестве первого аргумента
				принимает IBeveragePtr&& оборачиваемого напитка
	Args - список типов прочих параметров конструктора (возможно, пустой)
*/
template<typename Condiment, typename... Args>
auto MakeCondiment(const Args &... args)
{
    // Возвращаем функцию, декорирующую напиток, переданный ей в качестве аргумента
    // Дополнительные аргументы декоратора, захваченные лямбда-функцией, передаются
    // конструктору декоратора через make_unique
    return [=](auto &&b) {
        // Функции make_unique передаем b вместе со списком аргументов внешней функции
        return make_unique<Condiment>(forward<decltype(b)>(b), args...);
    };
}

/*
Перегруженная версия оператора <<, которая предоставляет нам синтаксический сахар
для декорирования компонента

Позволяет создать цепочку оборачивающих напиток декораторов следующим образом:
auto beverage = make_unique<CConcreteBeverage>(a, b, c)
					<< MakeCondimentA(d, e, f)
					<< MakeCondimentB(g, h);

Функциональные объекты MakeCondiment* запоминают аргументы, необходимые для создания
дополнения, и возвращают фабричную функцию, принимающую оборачиваемый напиток, которая
при своем вызове создаст нужный объект Condiment, передав ему запомненные аргументы.
Использование:
	auto beverage =
		make_unique<CConcreteBeverage>(a, b, c)
		<< MakeCondimentA(d, e, f)
		<< MakeCondimentB(g, h);
или даже так:
	auto beverage =
		make_unique<CConcreteBeverage>
		<< MakeCondiment<CondimentA>(d, e, f)
		<< MakeCondiment<CondimentB>(g, h);
В последнем случае нет необходимости писать вручную реализации MakeCondimentA и MakeCondimentB, т.к.
необходимую реализацию сгенерирует компилятор

Классический способ оборачивания выглядел бы так:
	auto baseBeverage = make_unique<CConcretedBeverage>(a, b, c);
	auto wrappedWithCondimentA = make_unique<CCondimentA>(move(baseBeverage), d, e, f);
	auto beverage = make_unique<CCondimentB>(move(wrappedWithCondimentA), g, h);
либо так:
	auto beverage = make_unique<CCondimentB>(
						make_unique<CCondimentA>(
							make_unique<CConcreteBeverage>(a, b, c), // Напиток
							d, e, f	// доп. параметры CondimentA
						),
						g, h		// доп. параметры CondimentB
					);

unique_ptr<CLemon> operator << (IBeveragePtr && lhs, const MakeLemon & factory)
{
	return factory(move(lhs));
}
unique_ptr<CCinnamon> operator << (IBeveragePtr && lhs, const MakeCinnamon & factory)
{
	return factory(move(lhs));
}
*/
template<typename Component, typename Decorator>
auto operator <<(Component &&component, const Decorator &decorate)
{
    return decorate(forward<Component>(component));
}

bool chooseCappuccino(unique_ptr<IBeverage> &beverage)
{
    std::cout << "Choose Cappuccino Portion:\n1 - Standard\n2 - Double" << endl;
    int CappuccinoPortionChoice;
    cin >> CappuccinoPortionChoice;

    if ((CappuccinoPortionChoice < 1) || (CappuccinoPortionChoice > 2))
    {
        std::cout << "Invalid Portion entered" << endl;
        return false;
    }

    beverage = make_unique<CCappuccino>(CappuccinoPortionChoice);
    return true;
}

bool chooseLatte(unique_ptr<IBeverage> &beverage)
{
    std::cout << "Choose Latte Portion:\n1 - Standard\n2 - Double" << endl;
    int LattePortionChoice;
    cin >> LattePortionChoice;

    if ((LattePortionChoice < 1) || (LattePortionChoice > 2))
    {
        std::cout << "Invalid Portion entered" << endl;
        return false;
    }

    beverage = make_unique<CLatte>(LattePortionChoice);
    return true;
}

bool chooseTea(unique_ptr<IBeverage> &beverage)
{
    cout << "Choose Tea type: 1 - Black, 2 - Green, 3 - Herbal, 4 - Red\n";
    int teaChoice;
    cin >> teaChoice;

    if (teaChoice > 4 || teaChoice < 1)
    {
        cout << "Invalid Tea type choice";
        return false;
    }

    beverage = make_unique<CTea>(teaChoice);
    return true;
}

bool chooseMilkshake(unique_ptr<IBeverage> &beverage)
{
    cout << "Choose Milkshake size: 1 - Small, 2 - Medium, 3 - Large\n";
    int milkShakeSizeChoice;
    cin >> milkShakeSizeChoice;

    if (milkShakeSizeChoice > 3 || milkShakeSizeChoice < 1)
    {
        cout << "Invalid size milkshake choice";
        return false;
    }

    beverage = make_unique<CMilkshake>(milkShakeSizeChoice);
    return true;
}

bool extendedBeverageChoice(unique_ptr<IBeverage> &beverage, int beverageChoice)
{
    switch (beverageChoice)
    {
        case 1:
            beverage = make_unique<CCoffee>();
            return true;
        case 2:
            return chooseCappuccino(beverage);
        case 3:
            return chooseLatte(beverage);
        case 4:
            return chooseTea(beverage);
        case 5:
            return chooseMilkshake(beverage);
        default:
            cout << "Invalid beverage choice" << endl;
            return false;
    }
}


bool addLemon(unique_ptr<IBeverage> &beverage)
{
    cout << "Choose Lemon pieces count\n";
    int lemonPieceChoice;
    cin >> lemonPieceChoice;

    beverage = move(beverage) << MakeCondiment<CLemon>(lemonPieceChoice);
    return true;
}

bool addCinnamon(unique_ptr<IBeverage> &beverage)
{
    beverage = move(beverage) << MakeCondiment<CCinnamon>();
    return true;
}

bool addIceCubes(unique_ptr<IBeverage> &beverage)
{
    cout << "Choose Ice Cube type: 1 - Dry, 2 - Water\n";
    int cubeTypeChoice;
    cin >> cubeTypeChoice;

    cout << "Choose Ice Cube count\n";
    int cubeCountChoice;
    cin >> cubeCountChoice;

    beverage = move(beverage) << MakeCondiment<CIceCubes>(cubeCountChoice, static_cast<IceCubeType>(cubeTypeChoice));
    return true;
}

bool addChocolateCrumbs(unique_ptr<IBeverage> &beverage)
{
    cout << "Choose Chocolate Crumbs mass\n";
    int chocolateCrumbsMassChoice;
    cin >> chocolateCrumbsMassChoice;

    beverage = move(beverage) << MakeCondiment<CChocolateCrumbs>(chocolateCrumbsMassChoice);
    return true;
}

bool addCoconutFlakes(unique_ptr<IBeverage> &beverage)
{
    cout << "Choose Coconut Flakes mass\n";
    int coconutFlakesMassChoice;
    cin >> coconutFlakesMassChoice;

    beverage = move(beverage) << MakeCondiment<CCoconutFlakes>(coconutFlakesMassChoice);
    return true;
}

bool addSyrup(unique_ptr<IBeverage> &beverage)
{
    cout << "Choose Syrup type: 1 - Chocolate, 2 - Maple\n";
    int syrupTypeChoice;
    cin >> syrupTypeChoice;

    beverage = move(beverage) << MakeCondiment<CSyrup>(static_cast<SyrupType>(syrupTypeChoice));
    return true;
}

bool addLiquor(unique_ptr<IBeverage> &beverage)
{
    cout << "Choose Liquor type: 1 - Chocolate, 2 - Nutty\n";
    int liquorTypeChoice;
    cin >> liquorTypeChoice;

    beverage = move(beverage) << MakeCondiment<CLiquor>(liquorTypeChoice);
    return true;
}

bool addCream(unique_ptr<IBeverage> &beverage)
{
    beverage = move(beverage) << MakeCondiment<CCream>();
    return true;
}

bool addChocolatePieces(unique_ptr<IBeverage> &beverage)
{
    int chocolatePiecesCountChoice;
    while (true)
    {
        cout << "Choose Count of Chocolate Pieces: 1 - 5\n";
        cin >> chocolatePiecesCountChoice;
        if ((chocolatePiecesCountChoice < 6) && (chocolatePiecesCountChoice > 0))
        {
            break;
        }
        cout << "Invalid Chocolate Pieces count\n";
    }

    beverage = move(beverage) << MakeCondiment<CChocolate>(chocolatePiecesCountChoice);
    return true;
}

bool extendedCondimentChoice(unique_ptr<IBeverage> &beverage, int condimentChoice)
{
    switch (condimentChoice)
    {
        case 1:
            return addLemon(beverage);
        case 2:
            return addCinnamon(beverage);
        case 3:
            return addIceCubes(beverage);
        case 4:
            return addChocolateCrumbs(beverage);
        case 5:
            return addCoconutFlakes(beverage);
        case 6:
            return addSyrup(beverage);
        case 7:
            return addLiquor(beverage);
        case 8:
            return addCream(beverage);
        case 9:
            return addChocolatePieces(beverage);
        default:
            return false;
    }
}

void DialogWithUser()
{
    vector<unique_ptr<IBeverage>> beverages;
    int beverageChoice;

    do
    {
        cout << "Type to choose: 1 - Coffee, 2 - Cappuccino, 3 - Latte, 4 - Tea, 5 - Milkshake, 0 - Checkout\n";
        cin >> beverageChoice;

        if (beverageChoice == 0)
        {
            break;
        }

        unique_ptr<IBeverage> beverage;

        if (extendedBeverageChoice(beverage, beverageChoice))
        {
            int condimentChoice;
            do
            {
                cout << "Choose your condiment:\n";
                cout << "1 - Lemon, 2 - Cinnamon, 3 - Ice Cubes\n";
                cout << "4 - Chocolate Crumbs, 5 - Coconut Flakes, 6 - Syrup\n";
                cout << "7 - Liquor, 8 - Cream, 9 - Chocolate Pieces\n";
                cout << "0 - Checkout\n";
                cin >> condimentChoice;
            }
            while (extendedCondimentChoice(beverage, condimentChoice));

            beverages.push_back(move(beverage));
        }

    } while (true);

    for (const auto& beverage : beverages)
    {
        cout << beverage->GetDescription() << ", cost: " << beverage->GetCost() << endl;
    }
}


int main()
{
    DialogWithUser();
}
