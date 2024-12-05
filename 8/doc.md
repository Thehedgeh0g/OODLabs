```mermaid
classDiagram
    IGumballMachine <|.. GumballMachine : "private"
    GumballMachine o-- IState
    GumballMachine *-- HasQuarterState
    GumballMachine *-- NoQuarterState
    GumballMachine *-- SoldOutState
    GumballMachine *-- SoldState

    class IGumballMachine {
        + ReleaseBall()*
        + GetBallCount() unsigned*
        + SetSoldOutState()*
        + SetNoQuarterState()*
        + SetSoldState()*
        + SetHasQuarterState()*
    }

    class GumballMachine {
        + EjectQuarters()
        + InsertQuarter()
        + TurnCrank()
        + ToString()
        - ReleaseBall()
        - GetBallCount() unsigned
        - SetSoldOutState()
        - SetNoQuarterState()
        - SetSoldState()
        - SetHasQuarterState()

        - m_count: unsigned 
        - m_soldState: SoldState 
        - m_soldOutState: SoldOutState
        - m_noQuarterState: NoQuarterState
        - m_hasQuarterState: HasQuarterState
        - m_state: * IState
    }

    IState <|.. HasQuarterState
    IState <|.. NoQuarterState
    IState <|.. SoldOutState
    IState <|.. SoldState

    HasQuarterState o-- IGumballMachine
    NoQuarterState o-- IGumballMachine
    SoldOutState o-- IGumballMachine
    SoldState o-- IGumballMachine

    namespace State {
        class IState {
            + InsertQuarter()*
            + EjectQuarter()*
            + TurnCrank()*
            + Dispense()*
            + ToString() string*
        }

        class HasQuarterState {
            + InsertQuarter()
            + EjectQuarter()
            + TurnCrank()
            + Dispense()
            + ToString() string

            - m_gumballMachine: & IGumballMachine
        }

        class NoQuarterState {
            + InsertQuarter()
            + EjectQuarter()
            + TurnCrank()
            + Dispense()
            + ToString() string

            - m_gumballMachine: & IGumballMachine
        }

        class SoldOutState {
            + InsertQuarter()
            + EjectQuarter()
            + TurnCrank()
            + Dispense()
            + ToString() string

            - m_gumballMachine: & IGumballMachine
        }

        class SoldState {
            + InsertQuarter()
            + EjectQuarter()
            + TurnCrank()
            + Dispense()
            + ToString() string

            - m_gumballMachine: & IGumballMachine
        }
    }
```

TODO: Зачем нужен контекст

1) Хранения текущего состояния:

- Контекст отслеживает текущее состояние объекта и делегирует ему выполнение соответствующих операций. Это позволяет
  изолировать логику состояний от самого контекста.

2) Переключения состояний:

- Контекст предоставляет интерфейс для смены текущего состояния, вызывая соответствующий метод (например,
  SetSoldOutState() в вашем примере). Это позволяет управлять переходами между состояниями внутри объекта.

3) Предоставления интерфейса для клиента:

- Клиент взаимодействует с контекстом через его публичный интерфейс, не зная о внутренней реализации состояний. Это
  упрощает использование объекта, скрывая сложность управления состояниями.

4) Обеспечения доступа состояниям к данным:

- Контекст может содержать данные и методы, которые состояния используют для выполнения своей логики. Например, в вашем
  примере CGumballMachine предоставляет метод ReleaseBall и количество шариков через GetBallCount.

5) Централизации управления:

- Контекст служит центральной точкой, через которую координируется вся логика состояний. Это упрощает добавление новых
  состояний или модификацию существующих.

TODO: Добавить тесты для каждого состояния - готово (покрытие = 100%) <br>
TODO: Не все кейсы