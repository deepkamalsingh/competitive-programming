

template<typename T>
struct fenwick_tree{

public:  

  fenwick_tree(int _n = 0){
    init(_n);
  }

  void init(int _n){
    n = _n;
    tree.assign(_n + 1, 0);
  }

  // i belongs to [0,n)
  void update(int i, T val){
    assert(0 <= i && i < n);
    for(++i; i <= n; i += i & -i)
      tree[i] += val;
  }

  void set(int i, T val){
    update(i, val - query(i, i + 1));
  }

  // returns sum until [0,i)
  T query(int i) const {
    assert(0 <= i && i <= n);
    T ret = 0;
    for(; i > 0; i -= i & -i)
      ret += tree[i];
    return ret;
  }

  // sum on range [l,r)
  T query(int l, int r) const {
    assert(0 <= l && l <= r && r <= n);
    return query(r) - query(l);
  }

  // returns largest i in [0,n] s.t. query(i) <= sum or -1 if sum < 0. 
  int find_last_prefix(int sum) const {
    if(sum < 0)
      return -1;

    int p = 0;
    for(int k = 31 - __builtin_clz(n); k >= 0; --k){
      if(p + (1 << k) <= n && tree[p + (1 << k)] <= sum){
        p += 1 << k;
        sum -= tree[p];
      }
    }
    return p;
  }

private:
  
  int n;
  vector<T> tree;
  
};