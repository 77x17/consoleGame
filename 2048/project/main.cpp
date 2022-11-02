#include <bits/stdc++.h>
using namespace std;

#include "buildWindow.h"
#include "2048.h"
#include "menu.h"

int main() {
    turnOnSetting();

    createMenu();

    while (not playerLose) gameLoop();

    return 0;
}
