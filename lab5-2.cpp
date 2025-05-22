#include <iostream>
#include <string>

class BasketballPlayer {
private:
    std::string name;
    int wage;

public:
    BasketballPlayer(std::string name = "", int wage = 0)
        : name(name), wage(wage) {}

    void print() const {
        std::cout << "Basketball player: " << name << "\n";
        std::cout << "Wage: " << wage << "\n";
    }

    int calculateWage(float averagePoints) const {
        if (averagePoints < 0) averagePoints = 0;
        return wage + 50 * averagePoints;
    }
};

class BasketballTeam {
private:
    std::string teamName;
    int numBasketballPlayers;
    float averagePoints;
    BasketballPlayer teamPlayers[8];

public:
    BasketballTeam(std::string teamName = "Unknown Team", int numBasketballPlayers = 0, float averagePoints = 0, BasketballPlayer* p = nullptr)
        : teamName(teamName),
          numBasketballPlayers((numBasketballPlayers < 0 || numBasketballPlayers > 8) ? 0 : numBasketballPlayers),
          averagePoints((averagePoints < 0) ? 0 : averagePoints)
    {
        if (p != nullptr) {
            for (int j = 0; j < numBasketballPlayers; ++j) {
                teamPlayers[j] = p[j];
            }
        }
    }

    void print() const {
        std::cout << "Team: " << teamName << "\n";
        std::cout << "Number of players: " << numBasketballPlayers << "\n";
        std::cout << "Average points: " << averagePoints << "\n";
        std::cout << "--- Team Members ---\n";
        for (int i = 0; i < numBasketballPlayers; ++i) {
            teamPlayers[i].print();
            std::cout << "Calculated Wage: " << teamPlayers[i].calculateWage(averagePoints) << " denari\n";
            std::cout << "--------------------\n";
        }
    }
};

int main() {
    BasketballPlayer players[5];
    std::string name;

    for (int i = 0; i < 5; ++i) {
        std::cout << "Enter name for player " << i + 1 << ": ";
        std::getline(std::cin, name);
        players[i] = BasketballPlayer(name, 30000);
    }

    std::string teamName;
    std::cout << "Enter the team name: ";
    std::getline(std::cin, teamName);

    float averagePoints = 85;

    BasketballTeam team(teamName, 5, averagePoints, players);
    std::cout << "\n=== Team Details ===\n";
    team.print();

    return 0;
}
