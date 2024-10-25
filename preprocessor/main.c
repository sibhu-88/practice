#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pre {
    char name[30];
    char def[50];
    struct pre *next;
} PRE;

void file_add(char *, char, char **);
void remove_cmd(char *);
void find_macro(PRE **, char *);
void replace_macro(char *, char *, PRE *);

void print(PRE *macro) {
    while (macro) {
        printf("%s --> %s\n", macro->name, macro->def);
        macro = macro->next;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("USAGE : ./a.out file\n");
        return 0;
    }

    FILE *cf = fopen(argv[1], "r");
    if (!cf) {
        perror("Failed to open file");
        return 1;
    }

    fseek(cf, 0, SEEK_END);
    long f_lent = ftell(cf);
    fseek(cf, 0, SEEK_SET);

    char *file_storage = malloc(f_lent + 1);
    if (!file_storage) {
        perror("Failed to allocate memory");
        fclose(cf);
        return 1;
    }

    fread(file_storage, 1, f_lent, cf);
    file_storage[f_lent] = '\0';
    fclose(cf);

    char *header = "include";
    char *header_name = malloc(100);
    char *exe_file = malloc(350000);
    exe_file[0] = '\0';

    PRE *head = NULL;

    int header_length = strlen(header);
    long i, j;

    for (i = 0; file_storage[i]; i++) {
        if (strncmp(file_storage + i, header, header_length) == 0) {
            i += header_length;

            while (file_storage[i] == ' ' || file_storage[i] == '\t') i++;

            char delimiter = file_storage[i];
            if (delimiter == '<' || delimiter == '"') {
                i++;
                for (j = 0; file_storage[i] != delimiter && file_storage[i] != '>'; j++, i++) {
                    header_name[j] = file_storage[i];
                }
                header_name[j] = '\0';
                file_add(header_name, 'h', &exe_file);
                i++;
            }
        }
    }

    file_add(argv[1], 'c', &exe_file);
    find_macro(&head, exe_file);
    remove_cmd(exe_file);
    replace_macro(argv[1],exe_file,head);
    print(head);
    printf("%s\n", exe_file);

    free(file_storage);
    free(header_name);
    free(exe_file);
    return 0;
}

void file_add(char *file_n, char file, char **exe_file) {
    char file_name[100];
    if (file == 'h') {
        snprintf(file_name, sizeof(file_name), "/usr/include/%s", file_n);
    } else {
        strcpy(file_name, file_n);
    }

    FILE *fd = fopen(file_name, "r");
    if (!fd) {
        perror("Failed to open file");
        printf("%s\n", file_name);
        return;
    }

    fseek(fd, 0, SEEK_END);
    int length = ftell(fd);
    fseek(fd, 0, SEEK_SET);

    char *temp = malloc(length + 1);
    if (!temp) {
        perror("Failed to allocate memory");
        fclose(fd);
        return;
    }

    fread(temp, 1, length, fd);
    temp[length] = '\0';
    fclose(fd);

    size_t current_length = strlen(*exe_file);
    if (current_length + length >= 350000) {
        *exe_file = realloc(*exe_file, current_length + length + 1);
        if (!*exe_file) {
            perror("Failed to reallocate memory");
            free(temp);
            return;
        }
    }

    strcat(*exe_file, temp);
    free(temp);
}

void remove_cmd(char *file) {
    long i, j = 0;
    char *exe_file = malloc(350000);
    exe_file[0] = '\0';

    for (i = 0; file[i]; i++) {
        if (strncmp(file + i, "//", 2) == 0) {
            while (file[i++] != '\n'); i++;
        } else if (strncmp(file + i, "/*", 2) == 0) {
            while (strncmp(file + i, "*/", 2) != 0) {
                i++;
            }
            i += 2;
        } else if (!strncmp("#include", file + i, 8)) {
            i += 8;
            while (file[i++] != '\n'); i++;
        } 
	while(file[i]=='\t') i++;
	 
        exe_file[j++] = file[i];
    }

    exe_file[j] = '\0';
    strcpy(file, exe_file);
    free(exe_file);
}

void find_macro(PRE **macro, char *file) {
    long i, j;

    for (i = 0; file[i]; i++) {
        if (file[i] == '#') {
            i++;
            if (file[i] == ' ' || file[i] == '\t') i++;

            if (strncmp(file + i, "define", 6) == 0) {
                i += 6;

                while (file[i] == ' ' || file[i] == '\t') i++;

                PRE *temp = (PRE *)malloc(sizeof(PRE));
                if (!temp) {
                    perror("Failed to allocate memory for macro");
                    return;
                }

                for (j = 0; file[i] != '\t' && file[i] != ' ' && file[i] != '\n' && file[i] != '\0' && j < sizeof(temp->name) - 1; j++, i++) {
                    if (file[i] == ',') {
                        temp->name[j++] = file[i];
                        while (file[i + 1] == ' ' || file[i + 1] == '\t') i++;
                    }
                    temp->name[j] = file[i];
                }
                temp->name[j] = '\0';
                while (file[i] == ' ' || file[i] == '\t') i++;
                for (j = 0; file[i] != '\t' && file[i] != '\n' && file[i] != '\0' && j < sizeof(temp->def) - 1; j++, i++) {
                    if (file[i] == ',') {
                        temp->def[j++] = file[i];
                        while (file[i + 1] == ' ' || file[i + 1] == '\t') i += 2;
                    }
                    temp->def[j] = file[i];
                }
                temp->def[j] = '\0';
                temp->next = NULL;

                if (*macro == NULL) {
                    *macro = temp;
                } else {
                    PRE *last = *macro;
                    while (last->next != NULL) {
                        last = last->next;
                    }
                    last->next = temp;
                }
            }
        }
    }
}

void replace_macro(char *file_n, char *file, PRE *macro) {
    char file_name[100];
    strncpy(file_name, file_n, strlen(file_n) - 1);
    strcat(file_name,"i");

    FILE *fd = fopen(file_name, "w");
    if (!fd) {
        perror("Failed to open file");
        printf("%s\n", file_name);
        return;
    }

    long i;

    for (i = 0; file[i]; i++) {
        if (strncmp(file + i, "int main", 8) == 0) {
            i += 8;

            while (file[i] != '{') i++;
            fputs("int main {", fd);

            for (; file[i]; i++) {
                PRE *current_macro = macro;
                int macro_found = 0;

                while (current_macro) {
                    if (strncmp(file + i, current_macro->name, strlen(current_macro->name)) == 0) {
			//if((file[i-1]!=' ' || file[i-1]!='\t') && (file[i+strlen(current_macro->name) + 1]!= ' ' || file[i+strlen(current_macro->name) + 1]!= '\t')) continue;
                        fputs(current_macro->def, fd);
                        i += strlen(current_macro->name) - 1;
                        macro_found = 1;
                        break;
                    }
                    current_macro = current_macro->next;
                }

                if (!macro_found) {
                    fputc(file[i], fd);
                }
            }
            break;
        }
        fputc(file[i], fd);
    }

    fclose(fd);
}
