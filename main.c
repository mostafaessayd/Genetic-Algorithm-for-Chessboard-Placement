#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char chess[8][8];
int numberOfGeneration;
char chromosomes[100][64];
int lengthOfChromosomes = 0;
float fitnes[100];
float propapility[100];
int isVictim[1000][8][8];
// additional grids
char victimsGrid[1000][8][8];
int lengthOfVictimsGrid = 0;

// init new grid into victims grid
void copier()
{
    for(int k = 0 ; k < 10 ; k++)
    {
        for(int i = 0 ; i < 8 ; i++)
        {
            for(int j = 0 ; j < 8 ; j++)
            {
                victimsGrid[lengthOfVictimsGrid][i][j] = chess[i][j];
            }
        }

        lengthOfVictimsGrid++;
    }
}

// show all victims of chromosome
void showVictimsOf(int idxOfChromosome)
{
    printf("|-------------");
    for(int j = 0 ; j < 10 ; j++)
    {
        printf("+");
        for(int k = 0 ; k < 8 ; k++)
        {
            printf("-");
        }
        printf("+ ");
    }
    printf("--------------|\n");


    for(int i = 0 ; i < 8 ; i++)
    {
        printf("|-------------");
        for(int j = idxOfChromosome * 10 ; j < idxOfChromosome * 10 + 10 ; j++)
        {
            printf("|");
            for(int k = 0 ; k < 8 ; k++)
            {
                if(isVictim[j][i][k])
                {
                    if(victimsGrid[j][i][k] == 'E')
                    {
                        printf("\033[1;35m\.\033[0m");
                    }
                    else
                    {
                        if(isVictim[j][i][k] == 2)
                        {
                            printf("\033[1;32m\%c\033[0m", victimsGrid[j][i][k]);
                        }
                        else
                        {
                            printf("\033[1;31m\%c\033[0m", victimsGrid[j][i][k]);
                        }
                    }
                }
                else
                {
                    printf(" ");
                }
            }
            printf("| ");
        }
        printf("--------------|");
        printf("\n");
    }

    printf("|-------------");
    for(int j = 0 ; j < 10 ; j++)
    {
        printf("+");
        for(int k = 0 ; k < 8 ; k++)
        {
            printf("-");
        }
        printf("+ ");
    }
    printf("--------------|\n");

}

void init()
{
    for(int i = 0 ; i < 8 ; i++)
    {
        for(int j = 0 ; j < 8 ; j++)
        {
            chess[i][j] = 'E';
        }
    }
}

void gridTovector(int targetIdx)
{
    int k = 0;
    for(int i = 0 ; i < 8 ; i++)
    {
        for(int j = 0 ; j < 8 ; j++)
        {
            chromosomes[targetIdx][k] = chess[i][j];
            k++;
        }
    }

    propapility[targetIdx] = (float)((float)(1 + rand() % 10) / 10.0);
}

// vector to matrice
void vectorToGrid(int targetIdx)
{
    int x = 0;
    int y = 0;
    for(int i = 0 ; i < 64 ; i++)
    {
        chess[x][y] = chromosomes[targetIdx][i];
        if(y + 1 == 8)
        {
            x++;
            y = 0;
        }
        else
        {
            y++;
        }
    }
}

// get fitness of queen
int getConflitOfQ(int x, int y)
{
    int res = 0;
    int i = x;
    int j = y + 1;
    while(j < 8)
    {
        res += (chess[i][j] != 'E');
        j++;
    }
    i = x;
    j = y - 1;
    while(j > -1)
    {
        res += (chess[i][j] != 'E');
        j--;
    }

    i = x + 1;
    j = y;
    while(i < 8)
    {
        res += (chess[i][j] != 'E');
        i++;
    }

    i = x - 1;
    j = y;
    while(i > -1)
    {
        res += (chess[i][j] != 'E');
        i--;
    }

    i = x + 1;
    j = y + 1;
    while(i < 8 && j < 8)
    {
        res += (chess[i][j] != 'E');
        i++;
        j++;
    }

    i = x - 1;
    j = y + 1;
    while(i > -1 && j < 8)
    {
        res += (chess[i][j] != 'E');
        i--;
        j++;
    }

    i = x + 1;
    j = y - 1;
    while(i < 8 && j > -1)
    {
        res += (chess[i][j] != 'E');
        i++;
        j--;
    }

    i = x - 1;
    j = y - 1;
    while(i > -1 && j > -1)
    {
        res += (chess[i][j] != 'E');
        i--;
        j--;
    }

    return res;
}

