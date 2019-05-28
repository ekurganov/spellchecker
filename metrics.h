#pragma once
#include <algorithm>
#include <vector>
#include <string>

namespace {
	const unsigned int max_word_dist = 1;
}

inline char RusCp1251tolower(char c) { return (c <= -33 && c >= -64) ? c + 32 : c; }

class LevensteinDistance {
public:
	mutable std::vector<size_t> v;
	explicit LevensteinDistance(size_t init_size = 11) : v(init_size) {}
	size_t operator()(const std::string& s1, const std::string& s2) const;
};
