#include <iostream>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        for (int i = 0; i < argc; i++) {
            int len = strlen(argv[i]);
            char* fileExt = &argv[i][len - 5];
            if (strcmp(fileExt, ".nums") == 0) {
                // Parser, lexer, etc...
            }
            else {
                std::cout << "Error: File must end in \".nums\"" << std::endl;
            }
        }
    }
    else {
        // Maybe live interpreter later?
        std::cout << "Error: Please provide a file" << std::endl;
        return 1;
    }

    return 0;
}
