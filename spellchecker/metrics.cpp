#include "metrics.h"

size_t LevensteinDistance::operator()(const std::string& s1, const std::string& s2) const {
//	std::vector<size_t> v(s2.size() + 1);
	if (v.size() < s2.size() + 1)
		v.resize(s2.size() + 1);
	for (size_t i = 0; i <= s2.size(); ++i)
		v[i] = i;

	for (size_t i = 0; i < s1.size(); ++i) {
		size_t rest = v[0];
		v[0] = i + 1;
		for (size_t j = 0; j < s2.size(); ++j) {
			size_t tmp = v[j + 1];
			v[j + 1] = std::min({ v[j + 1] + 1, v[j] + 1, rest + static_cast<size_t>(s1[i] != s2[j]) });
			rest = tmp;
		}
	}
	return v[s2.size()];
}