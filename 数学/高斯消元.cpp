//高斯消元法
struct GAUSS{
    const double eps=1e-6;
    bool gauss(std::vector<std::vector<double>> &a){
        int n=a.size()-1;
        for(int i=1;i<=n;i++){//枚举行列
            int r=i;
            for(int k=i;k<=n;k++){//找非零行
                if(fabs(a[k][i])>eps){
                    r=k;break;
                }
            }
            if(r!=i) std::swap(a[r],a[i]);//换行
            if(fabs(a[i][i])<eps) return false;//无解或无穷解
            for(int j=n+1;j>=i;j--) a[i][j]/=a[i][i];//变一
            for(int k=i+1;k<=n;k++){//变零
                for(int j=n+1;j>=i;j--){
                    a[k][j]-=a[k][i]*a[i][j];
                }
            }
        }
        for(int i=n-1;i>=1;i--){//回代
            for(int j=i+1;j<=n;j++){
                a[i][n+1]-=a[i][j]*a[j][n+1];
            }
        }
        return true;
    }

    int gaussJordan(std::vector<std::vector<double>> &a){
        int n=a.size()-1,r = 1;
        for(int c=1;c<=n;c++){//枚举列
            int now=r;
            double mx=fabs(a[r][c]);
            for(int i=r+1;i<=n;i++){//找非零行
                if(fabs(a[i][c])>mx){
                    now=i;
                    mx=fabs(a[i][c]);
                }
            }
            if(mx<eps) continue;//跳过当前行
            std::swap(a[r],a[now]);

            for(int i=1;i<=n;i++){//对角化
                if(r==i) continue;
                double t=a[i][c]/a[r][c];
                for(int j=c+1;j<=n+1;j++){
                    a[i][j]-=t*a[r][j];
                }
            }
            r++;//当前行变成下一行
        }
        if(r<=n){
            for(int i=r;i<=n;i++){
                if(fabs(a[i][n+1])>eps) return -1;//无解
            }
            return 0;//无穷解
        }
        for(int i=1;i<=n;i++) a[i][n+1]/=a[i][i];
        return 1;//为一解
    }
};