// get conflit of roocks
int getConflitOfR(int x, int y)
{
    int res = 0;
    int i = x;
    int j = y + 1;
    while(j < 8)
    {
        res += (chess[i][j] != 'E');
        j++;
    }
    i = x;
    j = y - 1;
    while(j > -1)
    {
        res += (chess[i][j] != 'E');
        j--;
    }

    i = x + 1;
    j = y;
    while(i < 8)
    {
        res += (chess[i][j] != 'E');
        i++;
    }

    i = x - 1;
    j = y;
    while(i > -1)
    {
        res += (chess[i][j] != 'E');
        i--;
    }

    return res;
}


// get conflit of bishop
int getConnflitOfB(int x, int y)
{
    int res = 0;
    int i = x + 1;
    int j = y + 1;
    while(i < 8 && j < 8)
    {
        res += (chess[i][j] != 'E');
        i++;
        j++;
    }

    i = x - 1;
    j = y + 1;
    while(i > -1 && j < 8)
    {
        res += (chess[i][j] != 'E');
        i--;
        j++;
    }

    i = x + 1;
    j = y - 1;
    while(i < 8 && j > -1)
    {
        res += (chess[i][j] != 'E');
        i++;
        j--;
    }

    i = x - 1;
    j = y - 1;
    while(i > -1 && j > -1)
    {
        res += (chess[i][j] != 'E');
        i--;
        j--;
    }

    return res;
}

// get conflit of knight
int getConflitOfK(int x, int y)
{
    int res = 0;
    if(x - 2 > -1 && y - 1 > -1)
    {
        res += (chess[x - 2][y - 1] != 'E');
    }
    if(x - 2 > -1 && y + 1 < 8)
    {
        res += (chess[x - 2][y + 1] != 'E');
    }
    if(x + 2 < 8 && y + 1 < 8)
    {
        res += (chess[x + 2][y + 1] != 'E');
    }
    if(x + 2 < 8 && y - 1 > -1)
    {
        res += (chess[x + 2][y - 1] != 'E');
    }

    return res;
}

//
int getConflit(int x, int y)
{
    if(chess[x][y] == 'Q') return getConflitOfQ(x, y);
    if(chess[x][y] == 'R') return getConflitOfR(x, y);
    if(chess[x][y] == 'K') return getConflitOfK(x, y);
    if(chess[x][y] == 'P') return getConnflitOfB(x, y);
    return 0;
}

void getFitnessOfChromosome(int indexeOfChromosome)
{
    vectorToGrid(indexeOfChromosome);
    float res = 0;
    for(int i = 0 ; i < 8 ; i++)
    {
        for(int j = 0 ; j < 8 ; j++)
        {
            res += getConflit(i, j);
        }
    }

    fitnes[indexeOfChromosome] = (float)((float)1 / ((float)1 + res));
}

void generateRandomChess()
{

    int vis[8][8];
    for(int i = 0 ; i < 8 ; i++)
    {
        for(int j = 0 ; j < 8 ; j++)
        {
            vis[i][j] = 0;
        }
    }

    char pices1[] = {'Q', 'Q','P','K', 'R', 'K', 'P','Q','Q','R'};
    for(int i = 0 ; i < 5 ; i++)
    {
        int x = rand() % 4;
        int y = rand() % 8;
        while(vis[x][y] == 1)
        {
            x = rand() % 4;
            y = rand() % 8;
        }
        chess[x][y] = pices1[i];
        vis[x][y]++;
    }

    for(int i = 5 ; i < 10 ; i++)
    {
        int x = rand() % 4 + 4;
        int y = rand() % 8;
        while(vis[x][y] == 1)
        {
            x = rand() % 4 + 4;
            y = rand() % 8;
        }
        chess[x][y] = pices1[i];
        vis[x][y]++;
    }
}

