#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <vector>
#include <string>

enum class STATES {
    OFF,
    WAIT,
    ACCEPT,
    CHECK,
    COOK
};

class Automata {
private:
    int cash;
    std::vector<std::string> menu;
    std::vector<int> prices;
    STATES state;
    int selectedDrink; // индекс выбранного напитка

public:
    Automata();

    void on();
    void off();
    void coin(int amount);
    std::vector<std::string> getMenu() const;
    STATES getState() const;
    void choice(int index);
    bool check();
    void cancel();
    void cook();
    void finish();
};

#endif // AUTOMATA_H