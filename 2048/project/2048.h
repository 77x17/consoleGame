#define Random(x) rand() % x + 1

const int dx[] = { 0, 1 };
const int dy[] = { 1, 0 };
const string table[9][9] = { { "╔", "═══════", "╤", "═══════", "╤", "═══════", "╤", "═══════", "╗" },
                             { "║", " x     ", "│", " x     ", "│", " x     ", "│", " x     ", "║" },
                             { "╟", "───────", "┼", "───────", "┼", "───────", "┼", "───────", "╢" },
                             { "║", " x     ", "│", " x     ", "│", " x     ", "│", " x     ", "║" },
                             { "╟", "───────", "┼", "───────", "┼", "───────", "┼", "───────", "╢" },
                             { "║", " x     ", "│", " x     ", "│", " x     ", "│", " x     ", "║" },
                             { "╟", "───────", "┼", "───────", "┼", "───────", "┼", "───────", "╢" },
                             { "║", " x     ", "│", " x     ", "│", " x     ", "│", " x     ", "║" },
                             { "╚", "═══════", "╧", "═══════", "╧", "═══════", "╧", "═══════", "╝" } };

int arr[4 + 2][4 + 2];
int point = 0, nMove = 0;
bool rightMove = false, playerLose = false, pointInc = false;

int Input() {
    char event; event = getch();
    if (event == 72 || event == 'w') return 0;
    if (event == 80 || event == 's') return 1;
    if (event == 75 || event == 'a') return 2;
    if (event == 77 || event == 'd') return 3;
    if (event == 27) return 4;                  // Esc

    return 5;
}

void Output(int x, int y, int u, int v) {
    setColor(15, 0 + (log(arr[x][y]) / log(2)));
    gotoxy(10 + (y - 1) * 8, 6 + (x - 1) * 2);
    cout << arr[x][y];
    gotoxy(10 + (v - 1) * 8, 6 + (u - 1) * 2);
    cout << "     ";
}

void Up() {
    for (int j = 1, k = 0; j <= 4; j++, k = 0) for (int i = 1; i <= 4; i++) {
        if (arr[i - 1][j] == 0 && arr[i][j]) {
            rightMove = true;

            int x = i; while (arr[x - 1][j] == 0) x--;

            swap(arr[x][j], arr[i][j]);

            if (arr[x - 1][j] == arr[x][j] && x - 1 > k) {
                k = x - 1;
                point += arr[x - 1][j] + arr[x][j], pointInc = true;
                arr[x - 1][j] += arr[x][j], arr[x][j] = 0;

                Output(x - 1, j, i, j);
            } else Output(x, j, i, j);
        }

        if (arr[i - 1][j] == arr[i][j] && arr[i][j] && i - 1 > k) {
            rightMove = true;

            k = i - 1;
            point += arr[i - 1][j] + arr[i][j], pointInc = true;
            arr[i - 1][j] += arr[i][j]; arr[i][j] = 0;

            if (arr[i - 1][j] == 0) {
                int x = i; while (arr[x - 1][j] == 0) x--;

                swap(arr[x][j], arr[i][j]);

                Output(x, j, i, j);
            } else Output(i - 1, j, i, j);
        }
    }
}

void Down() {
    for (int j = 1, k = 5; j <= 4; j++, k = 5) for (int i = 4; i >= 1; i--) {
        if (arr[i + 1][j] == 0 && arr[i][j]) {
            rightMove = true;

            int x = i; while (arr[x + 1][j] == 0) x++;

            swap(arr[x][j], arr[i][j]);

            if (arr[x + 1][j] == arr[x][j] && x + 1 < k) {
                k = x + 1;
                point += arr[x + 1][j] + arr[x][j], pointInc = true;
                arr[x + 1][j] += arr[x][j], arr[x][j] = 0;

                Output(x + 1, j, i, j);
            } else Output(x, j, i, j);
        }

        if (arr[i + 1][j] == arr[i][j] && arr[i][j] && i + 1 < k) {
            rightMove = true;

            k = i + 1;
            point += arr[i + 1][j] + arr[i][j], pointInc = true;
            arr[i + 1][j] += arr[i][j]; arr[i][j] = 0;

            if (arr[i + 1][j] == 0) {
                int x = i; while (arr[x + 1][j] == 0) x++;

                swap(arr[x][j], arr[i][j]);

                Output(x, j, i, j);
            } else Output(i + 1, j, i, j);
        }
    }
}

