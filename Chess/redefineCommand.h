void gotoXY(SHORT posY, SHORT posX) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = posX;
    Position.Y = posY;

    SetConsoleCursorPosition(hStdout, Position);
}

void gotoxy(int x, int y) {gotoXY(2 * x + 1, 4 * y);}

void setColor(int backgound_color, int text_color) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    int color_code = backgound_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}

void color(int text_color) {setColor(LIGHTAQUA, text_color);}
