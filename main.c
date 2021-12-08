#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>


void reverse(char *str);


int main() {
    int p_to_child[2];
    int created = pipe(p_to_child);
    if (created) {
        printf("couldn't create pipes (%s, %d), exiting...\n", strerror(errno), errno);
        return EXIT_FAILURE;
    }

    int child_to_p[2];
    created = pipe(child_to_p);
    if (created) {
        printf("couldn't create pipes (%s, %d), exiting...\n", strerror(errno), errno);
        return EXIT_FAILURE;
    }

    int pid = fork();
    if (pid == 0) {
        char input[500];

        while (1) {
            
            printf(">>> ");
            
            fgets(input, sizeof(input), stdin);
            input[strlen(input) - 1] = 0;
            write(p_to_child[1], input, strlen(input));

            int r = read(child_to_p[0], input, sizeof(input));
            input[r] = 0;
            
            printf("%s\n", input);
        }
    }
    else if (pid == -1) {
        printf("couldn't fork (%s, %d), exiting...\n", strerror(errno), errno);
        return EXIT_FAILURE;
    }
    else {
        char data[500];

        while (1) {
            int r = read(p_to_child[0], data, sizeof(data));
			data[r] = 0;
            
            reverse(data);
            write(child_to_p[1], data, strlen(data));
        }
    }

    return 0;
}

void reverse(char *str) {
    int len = strlen(str);

    int i;
    for (i = 0; i < len / 2; i++) {
        int temp = str[len - i - 1];
        str[len - i - 1] = str[i];
        str[i] = temp;
    }
}
