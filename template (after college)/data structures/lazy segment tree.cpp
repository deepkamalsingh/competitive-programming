// source : https://atcoder.github.io/ac-library/production/document_en/lazysegtree.html

// struct S{

// };

// S op(S l, S r){

// }

// S e(){

// }

// struct F{

// };

// S mapping(F f, S s){

// }

// F composition(F f, F g){

// }

// F id(){

// }

template <class S,
          S (*op)(S, S),
          S (*e)(),
          class F,
          S (*mapping)(F, S),
          F (*composition)(F, F),
          F (*id)()>
struct lazy_segtree{

public:

  lazy_segtree(int _n = -1){
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
    lz = vector<F>(size, id());
  }

  void set(int p, S x){
    assert(0 <= p && p < n);
    p += size;
    for(int i = log; i >= 1; --i) 
      push(p >> i);
    d[p] = x;
    for(int i = 1; i <= log; ++i)
      update(p >> i);
  }

  S get(int p){
    assert(0 <= p && p < n);
    p += size;
    for(int i = log; i >= 1; --i)
      push(p >> i);
    return d[p];
  }

  void range_update(int l, int r, int x, int lx, int rx, F f){
    push(x);

    if(lx >= r || l >= rx)
      return;

    if(l <= lx && rx <= r){
      apply(x, f);
    }else{
      int mid = (lx + rx)/2;
      range_update(l, r, 2 * x, lx, mid, f);
      range_update(l, r, 2 * x + 1, mid, rx, f);
      update(x);
    }
  }

  void range_update(int l, int r, F f){
    assert(0 <= l && l <= r && r <= n);
    range_update(l, r, 1, 0, size, f);
  }

  S range_query(int l, int r, int x, int lx, int rx){
    push(x);

    if(lx >= r || l >= rx)
      return e();

    if(l <= lx && rx <= r)
      return d[x];

    int mid = (lx + rx)/2;
    return op(range_query(l, r, 2 * x, lx, mid), range_query(l, r, 2 * x + 1, mid, rx));
  }

  S range_query(int l, int r) {
    assert(0 <= l && l <= r && r <= n);
    return range_query(l, r, 1, 0, size);
  }

private:

  int size, log, n;
  vector<S> d;
  vector<F> lz;

  void update(int k){
    d[k] = op(d[2 * k], d[2 * k + 1]);
  }

  void apply(int k, F f){
    d[k] = mapping(f, d[k]);
    if(k < size)
      lz[k] = composition(f, lz[k]);
  }

  void push(int k){
    if(k >= size)
      return;
    apply(2 * k, lz[k]);
    apply(2 * k + 1, lz[k]);
    lz[k] = id();
  }

};