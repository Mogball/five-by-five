#include <iostream>

static constexpr auto SIZE = 6;

struct Field {
    bool grid[SIZE][SIZE];
    std::size_t taken;
};

static std::ostream &operator<<(std::ostream &os, const Field &f) {
    using std::endl;
    for (auto i = 0; i < SIZE; ++i) {
        for (auto j = 0; j < SIZE; ++j) {
            os << (f.grid[i][j] ? "x" : "o") << " ";
        }
        os << endl;
    }
    return os;
}

static bool connect_next(Field &f, int x, int y) {
    f.grid[x][y] = true;
    ++f.taken;

    if (f.taken == SIZE * SIZE) {
        return true;
    }

    int X[] = { x, x-1, x+1, x };
    int Y[] = { y-1, y, y, y+1 };
    for (auto i = 0; i < 4; ++i) {
        int xn = X[i];
        int yn = Y[i];
        if (xn < 0 || xn >= SIZE || yn < 0 || yn >= SIZE) {
            continue;
        }
        if (xn == 1 && yn == 0 && f.taken != SIZE * SIZE - 1) {
            continue;
        }
        if (f.grid[xn][yn]) {
            continue;
        }
        if (connect_next(f, xn, yn)) {
            return true;
        }
        --f.taken;
        f.grid[xn][yn] = false;
    }
    return false;
}

int main() {
    Field f{};
    std::cout << connect_next(f, 0, 0) << std::endl;
}
