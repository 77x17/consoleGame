#include <conio.h>
#include <fstream>
#include <cstring>
#include <utility>

#define point std::pair<int, int>
#define x first
#define y second

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

namespace Chess {
    std::string board[] = {
       "##########",
       "#RNBQKBNR#",
       "#PPPPPPPP#",
       "#        #",
       "#        #",
       "#        #",
       "#        #",
       "#pppppppp#",
       "#rnbqkbnr#",
       "##########"};

    void drawBoard() {
        std::ifstream file((const std::string)"Board.txt");

        std::string s;
        while (getline(file, s)) std::cout << s << '\n';

        file.close();

        for (int i = 1; i <= 8; i++) for (int j = 1; j <= 8; j++) {
            gotoxy(i, j), color(board[i][j] >= 'a' ? BRIGHTWHITE : BLACK);
            std::cout << ' ' << board[i][j] << ' ';
        }

        gotoxy(7, 10), color(BRIGHTWHITE);
        std::cout << "[ ]";
    }

    int getEvent() {
        while (true) {
            char event; event = getch();

            switch (event) {
                case 72: case 'w': return 0;
                case 80: case 's': return 1;
                case 75: case 'a': return 2;
                case 77: case 'd': return 3;
                case 13:           return 4;  //Enter
                case 27:           return 5;  //Esc
                default: break;
            }
        }
    }

    int winner;
    bool pickup, whiteMove;
    point pre_pointer, pointer, target;

    bool aValidMove() {
        if (pointer == target) return false;
        if (board[pointer.x][pointer.y] != ' ' && board[target.x][target.y] != ' ') {
            if (board[pointer.x][pointer.y] >= 'a' && board[target.x][target.y] >= 'a') return false;
            if (board[pointer.x][pointer.y] <  'a' && board[target.x][target.y] <  'a') return false;
        }

        return true;
    }

    void main() {
        drawBoard();

        winner = 0;
        pickup = false, whiteMove = true;
        pointer = std::make_pair(1, 1);

        while (not winner) {
            gotoxy(pointer.x, pointer.y);
            color(whiteMove ? BRIGHTWHITE : BLACK); std::cout << '[';
            color(pickup && pointer == target ? GREEN : board[pointer.x][pointer.y] >= 'a' ? BRIGHTWHITE : BLACK); std::cout << board[pointer.x][pointer.y];
            color(whiteMove ? BRIGHTWHITE : BLACK); std::cout << ']';

            int event = getEvent(); switch (event) {
                case 0 ... 3: {
                    if (board[pointer.x + dx[event]][pointer.y + dy[event]] != '#') {
                        pre_pointer = pointer;
                        pointer = std::make_pair(pointer.x + dx[event], pointer.y + dy[event]);

                        gotoxy(pre_pointer.x, pre_pointer.y), color(pickup && pre_pointer == target ? GREEN : board[pre_pointer.x][pre_pointer.y] >= 'a' ? BRIGHTWHITE : BLACK);
                        std::cout << ' ' << board[pre_pointer.x][pre_pointer.y] << ' ';
                    }

                    break;
                }
                case 4: {
                    if (not pickup) {
                        if (board[pointer.x][pointer.y] == ' ') break;

                        if ((board[pointer.x][pointer.y] >= 'a' && whiteMove == false) or (board[pointer.x][pointer.y] < 'a' && whiteMove)) break;

                        pickup = true; target = pointer;
                        gotoxy(pointer.x, pointer.y), color(GREEN);
                        std::cout << ' ' << board[pointer.x][pointer.y] << ' ';
                    } else {
                        if (target == pointer) pickup = false;

                        if (not aValidMove()) break;

                        pickup = false; whiteMove = whiteMove ^ 1;
                        gotoxy(target.x, target.y), color(NULL);
                        std::cout << "   ";

                        if (board[pointer.x][pointer.y] == 'K') winner = 1;
                        if (board[pointer.x][pointer.y] == 'k') winner = 2;

                        board[pointer.x][pointer.y] = board[target.x][target.y];
                        board[target.x][target.y] = ' ';
                    }

                    break;
                }

                default: break;
            }
        }

        gotoxy(9, 1), color(BLACK);
        std::cout << (winner == 1 ? "White's" : "Black's") << " is winner!!!\tPress any key to exit.\n";
        char stop; stop = getch();
    }
}
