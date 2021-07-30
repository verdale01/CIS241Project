#include <stdio.h>
typedef struct{
    unsigned int month, day, year, put, call,vol;
    float ratio;
}dataDate,lowRatio,highRatio;

void importData(FILE* dataSet,dataDate newline[]){
    char line[100];
    int count=0;
    fgets(line, sizeof(line), dataSet);//Removes the first line
    while(!feof(dataSet))
    {
        fgets(line, sizeof(line), dataSet);
        sscanf(line,"%u/%u/%u,%f,%u,%u,%u",&newline[count].month,&newline[count].day,&newline[count].year,
               &newline[count].ratio,&newline[count].put,&newline[count].call,&newline[count].vol);
        count++;
    }
    fclose(dataSet);
}
void printData(dataDate newline[],int max){
    int i;
    printf("Date,PCR,Put Volume,Call Volume, Total Volume\n");
    for (i = 0; i<max ; ++i) {
        printf("%u/%u/%u,%f,%u,%u,%u\n",newline[i].month,newline[i].day,newline[i].year,
               newline[i].ratio,newline[i].put,newline[i].call,newline[i].vol);
    }
}
int lengthOfStruct(dataDate temp[])
{
    int i=0;
    //Returns the number of element in array where data is present.
    while(temp[i++].month != 0);
    return i-1;
}
void lowValueSorter(dataDate allDataPoints[],dataDate line2save[],int max)
{
    int i;
    int temp;
    for(i=0,temp=0;i<max;i++) {
        if (allDataPoints[i].ratio < 1) {
            line2save[temp] = allDataPoints[i];
            printf("%u/%u/%u,%f,%u,%u,%u\n", line2save[temp].month, line2save[temp].day, line2save[temp].year,
                   line2save[temp].ratio,line2save[temp].put, line2save[temp].call, line2save[temp].vol);
            temp++;
        }
    }
}
void maxValueSorter(dataDate allDataPoints[],dataDate line2save[],int max)
{
    int i;
    int temp;
    for(i=0,temp=0;i<max;i++) {
        if (allDataPoints[i].ratio > 3) {
            line2save[temp] = allDataPoints[i];
            printf("%u/%u/%u,%f,%u,%u,%u\n", line2save[temp].month, line2save[temp].day, line2save[temp].year,
                   line2save[temp].ratio,line2save[temp].put, line2save[temp].call, line2save[temp].vol);
            temp++;
        }
    }
}
void print2excel(dataDate allDataPoints[], int max)
{
    int i;
    FILE *fpt;
    fpt = fopen("data.csv", "w+");
    char date_str[11];
    fprintf(fpt,"Date,PCR,Put Volume,Call Volume, Total Volume\n");

    //Print to Excel
    for(i=0;i<max;i++)
    {
        sprintf(date_str, "%u/%u/%u", allDataPoints[i].month,allDataPoints[i].day,allDataPoints[i].year);
        //printf("Converted to string : %s\n", date_str);

        fprintf(fpt,"%s,%f,%u,%u,%u\n",date_str,allDataPoints[i].ratio,
                allDataPoints[i].put,allDataPoints[i].call,allDataPoints[i].vol);
    }
    fclose(fpt);
}
void consoleTitleBlocks(char *str)
{
    puts("****************************************************************************************");
    for (int i = 0; str[i]!='\0'; ++i) {
        printf("%c",str[i]);
    }
    puts("\n****************************************************************************************");
}
int main() {

    dataDate allDataPoints[3000];
    lowRatio  lowerRatio[100];
    highRatio  upperRatio[100];
    FILE* dataSet;
    dataSet = fopen("241Data.txt","r");
    importData(dataSet,allDataPoints);

    //puts("All Data Printed to Console");
    consoleTitleBlocks("All Data Printed to Console");
    printData(allDataPoints,lengthOfStruct(allDataPoints));
    consoleTitleBlocks("All Ratios Under 1 Are Printed To The Console");
    lowValueSorter(allDataPoints,lowerRatio,lengthOfStruct(allDataPoints));
    consoleTitleBlocks("All Ratios Above 3 Are Printed To The Console");
    maxValueSorter(allDataPoints,upperRatio,lengthOfStruct(allDataPoints));
    consoleTitleBlocks("All Data Points Are Exported To An Excel Table");
    print2excel(allDataPoints,lengthOfStruct(allDataPoints));
    return 0;
}


