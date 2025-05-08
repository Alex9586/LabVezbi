#include <iostream>
const int maxTeamMembers = 100;
class Cyclist {
private:
	std::string name;
	std::string lastName;
	int age;
	int points;
public:
	Cyclist(std::string name = "", std::string lastName = "", int age = 0, int points = 0)
		: name(name), lastName(lastName), age(age), points(points) {}
	int getPoints() const {
		return points;
	}
	void print() const {
		std::cout << "Cyclist: " << name << " " << lastName << ", age " << age << ", Points" << points << "\n";
	}
};
class CylcingTeam {
private:
	std::string teamName;
	std::string sponsorName;
	Cyclist cyclists[maxTeamMembers];
	int  numCyclists;
public:
	CylcingTeam(std::string teamName = "", std::string sponsorName = "", int numCyclists = 0)
		: teamName(teamName), sponsorName(sponsorName), numCyclists(numCyclists) {}

	void addCyclist(const Cyclist& c) {
		if(numCyclists < maxTeamMembers) {
			cyclists[numCyclists++] = c;
		} else {
			return;
		}
	}

	int teamPoints() const {
		int totalPoints = 0;
		for(int i = 0; i < numCyclists; ++i) {
			totalPoints += cyclists[i].getPoints();
		}
		return totalPoints;
	}

	void print() const {
		std::cout << "Team: " << teamName << ", Sponsor: " << sponsorName << "\n";
		std::cout << "TeamMembers: \n";
		for(int i = 0; i < numCyclists; ++i) {
			cyclists[i].print();
		}
		std::cout << "\n Total team points: " << teamPoints() << "\n";
	}

};
int main() {
	CylcingTeam team("FEIT Gaming", "Monster Energy");

	Cyclist c1("Marko", "Petrov", 25, 120);
	Cyclist c2("Ana", "Ilievska", 22, 140);
	Cyclist c3("Ivan", "Stanoev", 28, 100);

	team.addCyclist(c1);
	team.addCyclist(c2);
	team.addCyclist(c3);

	team.print();

	return 0;
}
