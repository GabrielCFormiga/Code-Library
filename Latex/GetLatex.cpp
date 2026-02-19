#include <bits/stdc++.h>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;

#define RED "\033[0;31m"
#define RESET "\033[0m"

bool LOOK_FOR_HASH_IN_FILE = false;
int HASH_LEN = 3;

string NO_HASH = "nohash";
string NO_PRINT = "noprint";

string path = "../";
vector<string> target_folders = {
	"Data Structures",
	"Dynamic Programming", 
	"Graph Theory",
	"Math",
	"Miscellaneous",
	"Strings"
};
string hash_cmd = "sed -n 1','10000' p' tmp.cpp | sed '/^#w/d' "
"| cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-";

bool print_all = false;

struct PcloseDeleter {
	void operator()(FILE* file) const {
		if (file) pclose(file);
	}
};

string exec(string cmd) {
	array<char, 128> buffer;
	string result;
	unique_ptr<FILE, PcloseDeleter> pipe(popen(cmd.c_str(), "r"));
	if (!pipe) throw runtime_error("popen() failed!");
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
		result += buffer.data();
	result.pop_back();
	return result;
}

// lines [l, r], hash of size
string get_file_hash(string s, int size, int l = 0, int r = 1e9) {
	ifstream fin(s.c_str());
	ofstream tmp("tmp.cpp", ios::out);
	string line;
	for (int i = 0; i <= r; i++) {
		if (!getline(fin, line)) break;
		if (i >= l) tmp << line << '\n';
	}
	fin.close();
	tmp.close();
	string hash = exec(hash_cmd + to_string(size));
	return hash;
}

bool find_in_file(string s, string t) {
	ifstream fin(s.c_str());
	bool found = false;
	string line;
	while (getline(fin, line)) {
		for (int i = int(t.size()) - 1; i < line.size(); i++) {
			if (line.substr(i - t.size() + 1, t.size()) == t) {
				found = true;
				break;
			}
		}
	}
	return found;
}

bool is_comment(string line) {
	while (line.size() and (line[0] == ' ' or line[0] == '\t'))
		line = line.substr(1);
	bool comment = line.size() == 0;
	if (line.size() >= 2 and line.substr(0, 2) == "//") comment = true;
	if (line.size() >= 2 and line.substr(0, 2) == "/*") comment = true;
	return comment;
}

vector<string> split(string line, char c) {
	vector<string> ret;
	string cur;
	line.push_back(c);
	for (char at : line) {
		if (at == c) {
			if (cur.size()) ret.push_back(cur);
			cur.clear();
			continue;
		}
		cur += at;
	}
	return ret;
}

