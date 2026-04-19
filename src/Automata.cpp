#include "Automata.h"
#include <iostream>

Automata::Automata() : cash(0), state(STATES::OFF), selectedDrink(-1) {
    // Инициализация меню и цен (можно загружать из файла, но для простоты зададим вручную)
    menu = {"Espresso", "Americano", "Latte", "Cappuccino", "Tea"};
    prices = {100, 120, 150, 150, 80};
}

void Automata::on() {
    if (state == STATES::OFF) {
        state = STATES::WAIT;
        std::cout << "Автомат включен. Ожидание действий.\n";
    }
}

void Automata::off() {
    if (state == STATES::WAIT) {
        state = STATES::OFF;
        std::cout << "Автомат выключен.\n";
    }
}

void Automata::coin(int amount) {
    if (state == STATES::WAIT || state == STATES::ACCEPT) {
        cash += amount;
        state = STATES::ACCEPT;
        std::cout << "Внесено " << amount << " руб. Текущая сумма: " << cash << " руб.\n";
    }
}

std::vector<std::string> Automata::getMenu() const {
    return menu;
}

STATES Automata::getState() const {
    return state;
}

void Automata::choice(int index) {
    if (state == STATES::ACCEPT) {
        if (index >= 0 && index < static_cast<int>(menu.size())) {
            selectedDrink = index;
            std::cout << "Выбран напиток: " << menu[index] << " (Цена: " << prices[index] << " руб.)\n";
            state = STATES::CHECK;
            if (check()) {
                state = STATES::COOK;
                cook();
            } else {
                std::cout << "Недостаточно средств. Внесите ещё денег или отмените.\n";
                state = STATES::ACCEPT;
            }
        } else {
            std::cout << "Неверный номер напитка.\n";
        }
    }
}

bool Automata::check() {
    if (state == STATES::CHECK) {
        if (selectedDrink >= 0 && cash >= prices[selectedDrink]) {
            return true;
        }
    }
    return false;
}

void Automata::cancel() {
    if (state == STATES::ACCEPT) {
        std::cout << "Обслуживание отменено. Возврат " << cash << " руб.\n";
        cash = 0;
        state = STATES::WAIT;
    }
}

void Automata::cook() {
    if (state == STATES::COOK) {
        std::cout << "Идёт приготовление напитка \"" << menu[selectedDrink] << "\"...\n";
        // Имитация процесса
        finish();
    }
}

void Automata::finish() {
    if (state == STATES::COOK) {
        int change = cash - prices[selectedDrink];
        std::cout << "Напиток готов! Заберите ваш " << menu[selectedDrink] << ".\n";
        if (change > 0) {
            std::cout << "Ваша сдача: " << change << " руб.\n";
        }
        cash = 0;
        selectedDrink = -1;
        state = STATES::WAIT;
        std::cout << "Спасибо за покупку! Автомат готов к новому заказу.\n";
    }
}