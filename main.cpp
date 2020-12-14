#include <iostream>
#include <algorithm>
#include <vector>

const unsigned short MAX_WORD_SIZE = 16;

bool WordEqual(const char* lhs, const char* rhs){
    for (int i = 0; i < MAX_WORD_SIZE; ++i){
        if (lhs[i] != rhs[i]){
            return false;
        }
    }
    return true;
}

void CalculateGoodSuffix(std::vector<char*> &pattern, std::vector<int> &reverseZ){
    for (int i = 0; i < reverseZ; ++i){
        reverseZ[i] = 0;
    }
    for (int i = pattern.size() - 2; i >= 0; --i){
        int cnt = 0;
        //int res = 0;
        while (i - cnt >= 0 && WordEqual(pattern[i - cnt], pattern[pattern.size() - 1 - cnt])){
            ++cnt;
        }
        reverseZ[i] = cnt;
    }
    for (int i = 0; i < pattern.size(); ++i){
        std::cout << reverseZ[i] << " ";
    }
    std::cout << "\n";
}

void CalculateBadSymbol(std::vector<char*> &pattern, std::vector<int> ){

}

int main() {
    std::vector<char*> pattern;
    char curChar = 0;
    char* curWord = new char[MAX_WORD_SIZE];
    for (int i = 0; i < MAX_WORD_SIZE; ++i){
        curWord[i] = 0;
    }
    unsigned int cnt = 0;

    while (scanf("%c", &curChar) > 0){
        curChar = (char)tolower(curChar);
        if (curChar == ' '){
            cnt = 0;
            pattern.push_back(curWord);
            curWord = new char[MAX_WORD_SIZE];
            for (int i = 0; i < MAX_WORD_SIZE; ++i){
                curWord[i] = 0;
            }
        } else if (curChar == '\n'){
            cnt = 0;
            pattern.push_back(curWord);
            break;
        } else {
            curWord[cnt] = curChar;
            ++cnt;
        }
    }
    for (int i = 0; i < pattern.size(); ++i){
        std::cout << pattern[i] << ' ';
    }
    std::cout << "\n";
    CalculateGoodSuffix(pattern);


    std::vector<char*> text;
    cnt = 0;
    curWord = new char[MAX_WORD_SIZE];
    for (int i = 0; i < MAX_WORD_SIZE; ++i){
        curWord[i] = 0;
    }
    while (scanf("%c", &curChar) > 0){
        if (curChar == ' '){
            cnt = 0;
            text.push_back(curWord);
            curWord = new char[MAX_WORD_SIZE];
            for (int i = 0; i < MAX_WORD_SIZE; ++i){
                curWord[i] = 0;
            }
        } else if (curChar == '\n'){
            cnt = 0;
            text.push_back(curWord);
//            for (int i = 0; i < text.size(); ++i){
//                std::cout << text[i] << ' ';
//            }
            break;
        } else {
            curWord[cnt] = curChar;
            ++cnt;
        }
    }

    return 0;
}