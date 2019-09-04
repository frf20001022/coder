#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<queue>
#define debug printf("%d--{%s}\n",__LINE__,__FUNCTION__);
using namespace std;
const int maxn = 60000;
const int maxm = 320000;
struct edge
{
	int to,next,val;
}e[maxm];
int h[maxn],dis[maxn],cur[maxn];
int n,m,tot,cnt=1,s,t;
queue<int> q;
inline int read(){
	char ch='*';
	int f=1;
	while(!isdigit(ch=getchar())) if(ch=='-') f=-1;
	int num=ch-'0';
	while(isdigit(ch=getchar())) num=num*10+ch-'0';
	return num*f;
}

inline void add(int from,int to,int val)
{
    e[++cnt].next=h[from];
    e[cnt].to=to;
    e[cnt].val=val;
    h[from]=cnt;
    e[++cnt].next=h[to];
    e[cnt].to=from;
    e[cnt].val=0;
    h[to]=cnt;
}
inline bool bfs()
{
    memset(dis,-1,sizeof(dis));
    dis[s]=0;	
    q.push(s);
    int j;
    while(!q.empty()){
        j=q.front();q.pop();
        for(register int i=h[j];i;i=e[i].next)
        {
            int v=e[i].to;
            if(dis[v]<0&&e[i].val>0)
            {
                dis[v]=dis[j]+1;
                q.push(v);
                
            }
        }
    }
    return dis[t]>0;
}
int qmin(int a, int b)
{
    int diff = b - a;
    // b < a: a + (diff & -1)
    // b > a: a + (diff &  0)
    return a + (diff & (diff >> 31));
}
int find(int x,int flow)
{
    if(x==t||flow==0) return flow;
    int a=0;
    int f=0;
    for(register int &i=cur[x];i;i=e[i].next)
    {
        //int v=e[i].to;
        if(e[i].val&&dis[x]<dis[e[i].to])
        {
            f=find(e[i].to,qmin(e[i].val,flow-a));
            e[i].val-=f;
            e[i^1].val+=f;
            a+=f;
            if(a==flow)break;
        }
    }
    if(!a) dis[x]=-1;
    return a;
}
inline int dinic()
{
    register int ans=0;
    while(bfs())
    {
        for(register int i=s;i<=t;i++) cur[i]=h[i];
        ans+=find(s,0x7fffffff);
    }
    return ans;
}

int main(){
//	debug
	n=read();m=read();
	s=0,t=n+m+1;
	for(register int i=1;i<=n;i++){
		int x=read();
		add(i+m,t,x);
	}
//	debug
	for(register int i=1;i<=m;i++){
		int a,b,c;
		a=read();b=read();c=read();
		add(s,i,c);
		add(i,a+m,1e9);
		add(i,b+m,1e9);
		tot+=c;
	}
//	debug
	int ans=tot-dinic();
	//cout<<tot<<endl;
	cout<<ans<<endl;
}


