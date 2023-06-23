#include <vector>
#include <string>
#include <iostream>

std::vector<int> Zfunc(std::string& str) {
    int size = str.size();
    std::vector<int> z(size, 0);
    int l = 0, r = 0;
    z[0] = size;

    for (int i = 1; i < size; ++i) {
        if (i <= r) {
            z[i] = std::min(z[i - l], r - i);
        }

        while (i + z[i] < size && str[z[i]] == str[i + z[i]]) {
            z[i]++;
        }

        if (r < i + z[i]) {
            r = i + z[i];
            l = i;
        }
    }

    return z;
}

int main() {
    std::string s;
    std::cin >> s;

    for (auto i : Zfunc(s)) {
        std::cout << i << " ";
    }
}