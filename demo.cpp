#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

std::unordered_map<std::string, std::string> opts = {
  {"num_entries", "10"}
};

void help(char* prog) {
  std::cout << "Usage: " << prog; 
  for (const auto& e : opts) {
    std::cout << ' ' << e.first << ' ' << e.second;
  }
  std::cout << std::endl;
}

bool std_lower_bound(unsigned* array, int n, unsigned v) {
  return *std::lower_bound(array, array + n, v) == v;
}

template<unsigned MAXN>
unsigned* binary_search_branchless_UR(unsigned *arr, unsigned key) {
  #define STEP(step) \
    if ((1 << step) < MAXN) arr += (arr[1 << step] <= key) * (1 << step)
  STEP(29);
  STEP(28);
  STEP(27);
  STEP(26);
  STEP(25);
  STEP(24);
  STEP(23);
  STEP(22);
  STEP(21);
  STEP(20);
  STEP(19);
  STEP(18);
  STEP(17);
  STEP(16);
  STEP(15);
  STEP(14);
  STEP(13);
  STEP(12);
  STEP(11);
  STEP(10);
  STEP(9);
  STEP(8);
  STEP(7);
  STEP(6);
  STEP(5);
  STEP(4);
  STEP(3);
  STEP(2);
  STEP(1);
  STEP(0);
  #undef STEP
  return arr;
}

bool branchless_bs(unsigned* array, size_t n, unsigned v) {
  #define CASE(s) \
    case 1 << s: return *binary_search_branchless_UR<1 << s>(array, v) == v
  switch(n) {
    CASE(0);
    CASE(1);
    CASE(2);
    CASE(3);
    CASE(4);
    CASE(5);
    CASE(6);
    CASE(7);
    CASE(8);
    CASE(9);
    CASE(10);
    CASE(11);
    CASE(12);
    CASE(13);
    CASE(14);
    CASE(15);
    CASE(16);
    CASE(17);
    CASE(18);
    CASE(19);
    CASE(20);
    CASE(21);
    CASE(22);
    CASE(23);
    CASE(24);
    CASE(25);
    CASE(26);
    CASE(27);
    CASE(28);
    CASE(29);
    default: {
      std::cout << "Unsupported array size: " << n << std::endl;
      exit(1);
    }
  }
}

int main(int argc, char** argv) {
  for (auto i = 1; i < argc; i += 2) {
    std::string key(argv[i]);
    auto iter = opts.find(key);
    if (iter == opts.end()) {
      std::cout << "Option key `" << argv[i] << "` not found.";
      help(argv[0]);
      exit(1);
    }
    iter->second = argv[i + 1];
  }

  unsigned num_e = 1 << std::stoi(opts.at("num_entries"));

  std::vector<unsigned> vals(num_e);
  for (auto i = 0; i < num_e; i++) {
    vals[i] = i << 1 | 1; // all odd
  }
  vals.back() = ~0u; // a very large value

  std::vector<bool> res1((num_e << 1) + 10);
  {
    auto st = std::chrono::steady_clock::now();
    for (int i = 0, sz = res1.size(); i < sz; i++) {
      res1[i] = std_lower_bound(&vals.front(), vals.size(), i);
    }
    auto ed = std::chrono::steady_clock::now();
    std::cout << "std_lower_bound takes " << std::chrono::duration_cast<std::chrono::microseconds>(ed - st).count() << " us" << std::endl;
  }

  std::vector<bool> res2((num_e << 1) + 10);
  {
    auto st = std::chrono::steady_clock::now();
    for (int i = 0, sz = res2.size(); i < sz; i++) {
      res2[i] = branchless_bs(&vals.front(), vals.size(), i);
    }
    auto ed = std::chrono::steady_clock::now();
    std::cout << "branchless takes " << std::chrono::duration_cast<std::chrono::microseconds>(ed - st).count() << " us" << std::endl;
  }

  for (int i = 0, sz = res1.size(); i < sz; i++) {
    if (res1[i] != res2[i]) {
      std::cout << "Different results at " << i << ": " << res1[i] << " vs " << res2[i] << std::endl;
    }
  }
  return 0;
}
