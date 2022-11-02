void createMenu() {
    cout << '\n';
    cout << R"(║*****************************************************************************************║)" << '\n';
    cout << R"(║      /\\\\\\\\\          /\\\\\\\                /\\\         /\\\\\\\\\                ║)" << '\n';
    cout << R"(║     /\\\///////\\\      /\\\/////\\\            /\\\\\       /\\\///////\\\             ║)" << '\n';
    cout << R"(║     \///      \//\\\    /\\\    \//\\\         /\\\/\\\      \/\\\     \/\\\            ║)" << '\n';
    cout << R"(║                /\\\/    \/\\\     \/\\\       /\\\/\/\\\      \///\\\\\\\\\/            ║)" << '\n';
    cout << R"(║              /\\\//      \/\\\     \/\\\     /\\\/  \/\\\       /\\\///////\\\          ║)" << '\n';
    cout << R"(║            /\\\//         \/\\\     \/\\\   /\\\\\\\\\\\\\\\\   /\\\      \//\\\        ║)" << '\n';
    cout << R"(║           /\\\/            \//\\\    /\\\   \///////////\\\//   \//\\\      \ \\\       ║)" << '\n';
    cout << R"(║          /\\\\\\\\\\\\\\\   \///\\\\\\\/              \/\\\      \///\\\\\\\\\///       ║)" << '\n';
    cout << R"(║          \///////////////      \///////                \///         \//////////         ║)" << '\n';
    cout << R"(║*****************************************************************************************║)" << '\n';
    cout << R"(                                   New game                                                )" << '\n'; // 35 - 12
    cout << R"(                                   Load saved file                                         )" << '\n'; // 35 - 13
    cout << R"(                                   Quit game                                               )" << '\n'; // 35 - 14


    int current = 1, next = 0;
    vector<string> menuList = { "New game", "Load saved file", "Quit game" };
    while (true) {
        if (current != next) {
            gotoxy(35, 12 + current);
            setColor(15, 0);
            cout << menuList[current];
            if (current == 1) cout << '\t' << R"(                              )";


            gotoxy(35, 12 + next);
            setColor(15, 2);
            cout << menuList[next];
            if (next == 1) cout << '\t' << R"((Saved file is used only once))";

            current = next;
        }

        int event = getch();
        if ((event == 72 || event == 'w') && current != 0) next = current - 1;;
        if ((event == 80 || event == 's') && current != 2) next = current + 1;
        if (event == 13) {
            if (current == 0) {
                setColor(15, 0);
                windowSetting(48, 20, true);

                createGame(false);

                return;
            }

            if (current == 1) {
                if (fopen("Save.txt", "r")) {
                    const string temp = "Save";
                    ifstream inp((temp + ".txt").c_str());

                    int e;
                    if (inp >> e) {
                        inp.close();

                        setColor(15, 0);
                        windowSetting(48, 20, true);

                        createGame(true);

                        return;
                    } else {
                        inp.close();

                        gotoxy(0, 17);
                        setColor(15, 0);
                        cout << "Unsave game";

                        Sleep(100);

                        gotoxy(0, 17);
                        cout << "           ";
                    }
                } else {
                    gotoxy(0, 17);
                    setColor(15, 0);
                    cout << "Save file not found";

                    Sleep(100);

                    gotoxy(0, 17);
                    cout << "                   ";
                }
            }

            if (current == 2) exit(0);
        }
    }
}
