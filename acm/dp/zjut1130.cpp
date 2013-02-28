#include <stdio.h>
#include <memory.h>
const int N=20001;
int b[N],c[N],hash[N],hash1[N];
int n;

int main()
{
	//freopen("a.txt","r",stdin);
	int t,temp;
	scanf("%d ",&t);
	while(t--)
	{
		scanf("%d ",&n);
		for(int i=0;i<n;i++)
		{
			scanf("%d ",&temp);
			hash[temp]=i;
		}
		for(int i=0;i<n;i++)
		{
			scanf("%d ",&b[i]);
			c[i]=hash[b[i]];
		}
		int max_n=1;
		memset(hash1,0,sizeof(hash1));
		hash1[1]=c[0];
		for(int i=1;i<n;i++)
		{
			if(c[i]>hash1[max_n])
			{
				max_n++;
				hash1[max_n]=c[i];
			}
			else
			{
				int start=1;
				int end=max_n;
				while(start<=end)
				{
					int mid=(start+end)>>1;
					if(hash1[mid]<c[i])
					{
						start=mid+1;
					}
					else
					{
						end=mid-1;
					}
				}
				hash1[start]=c[i];
				if(start>max_n)
				{
					max_n=start;
				}


			}
		}
		printf("%d\n",max_n);


	}
	return 0;
}
