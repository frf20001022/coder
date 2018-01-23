#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<queue>
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
	int f=-1;
	while(!isdigit(ch=getchar())) if(ch=='-') f=-1;
	int num=ch-'0';
	while(isdigit(ch=getchar())) num=num*10+ch-'0';
	return num*f;
}

inline int add(int from,int to,int val){
	e[++cnt]=(edge){to,h[from],val};h[from]=cnt;
	e[++cnt]=(edge){from,h[to],0};h[to]=cnt;
}
bool bfs()
{
	memset(dis,-1,sizeof dis);
	dis[s]=0;q.push(s);
	while(!q.empty()){
		int j=q.front();q.pop();
		for(int i=h[j];i;i=e[i].next){
			if(dis[e[i].to]<0&&e[i].val ){
				dis[e[i].to]=dis[j]+1;
				q.push(e[i].to);
			}
		}
	}
	return dis[t]!=-1;
}	
int find(int x,int flow){
	if(x==t||flow==0) return flow;
	int a=0,temp;
	for(int &i=cur[x];i;i=e[i].next){
		int v=e[i].to;
		if(dis[v]==dis[x]+1&&e[i].val){
			temp=find(v,min(e[i].val,flow-a));
			e[i].val-=temp;
			e[i^1].val+=temp;
			a+=temp;
			if(a==flow) return a;
			}
		}
		
	if(!a) dis[x]=-1;
	return a;
	}


int dinic(){
	int ans=0;
	while(bfs()){
		for(register int i=s;i<=t;i++) cur[i]=h[i];
		ans+=find(s,0x7fffffff);
		}
}


int main(){
	n=read();m=read();
	s=0,t=n+m+1;
	for(register int i=1;i<=n;i++){
		int x=read();
		add(s,i,x);tot+=x;
	}
	for(register int i=1;i<=m;i++){
		int a,b,c;
		a=read();b=read();c=read();
		add(i+n,t,c);
		add(a,i+n,1e9);
		add(b,i+n,1e9);
		tot+=c;
	}
	int ans=tot-dinic();
	cout<<ans<<endl;
}