void Left() {
    for (int i = 1, k = 0; i <= 4; i++, k = 0) for (int j = 1; j <= 4; j++) {
        if (arr[i][j - 1] == 0 && arr[i][j]) {
            rightMove = true;

            int x = j; while (arr[i][x - 1] == 0) x--;

            swap(arr[i][x], arr[i][j]);

            if (arr[i][x - 1] == arr[i][x] && x - 1 > k) {
                k = x - 1;
                point += arr[i][x - 1] + arr[i][x], pointInc = true;
                arr[i][x - 1] += arr[i][x], arr[i][x] = 0;

                Output(i, x - 1, i, j);
            } else Output(i, x, i, j);
        }

        if (arr[i][j - 1] == arr[i][j] && arr[i][j] && j - 1 > k) {
            rightMove = true;

            k = j - 1;
            point += arr[i][j - 1] + arr[i][j], pointInc = true;
            arr[i][j - 1] += arr[i][j]; arr[i][j] = 0;

            if (arr[i][j - 1] == 0) {
                int x = i; while (arr[i][x - 1] == 0) x--;

                swap(arr[i][x], arr[i][j]);

                Output(i, x, i, j);
            } else Output(i, j - 1, i, j);
        }
    }
}

void Right() {
    for (int i = 1, k = 5; i <= 4; i++, k = 5) for (int j = 4; j >= 1; j--) {
        if (arr[i][j + 1] == 0 && arr[i][j]) {
            rightMove = true;

            int x = j; while (arr[i][x + 1] == 0) x++;

            swap(arr[i][x], arr[i][j]);

            if (arr[i][x + 1] == arr[i][x] && x + 1 < k) {
                k = x + 1;
                point += arr[i][x + 1] + arr[i][x], pointInc = true;
                arr[i][x + 1] += arr[i][x], arr[i][x] = 0;

                Output(i, x + 1, i, j);
            } else Output(i, x, i, j);
        }

        if (arr[i][j + 1] == arr[i][j] && arr[i][j] && j + 1 < k) {
            rightMove = true;

            k = j + 1;
            point += arr[i][j + 1] + arr[i][j], pointInc = true;
            arr[i][j + 1] += arr[i][j]; arr[i][j] = 0;

            if (arr[i][j + 1] == 0) {
                int x = i; while (arr[i][x + 1] == 0) x++;

                swap(arr[i][x], arr[i][j]);

                Output(i, x, i, j);
            } else Output(i, j + 1, i, j);
        }
    }
}

void createGame(bool loadSave) {
    srand(time(NULL));

    setColor(15, 0);

    memset(arr, 0, sizeof arr);

    for (int x = 0; x <= 5; x++) {
        arr[x][0] = arr[x][5] = -1;
        arr[0][x] = arr[5][x] = -1;
    }

    if (loadSave) {
        const string temp = "Save";
        ifstream inp((temp + ".txt").c_str());

        for (int i = 1; i <= 4; i++) for (int j = 1; j <= 4; j++) inp >> arr[i][j];
        inp >> point >> nMove;

        inp.close();

        const string e = "Save";
        ofstream out((e + ".txt").c_str());

        out << "";

        out.close();
    } else {
        point = nMove = 0;

        int x[2], y[2];

        x[0] = x[1] = Random(4); y[0] = y[1] = Random(4);

        while (x[0] == x[1] && y[0] == y[1])
            x[1] = Random(4), y[1] = Random(4);

        arr[ x[0] ][ y[0] ] = (Random(10) <= 9 ? 2 : 4);
        arr[ x[1] ][ y[1] ] = (Random(10) <= 9 ? 2 : 4);
    }
    /*----------------------------------------------------------------*/
    system("cls");

    cout << "\n\n";
    cout << "\n\tPoint: " << point << "\t\tMove: " << nMove << "\n\n";

    for (int i = 0; i <= 8; i++) {
        cout << '\t';

        for (int j = 0; j <= 8; j++) {
            if (table[i][j] == " x     ") {
                int x = (i + 1) / 2, y = (j + 1) / 2;

                if (arr[x][y] == 0) cout << '\t';
                else {
                    setColor(15, 0 + (log(arr[x][y]) / log(2)));
                    cout << ' ' << arr[x][y] << '\t';
                    setColor(15, 0);
                }
            } else cout << table[i][j];
        }

        cout << '\n';
    }

    cout << '\n' << '\t' << R"(Press "Esc" to resume)" << '\n';
}

