#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pre {
    char name[30];
    char def[1000];
    struct pre *next;
} PRE;

void  file_add(char *,char ,char **);
void remove_cmd(char *);
void replace_macro(char *,char *);
void find_macro(PRE **,char *);

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
    char *define = "define";
    char *header_name = malloc(100);
    char temp_name[30];
    char temp_def[1000];
    char *exe_file = malloc(350000); 
    exe_file[0] = '\0';

    PRE *head=NULL;

    int header_length = strlen(header);
    int define_length = strlen(define);
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
              //  printf("Header: %s\n", header_name);
                i++;
            }
        } else if (strncmp(file_storage + i, define, define_length) == 0) {
            i += define_length;

            while (file_storage[i] == ' ' || file_storage[i] == '\t') i++;

            for (j = 0; file_storage[i] != ' ' && file_storage[i] != '\n' && file_storage[i] != '\0'; j++, i++) {
                if (j < sizeof(temp_name) - 1) {
                    temp_name[j] = file_storage[i];
                }
            }
            temp_name[j] = '\0';

            while (file_storage[i] == ' ' || file_storage[i] == '\t') i++;

            for (j = 0; file_storage[i] != '\n' && file_storage[i] != '\0'; j++, i++) {
                if (j < sizeof(temp_def) - 1) {
                    temp_def[j] = file_storage[i];
                }
            }
            temp_def[j] = '\0';

            //printf("%s ---> %s\n", temp_name, temp_def);
        }
    }

	file_add(argv[1], 'c', &exe_file);
	remove_cmd(exe_file);
	find_macro(&head,exe_file);
	print(head);
	//replace_macro(exe_file,argv[1]);
	    free(file_storage);
	    free(header_name);
	    //printf("%s\n", exe_file);
	    free(exe_file);
	    return 0;
}


void file_add(char *file_n, char file, char **exe_file) {
    char file_name[100];
    if(file=='h'){
		snprintf(file_name, sizeof(file_name), "/usr/include/%s", file_n);
	}else{
	      strcpy(file_name,file_n);
	}

    FILE *fd = fopen(file_name, "r");
    if (!fd) {
        perror("Failed to open file");
	printf("%s\n",file_name);
        return;
    }

    fseek(fd, 0, SEEK_END);
    int lenth = ftell(fd);
    fseek(fd, 0, SEEK_SET);

    char *temp = malloc(lenth + 1);
    if (!temp) {
        perror("Failed to allocate memory");
        fclose(fd);
        return;
    }

    fread(temp, 1, lenth, fd);
    temp[lenth] = '\0';
    fclose(fd);

    size_t current_length = strlen(*exe_file);
    if (current_length + lenth >= 350000) {
        *exe_file = realloc(*exe_file, current_length + lenth + 1);
        if (!*exe_file) {
            perror("Failed to reallocate memory");
            free(temp);
            return;
        }
    }

    strcat(*exe_file, temp);
    free(temp);
}

void remove_cmd(char *file){
	long i,j=0;
	char *exe_file = malloc(350000); 
	exe_file[0] = '\0';
	for(i=0;file[i];i++){
	 if((file[i]=='/') && (file[i+1]=='/')){
	    i++;
	    while(file[i++]!='\n');
	 }else if((file[i]=='/') && (file[i+1]=='*')){
	    i++;
    	    while (file[i] && strncmp(file + i, "*/", 2) != 0) {
		    i++;
		}
		i+=2;

	 }else if(!strncmp("#include",file+i,8)){
		i +=8;
	    while(file[i++]!='\n');
	 }

  	    exe_file[j++] = file[i];

	}

	exe_file[j] = '\0';

	strcpy(file,exe_file);
	free(exe_file);

}

void find_macro(PRE **macro, char *file) {
    long i, j = 0;
    
    for (i = 0; file[i]; i++) {
        if (strncmp(file + i, "#define", 7) == 0) {
            i += 7;

            while (file[i] == ' ' || file[i] == '\t') i++;

            PRE *temp = (PRE *)malloc(sizeof(PRE));
            if (!temp) {
                perror("Failed to allocate memory for macro");
                return;
            }

            for (j = 0; j < sizeof(temp->name) - 1 && file[i] != ' ' && file[i] != '\n' && file[i] != '\0'; j++, i++) {
	   	 temp->name[j] = file[i];
	    }
		temp->name[j] = '\0';

            while (file[i] == ' ' || file[i] == '\t') i++;

            for (j = 0; file[i] != '\n' && file[i] != '\0'; j++, i++) {
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
	    free(temp);
        }
	
    }
}


/*
void replace_macro(char *file_name,char *file){

	strncpy(file_name,filename,strlenth(file_name)-2);
	strcat(file_name,'i');

	if (strncmp(file + i, define, define_length) == 0) {
            i += define_length;

            while (file[i] == ' ' || file[i] == '\t') i++;

            for (j = 0; file[i] != ' ' && file[i] != '\n' && file[i] != '\0'; j$
                if (j < sizeof(temp_name) - 1) {
                    temp_name[j] = file[i];
                }
            }
            temp_name[j] = '\0';

            while (file[i] == ' ' || file[i] == '\t') i++;

            for (j = 0; file[i] != '\n' && file[i] != '\0'; j++, i++) {
                if (j < sizeof(temp.def) - 1) {
                    temp.def[j] = file[i];
                }
            }


	FILE *fd = fopen(file_name, "w");
	    if (!fd) {
	        perror("Failed to open file");
	        printf("%s\n",file_name);
	        return;
	    }

	for (i = 0; file[i]; i++) {
        if (strncmp(file + i, "main", 4) == 0) {
          if (strncmp(file + i, "", 4) == 0) {

            fputs(, fd);
            i += exist_length - 1;
        } else {
            fputc(file[i], fo);
        }
    }

}
*/
