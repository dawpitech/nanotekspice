/*
** EPITECH PROJECT, 2025
** nanotekspice
** File description:
** Debug.hpp
*/

#pragma once

#ifdef IS_DEBUG
     #define DEBUG_PRINT(c) std::clog << "\033[0;33m" << c << "\033[0m";
#else
    #define DEBUG_PRINT(c)
#endif
