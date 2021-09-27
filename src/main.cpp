#include <iostream>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            int len = strlen(argv[i]);
            char* fileExt = &argv[i][len - 6];

            if (strcmp(fileExt, ".corth") == 0) {
                // Parser, lexer, etc...
            }
            else {
                std::cout << "Error: File must end in \".corth\"" << std::endl;
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