void showChess(int idx)
{
    printf("|");
    printf("ChessBoared %2d" , idx);
    for(int k = 0 ; k < 49 ; k++) {
            printf(" ");
    }
    printf("+");
    for(int i = 0 ; i < 8 ; i++) {
        printf("-");
    }
    printf("+");
    for(int k = 0 ; k < 64 ; k++) {
            printf(" ");
    }
    printf("|\n");
    for(int i = 0 ; i < 8 ; i++)
    {
        printf("|");
        for(int k = 0 ; k < 63 ; k++) {
            printf(" ");
        }
        printf("|");
        for(int j = 0 ; j < 8 ; j++)
        {
            if(chess[i][j] == 'Q')
            {
                printf("\033[1;31m\Q\033[0m");
            }
            else
            {
                if(chess[i][j] == 'P')
                {
                    printf("\033[1;32m\P\033[0m");
                }
                else
                {
                    if(chess[i][j] == 'R')
                    {
                        printf("\033[1;33m\R\033[0m");
                    }
                    else
                    {
                        if(chess[i][j] == 'K')
                        {
                            printf("\033[1;34m\K\033[0m");
                        }
                        else
                        {
                            printf(".");
                        }
                    }
                }
            }
        }
        printf("|");
        for(int k = 0 ; k < 64 ; k++) {
            printf(" ");
        }
        printf("|\n");
    }
    printf("|");
    for(int k = 0 ; k < 63 ; k++) {
            printf(" ");
    }
    printf("+");
    for(int i = 0 ; i < 8 ; i++) {
        printf("-");
    }
    printf("+");
    for(int k = 0 ; k < 64 ; k++) {
            printf(" ");
    }
    printf("|\n");
}

void showvectors()
{

    for(int i = 0 ; i < numberOfGeneration ; i++)
    {
        printf("+");
        for(int j = 1 ; j <= 137 ; j++) {
            printf("-");
        }
        printf("+\n");

        vectorToGrid(i);
        showChess(i + 1);
        printf("|+");
        for(int k = 0 ; k < 64 ; k++)
        {
            printf("-+");
        }
        printf("---+---+|\n|");
        if(chromosomes[i][0] == 'Q')
        {
            printf("|\033[1;31m\Q\033[0m|");
        }
        else
        {
            if(chromosomes[i][0] == 'P')
            {
                printf("|\033[1;32m\P\033[0m|");
            }
            else
            {
                if(chromosomes[i][0] == 'R')
                {
                    printf("|\033[1;33m\R\033[0m|");
                }
                else
                {
                    if(chromosomes[i][0] == 'K')
                    {
                        printf("|\033[1;34m\K\033[0m|");
                    }
                    else
                    {
                        printf("|%c|", chromosomes[i][0]);
                    }
                }
            }
        }
        for(int j = 1 ; j < 64 ; j++)
        {
            if(chromosomes[i][j] == 'Q')
            {
                printf("\033[1;31m\Q\033[0m|");
            }
            else
            {
                if(chromosomes[i][j] == 'P')
                {
                    printf("\033[1;32m\P\033[0m|");
                }
                else
                {
                    if(chromosomes[i][j] == 'R')
                    {
                        printf("\033[1;33m\R\033[0m|");
                    }
                    else
                    {
                        if(chromosomes[i][j] == 'K')
                        {
                            printf("\033[1;34m\K\033[0m|");
                        }
                        else
                        {
                            printf("%c|", chromosomes[i][j]);
                        }
                    }
                }
            }
        }
        printf("%0.1f|%0.1f||", fitnes[i], propapility[i]);
        printf("\n|+");
        for(int k = 0 ; k < 64 ; k++)
        {
            printf("-+");
        }
        printf("---+---+|\n");

        ////////////////////
        showVictimsOf(i);
        /////////////////////
        printf("+");
        for(int j = 1 ; j <= 137 ; j++) {
            printf("-");
        }
        printf("+\n\n\n");
    }
}

