#include <bits/stdc++.h>
using namespace std;

#include "buildWindow.h"
#include "2048.h"
#include "menu.h"

int main() {
    turnOnSetting();

    createMenu();

    exit(0);

    while (not playerLose) {
        gameLoop();
    }

    system("cls");
    setColor(15, 0);
    gotoxy(0, 0);

    return 0;
}
