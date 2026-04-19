// Copyright 2026 <Grobforcode>
#ifndef INCLUDE_AUTOMATA_H_
#define INCLUDE_AUTOMATA_H_

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
    int selectedDrink;

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

#endif  // INCLUDE_AUTOMATA_H_