string sanitize_utf8_line(const string& line) {
	string sanitized;
	for (size_t i = 0; i < line.size(); i++) {
		unsigned char c = static_cast<unsigned char>(line[i]);

		// Thin/hair spaces (U+2009..U+200F: E2 80 89..8F) -> space
		if (i + 2 < line.size() && c == 0xE2 &&
		    static_cast<unsigned char>(line[i + 1]) == 0x80) {
			unsigned char d = static_cast<unsigned char>(line[i + 2]);
			if (d >= 0x89 && d <= 0x8F) {
				sanitized += ' ';
				i += 2;
				continue;
			}
		}
		if (c < 0x80) {
			sanitized += static_cast<char>(c);
			continue;
		}

		// UTF-8 thin spaces: U+2009 (E2 80 89), U+200A (E2 80 8A), U+202F (E2 80 AF)
		if (i + 2 < line.size() && c == 0xE2 &&
		    static_cast<unsigned char>(line[i + 1]) == 0x80 &&
		    (static_cast<unsigned char>(line[i + 2]) == 0x89 ||
		     static_cast<unsigned char>(line[i + 2]) == 0x8A ||
		     static_cast<unsigned char>(line[i + 2]) == 0xAF)) {
			sanitized += ' ';
			i += 2;
			continue;
		}

		// Non-breaking space (U+00A0: C2 A0)
		if (i + 1 < line.size() && c == 0xC2 &&
		    static_cast<unsigned char>(line[i + 1]) == 0xA0) {
			sanitized += ' ';
			i += 1;
			continue;
		}

		// Multiplication dot (U+00B7: C2 B7) -> '*'
		if (i + 1 < line.size() && c == 0xC2 &&
		    static_cast<unsigned char>(line[i + 1]) == 0xB7) {
			sanitized += '*';
			i += 1;
			continue;
		}

		// Ordinal indicator (U+00BA: C2 BA) -> 'o'
		if (i + 1 < line.size() && c == 0xC2 &&
		    static_cast<unsigned char>(line[i + 1]) == 0xBA) {
			sanitized += 'o';
			i += 1;
			continue;
		}

		// Common accented letters (C3 xx)
		if (i + 1 < line.size() && c == 0xC3) {
			unsigned char d = static_cast<unsigned char>(line[i + 1]);
			switch (d) {
				case 0xA1: case 0xA0: case 0xA2: case 0xA3: sanitized += 'a'; break;
				case 0xA7: sanitized += 'c'; break;
				case 0xA9: case 0xA8: case 0xAA: sanitized += 'e'; break;
				case 0xAD: case 0xAC: case 0xAE: sanitized += 'i'; break;
				case 0xB3: case 0xB2: case 0xB4: case 0xB5: sanitized += 'o'; break;
				case 0xBA: case 0xB9: case 0xBB: sanitized += 'u'; break;
				case 0x81: case 0x80: case 0x82: case 0x83: sanitized += 'A'; break;
				case 0x87: sanitized += 'C'; break;
				case 0x89: case 0x88: case 0x8A: sanitized += 'E'; break;
				case 0x8D: case 0x8C: case 0x8E: sanitized += 'I'; break;
				case 0x93: case 0x92: case 0x94: case 0x95: sanitized += 'O'; break;
				case 0x9A: case 0x99: case 0x9B: sanitized += 'U'; break;
				default: sanitized += ' '; break;
			}
			i += 1;
			continue;
		}

		// Skip any other multi-byte sequence.
		if ((c & 0xE0) == 0xC0 && i + 1 < line.size()) {
			i += 1;
			sanitized += ' ';
			continue;
		}
		if ((c & 0xF0) == 0xE0 && i + 2 < line.size()) {
			i += 2;
			sanitized += ' ';
			continue;
		}
		if ((c & 0xF8) == 0xF0 && i + 3 < line.size()) {
			i += 3;
			sanitized += ' ';
			continue;
		}

		sanitized += ' ';
	}
	return sanitized;
}

set<string> get_flags(string file) {
	ifstream fin(file.c_str());
	string line;
	getline(fin, line);
	fin.close();
	while (line.size() and line[0] != '[') line = line.substr(1);
	if (!line.size() or line.back() != ']') return {};
	vector<string> flags = split(line.substr(1, line.size() - 2), ',');
	return set<string>(flags.begin(), flags.end());
}

void remove_flags(string& line) {
	int has_flags = 0;
	for (char c : line) {
		if (has_flags == 0 and c == '[') has_flags++;
		if (has_flags == 1 and c == ']') has_flags++;
	}
	if (has_flags != 2) return;
	int idx = -1;
	for (int i = 0; i < line.size(); i++) if (line[i] == '[') {
		idx = i;
		break;
	}
	while (line.size() > idx) line.pop_back();
	while (line.size() and line.back() == ' ') line.pop_back();
}

void print_code_file(string file, bool extra = false) {
	cout << "\\begin{lstlisting}\n";
	ifstream fin(file.c_str());
	string line;
	int count = 0;
	bool started_code = false;
	int depth = 0;
	stack<int> st;
	for (int line_idx = 0; getline(fin, line); line_idx++) {
		int start_line = line_idx;
		if (count++ < 2 and !extra) continue;

		for (char c : line) {
			if (c == '{') depth++, st.push(line_idx);
			if (c == '}') depth--, start_line = st.top(), st.pop();
		}
		
		bool comment = is_comment(line);
		if (!comment) started_code = true;

		if (!extra and started_code) {
			string hash = get_file_hash(file, HASH_LEN, start_line, line_idx);

			if (comment) {
				if (depth != 0) {
					for (int i = 0; i < HASH_LEN + 1; i++)
						cout << " ";
				}
			} else cout << hash << " ";
		}
		cout << sanitize_utf8_line(line) << endl;
	}
	fin.close();
	cout << "\\end{lstlisting}\n\n";
}

