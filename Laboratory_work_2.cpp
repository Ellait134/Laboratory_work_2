#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

struct Galaxy { 
    string name;                     // Название галактики
    string type;                    // Тип галактики
    int age;                       // Возраст галактики (в миллиардах лет)
    long long int count;          // Количество звезд в галактике
    float distance;              // Расстояние от Земли (в миллионах световых лет)
};

void printGalaxy(const Galaxy& galaxy) {
    cout << "Название: " << galaxy.name << endl;
    cout << "Тип: " << galaxy.type << endl;
    cout << "Возраст: " << galaxy.age << " миллиардов лет" << endl;
    cout << "Количество звезд: " << galaxy.count << endl;
    cout << "Расстояние от Земли: " << galaxy.distance << " миллионов световых лет" << endl;
}

void readGalaxiesFromFile(const string& filename, vector<Galaxy>& galaxies) {
    ifstream file(filename);
    if (file.is_open()) {
        int numGalaxies;
        file >> numGalaxies;
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < numGalaxies; i++) {
            Galaxy galaxy;
            file.ignore(numeric_limits<streamsize>::max(), '\n'); // очищаем символ новой строки

            getline(file, galaxy.name);
            getline(file, galaxy.type);
            file >> galaxy.age;
            file >> galaxy.count;
            file >> galaxy.distance;
            file.ignore(numeric_limits<streamsize>::max(), '\n');
            galaxies.push_back(galaxy);
        }

        file.close();
    }
}
void printAllGalaxies(const vector<Galaxy>& galaxies) {
    cout << "Информация о всех галактиках:" << endl;
    for (int i = 0; i < galaxies.size(); i++) {
        cout << "Галактика " << i + 1 << ":" << endl;
        printGalaxy(galaxies[i]);
        cout << endl;
    }
}

Galaxy findGalaxyByAge(const vector<Galaxy>& galaxies, int targetAge) {
    for (const Galaxy& galaxy : galaxies) {
        if (galaxy.age == targetAge) {
            return galaxy;
        }
    }

    // Если галактика с заданным возрастом не найдена, создаем пустую галактику с пустыми полями
    return Galaxy{ "", "", 0, 0, 0.0f };
}

Galaxy findGalaxyWithMinDistanceAndStarsCount(const vector<Galaxy>& galaxies, float searchCount) {
    Galaxy minDistanceStarsCountGalaxy{ "", "", 0, 0, numeric_limits<float>::max() };

    for (const Galaxy& galaxy : galaxies) {
        if (galaxy.count > searchCount && galaxy.distance < minDistanceStarsCountGalaxy.distance) {
            minDistanceStarsCountGalaxy = galaxy;
        }
    }

    return minDistanceStarsCountGalaxy;
}

int main() {
    setlocale(LC_ALL, "Russian");   // Установка русской локализации

    vector<Galaxy> galaxies;
    readGalaxiesFromFile("galaxies.txt", galaxies);
    printAllGalaxies(galaxies);

    //////////////// ЗАДАНИЕ 1

    int targetAge;
    cout << "Введите возраст галактики для поиска: ";
    cin >> targetAge;

    Galaxy foundGalaxy = findGalaxyByAge(galaxies, targetAge);
    if (!foundGalaxy.name.empty()) {
        cout << "Найденная галактика с возрастом " << targetAge << ":" << endl;
        printGalaxy(foundGalaxy);
    }
    else {
        cout << "Галактика с возрастом " << targetAge << " не найдена." << endl;
    }
    //////// ЗАДАНИЕ 2

    long long int searchCount;
    cout << "Введите минимальное количество звезд для галактики, которую вы хотите найти: ";
    cin >> searchCount;

    Galaxy minDistanceGalaxy = findGalaxyWithMinDistanceAndStarsCount(galaxies, searchCount);

    if (minDistanceGalaxy.name.empty()) {
        cout << "Галактика с минимальным расстоянием и больше чем " << searchCount << " звездами не найдена." << endl;
    }
    else {
        cout << "Галактика с минимальным расстоянием и больше чем " << searchCount << " звездами:" << endl;
        printGalaxy(minDistanceGalaxy);
    }

    return 0;
}