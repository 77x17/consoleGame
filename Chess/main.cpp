#include <iostream>

#include "Setting.h"
#include "Color.h"
#include "redefineCommand.h"
#include "Chess.h"

int main() {
    std::cin.tie(0), std::cout.tie(0);

    Setting::main();
    Chess::main();

    return 0;
}
