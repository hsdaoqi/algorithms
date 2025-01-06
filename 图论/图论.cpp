1.树上一个点x到路径u-->v的最短路径距离为，dep[x]+dep[lca(u,v)]-dep[lca(x,u)]-dep[lca(x,v)]

2.树上一个点u到v的最短路径距离为，dep[u]+dep[v]-2*dep[lca(u,v)]