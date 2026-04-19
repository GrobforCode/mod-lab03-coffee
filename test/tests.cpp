// Copyright 2026 <Your Name>
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
    a.coin(30);
    a.choice(0);
}

TEST(AutomataTest, ChoiceWithEnoughMoneyGoesToCookAndThenWait) {
    Automata a;
    a.on();
    a.coin(150);
    a.choice(2);  // Latte за 150
    EXPECT_EQ(a.getState(), STATES::WAIT);
}

TEST(AutomataTest, ChoiceWithInsufficientMoneyStaysInAccept) {
    Automata a;
    a.on();
    a.coin(10);
    a.choice(0);  // Espresso 100
    EXPECT_EQ(a.getState(), STATES::ACCEPT);
}

TEST(AutomataTest, MultipleCoinsAccumulate) {
    Automata a;
    a.on();
    a.coin(50);
    a.coin(40);
    a.coin(10);
    a.choice(4);  // Tea 80
    EXPECT_EQ(a.getState(), STATES::WAIT);
}

TEST(AutomataTest, ChangeIsReturned) {
    Automata a;
    a.on();
    a.coin(200);
    a.choice(1);  // Americano 120, сдача 80
    EXPECT_EQ(a.getState(), STATES::WAIT);
    a.coin(50);
    EXPECT_EQ(a.getState(), STATES::ACCEPT);
}

TEST(AutomataTest, CannotTurnOffWhenNotInWait) {
    Automata a;
    a.on();
    a.coin(100);  // ACCEPT
    a.off();
    EXPECT_EQ(a.getState(), STATES::ACCEPT);
}

TEST(AutomataTest, GetMenuReturnsNonEmptyList) {
    Automata a;
    auto menu = a.getMenu();
    EXPECT_GE(menu.size(), 1U);
}
