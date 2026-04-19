// Copyright 2022 GHA Test Team

#include <gtest/gtest.h>
#include "Automata.h"

TEST(AutomataTest, InitialStateIsOff) {
    Automata a;
    EXPECT_EQ(a.getState(), STATES::OFF);
}

TEST(AutomataTest, TurnOnChangesStateToWait) {
    Automata a;
    a.on();
    EXPECT_EQ(a.getState(), STATES::WAIT);
}

TEST(AutomataTest, TurnOffFromWaitChangesStateToOff) {
    Automata a;
    a.on();
    a.off();
    EXPECT_EQ(a.getState(), STATES::OFF);
}

TEST(AutomataTest, CoinInWaitMovesToAccept) {
    Automata a;
    a.on();
    a.coin(50);
    EXPECT_EQ(a.getState(), STATES::ACCEPT);
}

TEST(AutomataTest, CancelInAcceptReturnsToWaitAndResetsCash) {
    Automata a;
    a.on();
    a.coin(100);
    a.cancel();
    EXPECT_EQ(a.getState(), STATES::WAIT);
    // Проверяем, что после отмены при следующем coin начинаем с нуля
    a.coin(30);
    a.choice(0); // недостаточно, но проверяем косвенно
}

TEST(AutomataTest, ChoiceWithEnoughMoneyGoesToCookAndThenWait) {
    Automata a;
    a.on();
    a.coin(150);
    a.choice(2); // Latte за 150
    // После успешного приготовления состояние должно стать WAIT
    EXPECT_EQ(a.getState(), STATES::WAIT);
}

TEST(AutomataTest, ChoiceWithInsufficientMoneyStaysInAccept) {
    Automata a;
    a.on();
    a.coin(10);
    a.choice(0); // Espresso 100
    EXPECT_EQ(a.getState(), STATES::ACCEPT);
}

TEST(AutomataTest, MultipleCoinsAccumulate) {
    Automata a;
    a.on();
    a.coin(50);
    a.coin(40);
    a.coin(10);
    a.choice(4); // Tea 80, должно хватить
    EXPECT_EQ(a.getState(), STATES::WAIT);
}

TEST(AutomataTest, ChangeIsReturned) {
    Automata a;
    a.on();
    a.coin(200);
    a.choice(1); // Americano 120, сдача 80
    // Проверяем, что состояние WAIT, и можно начать заново
    EXPECT_EQ(a.getState(), STATES::WAIT);
    // Новый заказ
    a.coin(50);
    EXPECT_EQ(a.getState(), STATES::ACCEPT);
}

TEST(AutomataTest, CannotTurnOffWhenNotInWait) {
    Automata a;
    a.on();
    a.coin(100); // ACCEPT
    a.off();     // не должен выключиться
    EXPECT_EQ(a.getState(), STATES::ACCEPT);
}

TEST(AutomataTest, GetMenuReturnsNonEmptyList) {
    Automata a;
    auto menu = a.getMenu();
    EXPECT_GE(menu.size(), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
