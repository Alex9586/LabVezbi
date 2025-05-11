#include <iostream>
#include <cstring>

using namespace std;

struct Ochela {
    char brand[50];
    int quantity;

    Ochela(const char * br = "", int q = 0) {
        strcpy(brand, br);
        quantity = q;
    }
};

class Prodavnica {
    private: 
        char name[50];
        char location[50];
        int numTypes;
        Ochela * glasses;
        
    public: 
        Prodavnica(const char * ime = "", const char * lokacija = "") {
            strcpy(name, ime);
            strcpy(location, lokacija);
            numTypes = 0;
            glasses = nullptr;
        }
        Prodavnica(const Prodavnica & other) {
            strcpy(name, other.name);
            strcpy(location, other.location);
            numTypes = other.numTypes;
            glasses = new Ochela[numTypes];
            for (int i = 0; i < numTypes; ++i)
                glasses[i] = other.glasses[i];
        }
        Prodavnica & operator = (const Prodavnica & other) {
            if (this != & other) {
                delete[] glasses;
                strcpy(name, other.name);
                strcpy(location, other.location);
                numTypes = other.numTypes;
                glasses = new Ochela[numTypes];
                for (int i = 0; i < numTypes; ++i)
                    glasses[i] = other.glasses[i];
            }
            return * this;
        }

        ~Prodavnica() {
            delete[] glasses;
        }

        Prodavnica & operator += (const Ochela & o) {
            Ochela * temp = new Ochela[numTypes + 1];
            for (int i = 0; i < numTypes; ++i)
                temp[i] = glasses[i];
            temp[numTypes] = o;
            delete[] glasses;
            glasses = temp;
            ++numTypes;
            return * this;
        }

        Prodavnica & operator -= (const Ochela & o) {
            Ochela * temp = new Ochela[numTypes + 1];
            temp[0] = o;
            for (int i = 0; i < numTypes; ++i)
                temp[i + 1] = glasses[i];
            delete[] glasses;
            glasses = temp;
            ++numTypes;
            return * this;
        }

        Prodavnica & operator++() {
            if (numTypes == 0) return * this;
                Ochela * temp = new Ochela[numTypes - 1];
            for (int i = 0; i < numTypes - 1; ++i)
                temp[i] = glasses[i];
            delete[] glasses;
            glasses = temp;
            --numTypes;
            return * this;
        }

        Prodavnica & operator--() {
            if (numTypes == 0) return * this;
            Ochela * temp = new Ochela[numTypes - 1];
            for (int i = 1; i < numTypes; ++i)
                temp[i - 1] = glasses[i];
            delete[] glasses;
            glasses = temp;
            --numTypes;
            return * this;
        }
        friend ostream & operator << (ostream & out,
            const Prodavnica & p) {
            out << "Ime: " << p.name << endl;
            out << "Lokacija: " << p.location << endl;
            out << "Broj na vidovi ochila: " << p.numTypes << endl;
            for (int i = 0; i < p.numTypes; ++i)
                out << i + 1 << ". Brand: " << p.glasses[i].brand << ", Kolicina: " << p.glasses[i].quantity << endl;
            return out;
        }
};
int main() {
    Prodavnica p("Optika Trend", "Skopje");

    Ochela o1("RayBan", 10);
    Ochela o2("Gucci", 5);
    Ochela o3("Prada", 8);

    p += o1;
    p += o2;

    p -= o3;

    cout << "Po dodavanje:\n" << p << endl;

    ++p;

    cout << "\nPo ++ (otstranuvanje posledniot):\n" << p << endl;

    --p;

    cout << "\nPo -- (otstranuvanje prviot):\n" << p << endl;

    return 0;
}
