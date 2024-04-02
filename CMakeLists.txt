cmake_minimum_required(VERSION 3.27)

project(hanabi)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(hanabi
        src/lib/cJSON.h
        src/lib/cJSON.c
        src/lib/vec.h
        src/lib/vec.c
        src/lib/lab.h
        src/lib/lab.c
        src/hanabi/interface.h
        src/hanabi/interface.c
        src/hanabi/card.h
        src/hanabi/card.c
        src/hanabi/hand.h
        src/hanabi/hand.c
        src/hanabi/deck.h
        src/hanabi/deck.c
        src/hanabi/bot.h
        src/hanabi/bot.c
        src/hanabi/player.h
        src/hanabi/player.c
        src/hanabi/game.h
        src/hanabi/game.c
        src/main.c
)