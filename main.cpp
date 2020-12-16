#include <iostream>
#include <algorithm>
#include <vector>
//#include <map>
#include <unordered_map>
#include <cctype>

void CalculateGoodSuffix(std::vector<std::string> &pattern, std::vector<int> &l){
    std::vector<int> reverseZ(pattern.size());
    for (int i = 0; i < reverseZ.size(); ++i){
        reverseZ[i] = 0;
    }
    for (int i = pattern.size() - 2; i >= 0; --i){
        int cnt = 0;
        while (i - cnt >= 0 && pattern[i - cnt] == pattern[pattern.size() - 1 - cnt]){
            ++cnt;
        }
        reverseZ[i] = cnt;
    }
    std::reverse(reverseZ.begin(), reverseZ.end());
    int j;
    for (int i = 0; i < pattern.size() - 1; ++i){
        j = pattern.size() - reverseZ[i];
        l[j] = i;
    }
    std::vector<int> L(pattern.size() + 1, pattern.size());
    for (int i = pattern.size() - 1; i >= 0; --i){
        j = pattern.size() - i;
        if (reverseZ[j - 1] == j){
            L[i] = j - 1;
        } else {
            L[i] = L[i + 1];
        }
    }
    for (int i = 0; i < pattern.size() + 1; ++i){
        if (l[i] == pattern.size()){
            l[i] = L[i];
        }
    }
    for (int i = 0; i < l.size(); ++i){
        if (l[i] != pattern.size()){
            l[i] = pattern.size() - l[i] - 1;
        }
    }
}

void CalculateBadSymbol(std::vector<std::string> &pattern, std::unordered_map<std::string, int> &r){
    for (int i = 0; i < pattern.size() - 1; ++i){
        r[pattern[i]] = i;
    }
}

int main() {
    std::vector<std::string> pattern;
    char tmpChar;
    std::string tmpString;
    while (scanf("%c", &tmpChar)){
        if (tmpChar == ' '){
            pattern.push_back(tmpString);
            tmpString.clear();
        } else if (tmpChar == '\n'){
            pattern.push_back(tmpString);
            tmpString.clear();
            break;
        } else {
            tmpString += std::tolower(tmpChar);
        }
    }

//    for (int i = 0; i < pattern.size(); ++i){
//        std::cout << pattern[i] << " ";
//    }
//    std::cout << "\n";

    std::vector<int> l(pattern.size() + 1);
    CalculateGoodSuffix(pattern, l);
    std::unordered_map<std::string, int> r;
    CalculateBadSymbol(pattern, r);

//    for (int i = 0; i < pattern.size(); ++i){
//        std::cout << l[i] << " ";
//    }
//    std::cout << "\n";

    int cnt = 0;
    std::vector<std::string> text;
    while (scanf("%c", &tmpChar)){
        if (tmpChar == ' '){
            text.push_back(tmpString);
            tmpString.clear();
        } else if (tmpChar == '\n'){
            ++cnt;
            text.push_back(tmpString);
            tmpString.clear();
            if (text.size() < pattern.size()){
                continue;
            } else {
                int shift;
                int bound = 0;
                int j;
                for (int i = 0; i < text.size() - pattern.size() + 1;){
                    //int k = pattern.size() - 1;
                    for (j = pattern.size() - 1; j >= 0; --j){
                        if (text[i + j] != pattern[j]){
                            break;
                        }
                    }
                    if (j < bound){
                        std::cout << cnt << ", " << i + 1 << '\n';
                        bound = pattern.size() - l[0];
                        j = -1;
                        shift = l[0];
                    } else {
                        bound = 0;
                        shift = std::max({1, l[j + 1], j - r[text[i + j]]});
                    }
                    i += shift;
                }
            }
            text.clear();
        } else {
            tmpString += std::tolower(tmpChar);
        }
    }

    return 0;
}