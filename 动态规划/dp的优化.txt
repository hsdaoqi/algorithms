1.单调队列优化dp,有一定区间转移来的


烽火台是重要的军事防御设施，一般建在交通要道或险要处。一旦有军情发生，则白天用浓烟，晚上有火光传递军情。
在某两个城市之间有 n 座烽火台，每个烽火台发出信号都有一定的代价。为了使情报准确传递，在连续 m 个烽火台中至少要有一个发出信号。现在输入 n,m 和每个烽火台的代价，请计算总共最少的代价在两城市之间来准确传递情报。
int n,m;cin>>n>>m;
    vector<int> a(n+2),dp(n+2);
    for(int i=1;i<=n;i++) cin>>a[i];
    deque<int> q;q.push_back(0);
    for(int i=1,j=0;i<=n+1;i++){
        if(i-j>m) j++;
        while(!q.empty()&&q.front()<j) q.pop_front();
        dp[i]=dp[q.front()]+a[i];
        while(!q.empty()&&dp[q.back()]>dp[i]) q.pop_back();
        q.push_back(i);
    }
    cout<<dp[n+1]<<"\n";