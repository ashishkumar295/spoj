#include <bits/stdc++.h>
using namespace std;
 
#define icin(x) scanf("%d",&x)
typedef long long LL;
const int maxn=int(5e5)+10;
 
class SuffixArray{
public:
	int n;
	char S[maxn];
	int RA[maxn], tempRA[maxn];		// rank array
	int SA[maxn], tempSA[maxn];		// suffix array
	int c[maxn];									// counting sort
	int phi[maxn], PLCP[maxn], LCP[maxn];		// LCP array
 
	void computeSA(){
		n = (int)strlen(S);
		S[n++] = '$';
 
		for(int i=0;i<n;i++) RA[i] = S[i];
		for(int i=0;i<n;i++) SA[i] = i;
		for(int k=1;k<n;k<<=1){
			countingSort(k);
			countingSort(0);
			int r;
			tempRA[SA[0]] = r = 0;
			for(int i=1;i<n;i++)
				tempRA[SA[i]] = ((RA[SA[i]] == RA[SA[i-1]]) && (RA[SA[i]+k] == RA[SA[i-1]+k])) ? r : ++r;
			for(int i=0;i<n;i++)
				RA[i] = tempRA[i];
			if(RA[SA[n-1]] == n-1)
				break;
		}
	}
	void countingSort(int k){
		int maxi = max(256, n);
		fill(c, c + maxi, 0);
		for(int i=0;i<n;i++)
			c[i+k<n ? RA[i+k] : 0]++;
		for(int i=0, sum=0;i<maxi;i++){
			int t = c[i];
			c[i] = sum;
			sum += t;
		}
		for(int i=0;i<n;i++)
			tempSA[c[SA[i]+k<n ? RA[SA[i]+k] : 0]++] = SA[i];
		for(int i=0;i<n;i++)
			SA[i] = tempSA[i];
	}
	void computeLCP(){
		phi[SA[0]] = -1;
		for(int i=1;i<n;i++)
			phi[SA[i]] = SA[i-1];
		for(int i=0, l=0;i<n;i++){
			if(phi[i]==-1){
				PLCP[i]=0;
				continue;
			}
			while(S[i+l] == S[phi[i]+l])l++;
			PLCP[i] = l;
			l = max(l-1, 0);
		}
		for(int i=0;i<n;i++)
			LCP[i] = PLCP[SA[i]];
	}
};

char A[maxn], B[maxn];
int main(){
	SuffixArray sa;
	scanf("%s", A);
	scanf("%s", B);
	int n1 =(int)strlen(A), n2 = (int)strlen(B);
	cout<<n1<<" "<<n2<<endl;
	memcpy(sa.S, A, n1);
	sa.S[n1]='#';
	memcpy(sa.S+n1+1, B, n2); 
	
	sa.computeSA();
	sa.computeLCP();
	int res=-1;
	for(int i=1;i<sa.n;i++){
		int sa1 = sa.SA[i], sa2 = sa.SA[i-1];
		if(min(sa1, sa2)<n1 && max(sa1, sa2)>n1 && sa.LCP[i]>res)
			res = sa.LCP[i];
	}
	printf("%d\n",res);
	return 0;
} 