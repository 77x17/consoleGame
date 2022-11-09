namespace chessRules {
    void Pawn() {
        if ('A' <= board[target.x][target.y] && board[target.x][target.y] <= 'Z') {
            if ('a' <= board[target.x + 1][target.y - 1] && board[target.x + 1][target.y - 1] <= 'z') validMoves.emplace(target.x + 1, target.y - 1);
            if ('a' <= board[target.x + 1][target.y + 1] && board[target.x + 1][target.y + 1] <= 'z') validMoves.emplace(target.x + 1, target.y + 1);

            if (board[target.x + 1][target.y] == ' ') {
                validMoves.emplace(target.x + 1, target.y);
                if (target.x == 2 && board[target.x + 2][target.y] == ' ') validMoves.emplace(target.x + 2, target.y);
            }

            if (enPassant == std::make_pair(target.x, target.y - 1)) {
                if ('a' <= board[target.x][target.y - 1] && board[target.x][target.y - 1] <= 'z') validMoves.emplace(target.x + 1, target.y - 1);
            }
            if (enPassant == std::make_pair(target.x, target.y + 1)) {
                if ('a' <= board[target.x][target.y + 1] && board[target.x][target.y + 1] <= 'z') validMoves.emplace(target.x + 1, target.y + 1);
            }
        } else {
            if ('A' <= board[target.x - 1][target.y - 1] && board[target.x - 1][target.y - 1] <= 'Z') validMoves.emplace(target.x - 1, target.y - 1);
            if ('A' <= board[target.x - 1][target.y + 1] && board[target.x - 1][target.y + 1] <= 'Z') validMoves.emplace(target.x - 1, target.y + 1);

            if (board[target.x - 1][target.y] == ' ') {
                validMoves.emplace(target.x - 1, target.y);
                if (target.x == 7 && board[target.x - 2][target.y] == ' ') validMoves.emplace(target.x - 2, target.y);
            }

            if (enPassant == std::make_pair(target.x, target.y - 1)) {
                if ('A' <= board[target.x][target.y - 1] && board[target.x][target.y - 1] <= 'Z') validMoves.emplace(target.x - 1, target.y - 1);
            }
            if (enPassant == std::make_pair(target.x, target.y + 1)) {
                if ('A' <= board[target.x][target.y + 1] && board[target.x][target.y + 1] <= 'Z') validMoves.emplace(target.x - 1, target.y + 1);
            }
        }
    }

    void Bishop() {
        const int dx[] = {-1, 1, -1, 1};
        const int dy[] = {-1, 1, 1, -1};

        for (int i = 0; i <= 3; i++) {
            point temp = target;
            while (board[temp.x += dx[i]][temp.y += dy[i]] == ' ') validMoves.insert(temp);

            if ('a' <= board[target.x][target.y] && board[target.x][target.y] <= 'z') {
                if ('A' <= board[temp.x][temp.y] && board[temp.x][temp.y] <= 'Z') validMoves.insert(temp);
            } else {
                if ('a' <= board[temp.x][temp.y] && board[temp.x][temp.y] <= 'z') validMoves.insert(temp);
            }
        }
    }

    void Knight() {
        const int dx[] = {-1, -2, -2, -1, 1, 2, 2, 1};
        const int dy[] = {-2, -1, 1, 2, 2, 1, -1, -2};

        for (int i = 0; i <= 7; i++) if (1 <= target.x + dx[i] && target.x + dx[i] <= 8 && 1 <= target.y + dy[i] && target.y + dy[i] <= 8) { 
            point temp = target; 

            if (board[temp.x += dx[i]][temp.y += dy[i]] == ' ') validMoves.insert(temp);
            else if ('a' <= board[target.x][target.y] && board[target.x][target.y] <= 'z') {
                if ('A' <= board[temp.x][temp.y] && board[temp.x][temp.y] <= 'Z') validMoves.insert(temp);
            } else {
                if ('a' <= board[temp.x][temp.y] && board[temp.x][temp.y] <= 'z') validMoves.insert(temp);
            }
        }
    }

    void Rook() {
        const int dx[] = {-1, 1, 0, 0};
        const int dy[] = {0, 0, -1, 1};

        for (int i = 0; i <= 3; i++) {
            point temp = target;
            while (board[temp.x += dx[i]][temp.y += dy[i]] == ' ') validMoves.insert(temp);

            if ('a' <= board[target.x][target.y] && board[target.x][target.y] <= 'z') {
                if ('A' <= board[temp.x][temp.y] && board[temp.x][temp.y] <= 'Z') validMoves.insert(temp);
            } else {
                if ('a' <= board[temp.x][temp.y] && board[temp.x][temp.y] <= 'z') validMoves.insert(temp);
            }
        }
    }

    void Queen() {
        const int dx[] = {-1, 1, -1, 1, -1, 1, 0, 0};
        const int dy[] = {-1, 1, 1, -1, 0, 0, -1, 1};

        for (int i = 0; i <= 7; i++) {
            point temp = target;
            while (board[temp.x += dx[i]][temp.y += dy[i]] == ' ') validMoves.insert(temp);

            if ('a' <= board[target.x][target.y] && board[target.x][target.y] <= 'z') {
                if ('A' <= board[temp.x][temp.y] && board[temp.x][temp.y] <= 'Z') validMoves.insert(temp);
            } else {
                if ('a' <= board[temp.x][temp.y] && board[temp.x][temp.y] <= 'z') validMoves.insert(temp);
            }
        }
    }

    void King() {
        const int dx[] = {-1, 1, -1, 1, -1, 1, 0, 0,  0, 0};
        const int dy[] = {-1, 1, 1, -1, 0, 0, -1, 1, -1, 1};

        for (int i = 0; i <= 7; i++) {
            point temp = target;
            if (board[temp.x += dx[i]][temp.y += dy[i]] == ' ') validMoves.insert(temp);

            if ('a' <= board[target.x][target.y] && board[target.x][target.y] <= 'z') {
                if ('A' <= board[temp.x][temp.y] && board[temp.x][temp.y] <= 'Z') validMoves.insert(temp);
            } else {
                if ('a' <= board[temp.x][temp.y] && board[temp.x][temp.y] <= 'z') validMoves.insert(temp);
            }
        }
        
        for (int i = 8; i <= 9; i++) {
            point temp = target;
            while (board[temp.x += dx[i]][temp.y += dy[i]] == ' ');

            if (castling[0] && 'a' <= board[target.x][target.y] && board[target.x][target.y] <= 'z') {
                if (board[temp.x][temp.y] && board[temp.x][temp.y] == 'r') {
                    temp = target;
                    while (board[temp.x += dx[i]][temp.y += dy[i]] == ' ') validMoves.insert(temp);
                }
            }
            if (castling[1] && 'A' <= board[target.x][target.y] && board[target.x][target.y] <= 'Z') {
                if (board[temp.x][temp.y] && board[temp.x][temp.y] == 'R') {
                    temp = target;
                    while (board[temp.x += dx[i]][temp.y += dy[i]] == ' ') validMoves.insert(temp);
                }
            }
        }
    }
}
