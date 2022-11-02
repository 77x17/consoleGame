#include <conio.h>
#include <windows.h>

void windowSetting(SHORT width, SHORT height, bool disableResize) {
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

void gotoxy(SHORT posX, SHORT posY) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = posX;
    Position.Y = posY;

	SetConsoleCursorPosition(hStdout, Position);
}

void setColor(int backgound_color, int text_color) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    int color_code = backgound_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}

void turnOnSetting() {
    system("color F0");

    SetConsoleOutputCP(65001);
    // Name
    SetConsoleTitle(TEXT("2048"));
    // width - height - disableResize
    windowSetting(92, 20, true);
//    windowSetting(46, 20, true);
    // disableClose - disableMin - disableMax - disableScrollBar - disableCursor
    buttonSetting(false, false, false, false, false);
}
