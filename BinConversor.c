#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Compilation: gcc BinConversor.c -o BinConversor.exe

void intro() {
    printf("\n@@@@@@@   @@@  @@@  @@@     @@@@@@@   @@@@@@   @@@  @@@  @@@  @@@  @@@@@@@@  @@@@@@@    @@@@@@    @@@@@@   @@@@@@@\n");   
    printf("@@@@@@@@  @@@  @@@@ @@@    @@@@@@@@  @@@@@@@@  @@@@ @@@  @@@  @@@  @@@@@@@@  @@@@@@@@  @@@@@@@   @@@@@@@@  @@@@@@@@\n");  
    printf("@@!  @@@  @@!  @@!@!@@@    !@@       @@!  @@@  @@!@!@@@  @@!  @@@  @@!       @@!  @@@  !@@       @@!  @@@  @@!  @@@\n");  
    printf("!@   @!@  !@!  !@!!@!@!    !@!       !@!  @!@  !@!!@!@!  !@!  @!@  !@!       !@!  @!@  !@!       !@!  @!@  !@!  @!@\n");  
    printf("@!@!@!@   !!@  @!@ !!@!    !@!       @!@  !@!  @!@ !!@!  @!@  !@!  @!!!:!    @!@!!@!   !!@@!!    @!@  !@!  @!@!!@! \n");  
    printf("!!!@!!!!  !!!  !@!  !!!    !!!       !@!  !!!  !@!  !!!  !@!  !!!  !!!!!:    !!@!@!     !!@!!!   !@!  !!!  !!@!@!  \n");  
    printf("!!:  !!!  !!:  !!:  !!!    :!!       !!:  !!!  !!:  !!!  :!:  !!:  !!:       !!: :!!        !:!  !!:  !!!  !!: :!! \n");
    printf(":!:  !:!  :!:  :!:  !:!    :!:       :!:  !:!  :!:  !:!   ::!!:!   :!:       :!:  !:!      !:!   :!:  !:!  :!:  !:!\n");
    printf(" :: ::::   ::   ::   ::     ::: :::  ::::: ::   ::   ::    ::::     :: ::::  ::   :::  :::: ::   ::::: ::  ::   :::\n");  
    printf(":: : ::   :    ::    :      :: :: :   : :  :   ::    :      :      : :: ::    :   : :  :: : :     : :  :    :   : :\n\n");
}

int menu() {
    int option;
    bool valido = false;

    while(!valido) {
        printf("\n<<< Main Menu >>>\n");
        printf("\n\tOption:\t\t\tDescription:\n");
        printf("\n\t  1 ........... Convert Binary to Decimal\n");
        printf("\n\t  2 ........... Convert Decimal to Binary\n");
        printf("\n\t  3 ........... Exit\n");
        printf("\n");
        
        printf("Choose an option: ");
        if(scanf("%d", &option) == 1 && option >= 1 && option <= 3) {
            valido = true;
        } else {
            while(getchar() != '\n');  // Clear the input buffer
            printf("\nUnrecognized value, please enter a valid option number (1, 2, or 3).\n");
        }
    }
    return option;
}

void bin2dec(char binarys[10][9], int count) {
    int Base_2[] = {128, 64, 32, 16, 8, 4, 2, 1};
    
    for (int i = 0; i < count; i++) {
        if (strlen(binarys[i]) != 8) {
            printf("-1 "); // Not an octet
            continue;
        }

        int dec = 0;
        bool invalid = false;

        for (int j = 0; j < 8; j++) {
            if (binarys[i][j] == '1') {
                dec += Base_2[j];
            } else if (binarys[i][j] != '0') {
                invalid = true;
                break;
            }
        }

        if (invalid || dec < 0 || dec > 255) {
            printf("-1 ");
        } else {
            printf("%d ", dec);
        }
    }
    
    printf("\n");
}

void dec2bin(char decimals[10][10], int count) {
    int Base_2[] = {128, 64, 32, 16, 8, 4, 2, 1};

    for (int i = 0; i < count; i++) {
        int decimal;
        bool valid = true;

        if (sscanf(decimals[i], "%d", &decimal) != 1 || decimal < 0 || decimal > 255) {
            valid = false;
        }

        if (!valid) {
            printf("-1 ");
            continue;
        }

        for (int j = 0; j < 8; j++) {
            if (decimal >= Base_2[j]) {
                printf("1");
                decimal -= Base_2[j];
            } else {
                printf("0");
            }
        }
        printf(" ");
    }
    printf("\n");
}

int main() {
    intro();
    bool salir = false;

    while (!salir) {
        int option = menu();
        char binarys[10][9];
        char decimals[10][10];

        if (option == 1) {
            printf("Binaries (separated by a space for each octet):\n");
            char input[90];
            fgets(input, sizeof(input), stdin);  // Clear the buffer
            fgets(input, sizeof(input), stdin);  // Get user input

            int i = 0;
            char *token = strtok(input, " ");
            while(token != NULL && i < 10) {
                strncpy(binarys[i], token, 9);
                binarys[i][8] = '\0';
                token = strtok(NULL, " ");
                i++;
            }

            printf("-1 means the octet is incomplete or invalid.\n");
            printf("Decimals: ");
            bin2dec(binarys, i);
        } else if (option == 2) {
            printf("Decimals (press Enter to finish and separate by spaces):\n");
            char input[100];
            fgets(input, sizeof(input), stdin);  // Clear the buffer
            fgets(input, sizeof(input), stdin);  // Get user input

            int i = 0;
            char *token = strtok(input, " ");
            while (token != NULL && i < 10) {
                strncpy(decimals[i], token, 10);
                decimals[i][9] = '\0';
                token = strtok(NULL, " ");
                i++;
            }

            printf("-1 means the decimal is invalid.\n");
            printf("Binaries: ");
            dec2bin(decimals, i);
        } else if (option == 3) {
            printf("Thank you for using BinaryConversor\n");
            salir = true;
        }
    }
    printf("Press Enter to exit...");
    while(getchar() != '\n');  // clear buffer
    getchar();
    
    return 0;
}