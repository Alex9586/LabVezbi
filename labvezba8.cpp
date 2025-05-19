#include <iostream>
#include <cstring>

class Sadnica {
protected:
    char *ime;
    float osnovna_cena;

public:
    Sadnica(const char *ime = "", float cena = 0.0) {
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
        osnovna_cena = cena;
    }

    Sadnica(const Sadnica &s) {
        this->ime = new char[strlen(s.ime) + 1];
        strcpy(this->ime, s.ime);
        osnovna_cena = s.osnovna_cena;
    }

    Sadnica &operator=(const Sadnica &s) {
        if (this != &s) {
            delete[] ime;
            this->ime = new char[strlen(s.ime) + 1];
            strcpy(this->ime, s.ime);
            osnovna_cena = s.osnovna_cena;
        }
        return *this;
    }

    virtual ~Sadnica() {
        delete[] ime;
    }

    virtual float presmetaj_cena() const {
        return osnovna_cena;
    }

    virtual void pechati() const {
        std::cout << "Ime: " << ime << ", Osnovna cena: " << osnovna_cena << "\n";
    }
};

class Drvo : public Sadnica {
private:
    int meseci;

public:
    Drvo(const char *ime = "", float cena = 0.0, int meseci = 0)
        : Sadnica(ime, cena) {
        this->meseci = meseci;
    }

    Drvo(const Drvo &d) : Sadnica(d) {
        this->meseci = d.meseci;
    }

    Drvo &operator=(const Drvo &d) {
        if (this != &d) {
            Sadnica::operator=(d);
            this->meseci = d.meseci;
        }
        return *this;
    }

    float presmetaj_cena() const override {
        int broj_dvojki = meseci / 2;
        return osnovna_cena * (1 + 0.10f * broj_dvojki);
    }

    void pechati() const override {
        Sadnica::pechati();
        std::cout << "Tip: Drvo, Meseci: " << meseci << ", Cena: " << presmetaj_cena() << "\n";
    }
};

class Cvet : public Sadnica {
private:
    int denovi;

public:
    Cvet(const char *ime = "", float cena = 0.0, int denovi = 0)
        : Sadnica(ime, cena) {
        this->denovi = denovi;
    }

    Cvet(const Cvet &c) : Sadnica(c) {
        this->denovi = c.denovi;
    }

    Cvet &operator=(const Cvet &c) {
        if (this != &c) {
            Sadnica::operator=(c);
            this->denovi = c.denovi;
        }
        return *this;
    }

    float presmetaj_cena() const override {
        if (denovi < 14)
            return osnovna_cena / 2;
        return osnovna_cena;
    }

    void pechati() const override {
        Sadnica::pechati();
        std::cout << "Tip: Cvet, Denovi: " << denovi << ", Cena: " << presmetaj_cena() << "\n";
    }
};

void fja(Sadnica *niza[], int n) {
    if (n == 0) return;

    int maxIndex = 0;
    float maxCena = niza[0]->presmetaj_cena();

    for (int i = 1; i < n; i++) {
        float cena = niza[i]->presmetaj_cena();
        if (cena > maxCena) {
            maxCena = cena;
            maxIndex = i;
        }
    }

    std::cout << "Najskapa sadnica:" << "\n";
    niza[maxIndex]->pechati();
}

// Главната функција
int main() {
    Sadnica *niza[20];
    Drvo m("Lipa", 400, 12);
    Cvet sl1("Lubicica", 300, 20), sl2("Krin", 400, 10);
    niza[0] = &m;
    niza[1] = &sl1;
    niza[2] = &sl2;

    fja(niza, 3);

    sl2 = sl1;
    sl2.pechati();

    return 0;
}
