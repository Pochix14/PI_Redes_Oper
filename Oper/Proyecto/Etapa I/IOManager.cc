#include <iostream>

#include "IOManager.h"

IOManager::IOManager() {}

IOManager::~IOManager() {}

void IOManager::WinnerMsg(int winnerId) {
    std::cout << "The Winner is: Player # " << winnerId << std::endl;
}

void IOManager::CurrentPlayer( int playerId) {
    std::cout << "Current player is: " << playerId << std::endl;
}

void IOManager::PotatoExplote( int playerId) {
    std::cout << "The potato exploded!! \nPlayer # " << playerId << " eliminated!" << std::endl;
    std::cout << std::endl;
}

void IOManager::PotatoValue(int potatoValue) {
    std::cout << "The potato value is: " << potatoValue << std::endl;
    std::cout << std::endl;
}

