/*
Name: Lara Foqaha
ID: 1220071
Section: 5
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct DistrictNode;
struct TownNode;
typedef struct DistrictNode* ptrDis;
typedef struct TownNode* ptrT;

struct TownNode
{
    char townName[50];
    int population;
    ptrT next;
    ptrT previous;
};
typedef ptrT TownsList;

struct DistrictNode
{
    char districtName[50];
    int total_population;
    ptrT townsHeader; // pointer to the header in the district
    ptrDis next;
    ptrDis previous;
};
typedef ptrDis DistrictsList;
DistrictsList DList; //global linked list for districts

void insertDistrict (DistrictsList L, char name[] );
DistrictsList createDistrictsList ();
TownsList createTownsList ();
ptrDis findDistrict (char name[], DistrictsList L);
ptrT findTown (char name [], ptrDis distict);
void addTown (ptrDis district, char name[], int population);
void displayTownsList (ptrDis district);
void loadInputFile ();
void printInfo ();
void menu();
int getMaxDistrictLength (DistrictsList L);
void makeEqualLength (DistrictsList L, int maxLength);
void radixSortDistricts(DistrictsList L);
void cleanStringsFromStar (DistrictsList L);
void DeleteTown (char distName[], char townName[]);
void sortTowns(DistrictsList L);
void deleteDistrict (char name[], DistrictsList L);
void calculatePopulation(DistrictsList L);
void printDistrictsAndPop (DistrictsList L);
void saveToOutputFile();

int main()
{
    DList = createDistrictsList();
    int option;
    int loadedFlag = 0,isSortedDis=0, isSortedT=0;
    do
    {
        menu();
        scanf("%d",&option);
        getchar();
        printf("\n");

        switch (option)
        {
        case 1:
           loadInputFile();
           loadedFlag = 1;
            break;

        case 2: //printing info without sorting
            if (loadedFlag == 1)
            {
                if (isSortedDis == 0 && isSortedT == 0)
                    printInfo();
                else
                      printf("Informations have been sorted.\n\n");
            }
            else
                printf ("Please load the file first (choose option 1).\n\n");
            break;

        case 3:
            if (loadedFlag == 1)
           {
            radixSortDistricts(DList);
            isSortedDis=1;
            printf("Districts have been sorted.\n\n");
           }
           else
                printf("The list is empty. Please load the file first.\n\n");
            break;

        case 4:
            if (loadedFlag == 1)
            {
                sortTowns(DList);
                isSortedT = 1;
                printf("Towns have been sorted.\n\n");
            }
            else
                printf("The list is empty. Please load the file first.\n\n");

            break;

        case 5: // print sorted info
            if (loadedFlag == 1)
            {
                //if they are not already sorted, sort them
                if (isSortedDis == 0)
                    {
                        radixSortDistricts(DList);
                        isSortedDis = 1;
                    }

                if (isSortedT == 0)
                {
                    sortTowns(DList);
                    isSortedT =1;
                }
                printInfo();
            }
            else
                printf("The list is empty. Please load the file first.\n\n");

            break;

        case 6:
            if (loadedFlag == 1)
            {
                if (isSortedDis == 0)
                    printf("Please sort the list first (Choose option 3).\n\n");
                else
            {
                printf("Enter the name of the new district.\n");
                char name[50];
                gets(name);
                if (findDistrict(name,DList) != NULL)
                    printf("District %s already exists.\n\n",name);
                else
                {
                insertDistrict(DList,name);
                radixSortDistricts(DList);
                printf("District %s is inserted and sorted.\n\n",name);
                }
           }

            }
            else
                printf("Please load the file first.\n\n");

            break;

        case 7:
            if (loadedFlag == 1)
            {
                printf("Enter the name of the district to add a town to.\n");
                char distName[50];
                gets(distName);
                ptrDis district = findDistrict(distName,DList); // to check if the district exists
                if (district == NULL)
                    printf("District %s does not exist.\n\n",distName);
                else
                {
                    printf("Enter the name of the town you want to add.\n");
                    char tName[50];
                    gets(tName);
                    if (findTown(tName,district) != NULL) // to check if the town exists or not
                        printf("Town %s already exists.\n\n",tName);
                    else
                    {
                        printf("Enter the number of population for the town.\n");
                        int population;
                        scanf("%d",&population);
                        getchar();
                        addTown(district,tName,population);
                        sortTowns(DList);
                        printf("Town %s with population %d has been added to district %s.\n\n",tName,population,distName);
                    }

                }
            }
            else
                printf("Please load the file first.\n\n");
            break;

        case 8:
            if (loadedFlag == 1)
            {
                printf("Enter the name of the district to delete from.\n");
            char distName[50];
            gets(distName);
            if (findDistrict(distName,DList) == NULL)
                printf("District %s does not exist.\n\n",distName);
            else
            {
                printf("Enter the name of the town you want to delete.\n");
                char tName[50];
                gets(tName);
                if(findTown(tName,findDistrict(distName,DList)) == NULL)
                    printf("Town %s does not exist.\n\n",tName);
                else
                {
                    DeleteTown(distName,tName);
                    printf("Town %s has been deleted from %s.\n\n",tName,distName);
                }
            }
            }
            else
                printf("Please load the file first.\n\n");
            break;

        case 9:
            if (loadedFlag == 1)
            {
                printf("Enter the name of the district you want to delete.\n");
                char name[50];
                gets(name);
                deleteDistrict(name,DList);
                printf("\n");
            }
            else
                printf("Please load the file first.\n\n");

            break;

        case 10:
            if (loadedFlag == 1)
            {
                calculatePopulation(DList);
            }
            else
                printf("Please load the file first.\n\n");

            break;

        case 11:
            if (loadedFlag == 1)
            {
                printDistrictsAndPop(DList);
                printf("\n");
            }
            else
                printf("Please load the file first.\n\n");
            break;

        case 12:
            if (loadedFlag == 1)
            {
                printf("Enter the name of the town's district.\n");
                char dName[50];
                gets(dName);
                ptrDis dist = findDistrict(dName,DList);
                if (dist == NULL)
                    printf("District %s does not exist.\n\n",dName);
                else
                {
                    printf("Enter the name of the town to change its population.\n");
                    char tName[50];
                    gets(tName);
                    ptrT town = findTown(tName, dist);
                    if (town == NULL)
                        printf("Town %s does not exist.\n\n",tName);
                    else
                    {
                        printf("Enter the new population of town %s.\n",tName);
                        int pop;
                        scanf("%d",&pop);
                        getchar();
                        if (pop > town->population)
                            dist->total_population = dist->total_population + (pop - town->population);
                        else if (pop < town->population)
                            dist->total_population = dist->total_population - (town->population - pop);
                        town->population = pop;
                        printf("Town %s now has a population of %d\n\n",tName,town->population);
                    }
                }
            }
            else
                printf("Please load the file first.\n\n");
            break;
        case 13:
            if (loadedFlag == 1)
            {
                saveToOutputFile();
                printf("Information saved to file sorted_districts.txt\n\n");
            }
            else
                printf("Please load the file first.\n\n");
            break;

        case 14:
            printf("Exited.\n");
            break;

        default:
            printf("No such option, try again.\n\n");

        }
    }
    while (option != 14);

    return 0;
}

DistrictsList createDistrictsList () // creates an empty districts list with L as its dummy header
{
    DistrictsList L = (DistrictsList)malloc(sizeof(struct DistrictNode));
    if (L == NULL)
        printf ("Out of memory.\n");
    L ->next = NULL;
    L ->previous = NULL;
    return L;
}
TownsList createTownsList () // creates an empty towns list
{
    TownsList L = (TownsList)malloc(sizeof(struct TownNode));
    if (L == NULL)
        printf("Out of memory.\n");
    L->next = NULL;
    L->previous = NULL;
    return L;
}
void insertDistrict (DistrictsList L, char name[] ) // to add a new district to the linked list
{
    if (L == NULL)
    {
        printf("ERROR: the list L is NULL.\n");
        return; // Exits the function if L is null
    }

    ptrDis existingDistrict = findDistrict(name, L); // if the district does not exist, it will return NULL
    if (existingDistrict != NULL) // if the district exists, exit the function
        return;

    ptrDis newDistrictNode = (ptrDis)malloc(sizeof(struct DistrictNode));
    if (newDistrictNode == NULL)
    {
        printf("Out of memory.\n");
        return; // Exits the function if the memory allocation fails
    }
    strcpy(newDistrictNode->districtName, name);
    newDistrictNode ->total_population =0;

    if (L->next == NULL) // if the list is empty, add the district after the header
    {
        newDistrictNode ->next = NULL;
        newDistrictNode->previous = L;
        L->next = newDistrictNode;
        newDistrictNode->townsHeader = createTownsList();
    }
    else // if the list is not empty, add the new district at the end of the list
    {
        ptrDis last = L;
        while (last ->next != NULL)
            last = last->next;
        newDistrictNode->next = NULL;
        newDistrictNode ->previous = last;
        last ->next = newDistrictNode;
        newDistrictNode->townsHeader = createTownsList();
    }

}
ptrDis findDistrict(char name[], DistrictsList L) //to find a district in a linked list
{
    ptrDis p = L->next;
    while (p != NULL && (strcmp(p->districtName, name) != 0))
        p = p->next;
    return p; // will return the district if found, and NULL if not found
}

ptrT findTown (char name [], ptrDis distict) //to find a town in a district
{
    ptrT p = distict->townsHeader->next;
    while (p != NULL && (strcmp(p->townName, name))!=0)
        p = p->next;
    return p;
}
void addTown (ptrDis district, char name[], int Population) //to add a new town to a certain district
{
    if (district == NULL)
    {
        printf("ERROR: District not found.\n");
        return;
    }

    if (findTown(name,district) != NULL) // if the town exists, exit the function
        return;

    ptrT newTownNode = (ptrT)malloc(sizeof(struct TownNode)); //creating a new town node
    if (newTownNode == NULL)
    {
        printf("Out of memory.\n");
        return;
    }

    strcpy(newTownNode ->townName, name);
    newTownNode ->population = Population;
    district->total_population += Population;
    if (district ->townsHeader ->next == NULL) //if the district has no towns yet, add the new town node after the header
    {
        newTownNode ->next = NULL;
        newTownNode ->previous = district ->townsHeader;
        district ->townsHeader ->next = newTownNode;
    }
    else // if the district has towns, find the last town node and add the new town node after it
    {
        ptrT last = district ->townsHeader;
        while(last ->next != NULL)
            last = last ->next;
        newTownNode ->next = NULL;
        newTownNode ->previous = last;
        last ->next = newTownNode;
    }

}
void displayTownsList (ptrDis district) // to print the towns of a district
{
    ptrT p = district->townsHeader;
    if (district->townsHeader->next == NULL)
        printf("The list is empty.\n");
    else
    do {
        p = p ->next;
        printf("%s\t", p ->townName);
    } while (p ->next != NULL);
    printf("\n");
}

void loadInputFile ()// to load the input file
{

    FILE* f = fopen ("dist.txt","r");
    if (f == NULL)
        {printf("Error opening the file.\n\n");
        return; }

    printf("\nLoading the input file...\n");

    char line[50];
    while (fgets(line,50,f) != NULL) // reading lines until it reaches the end of the file
    {
        char *districtName, *townName;
        int population;
        districtName = strtok(line,"|"); // assigns the first string before "|" to districtName
        townName = strtok(NULL, "|"); // strtok continues tokenizing the same string it started with
        population = atoi(strtok(NULL,"|")); // atoi (ASCII to int) converts string to int

        insertDistrict (DList, districtName);
        ptrDis district = findDistrict(districtName,DList);
        addTown (district,townName, population);
    }
    fclose(f);
    printf("Input file loaded.\n\n");

}
void printInfo ()// to print list information
{
    if (DList->next == NULL)
        printf("The list is empty.\n\n");
    ptrDis tempDistrict = DList->next;
    while (tempDistrict != NULL) // loop through the districts
    {
        printf("%s District, Population = %d\n",tempDistrict->districtName, tempDistrict->total_population);

        ptrT tempTown = tempDistrict->townsHeader->next;
        if (tempTown == NULL)
            printf("No towns added yet.\n");

        while (tempTown != NULL) // loop through the towns of the district
        {
            printf("%s, %d\n", tempTown->townName, tempTown->population);
            tempTown = tempTown->next;
        }
        tempDistrict = tempDistrict->next;
    }
    printf("\n");
}

void menu() //to print the main menu
{
        printf("Choose an option from 1 to 14.\n");
        printf("1- Load the input file.\n");
        printf("2- Print the loaded information before sorting.\n");
        printf("3- Sort the districts alphabetically using Radix sort.\n");
        printf("4- Sort the towns for each district based on population in ascending order.\n");
        printf("5- Print the sorted information.\n");
        printf("6- Add a new district to the list of sorted districts (and sort the list).\n");
        printf("7- Add a new town to a certain district.\n");
        printf("8- Delete a town from a specific district.\n");
        printf("9- Delete a complete district.\n");
        printf("10- Calculate the population of Palestine, the max and min town population.\n");
        printf("11- Print the districts and their total population.\n");
        printf("12- Change the population of a town.\n");
        printf("13- Save to output file.\n");
        printf("14- Exit.\n");

}
int getMaxDistrictLength (DistrictsList L) //to get max district name length to use in radix sort
{
    ptrDis temp = L->next;
    int maxLength = 0;
    while(temp != NULL)
    {
        int districtLength = strlen(temp->districtName);
        if (districtLength > maxLength)
            maxLength = districtLength;
        temp = temp->next;
    }
    return maxLength;
}
void makeEqualLength (DistrictsList L, int maxLength) // to make the names of districts equal in length
{
    ptrDis temp = L->next;
    while (temp != NULL)
    {
        int currentLength = strlen(temp->districtName);
        for (int i= currentLength; i<maxLength; i++)
            temp->districtName[i] ='*'; // Ex: Gaza, currentLength =4 -> districtName[4] = '*' -> Gaza*...etc
        temp->districtName[maxLength] ='\0'; // null character to indicate the end of the string -> Gaza**\0
        temp = temp->next;
    }
}
void cleanStringsFromStar (DistrictsList L) // to remove the * character from the end of a string
{
    if (L==NULL) // list doesn't exist
        return;
    if (L->next == NULL) //list is empty
        return;
    ptrDis currentDistrict = L->next;
    while (currentDistrict != NULL)
    {
        int length = strlen(currentDistrict->districtName);
        while (currentDistrict->districtName[length-1] == '*')
        {
                currentDistrict->districtName[length-1] = '\0'; //remove the star at the end by replacing it with null
                length--;
        }
        currentDistrict = currentDistrict->next;
    }

}
void radixSortDistricts(DistrictsList L) // to sort districts alphabetically
{
    if (L == NULL)
    {
        printf("List not found.\n");
        return;
    }
    if (L->next == NULL)
    {
        printf("The list is empty.\n");
        return;
    }

    int max = getMaxDistrictLength(L);
    makeEqualLength(L, max); //makes the length of districts names the same by adding * at the end (right)

    // creating an array of district lists for 26 capital letters, 26 small letters, and 1 '*'
    DistrictsList asciiCharacters[53];
    for(int i=0;i<53;i++) //initializing the buckets
    {
        asciiCharacters[i]= (DistrictsList)malloc(sizeof(struct DistrictNode));
        asciiCharacters[i]->next = NULL;
        asciiCharacters[i]->previous = NULL;
    }

    int location; // to determine the location of the district in the buckets
    for (int temp=max-1; temp>=0; temp--) // # of iterations used for sorting = max district name length
        {
        ptrDis currentDistrict = L->next;
        ptrDis nextDistrict;

        while (currentDistrict != NULL) {

            nextDistrict = currentDistrict->next;
            int p = currentDistrict->districtName[temp]; //this gives the ascii code for character districtName[temp]

            if (p == 42) //ascii code for * is 42
                location=0;

            else if (p >= 65&& p<= 90) // for capital letters. if p = 65 -> p='A' and location should be 1
                location = p - 65 +1; // for 'A': location = 65-65+1 = 1

            else if (p>= 97 && p<= 122) // for small letters
                location = p -97 +27; // for 'a': location = 27

            //detaching current district from L to add it to the appropriate bucket
            if (nextDistrict != NULL)
            {
                L->next = nextDistrict;
                nextDistrict->previous = L;
                currentDistrict->next = NULL;
                currentDistrict->previous =NULL;
            }
            else //if nextDistrict = NULL
            {
                L->next = nextDistrict;
                currentDistrict->previous = NULL;
            }

            //adding current district to the bucket
            if (asciiCharacters[location]->next == NULL) //if the character list is empty
            {
                currentDistrict->previous= asciiCharacters[location];
                asciiCharacters[location]->next = currentDistrict;
            }
            else
            {
                ptrDis last = asciiCharacters[location];
                while(last->next != NULL)
                    last = last->next;
                currentDistrict->previous = last;
                last->next = currentDistrict;

            }
            currentDistrict = nextDistrict;
        }

        for (int j=0; j<53; j++)
        {
            ptrDis currentDist = asciiCharacters[j]->next;
            ptrDis nextDist;
            while(currentDist != NULL)
            {
                nextDist = currentDist->next;
                // detaching currentDist from the bucket to re-add it to the list
                if (nextDist != NULL)
                {
                    asciiCharacters[j]->next = nextDist;
                    nextDist->previous = asciiCharacters[j];
                    currentDist->next = NULL;
                    currentDist->previous = NULL;
                }
                else
                {
                    asciiCharacters[j]->next = nextDist;
                    currentDist->previous = NULL;
                }
                // re-adding the district to the districts list
                if (L->next == NULL) // if the list L is empty
                {
                    currentDist->previous = L;
                    L->next = currentDist;
                }
                else
                {
                    ptrDis last = L;
                    while(last->next != NULL)
                        last = last ->next;
                    currentDist->previous = last;
                    last->next = currentDist;
                }

                currentDist = nextDist;

            }
        }
    }

    cleanStringsFromStar(L); // to remove the districts names from the character * at the end

    for (int i = 0; i < 53; i++) // to clean the memory from the characters nodes
        free(asciiCharacters[i]);
}

void sortTowns (DistrictsList L) // to sort towns populations in ascending order (bubble sort)
{
    if (L==NULL)
    {
        printf("List not found.\n");
        return;
    }

    ptrDis district = L->next;
    while (district != NULL)
    {
       int isSwapped;
       do
       {
           isSwapped=0;
           ptrT previousTown = district->townsHeader;
           ptrT currentTown = previousTown->next;
           while(currentTown != NULL && currentTown->next != NULL ) // there are at least two towns in the district to compare
           {
               ptrT nextTown = currentTown->next;
               previousTown = currentTown->previous;
               if (currentTown->population > nextTown->population) //swap them if true
               {
                   currentTown->next = nextTown->next;

                   if (nextTown->next != NULL) //if nextTown isn't the last town node
                   {
                       nextTown->next->previous = currentTown;
                       nextTown->previous = previousTown;
                       nextTown->next = currentTown;
                       currentTown->previous = nextTown;
                       previousTown->next = nextTown;
                   }
                   else
                   {
                       nextTown->previous = previousTown;
                       nextTown->next = currentTown;
                       currentTown->previous = nextTown;
                       previousTown->next = nextTown;
                   }


                   isSwapped = 1; //towns were swapped
               }
               else // if they are already sorted, move to the next towns
               {
                   previousTown = currentTown;
                   currentTown = currentTown->next;
               }
           }

       }
       while (isSwapped == 1); // if isSwapped =0, it means the list is sorted and no need to sort it again
       district = district->next;
    }

}

void DeleteTown (char distName[], char tName[]) // to delete a town from a specific district
{
    ptrDis district = findDistrict(distName, DList);
    ptrT town = findTown(tName, district);

    ptrT previousTown = town->previous;
    ptrT nextTown = town->next;

    if (town->next == NULL) // if town is the last node in the list
    {
        previousTown->next = NULL; //make previousTown the last node in the list
        free(town);
        district->total_population = district->total_population - town->population;
    }

    else if (town->previous == district->townsHeader) // if town is the first node in the list after the header
    {
        district->townsHeader->next = nextTown;
        nextTown->previous = district->townsHeader;
        free(town);
        district->total_population = district->total_population - town->population;
    }
    else //if town is in the middle
    {
        previousTown->next=nextTown;
        nextTown->previous = previousTown;
        free(town);
        district->total_population = district->total_population - town->population;
    }
}
void deleteDistrict (char name[], DistrictsList L) // to delete a complete district with its towns
{
    if (L==NULL)
    {
        printf("List not found.\n");
        return;
    }

    ptrDis district = findDistrict(name, L);
    if (district == NULL )
    {
        printf("District %s does not exist.\n",name);
        return;
    }

    ptrT currentTown = district->townsHeader->next;
    while(currentTown != NULL) //remove all the towns of the district first
    {
        ptrT temp = currentTown->next;
        DeleteTown(district->districtName, currentTown->townName);
        currentTown = temp;
    }

    free(district->townsHeader);
    ptrDis previousDistrict = district->previous;
    ptrDis nextDistrict = district->next;

    if (district->next == NULL) //if the district is the last node in the list
    {
        previousDistrict->next = NULL;
        free(district);
        printf("District %s has been deleted.\n",name);
    }
    else if (district->previous == L) //if the district is the first node after the list head (DList)
    {
        L->next = nextDistrict;
        nextDistrict->previous = L;
        free(district);
        printf("District %s has been deleted.\n",name);
    }
    else //if the district is in the middle of the list
    {
        nextDistrict->previous = previousDistrict;
        previousDistrict->next = nextDistrict;
        free(district);
        printf("District %s has been deleted.\n",name);
    }

}
void calculatePopulation (DistrictsList L) // to calculate population of Palestine, min and max town population
{
    int populationPalestine=0, max=0, min;
    ptrDis currentDistrict = L->next;
    ptrT currentTown = currentDistrict->townsHeader->next; //first town is after the header
    // I added this //////////////////////////////////////
    while (currentTown == NULL)
    {
        currentDistrict = currentDistrict->next;
        currentTown = currentDistrict->townsHeader->next;
    }
    /////////////////////////////////////////////////////
    min = currentTown->population; // initializing min to start comparing towns populations

    while (currentDistrict != NULL )
    {
        populationPalestine = populationPalestine + currentDistrict->total_population;

        currentTown = currentDistrict->townsHeader->next; //resetting currentTown for each district to start from the first town in the district
        while(currentTown != NULL)
        {
            if (currentTown->population > max)
                max = currentTown->population;

            if (currentTown->population < min)
                min = currentTown->population;

            currentTown = currentTown->next;
        }

        currentDistrict = currentDistrict->next; //moving to the next district

    }
    printf("The population of Palestine = %d\n",populationPalestine);
    printf("The maximum town population = %d\n",max);
    printf("The minimum town population = %d\n\n",min);

}
void printDistrictsAndPop (DistrictsList L) // to print the districts and their total population
{
    if (L == NULL)
    {
        printf("List not found.\n");
        return;
    }
    if (L->next == NULL)
    {
        printf("The list is empty.\n");
        return;
    }
    ptrDis currentDis = L->next;
    while(currentDis != NULL) //loop through all the districts in the list
    {
        printf("District: %s, Total population: %d\n",currentDis->districtName, currentDis->total_population);
        currentDis = currentDis->next;
    }

}
void saveToOutputFile() // to save to output file
{
    FILE *f = fopen("sorted_districts.txt","w");
    if (f == NULL)
    {
        printf("Error opening the file.\n");
        return;
    }

     ptrDis tempDistrict = DList->next;
    while (tempDistrict != NULL) // loop through the districts
    {
        fprintf(f,"%s District, Population = %d\n",tempDistrict->districtName, tempDistrict->total_population);
        ptrT tempTown = tempDistrict->townsHeader->next;
        if (tempTown == NULL)
            fprintf(f,"No towns added yet.\n");

        while (tempTown != NULL) // loop through the towns of the district
        {
            fprintf(f,"%s, %d\n",tempTown->townName, tempTown->population);
            tempTown = tempTown->next;
        }
        tempDistrict = tempDistrict->next;
    }
    fclose(f);
}
