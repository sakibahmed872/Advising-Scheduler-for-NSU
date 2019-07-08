#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<ctime>
#include<cstdlib>


using namespace std;

typedef struct info
    {
        int ID;
        string name;
        float credit;
        float cgpa;
    } info;

int strTOint(string s);
float strTof(string s);
void RandomizedQuickSort(info A[], int low, int high);
void writeToFile(info arr[], int n);
void scheduleStart(tm*& timeinfo);
string Time(int i, tm* timeinfo);
void AddTime(tm* date);

int main()
{
    info list[10000];
    int index=0;
    ifstream input("input.txt");

    if(input.is_open())
    {
        while(!input.eof())
        {
            string s,token;
            getline(input,s);
            string temp[4];
            int i=0;
            stringstream ss(s);
            char delim='\t';
            while (getline(ss, token, delim))
            {
                temp[i]=token;
                i++;
            }
            list[index].ID=strTOint(temp[0]);
            list[index].name=temp[1];
            list[index].credit=strTof(temp[2]);
            list[index].cgpa=strTof(temp[3]);
            index++;
            i=0;
        }
    }
    else
    {
        cout<<"File is not open successfully"<<endl;
    }
    RandomizedQuickSort(list,0,index-1);
    writeToFile(list,index);


    return 0;
}

int strTOint(string s)
{
    int x;
    stringstream temp(s);
    temp >> x;
    return x;
}

float strTof(string s)
{
    float y;
    stringstream temp(s);
    temp>>y;
    return y;
}

void swap(info *temp1, info *temp2)
{
	info temp;
	temp = *temp1;
	*temp1 = *temp2;
	*temp2 = temp;
}

int Partition(info A[], int Low, int High)
{
	int pivot, index, i;
	index = Low;
	pivot = High;

	// Getting index of pivot.
	for(i=Low; i < High; i++)
	{
		if(A[i].credit > A[pivot].credit)
		{
			swap(&A[i], &A[index]);
			index++;
		}
		else if(A[i].credit == A[pivot].credit)
        {
            if(A[i].cgpa > A[pivot].cgpa)
            {
                swap(&A[i],&A[index]);
                index++;
            }
        }
	}
	swap(&A[pivot], &A[index]);

	return index;
}

int RandomPivotPartition(info A[], int Low, int High)
{
	int pvt, n;
	n = rand();
	// Randomizing the pivot value in the given subpart of array.
	pvt = Low + n%(High-Low+1);
	swap(&A[High], &A[pvt]);

	return Partition(A, Low, High);
}


void RandomizedQuickSort(info A[], int Low, int High)
{
	int pindex;
	if(Low < High)
	{
		// Partitioning array using randomized pivot.
		pindex = RandomPivotPartition(A, Low, High);
		RandomizedQuickSort(A, Low, pindex-1);
		RandomizedQuickSort(A, pindex+1, High);
	}
}


void writeToFile(info arr[], int n)
{
    ofstream output("output.txt");
    if(output.is_open())
    {
        output<<"ID"<<"\t"<<"Name"<<"\t\t"<<"Credit"<<"\t"<<"Cgpa"<<"\t"<<"Advising Time"<<endl;
        struct tm * timeinfo;
        scheduleStart(timeinfo);
        for(int i=0;i<n;i++)
        {
            output<<arr[i].ID<<"\t"<<arr[i].name<<"\t"<<arr[i].credit<<"\t"<<arr[i].cgpa<<"\t"<<Time(i,timeinfo)<<endl;
        }
        cout<<"Data has beed written to txt file Successfully"<<endl;
    }
    else
    {
        cout<<"File is not open successfully"<<endl;
    }
}

void scheduleStart(tm*& timeinfo)
{
    time_t rawtime;
    char buffer [80];

    time(&rawtime);
    timeinfo = localtime ( &rawtime );
    timeinfo->tm_mday=01;
    timeinfo->tm_mon=00;
    timeinfo->tm_year=2019-1900;
    timeinfo->tm_hour=00;
    timeinfo->tm_min=00;
    mktime(timeinfo);
}

string Time(int i,tm* timeinfo)
{
    char buffer [80];
    if(i==0|| i%5>0)
    {
        strftime (buffer,80,"%d-%b-%Y %I:%M%p.",timeinfo);
    }
    else
    {
        AddTime(timeinfo);
        strftime (buffer,80,"%d-%b-%Y %I:%M%p.",timeinfo);
    }

    return buffer;
}

void AddTime(tm* date) {
    if (date == NULL) return;
    date->tm_sec += 1800;
    mktime(date);
}
