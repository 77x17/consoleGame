void createMenu() {
    cout << '\n';
    cout << R"(  ║*****************************************************************************************║)" << '\n';
    cout << R"(  ║      /\\\\\\\\\          /\\\\\\\                /\\\         /\\\\\\\\\                ║)" << '\n';
    cout << R"(  ║     /\\\///////\\\      /\\\/////\\\            /\\\\\       /\\\///////\\\             ║)" << '\n';
    cout << R"(  ║     \///      \//\\\    /\\\    \//\\\         /\\\/\\\      \/\\\     \/\\\            ║)" << '\n';
    cout << R"(  ║                /\\\/    \/\\\     \/\\\       /\\\/\/\\\      \///\\\\\\\\\/            ║)" << '\n';
    cout << R"(  ║              /\\\//      \/\\\     \/\\\     /\\\/  \/\\\       /\\\///////\\\          ║)" << '\n';
    cout << R"(  ║            /\\\//         \/\\\     \/\\\   /\\\\\\\\\\\\\\\\   /\\\      \//\\\        ║)" << '\n';
    cout << R"(  ║           /\\\/            \//\\\    /\\\   \///////////\\\//   \//\\\      \ \\\       ║)" << '\n';
    cout << R"(  ║          /\\\\\\\\\\\\\\\   \///\\\\\\\/              \/\\\      \///\\\\\\\\\///       ║)" << '\n';
    cout << R"(  ║          \///////////////      \///////                \///         \//////////         ║)" << '\n';
    cout << R"(  ║*****************************************************************************************║)" << '\n';
    cout << R"(                            Press “Enter” to play with the new game                          )" << '\n';
    cout << R"(                         Press “Ctrl + L”  to play with the saved game                       )" << '\n';
    cout << R"(                                    Press “Esc” to quit game                                 )" << '\n';

    while (true) {
        int temp = getch();

        if (temp == 27) exit(0);
        if (temp == 13) {
            windowSetting(47, 20, true);
            createGame(false);
            break;
        }
        if (temp == 12) {
            if (fopen("Save.txt", "r")) {
                freopen("Save.txt", "r", stdin);

                int e;
                if (cin >> e) {
                    fclose(freopen("Save.txt", "r", stdin));

                    windowSetting(47, 20, true);

                    createGame(true);

                    break;
                } else {
                    fclose(freopen("Save.txt", "r", stdin));

                    gotoxy(0, 17);
                    cout << "Unsave game";

                    Sleep(100);

                    gotoxy(0, 17);
                    cout << "           ";
                }
            } else {
                gotoxy(0, 17);
                cout << "Save file not found";

                Sleep(100);

                gotoxy(0, 17);
                cout << "                   ";
            }
        }
    }
}
