#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

#define NAME_SIZE 100
#define BG_SIZE 15
#define ADDRESS_SIZE 100
#define CONTACT_SIZE 25
#define DATE_SIZE 20
#define HOMEDISTRICT_SIZA 20
#define STUDENTID_SIZE 10
#define DEPARTMENT_SIZE 10

#define donarPath "data/donar.txt"

FILE *donarRecord = NULL;

// donar information
typedef struct Donar
{
    char NAME[NAME_SIZE];
    char BLOODGROUP[BG_SIZE];
    char ADDRESS[ADDRESS_SIZE];
    char CONTACTNO[CONTACT_SIZE];
    char DATE[DATE_SIZE];
    char HOMEDISTRICT[HOMEDISTRICT_SIZA];
    char STUDENTID[STUDENTID_SIZE];
    char DEPARTMENT[DEPARTMENT_SIZE];
} Donar;

// Cursor position change
void gotoxy(short x, short y)
{
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// open file
void openFile(const char *m)
{
    donarRecord = fopen(donarPath, m);
}

// ask to return main menu
void askToReturnMainMenu()
{
    puts("\n\t");
    system("echo Press any key to return Main Menu");
    getch();
}

void status(char st[])
{
    system("cls");
    printf("\n\n\n\n\t\t\t\t\t----------------------------------------------------------------------------------\n");
    printf("\n\t\t\t\t\t\t\t\t%s\n\n", st);
    printf("\t\t\t\t\t----------------------------------------------------------------------------------\n");
    Sleep(800);
}
void deleteSingleDonarinfo()
{
    getchar();
    system("cls");
    char sample[CONTACT_SIZE];
    printf("Get Donar Contart No :");
    gets(sample);
    openFile("r");
    Donar tmpDonar[500];
    int indx = 0;
    while (fread(&tmpDonar[indx], sizeof(Donar), 1, donarRecord) == 1)
    {
        if (!strcmp(tmpDonar[indx].CONTACTNO, sample))
        {
            puts("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
            printf("   %-35s%-20s%-20s%-15s%-20s%-30s%-20s%-15s\n", tmpDonar[indx].NAME, tmpDonar[indx].STUDENTID, tmpDonar[indx].DEPARTMENT, tmpDonar[indx].BLOODGROUP, tmpDonar[indx].ADDRESS, tmpDonar[indx].HOMEDISTRICT, tmpDonar[indx].CONTACTNO, tmpDonar[indx].DATE);
            puts("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
        }
        indx++;
    }
    fclose(donarRecord);
    openFile("w");
    for (int i = 0; i < indx; i++)
    {
        if (strcmp(sample, tmpDonar[i].CONTACTNO))
        {
            fwrite(&tmpDonar[i], sizeof(Donar), 1, donarRecord);
        }
    }
    fclose(donarRecord);
    getch();
}
void mainMenu()
{
    system("cls");
    printf("\t ----------------------------------------------------------------------------------\n");
    printf("\t\t\t\t Welcome To 'BSMRSTU'  Blood Bank\n");
    printf("\t ----------------------------------------------------------------------------------\n\n\n");
    printf("\t\t\t\tPress 1 to insert donar info \n");
    printf("\t\t\t\tPress 2 to search by blood group \n");
    printf("\t\t\t\tPress 3 to search by student ID \n");
    printf("\t\t\t\tPress 4 to search by Department Name \n");
    printf("\t\t\t\tPress 5 to show all donar \n");
    printf("\t\t\t\tpress 6 to edit donar information \n");
    printf("\t\t\t\tpress 7 to delete donar \n");
    printf("\t\t\t\tpress 8 to close program \n");
}

void toUpperCase(char *st)
{
    int index = 0;
    while (st[index] != '\0')
    {
        st[index] = toupper(st[index]);
    }
}

void insertData()
{
    getchar();
    Donar userData;
    printf("\t ------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\tGive Blood To Save Life\n");
    printf("\t ------------------------------------------------------------------------------------\n");
    printf("\t\tNAME: ");
    gets(userData.NAME);
    puts("");
    printf("\t\tSTUDENT ID: ");
    gets(userData.STUDENTID);
    puts("");
    printf("\t\tDEPARTMENT: ");
    gets(userData.DEPARTMENT);
    puts("");
    printf("\t\tBLOOD GROUP: ");
    gets(userData.BLOODGROUP);
    // toUpperCase(&userData.BLOODGROUP);
    puts("");
    printf("\t\tADDRESS: ");
    gets(userData.ADDRESS);
    puts("");
    printf("\t\tHOME DISTRICT: ");
    gets(userData.HOMEDISTRICT);
    puts("");
    printf("\t\tCONTACT NO: ");
    gets(userData.CONTACTNO);
    puts("");
    printf("\t\tDATE Of LAST DONATION: ");
    gets(userData.DATE);
    puts("");

    openFile("a");
    fwrite(&userData, sizeof(Donar), 1, donarRecord);
    fclose(donarRecord);
    status("The Data Is successfully Stored");
}

void searchResult(char bg[])
{
    int count = 1, isDonarExist = 0;
    Donar temInfo;
    openFile("r");
    printf("   %-35s%-20s%-20s%-15s%-20s%-30s%-20s%-15s\n", "Name", "Student_ID", "Department", "Blood Group", "Address", "Home_District", "Contact no.", "Date");
    puts("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    while (fread(&temInfo, sizeof(Donar), 1, donarRecord) == 1)
    {
        if (!strcmp(temInfo.BLOODGROUP, bg))
        {
            printf("%d. %-35s%-20s%-20s%-15s%-20s%-30s%-20s%-15s\n", count++, temInfo.NAME, temInfo.STUDENTID, temInfo.DEPARTMENT, temInfo.BLOODGROUP, temInfo.ADDRESS, temInfo.HOMEDISTRICT, temInfo.CONTACTNO, temInfo.DATE);
            puts("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
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

void searchResultStudintID(char id[])
{

    int count = 1, isDonarExist = 0;
    Donar temInfo;
    openFile("r");
    printf("   %-35s%-20s%-20s%-15s%-20s%-30s%-20s%-15s\n", "Name", "Student_ID", "Department", "Blood Group", "Address", "Home_District", "Contact no.", "Date");
    puts("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    while (fread(&temInfo, sizeof(Donar), 1, donarRecord) == 1)
    {
        if (!strcmp(temInfo.STUDENTID, id))
        {
            printf("%d. %-35s%-20s%-20s%-15s%-20s%-30s%-20s%-15s\n", count++, temInfo.NAME, temInfo.STUDENTID, temInfo.DEPARTMENT, temInfo.BLOODGROUP, temInfo.ADDRESS, temInfo.HOMEDISTRICT, temInfo.CONTACTNO, temInfo.DATE);
            puts("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
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
    system("pause");
}
void searchResultDepartmentName(char dep[])
{

    int count = 1, isDonarExist = 0;
    Donar temInfo;
    openFile("r");
    printf("   %-35s%-20s%-20s%-15s%-20s%-30s%-20s%-15s\n", "Name", "Student_ID", "Department", "Blood Group", "Address", "Home_District", "Contact no.", "Date");
    puts("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    while (fread(&temInfo, sizeof(Donar), 1, donarRecord) == 1)
    {
        if (!strcmp(temInfo.DEPARTMENT, dep))
        {
            printf("%d. %-35s%-20s%-20s%-15s%-20s%-30s%-20s%-15s\n", count++, temInfo.NAME, temInfo.STUDENTID, temInfo.DEPARTMENT, temInfo.BLOODGROUP, temInfo.ADDRESS, temInfo.HOMEDISTRICT, temInfo.CONTACTNO, temInfo.DATE);
            puts("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
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
    system("pause");
}
void searchBloodGroup()
{
    int inp;
    printf("\t ---------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\tHelp Me To Find Blood Doner\n");
    printf("\t ---------------------------------------------------------------------------------------\n");
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
    printf("\t\t\t\t\t\t\t------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\t\t\t\t\t\tShow Result For Blood Group\n");
    printf("\t\t\t\t\t\t\t------------------------------------------------------------------------------------------\n\n\n");

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
void studentId()
{
    char id[STUDENTID_SIZE];
    printf("\n\n\t\tInter Search Id:");
    scanf("%s", &id);
    system("cls");
    puts("\t\t\t\t\t\t--------------------------------------------------------------------------------------------------------------");
    puts("\t\t\t\t\t\t\t\t\t\t\tShow Result For Student_ID");
    puts("\t\t\t\t\t\t--------------------------------------------------------------------------------------------------------------\n\n");
    searchResultStudintID(id);
}
void departmentName()
{
    char dep[DEPARTMENT_SIZE];
    printf("\n\n\t\tInter Department Name:");
    scanf("%s", &dep);
    system("cls");
    puts("\t\t\t\t\t\t--------------------------------------------------------------------------------------------------------------");
    puts("\t\t\t\t\t\t\t\t\t\t\tShow Result For Department Name");
    puts("\t\t\t\t\t\t--------------------------------------------------------------------------------------------------------------\n\n");
    searchResultDepartmentName(dep);
}
void showAllDonar()
{
    puts("\t\t\t\t\t--------------------------------------------------------------------------------------------------------------");
    puts("\t\t\t\t\t\t\t\t\t\tShow All Donar Information");
    puts("\t\t\t\t\t--------------------------------------------------------------------------------------------------------------\n\n");
    int count = 1;
    openFile("r");
    Donar tmpDonar;
    printf("   %-35s%-20s%-20s%-15s%-20s%-30s%-20s%-15s\n", "Name", "Student_ID", "Department", "Blood Group", "Address", "Home_District", "Contact no.", "Date");
    puts("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    while (fread(&tmpDonar, sizeof(Donar), 1, donarRecord) == 1)
    {
        printf("%d. %-35s%-20s%-20s%-15s%-20s%-30s%-20s%-15s\n", count++, tmpDonar.NAME, tmpDonar.STUDENTID, tmpDonar.DEPARTMENT, tmpDonar.BLOODGROUP, tmpDonar.ADDRESS, tmpDonar.HOMEDISTRICT, tmpDonar.CONTACTNO, tmpDonar.DATE);
        puts("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    }
    fclose(donarRecord);
    askToReturnMainMenu();
}

void editDonarInfo()
{
    openFile("r");
    int count = 1;
    int serialNumber = 0;
    int index = 0;
    Donar *editDonar = (Donar *)calloc(1, sizeof(Donar));
    printf("   %-35s%-20s%-20s%-15s%-20s%-30s%-20s%-15s\n", "Name", "Student_ID", "Department", "Blood Group", "Address", "Home_District", "Contact no.", "Date");
    puts("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    while (fread(&editDonar[index], sizeof(Donar), 1, donarRecord) == 1)
    {
        editDonar = (Donar *)realloc(editDonar, (index + 2) * sizeof(Donar));
        printf("%d. %-35s%-20s%-20s%-15s%-20s%-30s%-20s%-15s\n", count++, editDonar[index].NAME, editDonar[index].STUDENTID, editDonar[index].DEPARTMENT, editDonar[index].BLOODGROUP, editDonar[index].ADDRESS, editDonar[index].HOMEDISTRICT, editDonar[index].CONTACTNO, editDonar[index].DATE);
        index++;
        puts("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    }
    fclose(donarRecord);
    printf("Put the serial number: ");
    scanf("%d", &serialNumber);
    fflush(stdin);
    if (serialNumber >= 1 && serialNumber <= index)
    {
        system("cls");
        puts("================================================================================================================================================================================");
        printf("%d. %-35s%-20s%-20s%-15s%-20s%-30s%-20s%-15s\n", serialNumber, editDonar[serialNumber - 1].NAME, editDonar[serialNumber - 1].STUDENTID, editDonar[serialNumber - 1].DEPARTMENT, editDonar[serialNumber - 1].BLOODGROUP, editDonar[serialNumber - 1].ADDRESS, editDonar[serialNumber - 1].HOMEDISTRICT, editDonar[serialNumber - 1].CONTACTNO, editDonar[serialNumber - 1].DATE);
        puts("================================================================================================================================================================================");
        printf("Are you sure want to edit (y / n): ");
        char ch;
        scanf("%c", &ch);
        fflush(stdin);
        if (ch == 'Y' || ch == 'y')
        {
            Donar newDonarData;
            puts("\n\n\t\t\t\tIf you don't want to update any field\n\t\t\t\t\t  Leave that blank.");
            gotoxy(35, 10);
            printf("%-16s :\n", "Name");
            gotoxy(35, 12);
            printf("%-16s :\n", "Student ID");
            gotoxy(35, 14);
            printf("%-16s :\n", "Department");
            gotoxy(35, 16);
            printf("%-16s :\n", "Blood group");
            gotoxy(35, 18);
            printf("%-16s :\n", "Address");
            gotoxy(35, 20);
            printf("%-16s :\n", "Home district");
            gotoxy(35, 22);
            printf("%-16s :\n", "Contact no");
            gotoxy(35, 24);
            printf("%-16s :\n", "Last donate date");

            gotoxy(55, 10);
            gets(newDonarData.NAME);
            gotoxy(55, 12);
            gets(newDonarData.STUDENTID);
            gotoxy(55, 14);
            gets(newDonarData.DEPARTMENT);
            gotoxy(55, 16);
            gets(newDonarData.BLOODGROUP);
            gotoxy(55, 18);
            gets(newDonarData.ADDRESS);
            gotoxy(55, 20);
            gets(newDonarData.HOMEDISTRICT);
            gotoxy(55, 22);
            gets(newDonarData.CONTACTNO);
            gotoxy(55, 24);
            gets(newDonarData.DATE);

            if (strlen(newDonarData.NAME) > 0)
            {
                strcpy(editDonar[serialNumber - 1].NAME, newDonarData.NAME);
            }
            if (strlen(newDonarData.STUDENTID) > 0)
            {
                strcpy(editDonar[serialNumber - 1].STUDENTID, newDonarData.STUDENTID);
            }
            if (strlen(newDonarData.DEPARTMENT) > 0)
            {
                strcpy(editDonar[serialNumber - 1].DEPARTMENT, newDonarData.DEPARTMENT);
            }
            if (strlen(newDonarData.BLOODGROUP) > 0)
            {
                strcpy(editDonar[serialNumber - 1].BLOODGROUP, newDonarData.BLOODGROUP);
            }
            if (strlen(newDonarData.ADDRESS) > 0)
            {
                strcpy(editDonar[serialNumber - 1].ADDRESS, newDonarData.ADDRESS);
            }
            if (strlen(newDonarData.HOMEDISTRICT) > 0)
            {
                strcpy(editDonar[serialNumber - 1].HOMEDISTRICT, newDonarData.HOMEDISTRICT);
            }
            if (strlen(newDonarData.CONTACTNO) > 0)
            {
                strcpy(editDonar[serialNumber - 1].CONTACTNO, newDonarData.CONTACTNO);
            }
            if (strlen(newDonarData.DATE) > 0)
            {
                strcpy(editDonar[serialNumber - 1].DATE, newDonarData.DATE);
            }

            openFile("w");
            for (int i = 0; i < index; i++)
            {
                fwrite(&editDonar[i], sizeof(Donar), 1, donarRecord);
            }
            fclose(donarRecord);
            status("Successfully updated");
        }
        else
        {
            status("Abort editing");
        }
    }
    else
    {
        status("Not found");
        return;
    }
    system("pause");
}

int main()
{
    system("cls");
    system("color 20");
    while (1)
    {
        system("md data");
        mainMenu();
        printf("\n\t\t\tInter Keyword:");
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
            studentId();
            break;
        case 4:
            system("cls");
            departmentName();
            break;
        case 5:
            system("cls");
            showAllDonar();
            break;
        case 6:
            system("cls");
            editDonarInfo();
            break;
        case 7:
            deleteSingleDonarinfo();
            break;
        case 8:
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
