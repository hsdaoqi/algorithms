//windy定义了一种windy数。不含前导零且相邻两个数字之差至少为2的正整数被称为windy数。
//windy想知道， 在A和B之间，包括A和B，总共有多少个windy数？

//数位dp模板。数位dp一般以递归来写
int dig[20],dp[20][12][2];
int dfs(int idx,int last,int lead,bool lim){//第几位,上一位数，是否有前导零，是否限制此数位
    if(idx<0) return 1;
    if(!lim&&dp[idx][last][lead]!=-1) return dp[idx][last][lead];
    int ans=0,up=lim?dig[idx]:9;
    for(int i=0;i<=up;i++){
        if(lead&&abs(i-last)<2) continue;//如果前面不全为零，并且两个数位之差小于2，不合法
        ans += dfs(idx-1,i,lead||i,lim&&i==up);
    }
    if(!lim) dp[idx][last][lead]=ans;//记忆化搜索
    return ans;
}

int count(int x){//求出1~n满足条件的合法的数
    int siz=0;
    memset(dp,-1,sizeof(dp));
    while(x){
        dig[siz++]=x%10;
        x/=10;
    }
    return dfs(siz-1,0,0,1);
}
void solve(){
    int l,r;cin>>l>>r;
    cout<<count(r)-count(l-1);
}



//沃洛佳是个古怪的孩子，他的品味也很奇怪。在他看来，一个正整数只有且仅当它能被它的每个非零数字整除时，才是美丽的。我们不争论这个问题，只计算//在给定范围内美丽数字的数量。

int dig[20],dp[20][2521][50],doc[2522],id;
void Init(){
    for(int i=1;i<=2520;i++){
        if(2520%i==0) doc[i]=id++;//1~9的最小公倍数为2520，记录一下不然dp数组开不下
    }
}
int dfs(int idx,int lc,int now,bool lim){//模板
    if(idx<0) return lc&&now%lc==0;
    if(!lim&&dp[idx][now][doc[lc]]!=-1) return dp[idx][now][doc[lc]];
    int ans=0,up=lim?dig[idx]:9;
    for(int i=0;i<=up;i++){
        ans+=dfs(idx-1, i!=0?lcm(lc,i):lc,(now*10+i)%2520,lim&&i==up);
    }
    if(!lim) dp[idx][now][doc[lc]]=ans;
    return ans;
}
int count(int n){
    int siz=0;
    while(n){
        dig[siz++]=n%10;
        n/=10;
    }
    return dfs(siz-1,1,0,1);
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(0);
    Init();
    memset(dp,-1,sizeof(dp));//放到外面初始化，避免多次初始化
    int t;cin>>t;
    while(t--) {
        int l, r;
        cin >> l >> r;
        cout << count(r) - count(l - 1) << "\n";
    }
    return 0;
}



//如果一个正整数的二进制表示中，0 的数目不小于 1 的数目，那么它就被称为「圆数」。
//例如，9 的二进制表示为 1001，其中有 2 个 0 与 2 个 1因此，9 是一个「圆数」。请你计算，区间 [l,r] 中有多少个「圆数」。

int dig[40],dp[40][65][2];
int dfs(int idx,int cha,int lead,bool lim){//套路模板
    if(idx<0) return !lead&&cha>=30;
    if(!lim&&dp[idx][cha][lead]!=-1) return dp[idx][cha][lead];
    int ans=0,up=lim?dig[idx]:1;//因为是二进制，所以最大到1
    for(int i=0;i<=up;i++){
        ans+=dfs(idx-1,cha+(lead?(i?-1:0):(i?-1:1)),lead&&!i,lim&&i==up);
    }
    if(!lim) dp[idx][cha][lead]=ans;
    return ans;
}
int count(int x){
    int siz=0;
    while(x){
        dig[siz++]=x%2;//因为题目要求二进制形式下的规律，所以转化为二进制
        x/=2;
    }
    memset(dp,-1,sizeof (dp));
    return dfs(siz-1,30,1,1);
}



//题目大意：一个数k的LIS称作这个数每个数位上的数字的LIS,例如1324的LIS为3. 求[L,R]中有多少个数的LIS = k.
//很显然，这是道数位dp题,但是要怎么记录状态呢？
//考虑LIS问题的O(nlogn)做法，每次插入一个数，找第一个大于这个数的数，弹出去，再插入这个数.最后还有多少个数，LIS就是多少。组成LIS的数字只有0 ~9,所以可以用一个二进制数S来表示状态，如果S的第i位为1，就说明i这个数存在.那么f[i][j]表示处理到第i位，状态为j的个数，这样处理就可以了.

int dp[25][12][1024][12],dig[25];
int K;
void calc(int &doc,int &k,int p){
    int bit=-1;
    for(int i=p;i<=9;i++){
        if(doc&(1<<i)){
            bit=i;
            break;
        }
    }
    if(bit==-1){
        doc |= 1<<p;
        k++;
    }else{
        doc -= 1<<bit;
        doc |= 1<<p;
    }
}
int dfs(int idx,int doc,int k,bool lead,bool lim){
    if(idx<0) return K==k;
    if(!lim&&dp[idx][K][doc][k]!=-1) return dp[idx][K][doc][k];
    int ans=0,up=lim?dig[idx]:9;
    for(int i=0;i<=up;i++){
        int ndoc=doc,nk=k;
        if(lead&&!i) nk=0;
        else calc(ndoc,nk,i);
        ans+=dfs(idx-1,ndoc,nk,lead&&i==0,lim&&i==up);
    }
    if(!lim) dp[idx][K][doc][k]=ans;
    return ans;
}
int count(int x){
    int siz=0;
    while(x) {
        dig[siz++] = x % 10;
        x /= 10;
    }
    return dfs(siz-1,0,0,1,1);
}











