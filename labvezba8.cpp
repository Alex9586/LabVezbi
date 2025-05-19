#include <iostream>
#include <cstring>

class Sadnica {
protected:
    char *name;
    float base_price;

public:
    Sadnica(const char *name = "", float price = 0.0) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        base_price = price;
    }

    Sadnica(const Sadnica &p) {
        this->name = new char[strlen(p.name) + 1];
        strcpy(this->name, p.name);
        base_price = p.base_price;
    }

    Sadnica &operator=(const Sadnica &p) {
        if (this != &p) {
            delete[] name;
            this->name = new char[strlen(p.name) + 1];
            strcpy(this->name, p.name);
            base_price = p.base_price;
        }
        return *this;
    }

    virtual ~Sadnica() {
        delete[] name;
    }

    virtual float calculate_price() const {
        return base_price;
    }

    virtual void print() const {
        std::cout << "Ime: " << name << ", Osnovna cena: " << base_price << "\n";
    }
};

class Devo : public Sadnica {
private:
    int months;

public:
    Devo(const char *name = "", float price = 0.0, int months = 0)
        : Sadnica(name, price) {
        this->months = months;
    }

    Devo(const Devo &t) : Sadnica(t) {
        this->months = t.months;
    }

    Devo &operator=(const Devo &t) {
        if (this != &t) {
            Sadnica::operator=(t);
            this->months = t.months;
        }
        return *this;
    }

    float calculate_price() const override {
        int pairs_of_months = months / 2;
        return base_price * (1 + 0.10f * pairs_of_months);
    }

    void print() const override {
        Sadnica::print();
        std::cout << "Tip: Drvo, Meseci: " << months << ", Cena: " << calculate_price() << "\n";
    }
};

class Cvet : public Sadnica {
private:
    int days_blooming;

public:
    Cvet(const char *name = "", float price = 0.0, int days = 0)
        : Sadnica(name, price) {
        this->days_blooming = days;
    }

    Cvet(const Cvet &f) : Sadnica(f) {
        this->days_blooming = f.days_blooming;
    }

    Cvet &operator=(const Cvet &f) {
        if (this != &f) {
            Sadnica::operator=(f);
            this->days_blooming = f.days_blooming;
        }
        return *this;
    }

    float calculate_price() const override {
        if (days_blooming < 14)
            return base_price / 2;
        return base_price;
    }

    void print() const override {
        Sadnica::print();
        std::cout << "Tip: Cvet, Denovi: " << days_blooming << ", Cena: " << calculate_price() << "\n";
    }
};

void fla(Sadnica *array[], int n) {
    if (n == 0) return;

    int maxIndex = 0;
    float maxPrice = array[0]->calculate_price();

    for (int i = 1; i < n; i++) {
        float price = array[i]->calculate_price();
        if (price > maxPrice) {
            maxPrice = price;
            maxIndex = i;
        }
    }

    std::cout << "Najskapa sadnica:" << "\n";
    array[maxIndex]->print();
}

int main() {
    Sadnica *array[20];
    Devo m("Lipa", 400, 12);
    Cvet sl1("Lubicica", 300, 20), sl2("Krin", 400, 10);
    array[0] = &m;
    array[1] = &sl1;
    array[2] = &sl2;

    fla(array, 3);
    std::cout << "\n";
    sl2 = sl1;
    sl2.print();

    return 0;
}
