#include "bktree.h"

bool BKNode::InsertWord(const std::string& word, 
	std::function<size_t(const std::string&, const std::string &)> distance) {
	size_t dist = distance(data_, word);
	if (dist == 0)
		return false;
	else if (nodes_.count(dist) == 1) {
		return nodes_[dist]->InsertWord(word, distance);
	}
	else {
		nodes_.insert(make_pair(dist, std::unique_ptr<BKNode>(new BKNode(word))));
		return true;
	}
}

std::optional<std::string_view> BKNode::FindWord(const std::string& query, 
	std::function<size_t(const std::string&, const std::string &)> distance, size_t shift) const {
	size_t dist = distance(data_, query);
	if (dist == shift)
		return data_;
	for (size_t offset = shift > dist ? 0 : dist - shift; offset <= dist + shift; ++offset) {
		if (nodes_.count(offset) == 1)
			return nodes_.at(offset)->FindWord(query, distance, shift);
	}
	return std::nullopt;
}