#include <iostream>
#include <array>
#include <vector>

void calculateLevenshtein(std::string word1, std::string word2);

int main()
{
    std::cout << "Hello World!\n";

	calculateLevenshtein("chato", "chiens");

}

void calculateLevenshtein(std::string word1, std::string word2)
{
    std::cout << word1.length() << "\n" << word2.length() << "\n";
    int distance = 0;

	int rows = 6;
	int columns = 7;

    std::array<std::array<int,7>,6> mat;

    for (int i = 0; i < word1.length() +1; i++)
    {
        for (int j = 0; j < word2.length() +1; j++)
        {
            if (i == 0) {
				mat[i][j] = j;
			}
			else if (j == 0) {
				mat[i][j] = i;
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

                mat[i][j] = temp;
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
}