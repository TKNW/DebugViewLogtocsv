#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<regex>
using namespace std;

vector<string> tokenize(
	const string str,
	const regex re)
{
	sregex_token_iterator it{ str.begin(),str.end(), re, -1 },end;
	vector<string> tokenized(it,end);
	// Additional check to remove empty strings
	tokenized.erase(
		std::remove_if(tokenized.begin(),
		tokenized.end(),
		[](std::string const& s) {
		return s.size() == 0;
	}), tokenized.end());
	return tokenized;
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "File not found." << endl;
		return -1;
	}
	if (argc > 2)
	{
		cout << "Too many Argment." << endl;
	}
	fstream inputfile;
	fstream outputfile;
	int FirstNum = 0;
	double FirstTime = 0.0;
	bool numisready = false, timeisready = false;
	string filename(argv[1]);
	filename = filename.substr(0, filename.find("."));
	filename += ".csv";
	string input;
	inputfile.open(argv[1], ios::in | ios::_Nocreate);
	outputfile.open(filename, ios::out | ios::trunc);
	outputfile << "Serial Number,Time,Text" << endl;
	while (getline(inputfile, input))
	{
		vector<string> aftertok = tokenize(input, regex("\t"));
		for (int i = 0; i < aftertok.size(); ++i)
		{
			if (i == 0)
			{

				if (numisready == false)
				{
					FirstNum = stoi(aftertok[i]) - 1;
					numisready = true;
				}
				aftertok[i] = to_string(stoi(aftertok[i]) - FirstNum);

			}
			else if (i == 1)
			{
				if (isdigit(aftertok[i][0]))
				{
					if (timeisready == false)
					{
						FirstTime = stod(aftertok[i]);
						timeisready = true;
					}
					aftertok[i] = to_string(stod(aftertok[i]) - FirstTime);
				}
			}
			else if (i == 2)
			{
				aftertok[i].insert(0, "\"");
				aftertok[i].push_back('\"');
				aftertok[i].push_back('\n');
			}
			else//超過的直接忽略
			{
				break;
			}
		}
		outputfile << aftertok[0] << ',' << aftertok[1] << ',' << aftertok[2];
	}
	inputfile.close();
	outputfile.close();
	return 0;
}