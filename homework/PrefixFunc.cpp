#include <iostream>
#include <string>
#include <vector>

std::vector<int> PrefixFunc(std::string s) {
  std::vector<int> prefix(s.size(), 0);

  for (uint64_t i = 1; i < s.size(); ++i) {
    int k = prefix[i - 1];

    while (k > 0 && s[k] != s[i]) {
      k = prefix[k - 1];
    }

    if (s[k] == s[i]) {
      prefix[i] = k + 1;
    }
  }

  return prefix;
}

int main() {
  std::string str;
  std::cin >> str;
  std::vector<int> pref(PrefixFunc(str));

  for (auto el : pref) {
    std::cout << el << " ";
  }
}