void getAllChromosomes()
{
    for(int i = 0 ; i < numberOfGeneration ; i++)
    {
        init();
        generateRandomChess();
        copier();
        initVictims();
        gridTovector(i);
        getFitnessOfChromosome(i);
    }
}

// init all victims
int localLength = 0;
void initVictims()
{
    for(int i = 0 ; i < 8 ; i++)
    {
        for(int j = 0 ; j < 8 ; j++)
        {
            char ch = victimsGrid[localLength][i][j];
            if(ch != 'Q' && ch != 'R' && ch != 'P' && ch != 'K')
            {
                continue;
            }

            isVictim[localLength][i][j] = 2;
            /////////////////////////////////////////
            if(victimsGrid[localLength][i][j] == 'Q')
            {
                int x = i;
                int y = j + 1;
                while(y < 8)
                {
                    isVictim[localLength][x][y] = 1;
                    y++;
                }

                y = j - 1;
                while(y > -1)
                {
                    isVictim[localLength][x][y] = 1;
                    y--;
                }

                x = i + 1;
                y = j;
                while(x < 8)
                {
                    isVictim[localLength][x][y] = 1;
                    x++;
                }

                x = i - 1;
                y = j;
                while(x > -1)
                {
                    isVictim[localLength][x][y] = 1;
                    x--;
                }

                x = i + 1;
                y = j + 1;
                while(x < 8 && y < 8)
                {
                    isVictim[localLength][x][y] = 1;
                    x++;
                    y++;
                }

                x = i + 1;
                y = j - 1;
                while(x < 8 && y > -1)
                {
                    isVictim[localLength][x][y] = 1;
                    x++;
                    y--;
                }

                x = i - 1;
                y = j + 1;
                while(x > -1 && y < 8)
                {
                    isVictim[localLength][x][y] = 1;
                    x--;
                    y++;
                }

                x = i - 1;
                y = j - 1;
                while(x > -1 && y > -1)
                {
                    isVictim[localLength][x][y] = 1;
                    x--;
                    y--;
                }

            }

            //////////////////////////////////////////
            if(victimsGrid[localLength][i][j] == 'R')
            {
                int x = i;
                int y = j + 1;
                while(y < 8)
                {
                    isVictim[localLength][x][y] = 1;
                    y++;
                }

                y = j - 1;
                while(y > -1)
                {
                    isVictim[localLength][x][y] = 1;
                    y--;
                }

                x = i + 1;
                y = j;
                while(x < 8)
                {
                    isVictim[localLength][x][y] = 1;
                    x++;
                }

                x = i - 1;
                y = j;
                while(x > -1)
                {
                    isVictim[localLength][x][y] = 1;
                    x--;
                }
            }

            ///////////////////////////////////////////
            if(victimsGrid[localLength][i][j] == 'P')
            {
                int x = i + 1;
                int y = j + 1;
                while(x < 8 && y < 8)
                {
                    isVictim[localLength][x][y] = 1;
                    x++;
                    y++;
                }

                x = i + 1;
                y = j - 1;
                while(x < 8 && y > -1)
                {
                    isVictim[localLength][x][y] = 1;
                    x++;
                    y--;
                }

                x = i - 1;
                y = j + 1;
                while(x > -1 && y < 8)
                {
                    isVictim[localLength][x][y] = 1;
                    x--;
                    y++;
                }

                x = i - 1;
                y = j - 1;
                while(x > -1 && y > -1)
                {
                    isVictim[localLength][x][y] = 1;
                    x--;
                    y--;
                }
            }

            ///////////////////////////////////////////
            if(victimsGrid[localLength][i][j] == 'K')
            {
                int x = i;
                int y = j;
                if(x - 2 > -1 && y - 1 > -1)
                {
                    isVictim[localLength][x - 2][y - 1] = 1;
                }
                if(x - 2 > -1 && y + 1 < 8)
                {
                    isVictim[localLength][x - 2][y + 1] = 1;
                }
                if(x + 2 < 8 && y + 1 < 8)
                {
                    isVictim[localLength][x + 2][y + 1] = 1;
                }
                if(x + 2 < 8 && y - 1 > -1)
                {
                    isVictim[localLength][x + 2][y - 1] = 1;
                }
            }
            //printf("(%d , %c)" , localLength , victimsGrid[localLength][i][j]);
            localLength++;
        }
    }
}


