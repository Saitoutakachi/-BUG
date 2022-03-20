#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int e[100010],h[100010],ne[100010],idx=0;
int d[100010];
int res[100010];
int n,m;
int k=0;

void add(int x,int y){
    e[idx]=y;ne[idx]=h[x];h[x]=idx++;
    d[y]++;
}

bool to_sort(){
    queue<int> q;
    for(int i=1;i<=n;i++){
        if(d[i]==0){
            q.push(i);
        }
    }
    while(q.size()){
        int temp=q.front();
        q.pop();
        res[k]=temp;
        k++;
        for(int i=h[temp];i!=-1;i=ne[i]){
            int j=e[i];
            d[j]--;
            if(d[j]==0){
                q.push(j);
            }
        }
    }
    if(k==n)
        return true;
    else
        return false;
}

int main(){
    memset(h,-1,sizeof(h));
    scanf("%d%d",&n,&m);
    while(m--){
        int x,y;
        scanf("%d%d",&x,&y);
        add(x,y);
    }
    if(to_sort()){
        for(int i=0;i<k;i++){
            cout<<res[i]<<" ";
        }
    }
    else
        cout<<-1<<endl;
    return 0;
}
