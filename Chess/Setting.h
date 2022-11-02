#include <windows.h>

namespace Setting {
    void windowSetting(SHORT height, SHORT width, bool disableResize) {
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

        SMALL_RECT WindowSize = { 0, 0, width, height };
        SetConsoleWindowInfo(hStdout, 1, &WindowSize);

        COORD NewSize;
        NewSize.X = width + 1;
        NewSize.Y = height + 1;
        SetConsoleScreenBufferSize(hStdout, NewSize);

        HWND hWnd = GetConsoleWindow();

        if (disableResize) SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
    }

    void buttonSetting(bool disableClose, bool disableMin, bool disableMax, bool disableScrollBar, bool disableCursor) {
        HWND hWnd = GetConsoleWindow();
        HMENU hMenu = GetSystemMenu(hWnd, false);

        if (disableClose) DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
        if (disableMin) DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
        if (disableMax) DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);

        ShowScrollBar(hWnd, SB_BOTH, !disableScrollBar);

        HANDLE hOut;
        CONSOLE_CURSOR_INFO ConCurInf;
        hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        ConCurInf.dwSize = 10;
        ConCurInf.bVisible = !disableCursor;
        SetConsoleCursorInfo(hOut,&ConCurInf);
    }

    void main() {
        system("color B0");

        SetConsoleOutputCP(65001);
        // Name
        SetConsoleTitle(TEXT("Chess"));
        // width - height - disableResize
//        windowSetting(16 + 2, 32 + 2, true);        //Board.txt
        windowSetting(20 + 2, 56 + 2, true);        //Debug

        // disableClose - disableMin - disableMax - disableScrollBar - disableCursor
        buttonSetting(false, true, true, true, true);
    }
}
