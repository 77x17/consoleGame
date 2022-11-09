#include <conio.h>
#include <fstream>
#include <string>
#include <utility>
#include <set>

#define point std::pair<int, int>
#define x first
#define y second

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

int status[][10] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, 0},
        {0, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, BRIGHTWHITE, BRIGHTWHITE, BRIGHTWHITE, BRIGHTWHITE, BRIGHTWHITE, BRIGHTWHITE, BRIGHTWHITE, BRIGHTWHITE, 0},
        {0, BRIGHTWHITE, BRIGHTWHITE, BRIGHTWHITE, BRIGHTWHITE, BRIGHTWHITE, BRIGHTWHITE, BRIGHTWHITE, BRIGHTWHITE, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

int winner;
bool pickup, whiteMove, castling[2];
point pointer, target, enPassant;

std::set<point> validMoves;

#include "chessRules.h"

namespace Chess {
    void drawBoard() {
        std::ifstream file((const std::string)"Board.txt");

        std::string s;
        while (getline(file, s)) std::cout << s << '\n';

        file.close();

        for (int i = 1; i <= 8; i++) for (int j = 1; j <= 8; j++) {
            gotoxy(i, j), color(status[i][j]);
            std::cout << ' ' << board[i][j] << ' ';
        }

        gotoXY(16, 54), color(BRIGHTWHITE);
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

    bool aValidMove() {
        return validMoves.find(pointer) != validMoves.end();
    }

    void findValidMove() {
        switch (board[target.x][target.y]) {
            case 'p': case 'P': chessRules::Pawn();     break;
            case 'b': case 'B': chessRules::Bishop();   break;
            case 'n': case 'N': chessRules::Knight();   break;
            case 'r': case 'R': chessRules::Rook();     break;
            case 'q': case 'Q': chessRules::Queen();    break;
            case 'k': case 'K': chessRules::King();     break;
            default:;
        }

        for (auto A : validMoves) {
            if (board[A.x][A.y] == ' ') {
                board[A.x][A.y] = 'x', status[A.x][A.y] = GREEN;
            } else if (board[A.x][A.y] != 'x') status[A.x][A.y] = RED;

            gotoxy(A.x, A.y), color(status[A.x][A.y]), std::cout << ' ' << board[A.x][A.y] << ' ';
        }
    }

    void main() {
        drawBoard();

        winner = 0;
        pickup = false, whiteMove = true, castling[0] = castling[1] = true;
        pointer = std::make_pair(1, 1), enPassant = std::make_pair(0, 0);

        while (winner == false) {
            gotoxy(pointer.x, pointer.y);
            color(whiteMove ? BRIGHTWHITE : BLACK); std::cout << '[';
            color(status[pointer.x][pointer.y]);    std::cout << board[pointer.x][pointer.y];
            color(whiteMove ? BRIGHTWHITE : BLACK); std::cout << ']';

            int event = getEvent();
            if (event <= 3) {
                const int dx[] = {-1, 1, 0, 0};
                const int dy[] = {0, 0, -1, 1};
                
                if (board[pointer.x + dx[event]][pointer.y + dy[event]] != '#') {
                    gotoxy(pointer.x, pointer.y), color(status[pointer.x][pointer.y]);
                    std::cout << ' ' << board[pointer.x][pointer.y] << ' ';

                    pointer = std::make_pair(pointer.x + dx[event], pointer.y + dy[event]);
                }
            } else if (event == 4) {
                if (pickup == false) {
                    if (board[pointer.x][pointer.y] == ' ') continue;

                    if ((status[pointer.x][pointer.y] == BRIGHTWHITE && whiteMove == false) || (status[pointer.x][pointer.y] == BLACK && whiteMove)) continue;

                    pickup = true; target = pointer;
                    gotoxy(pointer.x, pointer.y), color(status[pointer.x][pointer.y] = GREEN);
                    std::cout << ' ' << board[pointer.x][pointer.y] << ' ';

                    findValidMove();
                } else {
                    if (target == pointer) {
                        pickup = false;

                        status[target.x][target.y] = (board[target.x][target.y] <= 'Z' ? BLACK : BRIGHTWHITE);

                        for (auto A : validMoves) {
                            if (board[A.x][A.y] == 'x') {
                                board[A.x][A.y] = ' ';
                                status[A.x][A.y] = 0;
                            } else if (board[A.x][A.y] != ' ') {
                                status[A.x][A.y] = (board[A.x][A.y] <= 'Z' ? BLACK : BRIGHTWHITE);
                            }

                            gotoxy(A.x, A.y), color(status[A.x][A.y]), std::cout << ' ' << board[A.x][A.y] << ' ';
                        }

                        validMoves.clear();
                    } else {
                        if (aValidMove() == false) continue;

                        for (auto A : validMoves) {
                            if (board[A.x][A.y] == 'x') {
                                board[A.x][A.y] = ' ';
                                status[A.x][A.y] = 0;
                            } else if (board[A.x][A.y] != ' ') {
                                status[A.x][A.y] = (board[A.x][A.y] <= 'Z' ? BLACK : BRIGHTWHITE);
                            }

                            gotoxy(A.x, A.y), color(status[A.x][A.y]), std::cout << ' ' << board[A.x][A.y] << ' ';
                        }

                        validMoves.clear();

                        pickup = false; whiteMove = whiteMove ^ 1;
                        gotoxy(target.x, target.y), color(0);   
                        std::cout << "   ";

                        if (board[pointer.x][pointer.y] == 'K') winner = 1;
                        if (board[pointer.x][pointer.y] == 'k') winner = 2;

                        if (whiteMove && pointer.x == enPassant.x + 1 && pointer.y == enPassant.y) {
                            gotoxy(enPassant.x, enPassant.y), color(BLACK);
                            board[enPassant.x][enPassant.y] = ' ';
                            std::cout << "   ";
                        } 

                        if (whiteMove == false && pointer.x == enPassant.x - 1 && pointer.y == enPassant.y) {
                            gotoxy(enPassant.x, enPassant.y), color(BLACK);
                            board[enPassant.x][enPassant.y] = ' ';
                            std::cout << "   ";
                        }

                        if (board[target.x][target.y] == 'p' || board[target.x][target.y] == 'P') {
                            if (pointer.x == 1) board[target.x][target.y] = 'q';
                            if (pointer.x == 8) board[target.x][target.y] = 'Q';
                        }

                        if (board[target.x][target.y] == 'p' || board[target.x][target.y] == 'P') enPassant = pointer;
                        else enPassant = std::make_pair(0, 0);

                        if ((castling[0] && board[target.x][target.y] == 'k') || (castling[1] && board[target.x][target.y] == 'K')) {
                            if (target.y - pointer.y >= 2) {
                                status[target.x][pointer.y + 1] = status[target.x][1];
                                board[target.x][pointer.y + 1] = board[target.x][1]; board[target.x][1] = ' ';
                                gotoxy(target.x, pointer.y + 1), color(status[target.x][1]);
                                std::cout << ' ' << board[target.x][1] << ' ';
                                gotoxy(target.x, 1); std::cout << "   ";
                            }

                            if (pointer.y - target.y >= 2) {
                                status[target.x][pointer.y - 1] = status[target.x][8];
                                board[target.x][pointer.y - 1] = board[target.x][8]; board[target.x][8] = ' ';
                                gotoxy(target.x, pointer.y - 1), color(status[target.x][8]);
                                std::cout << ' ' << board[target.x][pointer.y - 1] << ' ';
                                gotoxy(target.x, 8); std::cout << "   ";
                            }
                        }

                        if (board[target.x][target.y] == 'k' || board[target.x][target.y] == 'r') castling[0] = false;
                        if (board[target.x][target.y] == 'K' || board[target.x][target.y] == 'R') castling[1] = false;
                        
                        status[pointer.x][pointer.y] = (board[target.x][target.y] <= 'Z' ? BLACK : BRIGHTWHITE);
                        board[pointer.x][pointer.y] = board[target.x][target.y];
                        board[target.x][target.y] = ' ';
                    }
                }
            } else if (event == 5) {
                // will show menu;
                exit(0);
            }
        }

        gotoxy(pointer.x, pointer.y);
        color(whiteMove ? BRIGHTWHITE : BLACK); std::cout << '[';
        color(status[pointer.x][pointer.y]);    std::cout << board[pointer.x][pointer.y];
        color(whiteMove ? BRIGHTWHITE : BLACK); std::cout << ']';

        gotoxy(9, 1), color(BLACK);
        std::cout << (winner == 1 ? "White's" : "Black's") << " is winner!!!\tPress any key to exit.\n";
        getch();
    }
}
