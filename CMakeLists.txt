cmake_minimum_required(VERSION 3.23)
project(Yann_TP2_chargement_graphe_C C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Yann_TP2_chargement_graphe_C
        fifo.h
        fifo.c
        Graphe.h
        Graphe.c
        Cellule.c
        Cellule.h
        main.c)
