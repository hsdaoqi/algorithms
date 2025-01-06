//0-1背包(不压缩空间)
    int n,m;cin>>n>>m;
    vector<int> v(n+1),w(n+1);
    vector<vector<int>> dp(n+1,vector<int>(m+1));
    for(int i=1;i<=n;i++){
        cin>>w[i]>>v[i];//体积,价值
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){//要倒序枚举
            dp[i][j]=max(dp[i][j],dp[i-1][j]);//不选
           if(j>=w[i]) dp[i][j]=max(dp[i][j],dp[i-1][j-w[i]]+v[i]);//选
        }
    }
    cout<<dp[n][m]<<"\n";

//0-1背包(压缩空间)
    int n,m;cin>>n>>m;
    vector<int> v(n+1),w(n+1),dp(m+1);
    for(int i=1;i<=n;i++){
        cin>>v[i]>>w[i];//价值，体积
    }
    for(int i=1;i<=n;i++){
        for(int j=m;j>=w[i];j--){//要倒序枚举
            dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
        }
    }
    cout<<dp[m]<<"\n";

//完全背包(不压缩空间)
    int n,m;cin>>n>>m;
    vector<int> v(n+1),w(n+1);
    vector<vector<int>> dp(n+1,vector<int>(m+1));
    for(int i=1;i<=n;i++){
        cin>>w[i]>>v[i];//体积,价值
    }
    for(int i=1;i<=n;i++){
        for(int j=w[i];j<=m;j++){//要倒序枚举
            dp[i][j]=max(dp[i-1][j],dp[i][j]);//不选
           if(j>=w[i]) dp[i][j]=max(dp[i][j],dp[i][j-w[i]]+v[i]);//选
        }
    }
    cout<<dp[n][m]<<"\n";

//完全背包(压缩空间)
    int n,m;cin>>n>>m;
    vector<int> v(n+1),w(n+1),dp(m+1);
    for(int i=1;i<=n;i++){
        cin>>w[i]>>v[i];//体积,价值
    }
    for(int i=1;i<=n;i++){
        for(int j=w[i];j<=m;j++){//要倒序枚举
            dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
        }
    }
    cout<<dp[m]<<"\n";

//多重背包(朴素写法,O(m*si的和))
    int n,m;cin>>n>>m;
    vector<int> v(n+1),w(n+1),s(n+1);//价值，体积，数量
    vector<int> dp(m+1);
    for(int i=1;i<=n;i++){
        cin>>w[i]>>v[i]>>s[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=m;j>=w[i];j--){//要倒序枚举
            for(int k=0;k<=s[i]&&k*w[i]<=j;k++){
                dp[j]=max(dp[j],dp[j-k*w[i]]+k*v[i]);
            }
        }
    }
    cout<<dp[m]<<"\n";


//多重背包(二进制优化,O(m*log(si的和)))
    int n,m;cin>>n>>m;
    vector<int> v(1),w(1);//价值，体积，数量
    vector<int> dp(m+1);
    for(int i=1;i<=n;i++){
        int ss,ww,vv;cin>>ss>>ww>>vv;
        for(int j=1;j<=ss;j<<=1){
            v.push_back(vv*j);
            w.push_back(ww*j);
            ss-=j;
        }
        if(ss){
            v.push_back(ss*vv);
            w.push_back(ss*ww);
        }
    }
    //01背包处理
    n=v.size()-1;
    for(int i=1;i<=n;i++){
        for(int j=m;j>=w[i];j--){
            dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
        }
    }
    cout<<dp[m]<<"\n";



//多重背包--单调队列优化(O(nm))
    int n,m;cin>>n>>m;
    int dp[N],pre[N],q[N];
    memset(dp,0,sizeof (dp));
    for(int i=1;i<=n;i++){
        int w,v,s;cin>>w>>v>>s;//体积，价值,数量
        memcpy(pre,dp,sizeof (dp));//备份dp
        for(int j=0;j<w;j++){//分成w个类
            int l=0,r=-1;
            for(int k=j;k<=m;k+=w){//对每个类使用单调队列
                //q[l]不在窗口[k-s[i]*w[i],k-w[i]]内，队头出列
                if(l<=r&&q[l]<k-w*s) l++;
                //使用队头最大值更新dp
                if(l<=r) dp[k]=max(pre[k],pre[q[l]]+(k-q[l])/w*v);
                //当前值比队尾值更有价值，队尾出列
                while(l<=r&&pre[k]>=pre[q[r]]+(k-q[r])/w*v) r--;
                q[++r]=k;//下标入队，方便队头出列
            }
        }
    }
    cout<<dp[m]<<"\n";


