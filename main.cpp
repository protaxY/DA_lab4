#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

void GoodSuffix(const std::vector<std::string> &pattern, std::vector<int> &goodSuff)
{
    int left = 0;
    int right = 0;
    std::vector<int> zFunction(pattern.size(), 0);
    for (int i = 1; i < pattern.size(); ++i) {
        if (i <= right){
            zFunction[i] = std::min(right - i + 1, zFunction[i - left]);
        }

        while (i + zFunction[i] < pattern.size() &&
        (pattern[pattern.size() - 1 - zFunction[i]] == pattern[pattern.size() - 1 - (i + zFunction[i])])) {
            zFunction[i]++;
        }

        if (i + zFunction[i] - 1 > right) {
            left = i;
            right = i + zFunction[i] - 1;
        }
    }
    std::vector<int> N(zFunction.rbegin(), zFunction.rend());
    int j = 0;
    for (int i = 0; i < pattern.size() - 1; ++i) {
        j = pattern.size() - N[i];
        goodSuff[j] = i;
    }
    std::vector<int> l(pattern.size() + 1, pattern.size());
    for (int i = pattern.size() - 1; i >= 0; i--) {
        j = pattern.size() - i;
        if (N[j - 1] == j){
            l[i] = (j - 1);
        }
        else{
            l[i] = l[i + 1];
        }
    }
    for (int i = 0; i < pattern.size() + 1; ++i) {
        if (goodSuff[i] == pattern.size()){
            goodSuff[i] = l[i];
        }
    }
    for (int i = 0; i < goodSuff.size(); ++i) {
        if (goodSuff[i] != pattern.size()){
            goodSuff[i] = pattern.size() - 1 - goodSuff[i];
        }
    }
}

void BadCharacter(const std::vector<std::string> &pattern, std::map<std::string, int> &badChar)
{
    for (int i = 0; i < (int)pattern.size() - 1; ++i){
        badChar[pattern[i]] = i;
    }
}

void inputParser(std::vector<std::string> &pattern, std::vector<std::string> &text, std::vector<std::pair<int, int>> &positions)
{
    std::string curString;
    curString.clear();
    char curSymbol;
    curSymbol = getchar();
    bool flag = false;
    while (curSymbol != '\n' && curSymbol != -1) {
        if (curSymbol == ' ' && flag) {
            flag = false;
            pattern.push_back(curString);
            curString.clear();
        }
        else if (curSymbol != ' ' && curSymbol != '\n') {
            flag = true;
            curString.push_back(std::tolower(curSymbol));
        }
        curSymbol = getchar();
    }
    if (flag) {
        pattern.push_back(curString);
    }
    curString.clear();
    unsigned linePos = 1;
    unsigned columnPos = 0;
    flag = false;
    std::pair<int, int> pos;
    while ((curSymbol = getchar()) != EOF) {
        if (curSymbol == ' ' && flag) {
            flag = false;
            ++columnPos;
            text.push_back(curString);
            pos.first = linePos;
            pos.second = columnPos;
            positions.push_back(pos);
            curString.clear();
        }
        else if (curSymbol == '\n') {
            if (flag) {
                ++columnPos;
                text.push_back(curString);
                pos.first = linePos;
                pos.second = columnPos;
                positions.push_back(pos);
                curString.clear();
            }
            flag = false;
            columnPos = 0;
            ++linePos;
        }
        else if (curSymbol != ' ' && curSymbol != '\n') {
            flag = true;
            curString.push_back(std::tolower(curSymbol));
        }
    }
    if (flag) {
        ++columnPos;
        text.push_back(curString);
        pos.first = linePos;
        pos.second = columnPos;
        positions.push_back(pos);
    }
}

int main()
{
//    std::ios::sync_with_stdio(false);
//    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::vector<std::string> pattern;
    std::vector<std::string> text;
    std::vector<std::pair<int, int>> positions;
    inputParser(pattern, text, positions);
    std::vector<int> goodSuff(pattern.size() + 1, pattern.size());
    GoodSuffix(pattern, goodSuff);
    std::map<std::string, int> badChar;
    BadCharacter(pattern, badChar);

    int patternPos, bound = 0, shift = 0;
    for (int textPos = 0; textPos < 1 + text.size() - pattern.size();) {
        for (patternPos = pattern.size() - 1; patternPos >= bound; patternPos--) {
            if (pattern[patternPos] != text[textPos + patternPos]) {
                break;
            }
        }
        if (patternPos < bound) {
            std::cout << positions[textPos].first << ", " << positions[textPos].second << '\n';
            bound = pattern.size() - goodSuff[0];
            patternPos = -1;
        }
        else {
            bound = 0;
        }
        if (patternPos < bound) {
            shift = goodSuff[patternPos + 1];
        }
        else {
            shift = std::max({1, goodSuff[patternPos + 1], patternPos - badChar[text[textPos + patternPos]]});
        }
        textPos += shift;
    }
    return 0;
}

