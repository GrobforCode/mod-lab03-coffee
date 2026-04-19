#include "Automata.h"
#include <iostream>

int main() {
    Automata machine;

    // Демонстрация работы
    machine.on();                          // WAIT
    machine.coin(50);                      // ACCEPT
    machine.coin(30);                      // ещё 30, всего 80
    machine.choice(4);                     // выбор чая за 80
    // Ожидается: проверка -> приготовление -> завершение
    // Затем снова WAIT

    std::cout << "\n--- Новый заказ ---\n";
    machine.coin(100);                     // ACCEPT
    machine.choice(0);                     // Espresso за 100
    // Успешно

    std::cout << "\n--- Проверка отмены ---\n";
    machine.coin(200);                     // ACCEPT
    machine.cancel();                      // WAIT, возврат

    std::cout << "\n--- Недостаточно средств ---\n";
    machine.coin(10);                      // ACCEPT
    machine.choice(1);                     // Americano за 120, недостаточно
    machine.coin(120);                     // докидываем
    machine.choice(1);                     // теперь хватает

    machine.off();                         // OFF
    return 0;
}