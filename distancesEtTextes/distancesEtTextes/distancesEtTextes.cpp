#include <iostream>
#include <array>
#include <vector>

void calculateLevenshtein(std::string word1, std::string word2);

int main()
{
    std::cout << "Veuillez entrer le premier mot: ";
    std::string word1;
    std::cin >> word1;

    std::cout << "Veuillez entrer le deuxième mot: ";
    std::string word2;
    std::cin >> word2;

    calculateLevenshtein(word1, word2);
}

void calculateLevenshtein(std::string word1, std::string word2)
{
    std::cout << word1.length() << "\n" << word2.length() << "\n";

    std::vector<std::vector<int>> mat;

    for (int i = 0; i < word1.length() +1; i++)
    {
        mat.push_back(std::vector<int>());
        for (int j = 0; j < word2.length() +1; j++)
        {
            if (i == 0) {
				mat[i].push_back(j);
			}
			else if (j == 0) {
				mat[i].push_back(i);
            }
            else
            {
                std::vector<int> array;

                int temp = word1[i-1] == word2[j-1] ? 0 : 1;
                if (temp != 0) {
				    array.push_back(mat[i - 1][j] + 1);
				    array.push_back(mat[i][j - 1] + 1);
				    array.push_back(mat[i - 1][j - 1] + 1);
				    temp = *std::min_element(array.begin(), array.end());
                }
                else if (mat[i - 1][j - 1] != 0)
                {
                    temp = mat[i - 1][j - 1];
                }

                mat[i].push_back(temp);
            }
        }
    }


    for(auto var : mat)
    {
        for (auto a : var) {
			std::cout << a << " ";
        }
		std::cout << "\n";
    }

	int distance = mat[word1.length()][word2.length()];

	std::cout << "\nLa distance de Levenshtein entre le mot " << word1 << " et le mot " << word2 << " est: " << distance;

}