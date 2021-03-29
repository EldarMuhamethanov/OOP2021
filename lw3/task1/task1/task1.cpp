#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include "Car.h"


using namespace std;

enum class Action {
    INFO,
    ENGINE_ON,
    ENGINE_OFF,
    SET_GEAR,
    SET_SPEED,
    EXIT,
};

string GetEngineState(bool IsTurnedOn)
{
    return IsTurnedOn ? "Включен" : "Выключен";
}

const map<Direction, string> DirectionToDescriptionMap{
    {Direction::BACK, "Назад"},
    {Direction::FORWARD, "Вперед"},
    {Direction::STAY, "Стоит на месте"},
};

const map<int, string> GearToDescriptionMap{
    {-1, "Задний ход"},
    {0, "Нейтральная"},
    {1, "Первая"},
    {2, "Вторая"},
    {3, "Третья"},
    {4, "Четвертая"},
    {5, "Пятая"},
};

const map<string, Action> RequestToActionMap{
    {"Info", Action::INFO},
    {"EngineOn", Action::ENGINE_ON},
    {"EngineOff", Action::ENGINE_OFF},
    {"SetGear", Action::SET_GEAR},
    {"SetSpeed", Action::SET_SPEED},
    {"Exit", Action::EXIT}
};

void PrintInfo(Car& car)
{
    cout << "Состояние двигателя: " << GetEngineState(car.IsTurnedOn()) << endl;
    cout << "Включенная передача: " << GearToDescriptionMap.at(car.GetGear()) << endl;
    cout << "Текущая скорость: " << car.GetSpeed() << endl;
    cout << "Направление движения: " << DirectionToDescriptionMap.at(car.GetDirection()) << endl;
    cout << endl;
}

void EngineOn(Car& car)
{
    car.TurnOnEngine();
}

void EngineOff(Car& car)
{
    car.TurnOffEngine();
}

void SetGear(Car& car, int gear)
{
    car.SetGear(gear);
}

void SetSpeed(Car& car, int speed)
{
    car.SetSpeed(speed);
}

void HandleRequest(string const& request, Car& car, bool& isExit)
{
    istringstream strm(request);
    string action;
    strm >> action;
    if (RequestToActionMap.find(action) == RequestToActionMap.end())
    {
        cout << "Неизвестная команда" << endl;
        return;
    }
    switch (RequestToActionMap.at(action))
    {
        case Action::INFO:
            PrintInfo(car);
            break;
        case Action::ENGINE_ON:
            EngineOn(car);
            break;
        case Action::ENGINE_OFF:
            EngineOff(car);
            break;
        case Action::SET_GEAR:
            int gear;
            strm >> gear;
            SetGear(car, gear);
            break;
        case Action::SET_SPEED:
            int speed;
            strm >> speed;
            SetSpeed(car, speed);
            break;
        case Action::EXIT:
            isExit = true;
            break;
        default:
            break;
    }
}

int main()
{
    Car car;
    string request;
    bool isExit = false;
    while (!isExit)
    {
        getline(cin, request);
        if (!request.empty())
        {
            HandleRequest(request, car, isExit);
        }
    }
}