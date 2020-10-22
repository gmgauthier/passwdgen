#include <iostream>
#include <random>

std::string random_string(std::size_t length, bool punc) {
    std::string CHARACTERS;
    std::string ALPHANUM = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string SPECIALS = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

    if (punc) {
        CHARACTERS = ALPHANUM.append(SPECIALS);
    } else {
        CHARACTERS = ALPHANUM;
    }
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

    std::string random_string;
    for (std::size_t i = 0; i < length; ++i) {
        random_string += CHARACTERS[distribution(generator)];
    }
    return random_string;
}

void show_usage(std::string binname) {
    std::cerr << "Usage: " << binname << " [OPTIONS] " << std::endl
              << "Options:" << std::endl
              << "\t-h, --help        \t\tShow this help message" << std::endl
              << "\t-l, --length      \t\tThe length of the password (default: 32)" << std::endl
              << "\t-p, --punctuation \t\tToggle special characters (default: false)"
              << std::endl;
}

int main(int argc, char *argv[]) {
    std::string passlenstr;
    int passlen;
    bool punc = false;

    if (argc < 1) {
        std::cout << random_string(32, false) << std::endl;
        return 0;
    } else {
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if ((arg == "-h") || (arg == "--help")) {
                show_usage(argv[0]);
                return 0;
            } else if (arg == "-p") {
                punc = true;
            } else if ((arg == "-l") || (arg == "--length")) {
                passlenstr = argv[i + 1];
                if (passlenstr.empty()) {
                    std::cerr << "--destination option requires one argument." << std::endl;
                    return 1;
                }
            }
        }

        if (passlenstr.empty()) {
            passlenstr = "32";
        }
        passlen = std::stoi(passlenstr);
        std::string password = random_string(passlen, punc);
        std::cout << password << std::endl;
        return 0;
    }
}

