#include <iostream>
#include <array>
#include <vector>
#include <fstream>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

std::vector<std::vector<int>> calculateLevenshteinMatrice(std::string word1, std::string word2);
void findClosestWords(std::string userWord);
char menuChoiceUpper();
void calculateDistanceTwoWords();

int main()
{
    char choice;

    do {
        std::cout << "\n\nBienvenue ! Veuillez choisir une option : " << std::endl;
        std::cout << "A: Calculer la distance entre deux mots" << std::endl;
        std::cout << "B: Trouver les n nombres les plus proche d'un mot" << std::endl;
        std::cout << "Q: Quitter" << std::endl;

        choice = menuChoiceUpper();

        switch (choice) {
        case 'A':
            calculateDistanceTwoWords();
            break;
        case 'B':
            //todo: b
            break;
        case 'Q':
            return 0;
        default:
            std::cout << "Veuillez choisir une option valide" << std::endl;
            break;
        }
    } while (choice != 'Q');
    

	std::cout << "Veuillez entrer un mot: ";
	std::string word1;
	std::cin >> word1;

	findClosestWords(word1);
}

void calculateDistanceTwoWords() {
    std::string word1;
    std::string word2;

    std::cout << "Veuillez entrer le premier mot: ";
    std::cin >> word1;

    std::cout << "Veuillez entrer le deuxième mot: ";
    std::cin >> word2;

    std::vector<std::vector<int>> levenshteinMatrice = calculateLevenshteinMatrice(word1, word2);

    for (auto elem : levenshteinMatrice)
    {
       for (auto e : elem) {
     	  std::cout << e << " ";
       }
       std::cout << "\n";
    }

    std::cout << "La distance entre le mot " << word1 << " et le mot " << word2 << " est de " << levenshteinMatrice[word1.length()][word2.length()] << ".\n";
}


char menuChoiceUpper() {
    char choice;
    std::cin >> choice;
    return std::toupper(choice);
}

std::vector<std::vector<int>> calculateLevenshteinMatrice(std::string word1, std::string word2)
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

	return mat;

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

    std::map<std::string, int> distances;

    std::map<int, std::vector<std::string>> testMap;


    for (auto word : frequentWords)
    {
		int wLength = word.second.length();
		int uwLength = userWord.length();

        std::vector<std::vector<int>> calc = calculateLevenshteinMatrice(word.second, userWord);
        int test = calc[wLength][uwLength];
		if (test != 0) {
            distances[word.second] = test;
			testMap[test].push_back(word.second);
		}
    }

  //  for (auto e : distances)
  //  {
		//std::cout << e.second << " " << e.first << std::endl;
  //  }
	//std::cout << distances[frequentWords[0]] << std::endl;

    // Source - https://stackoverflow.com/a/26843031
    // Posted by Timmmm, modified by community. See post 'Timeline' for change history
    // Retrieved 2026-10-02, License - CC BY-SA 4.0


    auto a = min_element(distances.begin(), distances.end(),[](const auto& l, const auto& r) {return l.second < r.second;});

	std::string word = a->first;

    std::cout << "Le mot le plus proche de " << userWord << " est: " << a->first << std::endl;


	//for (auto a : distances)
	//{
	//	std::cout << a.first << a.second << std::endl;
	//}

    std::vector<std::string> ouioui;

	for (auto b : testMap)
	{
		for (auto word : b.second) {
            ouioui.push_back(word);
		}
	}


	for (int i = 0; i < 6; i++)
	{
		std::cout << "Mot " << i + 1 << ": " << ouioui[i] << std::endl;
	}

	//std::vector<std::vector<int>> mat = calculateLevenshtein(word, userWord);

 //   for(auto var : mat)
 //   {
 //       for (auto a : var) {
 //     	std::cout << a << " ";
 //       }
 //       std::cout << "\n";
 //   }

    //int temp = *std::min_element(distances.begin(), distances.end());

}   