void print_file(string file, bool extra = false) {
	ifstream fin(file.c_str());
	string line;
	int count = 0;
	while (getline(fin, line)) {
		if (count++ < 2 and !extra) continue;
		cout << line << endl;
	}
	fin.close();
}

string get_name(string file) {
	ifstream fin(file.c_str());
	string line;
	getline(fin, line);
	fin.close();
	remove_flags(line);
	if (line[2] == ' ') return line.substr(3);
	return line.substr(2);
}

void print_escaped(string s) {
	for (char c : s) {
		if (c == '^') cout << '\\';
		cout << c;
		if (c == '^') cout << "{}";
	}
}

bool print_listing(string sub, string file, bool extra = false) {
	set<string> flags = get_flags(file);

	if (!print_all and flags.count(NO_PRINT)) return false;

	if (LOOK_FOR_HASH_IN_FILE and !extra and !flags.count(NO_HASH)) {
		if (!find_in_file(file, get_file_hash(file, HASH_LEN)))
			cerr << RED << "WARNING" << RESET << ": hash not found for: "
			<< file.substr(10) << '\n';
	}

	cout << "\\subsection{";
	if (!extra) print_escaped(get_name(file));
	else print_escaped(sub);
	cout << "}\n";

	print_code_file(file, extra);
	return true;
}

void dfs(vector<pair<string, string>>& files, string s, bool extra = false) {
	struct dirent* entry = nullptr;
	DIR* dp = nullptr;
	dp = opendir(s.c_str());
	if (dp != nullptr) while (entry = readdir(dp)) {
		if (entry->d_name[0] == '.') continue;	

		if (entry->d_type == DT_DIR) dfs(files, s + "/" + string(entry->d_name), extra);
		else {
			if (!extra) files.emplace_back(entry->d_name, s + "/" + string(entry->d_name));
			else print_listing(entry->d_name, s + "/" + entry->d_name,
					extra and strcmp(entry->d_name, "vimrc"));
			//	The condition above prints the hash for vimrc.
			//	To remove it, use just "extra".
		}
	}
}

void print_section(string s) {
	cout << "\n\n";

	for (int i = 0; i < 20; i++) cout << "%";
	cout << "\n%\n% " << s << "\n%\n";
	for (int i = 0; i < 20; i++) cout << "%";
	cout << "\n\n";

	cout << "\\section{" << s << "}\n\n";
}

string lower(string s) {
	for (char& c : s) if (c >= 'A' and c <= 'Z') c ^= 32;
	return s;
}

int main(int argc, char** argv) {
	if (argc > 1) {
		string arg1(argv[1]);
		if (arg1 == "--printall") {
			print_all = true;
			cerr << "Printing all files..." << endl << endl;
		}
	}

	print_file("Header.tex", true);
	
	for (string dir : target_folders) {
		string full_path = path + dir;
		struct stat info;
		if (stat(full_path.c_str(), &info) != 0 || !(info.st_mode & S_IFDIR)) {
			cerr << "Warning: Directory not found: " << dir << endl;
			continue;
		}
		
		print_section(dir);

		vector<pair<string, string>> files;
		dfs(files, full_path);

		sort(files.begin(), files.end(), [&](auto f1, auto f2) {
			return lower(get_name(f1.second)) < lower(get_name(f2.second));
		});

		cerr << "=== " << dir << " ===" << endl;
		for (auto [f, file_path] : files) {
			bool printed = print_listing(f.substr(0, f.size() - 4), file_path);
			if (printed) cerr << get_name(file_path) << endl;
		}
		cerr << endl;
	}

	cout << "\\pagebreak" << endl;
	print_section("Extra");
	vector<pair<string, string>> files;
	dfs(files, path + "Extra", true);

	cout << "\\end{document}\n";
	return 0;
}