//混合背包
//若s[i]==-1,则只有一个此物品,s[i]==0,有无数个，s[i]>0,有s[i]次个物品
//先将多重背包转化为01背包，之后跑01背包和完全背包的代码
    int n, m;
    cin >> n >> m;
    vector<int> v(1), w(1), s(1);//价值，体积，数量
    vector<int> dp(m + 1);
    for (int i = 1; i <= n; i++) {
        int ss, ww, vv;
        cin >> ww >> vv >> ss;
        if (ss == 0) {
            v.push_back(vv);
            w.push_back(ww);
            s.push_back(0);
        } else {
            if (ss == -1) ss = 1;
            for (int j = 1; j <= ss; j <<= 1) {
                v.push_back(vv * j);
                w.push_back(ww * j);
                s.push_back(1);
                ss -= j;
            }
            if (ss) {
                s.push_back(1);
                v.push_back(ss * vv);
                w.push_back(ss * ww);
            }
        }
    }
    //做一遍两类背包
    n = v.size()-1;
    for (int i = 1; i <= n; i++) {
        if (s[i] == 1) {//01背包
            for (int j = m; j >= w[i]; j--) {
                dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
            }
        } else {//完全背包
            for (int j = w[i]; j <= m; j++) {
                dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
            }
        }
    }
    cout << dp[m] << "\n";

//二维费用背包
    int n,V,M;cin>>n>>V>>M;//物品数量，背包容量，背包承重
    vector<int> w(n+1),m(n+1),v(n+1);//物品的体积，重量，价值
    vector<vector<int>> dp(V+1,vector<int>(M+1));//在背包容量为V,承重为M时，所能得到的最大值
    for(int i=1;i<=n;i++){
        cin>>w[i]>>m[i]>>v[i];//仿照01背包
        for(int j=V;j>=w[i];j--){
            for(int k=M;k>=m[i];k--){
                dp[j][k]=max(dp[j][k],dp[j-w[i]][k-m[i]]+v[i]);
            }
        }
    }
    cout<<dp[V][M]<<"\n";


//分组背包
    int n,m;cin>>n>>m;
    vector<int> v(N),w(N),dp(m+1);//价值，体积
    for(int i=1;i<=n;i++){//物品
        int s;cin>>s;
        for(int j=1;j<=s;j++) cin>>w[j]>>v[j];
        for(int j=m;j>=1;j--){//体积
            for(int k=1;k<=s;k++){//决策
                if(j>=w[k]) dp[j]=max(dp[j],dp[j-w[k]]+v[k]);
            }
        }
    }
    cout<<dp[m]<<"\n";

//背包求方案数
    int n,m;cin>>n>>m;
    vector<int> v(N),w(N),dp(m+1),c(m+1,1);//价值，体积,c[i]:背包容量为i时最优选法的方案数
    for(int i=1;i<=n;i++) {
        cin>>w[i]>>v[i];
        for(int j=m;j>=w[i];j--){
            if(dp[j-w[i]]+v[i]>dp[j]){
                dp[j]=dp[j-w[i]]+v[i];
                c[j]=c[j-w[i]];
            }else if(dp[j-w[i]]+v[i]==dp[j]){
                c[j]=(c[j]+c[j-w[i]])%mod;
            }
        }
    }
    cout<<c[m]<<"\n";


    //背包求具体方案(背景：0-1背包)
    //输出一行，包含若干个用空格隔开的整数，表示最优解中所选物品的编号序列，且该编号序列的字典序最小。
    int n,m;cin>>n>>m;
    vector<int> v(N),w(N);//价值，体积,c[i]:背包容量为i时最优选法的方案数
    vector<vector<int>> dp(n+2,vector<int>(m+1));
    for(int i=1;i<=n;i++) cin>>w[i]>>v[i];
    for(int i=n;i>=1;i--){//逆序取物
        for(int j=0;j<=m;j++){
            dp[i][j]=dp[i+1][j];
            if(j>=w[i]) dp[i][j]=max(dp[i][j],dp[i+1][j-w[i]]+v[i]);
        }
    }
    int rest=m;//背包剩余容量
    for(int i=1;i<=n;i++){//找路
        if(rest>=w[i]&&dp[i][rest]==dp[i+1][rest-w[i]]+v[i]){
            cout<<i<<" ";
            rest-=w[i];//选了第i个物品，剩余容量要减小
        }
    }


//逆向思维，当代价w很大,但价值v很小时，我们可以定义dp[i]为，当价值为i时，可以使用的最小代价
    int n,m;cin>>n>>m;
    vector<int> v(n),w(n);
    for(int i=0;i<n;i++) cin>>w[i]>>v[i];
    int c= accumulate(v.begin(),v.end(),0ll);//先算出总的价值
    vector<int> dp(c+1,1e18);
    dp[0]=0;
    for(int i=0;i<n;i++){
        for(int j=c;j>=v[i];j--){
            dp[j]=min(dp[j],dp[j-v[i]]+w[i]);
        }
    }
    for(int i=c;i>=0;i--){
        if(dp[i]<=m){//如果达到某个价值时的代价<=m，就返回
            cout<<i<<"\n";
            return;
        }
    }