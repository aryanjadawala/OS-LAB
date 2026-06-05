#include <stdio.h>

int search(int page, int frame[], int f)
{
    for(int i=0;i<f;i++)
        if(frame[i]==page)
            return 1;
    return 0;
}

/* FIFO */

void FIFO(int pages[], int n, int f)
{
    int frame[20];
    int faults=0, index=0;

    for(int i=0;i<f;i++)
        frame[i]=-1;

    for(int i=0;i<n;i++)
    {
        if(!search(pages[i],frame,f))
        {
            frame[index]=pages[i];
            index=(index+1)%f;
            faults++;
        }
    }

    printf("\nFIFO Page Faults = %d\n",faults);
}

/* LRU */

void LRU(int pages[], int n, int f)
{
    int frame[20];
    int recent[20];
    int faults=0;

    for(int i=0;i<f;i++)
    {
        frame[i]=-1;
        recent[i]=-1;
    }

    for(int i=0;i<n;i++)
    {
        int found=0;

        for(int j=0;j<f;j++)
        {
            if(frame[j]==pages[i])
            {
                recent[j]=i;
                found=1;
                break;
            }
        }

        if(!found)
        {
            int pos=0;

            for(int j=1;j<f;j++)
            {
                if(recent[j]<recent[pos])
                    pos=j;
            }

            frame[pos]=pages[i];
            recent[pos]=i;
            faults++;
        }
    }

    printf("LRU Page Faults = %d\n",faults);
}

/* OPTIMAL */

void OPTIMAL(int pages[], int n, int f)
{
    int frame[20];
    int faults=0;

    for(int i=0;i<f;i++)
        frame[i]=-1;

    for(int i=0;i<n;i++)
    {
        if(search(pages[i],frame,f))
            continue;

        int pos=-1;

        for(int j=0;j<f;j++)
        {
            if(frame[j]==-1)
            {
                pos=j;
                break;
            }
        }

        if(pos==-1)
        {
            int farthest=-1;
            int replace=0;

            for(int j=0;j<f;j++)
            {
                int k;

                for(k=i+1;k<n;k++)
                {
                    if(frame[j]==pages[k])
                        break;
                }

                if(k==n)
                {
                    replace=j;
                    break;
                }

                if(k>farthest)
                {
                    farthest=k;
                    replace=j;
                }
            }

            pos=replace;
        }

        frame[pos]=pages[i];
        faults++;
    }

    printf("Optimal Page Faults = %d\n",faults);
}

int main()
{
    int n,f;

    printf("Enter number of pages: ");
    scanf("%d",&n);

    int pages[50];

    printf("Enter reference string:\n");
    for(int i=0;i<n;i++)
        scanf("%d",&pages[i]);

    printf("Enter number of frames: ");
    scanf("%d",&f);

    FIFO(pages,n,f);
    LRU(pages,n,f);
    OPTIMAL(pages,n,f);

    return 0;
}
