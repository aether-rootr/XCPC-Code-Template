// DA算法 时间复杂度O(nlogn)
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=100010;
int wa[N],wb[N],wv[N],wss[N],cal[N];
int rak[N],height[N],sa[N];
char s[N];
int cmp(int *r,int a,int b,int l)
{return r[a]==r[b]&&r[a+l]==r[b+l];}
//sa
void da(int *r,int *sa,int n,int M) {
     int i,j,p,*x=wa,*y=wb,*t;
     for(i=0;i<M;i++) wss[i]=0;
     for(i=0;i<n;i++) wss[x[i]=r[i]]++;
     for(i=1;i<M;i++) wss[i]+=wss[i-1];
     for(i=n-1;i>=0;i--) sa[--wss[x[i]]]=i;
     for(j=1,p=1;p<n;j*=2,M=p) {
        for(p=0,i=n-j;i<n;i++) y[p++]=i;
        for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
        for(i=0;i<n;i++) wv[i]=x[y[i]];
        for(i=0;i<M;i++) wss[i]=0;
        for(i=0;i<n;i++) wss[wv[i]]++;
        for(i=1;i<M;i++)wss[i]+=wss[i-1];
        for(i=n-1;i>=0;i--) sa[--wss[wv[i]]]=y[i];
        for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
        x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
     }
     return;
}
//height
void calheight(int *r,int *sa,int n) {
     int i,j,k=0;
     for(i=1;i<=n;i++) rak[sa[i]]=i;
     for(i=0;i<n;height[rak[i++]]=k)
     for(k?k--:0,j=sa[rak[i]-1];r[i+k]==r[j+k];k++);
     for(int i=n;i;i--)rak[i]=rak[i-1],sa[i]++;
}
int n,k;
//RMQ
int lg[N], bin[30], d[32][N];
void rmq() {
    bin[0]=1;lg[0]=-1;
    for(int i=1;i<=30;i++)bin[i]=(bin[i-1]<<1);
    for(int i=1;i < N;i++)lg[i]=lg[i>>1]+1;
    int t = lg[n];
    for(int i=1;i<=n;i++)d[0][i]=height[i];
    for(int i=1;i<=t;i++)
        for(int j=1;j+bin[i]-1<=n;j++)
            d[i][j] = min(d[i-1][j], d[i-1][j+bin[i-1]]);
}
int query(int a, int b) {
    a = rak[a], b = rak[b];
    if (a > b) swap(a, b); ++a;
    int t = lg[b-a+1];
    return min(d[t][a], d[t][b-bin[t]+1]);
}
int ok(int x)
{
	int cnt = 0 ;
	for(int i=1;i<=n;i++)
	{
		if(height[i]>=x) cnt ++ ;
		else {
			if(cnt + 1 >= k) return 1;
			cnt = 0;
		}
	}
	return 0 ;
}
int main(){
    int cas=1;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%d",&cal[i]);
    cal[n+1]=0;//不能删除
    da(cal+1,sa,n+1,200);
    calheight(cal+1,sa,n);
    // rmq();
    int l = 1 ,r = n , ans = 0;
    while(l<=r){
        int mid = (l+r)/2;
     	if(ok(mid)){
     	  ans = mid ;
     	  l = mid + 1;
		}else r = mid - 1;
	}
	printf("%d\n",ans);
}
    

/////////////////////////////////////////////////////

//DC3算法,时间复杂度O(n),空间复杂度O(3*n)


#include <cstdio>
#include <cstring>
#include <algorithm>
#define F(x) ((x) / 3 + ((x) % 3 == 1 ? 0 : tb))
#define G(x) ((x) < tb ? (x) * 3 + 1 : ((x) - tb) * 3 + 2)
using namespace std;
const int N = 3*(1e5+5);
int wa[N], wb[N], ws[N], wv[N], sa[N];
int rak[N], height[N], cal[N],n;
char s[N],ans[N],s1[N];
int cnt[N];
int c0(int *r, int a, int b) {
    return r[a] == r[b] && r[a + 1] == r[b + 1] && r[a + 2] == r[b + 2];
}
int c12(int k, int *r, int a, int b) {
    if (k == 2)
        return r[a] < r[b] || r[a] == r[b] && c12(1, r, a + 1, b + 1);
    return r[a] < r[b] || r[a] == r[b] && wv[a + 1] < wv[b + 1];
}
void Rsort(int *r, int *a, int *b, int n, int m) {
    for (int i = 0; i < n; i++) wv[i] = r[a[i]];
    for (int i = 0; i < m; i++) ws[i] = 0;
    for (int i = 0; i < n; i++) ws[wv[i]]++;
    for (int i = 1; i < m; i++) ws[i] += ws[i - 1];
    for (int i = n - 1; i >= 0; i--) b[--ws[wv[i]]] = a[i];
}
void dc3(int *r, int *sa, int n, int m) {
    int i, j, *rn = r + n, *san = sa + n, ta = 0, tb = (n + 1) / 3, tbc = 0, p;
    r[n] = r[n + 1] = 0;
    for (i = 0; i < n; i++) if (i % 3 != 0) wa[tbc++] = i;
    Rsort(r + 2, wa, wb, tbc, m);
    Rsort(r + 1, wb, wa, tbc, m);
    Rsort(r, wa, wb, tbc, m);
    for (p = 1, rn[F(wb[0])] = 0, i = 1; i < tbc; i++)
        rn[F(wb[i])] = c0(r, wb[i - 1], wb[i]) ? p - 1 : p++;
    if (p < tbc) dc3(rn, san, tbc, p);
    else for (i = 0; i < tbc; i++) san[rn[i]] = i;
    for (i = 0; i < tbc; i++) if (san[i] < tb) wb[ta++] = san[i] * 3;
    if (n % 3 == 1) wb[ta++] = n - 1;
    Rsort(r, wb, wa, ta, m);
    for (i = 0; i < tbc; i++) wv[wb[i] = G(san[i])] = i;
    for (i = 0, j = 0, p = 0; i < ta && j < tbc; p++)
        sa[p] = c12(wb[j] % 3, r, wa[i], wb[j]) ? wa[i++] : wb[j++];
    for (; i < ta; p++) sa[p] = wa[i++];
    for (; j < tbc; p++) sa[p] = wb[j++];
}
void calheight(int *r, int *sa, int n) {
    int i, j, k = 0;
    for (i = 1; i <= n; i++) rak[sa[i]] = i;
    for (i = 0; i < n; height[rak[i++]] = k)
        for (k ? k-- : 0, j = sa[rak[i] - 1]; r[i + k] == r[j + k]; k++);
    for(int i=n;i;i--) rak[i]=rak[i-1];
    for(int i=n;i;i--) sa[i]++;
}
int main() {
    while (scanf("%s", s+1)&&s[1] != '#') {
        n = strlen(s+1);
        for (int i = 1; i <= n; i++)
            cal[i] = s[i] - 'a' + 1;
        cal[n+1] = 0;
        dc3(cal+1, sa, n + 1, 30);
        calheight(cal+1, sa, n);
        for(int i=1;i<=n;i++) {
            printf("%d ",height[i]);
        }puts("");
    }
    return 0;
}

