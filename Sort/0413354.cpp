#include <iostream>
#include <fstream>
#include<cstdlib>
using namespace std;

void quicksort(int *data, int left, int right);
void swap(int *a, int *b);

int main(void)
{
	int n;
	string s;
	ifstream infile("input.txt",ios::in);
	ofstream outfile("output.txt",ios::out);

	infile>>n;
	getline(infile,s);

	while(n)
	{
		int i=0,x=0;
		string str;
		int a[100000]={0};
		getline(infile,str) ;

			for(int j=0;j<str.size()+1;j++)
			{

				if(str[j]==' '||str[j]=='\0')
				{
					a[i]=x;
					x=0;
					i++;

				}
				else
				{
					x=x*10+str[j]-48;

				}


			}

		quicksort(a, 0, i - 1);

		for(int j=0;j<i;j++)
		{
			outfile<<a[j]<<" ";
		}
		outfile<<endl;

		n--;
	}


	system("pause");

	return 0;

}





void quicksort(int *data, int left, int right)
{
    int pivot, i, j;

    if (left >= right) { return; }

    pivot = data[left];

    i = left + 1;
    j = right;

    while (1)
    {
        while (i <= right)
        {
            if (data[i] > pivot)
            {
                break;
            }

            i = i + 1;
        }

        while (j > left)
        {
            if (data[j] < pivot)
            {
                break;
            }

            j = j - 1;
        }

        if (i > j) { break; }

        swap(&data[i], &data[j]);
    }

    swap(&data[left], &data[j]);

    quicksort(data, left, j - 1);
    quicksort(data, j + 1, right);
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
