//Author: RK-Coding
//Description: Makes ansi escape codes work on Windows and Mac
//Based-On: "https://solarianprogrammer.com/2019/04/08/c-programming-ansi-escape-codes-windows-macos-linux-terminals/"


#include "ConsoleManager.hpp"

#ifdef _WIN32
#define  _CRT_SECURE_NO_WARNINGS 1
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
// Some old MinGW/CYGWIN distributions don't define this:
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
#endif

namespace VPP
{
    static HANDLE stdoutHandle, stdinHandle;
    static DWORD outModeInit, inModeInit;

    void setupConsole() {
        DWORD outMode = 0, inMode = 0;
        stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        stdinHandle = GetStdHandle(STD_INPUT_HANDLE);

        if(stdoutHandle == INVALID_HANDLE_VALUE || stdinHandle == INVALID_HANDLE_VALUE) {
            exit(GetLastError());
        }
        
        if(!GetConsoleMode(stdoutHandle, &outMode) || !GetConsoleMode(stdinHandle, &inMode)) {
            exit(GetLastError());
        }

        outModeInit = outMode;
        inModeInit = inMode;
        
        // Enable ANSI escape codes
        outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

        // Set stdin as no echo and unbuffered
        inMode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);

        if(!SetConsoleMode(stdoutHandle, outMode) || !SetConsoleMode(stdinHandle, inMode)) {
            exit(GetLastError());
        }    
    }

    void restoreConsole(void) {
        // Reset colors
        printf("\x1b[0m");    
        
        // Reset console mode
        if(!SetConsoleMode(stdoutHandle, outModeInit) || !SetConsoleMode(stdinHandle, inModeInit)) {
            exit(GetLastError());
        }
    }
    #else

    static struct termios orig_term;
    static struct termios new_term;

    void setupConsole() {
        tcgetattr(STDIN_FILENO, &orig_term);
        new_term = orig_term;

        new_term.c_lflag &= ~(ICANON | ECHO);

        tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
    }

    void restoreConsole() {
        // Reset colors
        printf("\x1b[0m");

        // Reset console mode
        tcsetattr(STDIN_FILENO, TCSANOW, &orig_term);
    }
    #endif
}