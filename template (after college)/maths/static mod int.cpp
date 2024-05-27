template<int32_t MOD>
struct static_mint {

public:

  static_mint() : _v(0) {}

  static constexpr int32_t mod() {
    return MOD;
  }

  int32_t val() const {
    return _v;
  }

  static_mint(int32_t v){
    if(v < 0)
      v = v % MOD + MOD;
    if(v >= MOD)
      v = v % MOD;
    _v = int32_t(v);
  }

  static_mint(int64_t v){
    if(v < 0)
      v = v % MOD + MOD;
    if(v >= MOD)
      v = v % MOD;
    _v = int32_t(v);
  }

  static_mint& operator++(){
    _v++;
    if(_v == MOD)
      _v = 0;
    return *this;
  }

  static_mint& operator--(){
    if(_v == 0)
      _v = MOD;
    _v--;
    return *this;
  }

  static_mint operator++(int32_t){
    static_mint result = *this;
    ++(*this);
    return result;
  }

  static_mint operator--(int32_t){
    static_mint result = *this;
    --(*this);
    return result;
  }

  static_mint& operator+=(const static_mint& other){
    _v += other._v;
    if(_v >= MOD) 
      _v -= MOD;
    return *this;
  }

  static_mint& operator-=(const static_mint& other){
    _v -= other._v;
    if(_v < 0) 
      _v += MOD;
    return *this;
  }

  static_mint& operator*=(const static_mint& other){
    _v = (int64_t)_v * other._v % MOD;
    return *this;
  }

  static_mint& operator/=(const static_mint& other){
    (*this) = (*this) * other.inv();
    return *this;
  }

  static_mint operator+() const {
    return *this;
  }

  static_mint operator-() const {
    return (*this) * static_mint(-1);
  }

  static_mint pow(int64_t n) const {
    assert(0 <= n);
    static_mint x = *this, r = 1;
    while(n){
      if(n & 1)
        r = r * x;
      x = x * x;
      n >>= 1;
    }
    return r;
  }

  static_mint inv() const {
    return pow(MOD - 2);
  }

  friend bool operator==(const static_mint& lhs, const static_mint& rhs){
    return lhs.val() == rhs.val();
  }

  friend static_mint operator+(const static_mint& lhs, const static_mint& rhs){
    return static_mint(lhs) += rhs;
  }

  friend static_mint operator-(const static_mint& lhs, const static_mint& rhs){
    return static_mint(lhs) -= rhs;
  }

  friend static_mint operator*(const static_mint& lhs, const static_mint& rhs){
    return static_mint(lhs) *= rhs;
  }

  friend static_mint operator/(const static_mint& lhs, const static_mint& rhs){
    return static_mint(lhs) /= rhs;
  }

private:
  
  int32_t _v;

};


const int MOD = 1e9 + 7;
using mint = static_mint<MOD>;


vector<mint> fact, inv_fact;

void prepare(int n){
  fact = inv_fact = {1, 1};
  fact.resize(n + 1);
  inv_fact.resize(n + 1);

  for(int i = 2; i <= n; ++i)
    fact[i] = mint(i) * fact[i - 1];

  inv_fact[n] = mint(1) / fact[n];

  for(int i = n - 1; i >= 2; --i)
    inv_fact[i] = mint(i + 1) * inv_fact[i + 1];

  // inv[i] = inv[MOD % i] * (MOD - MOD / i);
}

mint choose(int n, int r){
  if(r < 0 || r > n) return mint(0);
  return fact[n] * inv_fact[r] * inv_fact[n - r];
}