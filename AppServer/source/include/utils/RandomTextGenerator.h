//
// Created by juan on 23/04/16.
//

#ifndef TINDER_RANDOMTEXTGENERATOR_H
#define TINDER_RANDOMTEXTGENERATOR_H

#include <string>
#include <cstdlib>
#include <ctime>

class RandomTextGenerator {
public:
    RandomTextGenerator(const std::string &str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") : m_str(str) { }

    std::string generate(std::size_t len = 1) {
        std::string seq;
        std::size_t siz = m_str.size();
        if (siz) {
            while (len--) {
                seq.push_back(m_str[rand() % siz]);
            }
        }
        return seq;
    }

private:
    std::string m_str;
};

#endif //TINDER_RANDOMTEXTGENERATOR_H
