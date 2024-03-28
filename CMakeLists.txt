cmake_minimum_required(VERSION 3.28)

project(hanabi)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(hanabi
        src/lab.h
        src/lab.c
        src/interface.h
        src/interface.c
        src/card.h
        src/card.c
        src/hand.h
        src/hand.c
        src/deck.h
        src/deck.c
        src/bot.h
        src/bot.c
        src/player.h
        src/player.c
        src/game.h
        src/game.c
        main.c
)