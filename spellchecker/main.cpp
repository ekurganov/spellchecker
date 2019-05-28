#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <locale>
#include "metrics.h"
#include "bktree.h"
#include "arguments.h"

int main(int argc, char *argv[]) {
	try {
		Args args;
		if (argc > 1) {
			args.ReadOpts(argc, argv);
		}

		std::string tmp;
		BKTree<LevensteinDistance> dict;

		std::ifstream in_dict(args.dict_path_);
		if (!in_dict) {
			throw std::runtime_error("Cannot open input file " + args.dict_path_);
		}
		while (in_dict >> tmp) {
			if (args.lang_ == eng) {
				std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
			}
			else {
				std::transform(tmp.begin(), tmp.end(), tmp.begin(), RusCp1251tolower);
			}
			dict.InsertWord(tmp);
		}
		std::cout << "Dict size = " << dict.GetSize() << std::endl;

		std::ifstream in_text(args.text_path_);
		if (!in_text) {
			throw std::runtime_error("Cannot open input file " + args.text_path_);
		}
		std::ofstream out_text(args.corr_text_path_);
		if (!out_text) {
			throw std::runtime_error("Cannot open output file " + args.corr_text_path_);
		}

		size_t success_cnt = 0;
		while (in_text >> tmp) {
			if (args.lang_ == eng) {
				std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
			}
			else {
				std::transform(tmp.begin(), tmp.end(), tmp.begin(), RusCp1251tolower);
			}
			auto res = dict.FindWord(tmp, max_word_dist);
			if (res) {
				success_cnt++;
			}
			out_text << (res ? *res : tmp) << "\n";
		}

		std::cout << success_cnt << " entries found\n";
	}
	catch (const std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
}
