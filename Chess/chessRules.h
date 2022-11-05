namespace chessRules {
    bool isEnemy(point a, point b) {
        if (board[a.x][a.y] == ' ' || board[b.x][b.y] == ' ') return false;

        if (board[a.x][a.y] >= 'a' && board[b.x][b.y] <  'a') return true;
        if (board[a.x][a.y] <  'a' && board[b.x][b.y] >= 'a') return true;

        return false;
    }

    bool Pawn(bool whiteMove) {
        if (whiteMove) {
            if (target.y == pointer.y) {
                if (target.x == 7) if (pointer.x == 6 || pointer.x == 5) return true;
                if (target.x != 7) if (pointer.x == target.x - 1) return true;
            } else if (target.x - 1 == pointer.x) {
                if (target.y - 1 == pointer.y && isEnemy(target, pointer)) return true;
                if (target.y + 1 == pointer.y && isEnemy(target, pointer)) return true;
            }
        } else {
            if (target.y == pointer.y) {
                if (target.x == 2) if (pointer.x == 3 || pointer.x == 4) return true;
                if (target.x != 2) if (pointer.x == target.x + 1) return true;
            } else if (target.x + 1 == pointer.x) {
                if (target.y - 1 == pointer.y && isEnemy(target, pointer)) return true;
                if (target.y + 1 == pointer.y && isEnemy(target, pointer)) return true;
            }
        }

        return false;
    }

    bool Bishop(bool whiteMove) {
        return false;
    }

    bool Knight(bool whiteMove) {
        return false;
    }

    bool Rook(bool whiteMove) {
        return false;
    }

    bool Queen(bool whiteMove) {
        return false;
    }

    bool King(bool whiteMove) {
        return false;
    }
}
