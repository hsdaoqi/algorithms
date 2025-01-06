template<class T>
int minp(vector<T> s){
    int n=s.size();
    for(int i=1;i<n;i++) s.push_back(s[i]);
    int i=1,j=2,k=0;
    while(i<n&&j<n){
        for(k=0;k<n&&s[i+k]==s[j+k];k++);
        s[i+k]>s[j+k]?i=i+k+1:j=j+k+1;
        if(i==j) j++;
    }
    return min(i,j);
}