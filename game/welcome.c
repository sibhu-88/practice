#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define pf printf

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define RESET   "\033[0m" 

int main() {
    char c;

    for (int i = 0; i < 10; i++) {
        system("clear");
        usleep(500000);
      
	      pf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        pf(RED"             ██╗       ██╗███████╗██╗      █████╗  █████╗ ███╗   ███╗███████╗ \n"RESET);
        pf(GREEN"             ██║  ██╗  ██║██╔════╝██║     ██╔══██╗██╔══██╗████╗ ████║██╔════╝ \n"RESET);
        pf(YELLOW"             ╚██╗████╗██╔╝█████╗  ██║     ██║  ╚═╝██║  ██║██╔████╔██║█████╗   \n"RESET);
        pf(BLUE"              ████╔═████║ ██╔══╝  ██║     ██║  ██╗██║  ██║██║╚██╔╝██║██╔══╝   \n"RESET);
        pf(MAGENTA"              ╚██╔╝ ╚██╔╝ ███████╗███████╗╚█████╔╝╚█████╔╝██║ ╚═╝ ██║███████╗ \n"RESET);
        pf(CYAN"               ╚═╝   ╚═╝  ╚══════╝╚══════╝ ╚════╝  ╚════╝ ╚═╝     ╚═╝╚══════╝ \n"RESET);
        pf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
      
        usleep(500000);

    }

    printf("Press E to exit: ");
    scanf(" %c", &c);
    return 0;
}
