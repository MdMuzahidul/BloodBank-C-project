#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

#define NAME_SIZE 100
#define BG_SIZE 5
#define ADDRESS_SIZE 100
#define CONTACT_SIZE 15
#define donarPath "data/donar.txt"

FILE *donarRecord = NULL;

typedef struct Donar
{
    char NAME[NAME_SIZE];
    char BLOODGROUP[BG_SIZE];
    char ADDRESS[ADDRESS_SIZE];
    char CONTACTNO[CONTACT_SIZE];
} Donar;

void openFile(const char *m)
{
    donarRecord = fopen(donarPath, m);
}

// ask to return main menu
void askToReturnMainMenu()
{
    system("echo Press any key to return");
    getch();
}

void mainMenu()
{
    system("cls");
    printf("\t **************************************\n");
    printf("\t ******* Welcome To  Blood Bank *******\n");
    printf("\t **************************************\n");
    printf("\t\tPress 1 to insert donar info \n");
    printf("\t\tPress 2 to search by blood group \n");
    printf("\t\tPress 3 to show all donar \n");
    printf("\t\tPress 4 to delete data \n");
    printf("\t\tpress 5 to close program \n");
}
void insertData()
{
    getchar();
    Donar userData;
    printf("\t *************************************\n");
    printf("\t ****** Give Blood To Save Life ******\n");
    printf("\t *************************************\n");
    printf("\t\tNAME: ");
    gets(userData.NAME);
    puts("");
    printf("\t\tBLOOD GROUP: ");
    gets(userData.BLOODGROUP);
    puts("");
    printf("\t\tADDRESS: ");
    gets(userData.ADDRESS);
    puts("");
    printf("\t\tCONTACT NO: ");
    gets(userData.CONTACTNO);
    puts("");

    openFile("a");
    fwrite(&userData, sizeof(Donar), 1, donarRecord);
    fclose(donarRecord);
}
void searchBloodGroup()
{

    printf("\t *****************************************\n");
    printf("\t ****** Help Me To Find Blood Doner ******\n");
    printf("\t *****************************************\n");
    printf("\t\t 1. A(+ev)\n");
    printf("\t\t 2. A(-ev)\n");
    printf("\t\t 3. B(+ev)\n");
    printf("\t\t 4. B(-ev)\n");
    printf("\t\t 5. AB(+ev)\n");
    printf("\t\t 6. AB(-ev)\n");
    printf("\t\t 7. O(+ev)\n");
    printf("\t\t 8. O(-ev)\n");
}
void deleteData()
{
    system("rmdir /s data");
    puts("Data deleted");
    getch();
}

void showAllDonar()
{
    int count = 1;
    openFile("r");
    Donar tmpDonar;
    printf("   %-35s%-20s%-30s%-20s\n", "Name", "Blood Group", "Address", "Contact no.");
    puts("----------------------------------------------------------------------------------------------------");
    while (fread(&tmpDonar, sizeof(Donar), 1, donarRecord) == 1)
    {
        printf("%d. %-35s%-20s%-30s%-20s\n", count++, tmpDonar.NAME, tmpDonar.BLOODGROUP, tmpDonar.ADDRESS, tmpDonar.CONTACTNO);
        puts("----------------------------------------------------------------------------------------------------");
    }
    fclose(donarRecord);
    askToReturnMainMenu();
}

int main()
{
    while (1)
    {
        system("md data");
        mainMenu();
        int tag;
        scanf("%d", &tag);
        switch (tag)
        {
        case 1:
            system("cls");
            insertData();
            break;
        case 2:
            system("cls");
            searchBloodGroup();
            break;
        case 3:
            system("cls");
            showAllDonar();
            break;
        case 4:
            deleteData();
            break;
        case 5:
            return 0;
        default:
            system("cls");
            puts("\t\t--------------------------");
            puts("\t\t      Invalid command");
            puts("\t\tPlease inter right command");
            puts("\t\t--------------------------");
            Sleep(1000);
            system("cls");
            break;
        }
    }
}