// cross best
void cross()
{
    float x = 0;
    float y = 0;
    for(int i = 0 ; i < numberOfGeneration ; i++)
    {
        if(fitnes[i] > x)
        {
            y = x;
            x = fitnes[i];
        }
        else if(fitnes[i] > y)
        {
            y = fitnes[i];
        }
    }

    int idxOfFirstFitness = -1;
    int idxOfSecondFitness = -1;
    for(int i = 0 ; i < numberOfGeneration ; i++)
    {
        if(fitnes[i] == x)
        {
            idxOfFirstFitness = i;
        }
        if(fitnes[i] == y && i != x)
        {
            idxOfSecondFitness = i;
        }
    }

    for(int i = 0 ; i < 32 ; i++)
    {
        char temp = chromosomes[idxOfFirstFitness][i];
        chromosomes[idxOfFirstFitness][i] = chromosomes[idxOfSecondFitness][i + 32];
        chromosomes[idxOfSecondFitness][i + 32] = temp;
    }
    for(int i = 32 ; i < 64 ; i++)
    {
        char temp = chromosomes[idxOfFirstFitness][i];
        chromosomes[idxOfFirstFitness][i] = chromosomes[idxOfSecondFitness][i - 32];
        chromosomes[idxOfSecondFitness][i - 32] = temp;
    }


    printf("\n\nResulte : \n");
    for(int i = 0 ; i < numberOfGeneration ; i++)
    {
        if(i != idxOfFirstFitness && i != idxOfSecondFitness) {
            continue;
        }

        printf("     +");
        for(int k = 0 ; k < 64 ; k++)
        {
            printf("-+");
        }

        printf("\nC%3d ", i + 1);
        if(chromosomes[i][0] == 'Q')
        {
            printf("\033[1;31m\|Q|\033[0m");
        }
        else
        {
            if(chromosomes[i][0] == 'P')
            {
                printf("\033[1;32m\|P|\033[0m");
            }
            else
            {
                if(chromosomes[i][0] == 'R')
                {
                    printf("\033[1;33m\|R|\033[0m");
                }
                else
                {
                    if(chromosomes[i][0] == 'K')
                    {
                        printf("\033[1;34m\|K|\033[0m");
                    }
                    else
                    {
                        printf("|%c|", chromosomes[i][0]);
                    }
                }
            }
        }
        for(int j = 1 ; j < 64 ; j++)
        {
            if(chromosomes[i][j] == 'Q')
            {
                printf("\033[1;31m\Q|\033[0m");
            }
            else
            {
                if(chromosomes[i][j] == 'P')
                {
                    printf("\033[1;32m\P|\033[0m");
                }
                else
                {
                    if(chromosomes[i][j] == 'R')
                    {
                        printf("\033[1;33m\R|\033[0m");
                    }
                    else
                    {
                        if(chromosomes[i][j] == 'K')
                        {
                            printf("\033[1;34m\K|\033[0m");
                        }
                        else
                        {
                            printf("%c|", chromosomes[i][j]);
                        }
                    }
                }
            }
        }
        printf("\n     +");
        for(int k = 0 ; k < 64 ; k++)
        {
            printf("-+");
        }
        printf("\n");

        ////////////////////
        /////////////////////
    }
}


int main()
{
    srand(time(0));
    init();
    generateRandomChess();
    //showChess();

    printf("-number of generation : ");
    scanf("%d", &numberOfGeneration);

    getAllChromosomes();
    showvectors();
    cross();


    return 0;
}
