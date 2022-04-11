#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

#define NAME_SIZE 100
#define BG_SIZE 15
#define ADDRESS_SIZE 100
#define CONTACT_SIZE 25
#define donarPath "data/donar.txt"

FILE *donarRecord = NULL;

// donar information
typedef struct Donar
{
    char NAME[NAME_SIZE];
    char BLOODGROUP[BG_SIZE];
    char ADDRESS[ADDRESS_SIZE];
    char CONTACTNO[CONTACT_SIZE];
} Donar;

// open file
void openFile(const char *m)
{
    donarRecord = fopen(donarPath, m);
}

// ask to return main menu
void askToReturnMainMenu()
{
    puts("\n\t");
    system("echo Press any key to return");
    getch();
}

void status(char st[])
{
    system("cls");
    puts("****************************************************");
    printf("\n\t%s\n\n", st);
    puts("****************************************************");
    Sleep(800);
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
    status("****The Data Is successfully Stored****");
}

void searchResult(char bg[])
{
    int count = 1, isDonarExist = 0;
    Donar temInfo;
    openFile("r");
    printf("   %-35s%-20s%-30s%-20s\n", "Name", "Blood Group", "Address", "Contact no.");
    puts("----------------------------------------------------------------------------------------------------");
    while (fread(&temInfo, sizeof(Donar), 1, donarRecord) == 1)
    {
        if (!strcmp(temInfo.BLOODGROUP, bg))
        {
            printf("%d. %-35s%-20s%-30s%-20s\n", count++, temInfo.NAME, temInfo.BLOODGROUP, temInfo.ADDRESS, temInfo.CONTACTNO);
            puts("----------------------------------------------------------------------------------------------------");
            isDonarExist++;
        }
    }
    if (isDonarExist == 0)
    {
        system("cls");
        puts("\t---------------------------------------------------------------------");
        printf("\n\t\t\t\tData Not Found\n\n");
        puts("\t---------------------------------------------------------------------");
    }
}

void searchBloodGroup()
{
    int inp;
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
    printf("\n\tInter Keyword:");
    scanf("%d", &inp);
    getchar();
    system("cls");
    printf("\t *****************************************\n");
    printf("\t ****** Help Me To Find Blood Doner ******\n");
    printf("\t *****************************************\n");

    switch (inp)
    {
    case 1:
        searchResult("A+");
        break;
    case 2:
        searchResult("A-");

        break;
    case 3:

        searchResult("B+");
        break;

    case 4:
        searchResult("B-");
        break;
    case 5:
        searchResult("AB+");

        break;
    case 6:
        searchResult("AB-");

        break;
    case 7:
        searchResult("O+");

        break;
    case 8:
        searchResult("O-");

        break;

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
    fclose(donarRecord);
    getch();
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
    system("color F0");
    while (1)
    {
        system("md data");
        mainMenu();
        printf("\n\tInter Keyword:");
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
            system("cls");
            system("exit");
            return 0;
            break;
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