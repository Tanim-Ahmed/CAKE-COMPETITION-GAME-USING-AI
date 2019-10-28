
#include <stdio.h>
#include <stdlib.h>
#include<time.h> //for random value
#define max(x, y) (((x) > (y)) ? (x) : (y)) //max calculation
#define min(x, y) (((x) < (y)) ? (x) : (y)) //min calculation

typedef long long int lli;
lli arr[100];
lli n;
lli dp[100];
lli com(lli i); //function for computer
lli cdp[100][2], udp[100][2];
lli user(lli i) //function for player
{
    if (i==n) return 0;
  //  cout<<"i"<<i<<endl;
    //cout<<"udp:"<<udp[i][0]<<endl;
    if (udp[i][0]!=-1) return udp[i][0];
    //cout<<udp[i][0];
    lli a=arr[i]+dp[i+1]-com(i+1);
    //cout<<"COM:"<<com(i+1)<<endl;
    //cout<<"a:"<<a<<endl;
    lli b=user(i+1);
    //cout<<"b:"<<b<<endl;

    udp[i][0]= max(a,b);
//cout<<":"<<udp[i][0];
    if(a>b) udp[i][1]=i;
    else udp[i][1]=udp[i+1][1];
    return udp[i][0];
}

lli com(lli i)
{

    if (i==n) return 0;
    if (cdp[i][0]!=-1) return cdp[i][0];
    lli a=arr[i]+dp[i+1]-user(i+1);
    //cout<<"am:"<<a<<" ";
    lli b=com(i+1);
   // cout<<"bcm:"<<b<<" ";
    if(a>b) cdp[i][1]=i;
    else cdp[i][1]=cdp[i+1][1];
    cdp[i][0]= max(a,b);
    return cdp[i][0];
}

void initialization() //index and value ta initialize kra hoice zero diye
{
    for(int i=0; i< 60; i++)
    {
        udp[i][0]=-1;
        cdp[i][0]=-1;
        udp[i][1]=-1;
        cdp[i][1]=-1;


    }
}


int main()
{
    initialization();
    //random cake weight calculation er jonno time function use kra hoice
    time_t t = time(0);
   struct tm* now = localtime(&t);

    int rr=min(now->tm_sec+5, 40);
    printf("Enter how many cakes:");
    scanf("%d",&n);

   // n=5; //kto gula cake index nibo

    // ar te rakha hoice cake index gula
    for(lli i=0; i<n; i++)
    {
        arr[i]=rand()%rr+1;
    }
    //cumulative sum ulta dik theke save kra hoice
    for(lli i=n-1; i>=0; i--)
    {
        dp[i]=arr[i]+dp[i+1];

    }
    //first call user
    lli uu=user(0);
//    for(int i=0; i< n; i++)
//    {
//        printf("%5d ", i);
//        cout<<cdp[i][1]<<"\n";
//    }
    int x;
    int user=0, cm=0, in=-1;
    printf("Game is ready to start\n");
    //index
    for(int i=0; i<n; i++)
    {
        printf("%5d", i+1);
    }
    printf("\n");
    //cake weight
    for(int i=0; i<n; i++)
    {
        printf("%5d", arr[i]);
    }
    printf("\nENTER THE INDEX OF CAKE THAT YOU WANT TO EAT \n->");

    // x indicates which index player want to eat in for boundar checking
    while(scanf("%d",&x) && in+1<=n-1)
    {
       // cout<<"In+1:"<<in+1<<" ";
        //check krbo x er value ki n er theke boro or jeta age diye disi oita or ager gula disse
        if(x>n || x-1<=in)
        {
            printf("INDEX IS NOT VALID");

        }
        else
        {
            //computer array zero theke suru eijonno ek komay dise as user er index 1 theke suru kra hoice

            x--;
          //  cout<<"x:"<<x<<" ";

          //computer er point in cm jeta user fele rakhse tar ager gulaw jog hoie jabe

            for(int i=in+1; i<x; i++)
            {
                cm+=arr[i];
                //cout<<"cm"<<cm<<" ";
            }

            printf("USER MOVES TO :%d\n",x+1);
            printf("USER :%d\n",user+arr[x]);
            printf("COMPUTER :%d\n",cm);
            //in indicates kon index er por theke computer chal dite parbe

            in=udp[x+1][1];

          //  cout<<"in:"<<in<<endl;

          //last index dile ses end hbe
            if(in==-1) break;

//user er point
            for(int i=x; i<in; i++)
            {
                user+=arr[i];
               // cout<<"user:"<<user;
            }

            //maximum value jeta dile luv hsse
            cm+=arr[in];
            //cout<<cm<<"";
            printf("\n->",in+1);

           printf("COMPUTER MOVES TO :%lld\n",in+1);

            printf("USER :%d\n",user);
            printf("COMPUTER :%d\n",cm);
//ses index
            if(in==n-1) break;

printf("\n->");


        }
    }

    printf("\n\n");
    if(user>cm)
        printf("USER WINS");

    else if(user<cm)
        printf("COMPUTER WINS");

    else
        printf("DRAW");
    printf("\n\n");

}
