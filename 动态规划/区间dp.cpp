//在一个圆形操场的四周摆放 N 堆石子，现要将石子有次序地合并成一堆，规定每次只能选相邻的 
//2 堆合并成新的一堆，并将新的一堆的石子数，记为该次合并的得分。试设计出一个算法,计算出将 N 堆石子合并成 1 堆的最小得分和最大得分。

int n;cin>>n;
    vector<int> a(2*n+1),pre(2*n+1);
    vector<vector<int>> dp1(2*n+1,vector<int>(2*n+1,1e9)),dp2(2*n+1,vector<int>(2*n+1,-1e9));
    for(int i=1;i<=n;i++){
        cin>>a[i];
        a[i+n]=a[i];//将数组扩增一倍
    }
    for(int i=1;i<=2*n;i++){
        pre[i]=pre[i-1]+a[i];//前缀和
        dp1[i][i]=0;dp2[i][i]=0;
    }
    for(int len=2;len<=n;len++){//第一层：枚举长度
        for(int l=1;l+len-1<=2*n;l++){//调用链式模板将范围扩大，枚举左端点
            int r=l+len-1;//右端点
            for(int k=l;k<r;k++){//决策，枚举分割点
                dp1[l][r]=min(dp1[l][r],dp1[l][k]+dp1[k+1][r]+pre[r]-pre[l-1]);
                dp2[l][r]=max(dp2[l][r],dp2[l][k]+dp2[k+1][r]+pre[r]-pre[l-1]);
            }
        }
    }
    int mn=1e9,mx=-1e9;
    for(int i=1;i<=n;i++){
        mn=min(mn,dp1[i][i+n-1]);
        mx=max(mx,dp2[i][i+n-1]);
    }
    cout<<mn<<"\n"<<mx<<"\n";



//n堆石子排成一行，每堆石子数量不同，a和b玩游戏，a先手，两者每次只能从最前面或最后面拿一堆石子，请问最后a会赢吗

   vector<int> a(n+1);
   for(int i=1;i<=n;i++)cin>>a[i];
   vector<vector<int>> dp(n+1,vector<int>(n+1));dp[l][r],区间[l,r]时先手与后手的最大得分差值是多少
   for(int i=1;i<=n;i++) dp[i][i]=a[i];//只剩一个，只能拿这个
   for(int len=2;len<=n;len++){
       for(int l=1;l+len-1<=n;len++){
           int r=l+len-1;
           dp[l][r]=max(a[l]-dp[l+1][r],a[r]-dp[l][r-1]);//
       }
    }
   cout<<dp[1][n];//若dp[1][n]大于0,则a可以赢，如果想知道a可以拿多少石子，可以根据这个结果算出来a-->x,b-->y,则x+y==sum,x-y=dp[1][n];