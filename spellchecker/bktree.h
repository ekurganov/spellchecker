#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <optional>
#include <iostream>
#include <string_view>
#include <functional>
#include "metrics.h"

class BKNode {
public:
	BKNode(const std::string& new_data) : data_(new_data) {}
	bool InsertWord(const std::string& word,
		std::function<size_t(const std::string&, const std::string &)> distance);
	std::optional<std::string_view> FindWord(const std::string& query, 
		std::function<size_t(const std::string&, const std::string &)> distance, size_t shift) const;
private:
	std::string data_;
	std::unordered_map<size_t, std::unique_ptr<BKNode>> nodes_;
};

template<class Metric>
class BKTree {
public:
	BKTree() : root_(nullptr), size_(0) { }
	bool InsertWord(const std::string& word);
	std::optional<std::string_view> FindWord(const std::string& query, size_t max_dist) const;
	size_t GetSize()const { return size_; }
private:
	std::unique_ptr<BKNode> root_;
	const Metric distance_;
	size_t size_;
};


template<class Metric>
bool BKTree<Metric>::InsertWord(const std::string& word) {
	if (root_ == nullptr) {
		root_ = std::unique_ptr<BKNode>(new BKNode(word));
		size_ = 1;
		return true;
	}
	else if (root_->InsertWord(word, distance_)) {
		++size_;
		return true;
	}
	return false;
}

template<class Metric>
std::optional<std::string_view> BKTree<Metric>::FindWord(const std::string& query, size_t max_dist) const {
	if (root_ == nullptr)
		return std::nullopt;
	for (size_t i = 0; i <= max_dist; ++i) {
		auto ret = root_->FindWord(query, distance_, i);
		if (ret)
			return ret;
	}
	return std::nullopt;
}