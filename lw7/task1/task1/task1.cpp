#include <iostream>
#include "FindMax.h"

using namespace std;

struct Sportsman
{
	string data;
	int height;
	int weight;
};

int main()
{
	vector<Sportsman> sportsmans;

	sportsmans.push_back({ "Артём Никитин", 160, 50 });
	sportsmans.push_back({ "Пётр Нестеров", 170, 60 });
	sportsmans.push_back({ "Дмитрий Горшков", 180, 70 });
	sportsmans.push_back({ "Анна Прокофьева", 190, 80 });
	sportsmans.push_back({ "Сергей Балашов", 200, 90 });

	Sportsman resOfMaxVal;

	FindMax(sportsmans, resOfMaxVal, [](Sportsman a, Sportsman b) { return a.height < b.height; });
	cout << "Max of height: " << resOfMaxVal.data << "\n";

	FindMax(sportsmans, resOfMaxVal, [](Sportsman a, Sportsman b) { return a.height > b.height; });
	cout << "Min of height: " << resOfMaxVal.data << "\n";

	FindMax(sportsmans, resOfMaxVal, [](Sportsman a, Sportsman b) { return a.weight < b.weight; });
	cout << "Max of weight: " << resOfMaxVal.data << "\n";

	FindMax(sportsmans, resOfMaxVal, [](Sportsman a, Sportsman b) { return a.weight > b.weight; });
	cout << "Min of weight: " << resOfMaxVal.data << "\n";

	return 0;
}