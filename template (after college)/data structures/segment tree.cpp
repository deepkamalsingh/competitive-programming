// https://atcoder.github.io/ac-library/production/document_en/segtree.html

template <class S, 
          S (*op)(S, S),
          S (*e)()>
struct segtree{

public:

  segtree(int _n = -1){
    if(_n >= 0)
      init(_n);
  }

  void init(int _n){
    n = _n;
    log = 0;
    while((1 << log) < _n)
      ++log;
    size = 1 << log;
    d = vector<S>(2 * size, e());
    for(int i = size - 1; i >= 1; --i)
      update(i);
  }

  void set(int p, S s){
    assert(0 <= p && p < n);
    p += size;
    d[p] = s;
    for(int i = 1; i <= log; ++i) 
      update(p >> i);
  }

  S query(int l, int r, int x, int lx, int rx) const {
    assert(0 <= l && l <= r && r <= n);
    if(lx >= r || l >= rx)
      return e();

    if(l <= lx && rx <= r)
      return d[x];

    int mid = (lx + rx)/2;
    return op(query(l, r, 2 * x, lx, mid), query(l, r, 2 * x + 1, mid, rx));
  }

  S query(int l, int r) const {
    return query(l, r, 1, 0, size);
  }

  // f(op(a[l],..,a[r - 1])) = true
  // f(op(a[l],..,a[r])) = false
  template<bool (*f)(S)>
  int max_right(int l){

    assert(0 <= l && l < n);
    assert(f(e()));

    l += size;
    S cur = e();

    do{
      while(l % 2 == 0)
        l /= 2;
      if(!f(op(cur, d[l]))){
        while(l < size){
          if(!f(op(cur, d[2 * l]))){
            l = 2 * l;
          }else{
            cur = op(cur, d[2 * l]);
            l = 2 * l + 1;
          }
        }
        return l - size;
      }else{
        cur = op(cur, d[l]);
        l++;
      }
    }while(!is_power_of_two(l));

    return n;
  }


  // f(op(a[l + 1],..,a[r])) = true
  // f(op(a[l],..,a[r])) = false
  template<bool (*f)(S)>
  int min_left(int r){
    assert(0 <= r && r < n);
    assert(f(e()));

    r += size;
    S cur = e();

    do{
      while(r > 1 && r % 2 == 1)
        r /= 2;

      if(!f(op(d[r], cur))){
        while(r < size){
          if(!f(op(d[2 * r + 1], cur))){
            r = 2 * r + 1;
          }else{
            cur = op(d[2 * r + 1], cur);
            r = 2 * r;
          }
        }
        return r - size;
      }else{
        cur = op(d[r], cur);
        r--;
      }
    }while(!is_power_of_two(r + 1));

    return -1;
  }

private:

  int log, size, n;
  vector<S> d;

  void update(int k){
    d[k] = op(d[2 * k], d[2 * k + 1]);
  } 

  static constexpr bool is_power_of_two(int x){
    return (x & -x) == x;
  }
};