void Add() {
    int cnt = 0;
    pair<int, int> order[4 * 4 + 1];
    for (int i = 1; i <= 4; i++) for (int j = 1; j <= 4; j++)
        if (arr[i][j] == 0) order[++cnt] = { i, j };

    if (cnt == 0) playerLose = true;
    else {
        int e = Random(cnt), x = order[e].first, y = order[e].second;

        arr[x][y] = (Random(10) <= 9 ? 2 : 4);

        setColor(15, 0 + (log(arr[x][y]) / log(2)));
        gotoxy(10 + (y - 1) * 8, 6 + (x - 1) * 2);
        cout << arr[x][y];
    }
}

void Checker() {
    for (int i = 1; i <= 4; i++) for (int j = 1; j <= 4; j++) for (int x = 0; x <= 1; x++)
        if (arr[i][j] == arr[i + dx[x]][j + dy[x]] || arr[i][j] == 0) return;

    playerLose = true;
}

void Save() {
    const string e = "Save";
    ofstream out((e + ".txt").c_str());

    for (int i = 1; i <= 4; i++) for (int j = 1; j <= 4; j++) out << arr[i][j] << ' ';
    out << point << ' ' << nMove;

    out.close();
}

void gameLoop() {
    switch (Input()) {
        case 0: { Up(); break; }
        case 1: { Down(); break; }
        case 2: { Left(); break; }
        case 3: { Right(); break; }
        case 4: {
            gotoxy(0, 15);
            setColor(15, 0);
            cout << "\tResume               \n";
            cout << "\tNew game\n";
            cout << "\tSave game\n";
            cout << "\tQuit game\n";

            int current = 1, next = 0;
            vector<string> menuList = { "Resume", "New game", "Save game", "Quit game" };
            while (true) {
                if (current != next) {
                    gotoxy(8, 15 + current);
                    setColor(15, 0);
                    cout << menuList[current];

                    gotoxy(8, 15 + next);
                    setColor(15, 2);
                    cout << menuList[next];

                    current = next;
                }

                int event = getch();
                if ((event == 72 || event == 'w') && current != 0) next = current - 1;;
                if ((event == 80 || event == 's') && current != 3) next = current + 1;
                if (event == 13) {
                    if (current == 0) {
                        gotoxy(0, 15);
                        setColor(15, 0);

                        cout << '\t' << R"(Press "Esc" to resume)" << '\n';
                        cout << "\t                  \n";
                        cout << "\t                  \n";
                        cout << "\t                  \n";

                        break;
                    }

                    if (current == 1) {
                        createGame(false);

                        break;
                    }

                    if (current == 2) {
                        Save();

                        gotoxy(0, 15);
                        setColor(15, 0);

                        cout << '\t' << R"(Press "Esc" to resume)" << '\n';
                        cout << "\t                  \n";
                        cout << "\t                  \n";
                        cout << "\t                  \n";
                        break;
                    }

                    if (current == 3) exit(0);
                }
            }
        }
        default: break;
    }

    if (rightMove) {
        nMove++;

        setColor(15, 0);
        if (pointInc) gotoxy(15, 3), pointInc = false, cout << point;
        gotoxy(38, 3), cout << nMove;

        rightMove = false;

        Add();
    }

    Checker();

    if (playerLose == true) {
        playerLose = false;

        setColor(15, 0);
        gotoxy(0, 0);

        cout << '\n';
        cout << "\tYour lose!!!\n";

        gotoxy(0, 15);
        cout << "\tWanna play again?    \n";
        cout << "\tYes\n";
        cout << "\tNo\n";

        int current = 1, next = 0;
        vector<string> yesNo = { "Yes", "No" };
        while (true) {
            if (current != next) {
                gotoxy(8, 16 + current);
                setColor(15, 0);
                cout << yesNo[current];

                gotoxy(8, 16 + next);
                setColor(15, 2);
                cout << yesNo[next];

                current = next;
            }

            int event = getch();
            if ((event == 72 || event == 'w') && current != 0) next = current - 1;;
            if ((event == 80 || event == 's') && current != 1) next = current + 1;
            if (event == 13) {
                if (current == 0) {
                    createGame(false);

                    break;
                }

                if (current == 1) exit(0);
            }
        }
    }
}
