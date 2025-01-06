//题目大意NxM的地图，p=平原，可放炮兵,炮兵会攻击自己四个方向两个单位的东西，最多可以放几个炮兵使其不会相互攻击

int dp[110][1025][1025],num[1025],g[110],cnt,s[1025];
signed main(){
    ios::sync_with_stdio(false);cin.tie(0);
    int n,m;cin>>n>>m;
    for(int i=1;i<=n;i++){
        int tmp=0;
        for(int j=1;j<=m;j++){
            char c;cin>>c;
            tmp=tmp*2+(c=='P');
        }
        g[i]=tmp;//记录每一行的状态1可放，0不可放
    }
    g[0]=(1<<m)-1;
    for(int i=0;i<(1<<m);i++){
        if(!(i&(i>>1))&&!(i&(i>>2))) s[cnt++]=i;//记录合法状态
        num[i]=__builtin_popcount(i);//记录每个合法状态中有几个1，也就是炮兵
    }

    //dp[i][a][b]前i行，第i行状态为s[a],i-1行状态为s[b]时的最大值
    for(int i=1;i<=n+2;i++){//当前行，到n+2行输出时更方便
        for(int a=0;a<cnt;a++){//第i行的状态
            for(int b=0;b<cnt;b++){//第i-1行的状态
                for(int c=0;c<cnt;c++){//第i-2行的状态
                    if(!(s[a]&s[b])&&!(s[a]&s[c])&&!(s[b]&s[c])&&(g[i]&s[a])==s[a]&&(g[i-1]&s[b])==s[b]){
                       dp[i][s[a]][s[b]]=max(dp[i][s[a]][s[b]],dp[i-1][s[b]][s[c]]+num[s[a]]);
                    }
                }
            }
        }
    }
    cout<<dp[n+2][0][0];
    return 0;
}








//在 N×N 的棋盘里面放 K 个国王，使他们互不攻击，共有多少种摆放方案。国王能攻击到它上下左右，
//以及左上左下右上右下八个方向上附近的各一个格子，共 8 个格子。
signed main(){
    ios::sync_with_stdio(false);cin.tie(0);
    vector<int> num(200),s(1024);
    int cnt=0;
    int n,k;cin>>n>>k;
    for(int i=0;i<(1<<n);i++){
        if(!(i&(i>>1))) num[cnt++]=i;//每一行的合法方案数
        s[i]=__builtin_popcount(i);//合法方案数包含的1的个数，也就是国王的数量
    }
    int dp[11][100][200];//dp[i][j][a]前i行放j个国王，第i行状态为a时的方案数
    dp[0][0][0]=1;
    for(int i=1;i<=n+1;i++){//当前行
        for(int j=0;j<=k;j++){//已放国王数
            for(int a=0;a<cnt;a++){//当前行状态
                for(int b=0;b<cnt;b++){//上一行状态
                    int c=s[num[a]];
                    if(j>=c&&!(num[a]&num[b])&&!(num[a]&(num[b]<<1))&&!(num[a]&(num[b]>>1))){
                        dp[i][j][a]+=dp[i-1][j-c][b];
                    }
                }
            }
        }
    }
    cout<<dp[n+1][k][0]<<"\n";//包含第n行所有状态的方案数总和
    return 0;
}







//房间里放着 n 块奶酪。一只小老鼠要把它们都吃掉，问至少要跑多少距离？老鼠一开始在 (0,0) 点处。

//输入格式
//第一行有一个整数，表示奶酪的数量 n。

//第 2 到第 (n+1) 行，每行两个实数，第 (i+1) 行的实数分别表示第 i 块奶酪的横纵坐标 xi,yi

//输出格式
//输出一行一个实数，表示要跑的最少距离，保留 2 位小数。


double a[20][20];//预处理，从第i块到第j块的距离，使用两点之间距离公式 
double x[20],y[20];//每块奶酪的横、纵坐标
double F[18][34000];//状压DP数组 在第i个点上，走过的二进制状态的十进制表达为j时，最短的距离 
int N; 
double distance(int v,int w)//计算第v个和第w个奶酪之间的距离 
{
	return sqrt((x[v]-x[w])*(x[v]-x[w])+(y[v]-y[w])*(y[v]-y[w]));//两点间距离公式 
}
int main()
{
	int i,j,k;
	double ans;
	memset(F,127,sizeof(F));//这样可以给浮点数赋值无穷大 
	ans=F[0][0];
	scanf("%d",&N);
	for(i=1;i<=N;i++)
	{
		scanf("%lf%lf",&x[i],&y[i]);//数据读入 
	}
	x[0]=0;y[0]=0;
	for(i=0;i<=N;i++)
	{
		for(j=i+1;j<=N;j++)
		{
			a[i][j]=distance(i,j);//初始化距离数组 
			a[j][i]=a[i][j];
		}
	} 
	for(i=1;i<=N;i++)//初始化 
	{
		F[i][(1<<(i-1))]=a[0][i];//在i点上且只有经过i点时距离是原点到i点的距离 
	}
	for(k=1;k<(1<<N);k++)//枚举所有二进制的状态 
	{
		for(i=1;i<=N;i++)
		{
			if((k&(1<<(i-1)))==0)
				continue;//i的位置没被走过，所以不需要再继续计算了 
			for(j=1;j<=N;j++)
			{
				if(i==j)
					continue;//同一个点不需要再计算 
				if((k&(1<<(j-1)))==0)
					continue;//j的位置没走过  
				F[i][k]=min(F[i][k],F[j][k-(1<<(i-1))]+a[i][j]);
			} 
		} 
	} 
	for(i=1;i<=N;i++)
	{
		ans=min(ans,F[i][(1<<N)-1]);
	}
	printf("%.2f\n",ans);
}