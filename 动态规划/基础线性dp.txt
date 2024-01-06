//最长上升子序列
int maxLAS(vector<int> &a){
    int n=a.size()-1,ans=0;
    vector<int> dp(n+1,1);
    for(int i=2;i<=n;i++){
        for(int j=1;j<i;j++){
            if(a[i]>a[j]) dp[i]=max(dp[i],dp[j]+1);
        }
        ans=max(ans,dp[i]);
    }
    return ans;
}



//最长上升子序列(二分优化)
int maxLAS(vector<int> &a){
    int n=a.size(),ans=1;
    vector<int> dp(n,0);
    dp[1]=a[1];
    for(int i=2;i<n;i++){
        if(a[i]>dp[ans]){
            dp[++ans]=a[i];
        }else{
            *lower_bound(dp.begin(),dp.begin()+ans+1,a[i])=a[i];
        }
    }
    return ans;
}



//最长公共子序列
int maxLCS(string &a,string &b){
    int n=a.size(),m=b.size();
    vector<vector<int>> dp(n+1,vector<int>(m+1,0));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i-1]==b[j-1])//注意下标
                dp[i][j]=dp[i-1][j-1]+1;
            else
                dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
        }
    }
    return dp[n][m];
}



//获取最长公共子序列
string getLCS(string &a,string &b){
    int n=a.size(),m=b.size();
    vector<vector<int>> dp(n+1,vector<int>(m+1,0));
    auto p=dp;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i-1]==b[j-1]) {//注意下标
                dp[i][j] = dp[i - 1][j - 1] + 1;
                p[i][j]=1;//左上方
            }else if(dp[i][j-1]>dp[i-1][j]) {
                dp[i][j]=dp[i][j-1];
                p[i][j]=2;//左边
            }else{
                dp[i][j]=dp[i-1][j];
                p[i][j]=3;//上边
            }
        }
    }
    //倒推公共子序列
    string s="";
    for(int i=n,j=m;i>0&&j>0;){
        if(p[i][j]==1){//左上方
            s=a[i-1]+s;
            i--;j--;
        }else if(p[i][j]==2) j--;//左边
        else i--;//上边
    }
    return s;
}



//最长公共子串
int getLCS(string &a,string &b){
    int n=a.size(),m=b.size();
    vector<int> dp(m+1);
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=m;j>=1;j--){
            if(a[i-1]==b[j-1]) dp[j]=dp[j-1]+1;//压缩空间之前dp[i][j]=dp[i-1][j-1]+1;
            ans=max(ans,dp[j]);
        }
    }
    return ans;
}



//编辑距离(将字符串a通过修改，插入，删除变为b所需要的最小操作次数)
    int LD(string &a,string &b){
        int n=a.size(),m=b.size();
        vector<vector<int>> dp(n+1,vector<int>(m+1));
        for(int i=1;i<=n;i++) dp[i][0]=i;
        for(int j=1;j<=m;j++) dp[0][j]=j;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(a[i-1]==b[j-1]) dp[i][j]=dp[i-1][j-1];
                else dp[i][j]=min(dp[i-1][j-1],min(dp[i][j-1],dp[i-1][j]))+1;//对应修改，插入，删除
            }
        }
        return dp[n][m];
    }





