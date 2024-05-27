struct dsu {

public:

  dsu(int _n = 0){
    init(_n);
  }

  void init(int _n){
    z = n = _n;
    parent_or_size.assign(n, -1);
  } 

  bool merge(int a, int b){
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    int x = leader(a), y = leader(b);
    if(x == y) 
      return false;
    if(-parent_or_size[x] < -parent_or_size[y]) 
      swap(x, y);
    parent_or_size[x] += parent_or_size[y];
    parent_or_size[y] = x;
    z--;
    return true;
  }

  bool same(int a, int b){
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    return leader(a) == leader(b);
  }

  int leader(int a){
    assert(0 <= a && a < n);
    if(parent_or_size[a] < 0) 
      return a;
    return parent_or_size[a] = leader(parent_or_size[a]);
  }

  int size(int a){
    return -parent_or_size[leader(a)];
  }
  
  vector<vector<int>> groups() {
    vector<vector<int>> result(n);
    for(int i = 0; i < n; i++)
      result[leader(i)].push_back(i); 
    result.erase(remove_if(result.begin(), result.end(),[&](const auto& v){return v.empty(); }),result.end());
    return result;
  }

  int comp() const {
    return z;
  }

private:
  
  int n, z;
  vector<int> parent_or_size;

};