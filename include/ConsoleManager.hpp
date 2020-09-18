//Author: RK-Coding
//Description: Makes ansi escape codes work on Windows and Mac
//Based-On: "https://solarianprogrammer.com/2019/04/08/c-programming-ansi-escape-codes-windows-macos-linux-terminals/"

#pragma once
 
namespace VPP
{
    void setupConsole();
    void restoreConsole();
}