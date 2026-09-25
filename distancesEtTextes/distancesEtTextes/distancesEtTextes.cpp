#include <iostream>
#include <array>
#include <vector>
#include <fstream>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

int calculateLevenshtein(std::string word1, std::string word2);
void findClosestWords(std::string userWord);

int main()
{
    //std::cout << "Veuillez entrer le premier mot: ";
    //std::string word1;
    //std::cin >> word1;

    //std::cout << "Veuillez entrer le deuxième mot: ";
    //std::string word2;
    //std::cin >> word2;

    //calculateLevenshtein(word1, word2);

	findClosestWords("bonjour");
}

int calculateLevenshtein(std::string word1, std::string word2)
{
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


  //  for(auto var : mat)
  //  {
  //      for (auto a : var) {
		//	std::cout << a << " ";
  //      }
		//std::cout << "\n";
  //  }

	return mat[word1.length()][word2.length()];

	//std::cout << "\nLa distance de Levenshtein entre le mot " << word1 << " et le mot " << word2 << " est: " << distance;
}

void findClosestWords(std::string userWord) {

	std::unordered_map<int, std::string> frequentWords;
    std::ifstream frequentWordsFile("frequentWords/frequence.json");

    json frequentWordsJson = json::parse(frequentWordsFile);
	int i = 0;
    for(auto elem : frequentWordsJson)
    {
		frequentWords[i] = elem["label"].get<std::string>();
        i++;
    }

    std::unordered_map<std::string, int> distances;
    for (auto word : frequentWords)
    {
        distances[word.second] = calculateLevenshtein(word.second, userWord);
    }

    for (auto e : distances)
    {
		std::cout << e.second << " " << e.first << std::endl;
    }
	//std::cout << distances[frequentWords[0]] << std::endl;


    //int temp = *std::min_element(distances.begin(), distances.end());

}
