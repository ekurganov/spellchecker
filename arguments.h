#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <optional>

enum language {
	eng,
	rus
};

namespace {
	const language def_lang = language::eng;
	const std::string def_dict_path = "words.txt";
	const std::string def_text_path = "check_words.txt";
	const std::string def_corr_text_path = "result.txt";
	const std::unordered_map<std::string, language> langs = { {"eng", language::eng}, {"rus", language::rus} };
}

struct Args {
	language lang_;
	std::string dict_path_;
	std::string text_path_;
	std::string corr_text_path_;

	Args() : lang_(language::eng), 
		dict_path_(def_dict_path), text_path_(def_text_path), corr_text_path_(def_corr_text_path) {	}

	void ReadOpts(int argc, char *argv[]);

private:
	std::vector <std::string> tokens;
};


void Args::ReadOpts(int argc, char *argv[]) {
	if (!(argc & 1)) {
		std::cout << "\nUsage: <program name> [option] [parameter]\n"
			<< "Options:\n"
			<< "-l or --lang <lang> : specify language\n"
			<< "-d or --dict <path> : specify dictionary path\n"
			<< "-t or --text <path> : specify input text path\n"
			<< "-r or --res <path>  : specify output text path\n\n";
		throw std::invalid_argument("Incorrect number of options");
	}
	for (int i = 1; i < argc; ++i) {
		this->tokens.push_back(std::string(argv[i]));
	}
	for (size_t i = 0; i < tokens.size(); i += 2) {
		if (tokens[i] == "-l" || tokens[i] == "--lang") {
			lang_ = langs.count(tokens[i + 1]) ? langs.at(tokens[i + 1]) : def_lang;
			if (langs.count(tokens[i + 1])) {
				lang_ = langs.at(tokens[i + 1]);
			}
			else {
				throw std::invalid_argument("Incorrect language");
			}
		}
		else if (tokens[i] == "-d" || tokens[i] == "--dict") {
			dict_path_ = tokens[i + 1];
		}
		else if (tokens[i] == "-t" || tokens[i] == "--text") {
			text_path_ = tokens[i + 1];
		}
		else if (tokens[i] == "-r" || tokens[i] == "--res") {
			corr_text_path_ = tokens[i + 1];
		}
		else {
			throw std::invalid_argument("Incorrect option");
		}
	}
}