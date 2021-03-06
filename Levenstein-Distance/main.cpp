#include "stdafx.h"

string word1, word2;
ifstream f("distance.txt");
int cInsert, cDelete, cReplace;
int m[21][21];
map < Position, Result> messages;

void Read() {

	f >> word1 >> word2;
	f >> cInsert >> cDelete >> cReplace;

	f.close();
}

int Levenstein() {

	for (int i = 0; i <= word1.size(); i++)
	{
		m[i][0] = i*cDelete;
		// Append to the result "stergem"
		string sir = "stergem ";
		sir.append(1, word1[0]);
		messages[*new Position(i, 0)] = *new Result(*new Position(0, 0), sir);
	}

	for (int j = 0; j <= word2.size(); j++) {
		m[0][j] = cInsert * j;
		// Append to the result "inseram"
		string sir = "inseram ";
		sir.append(1, word2[0]);
		messages[*new Position(0, j)] = *new Result(*new Position(0, 0), sir);
	}

	for (int i = 1; i <= word1.size(); i++) {
		for (int j = 1; j <= word2.size(); j++) {

			if (word1[i - 1] == word2[j - 1]) {
				m[i][j] = m[i - 1][j - 1];
				// Append to the result "pastram"
				string sir = "pastram ";
				sir.append(1, word1[i - 1]);
				messages[*new Position(i, j)] = *new Result(*new Position(i - 1, j - 1), sir);
			}
			else {

				int _min = min(m[i][j - 1] + cInsert, min(m[i - 1][j] + cDelete, m[i - 1][j - 1] + cReplace));

				if (_min == m[i][j - 1] + cInsert) {
					// Append to the result "inseram"
					string sir = "inseram ";
					sir.append(1, word2[j - 1]);
					messages[*new Position(i, j)] = *new Result(*new Position(i, j - 1), sir);
				}
				else if (_min == m[i - 1][j] + cDelete) {
					// Append to the result "stergem"
					string sir = "stergem ";
					sir.append(1, word1[i - 1]);
					messages[*new Position(i, j)] = *new Result(*new Position(i - 1, j), sir);
				}
				else if (_min == m[i - 1][j - 1] + cReplace) {
					// Append to the result "inlocuim"
					string sir = "inlocuim ";
					sir.append(1, word1[j - 1]);
					sir.append(1, '-');
					sir.append(1, word2[j - 1]);
					messages[*new Position(i, j)] = *new Result(*new Position(i - 1, j - 1), sir);
				}

				m[i][j] = _min;
			}
		}
	}
	return m[word1.size()][word2.size()];
}

void ShowChain(int i, int j) {

	if (i > 1 || j > 1) {
		i = messages[*new Position(i, j)].Prev().I();
		j = messages[*new Position(i, j)].Prev().J();

		ShowChain(i, j);

		cout << messages[*new Position(i, j)].Operation() << endl;
	}
}

void Show() {
	cout << Levenstein() << endl;
	ShowChain(word1.size(), word2.size());
	cout << messages[*new Position(word1.size(), word2.size())].Operation() << endl;
}

int main()
{
	Read();

	Show();

	system("pause");

	return 0;
}

