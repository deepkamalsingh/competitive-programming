struct dynamic_mint {

public:

  static int32_t MOD;

  dynamic_mint() : _v(0) {}

  int32_t mod() const {
    return MOD;
  }

  int32_t val() const {
    return _v;
  }

  dynamic_mint(int32_t v){
    if(v < 0)
      v = v % MOD + MOD;
    if(v >= MOD)
      v = v % MOD;
    _v = int32_t(v);
  }

  dynamic_mint(int64_t v){
    if(v < 0)
      v = v % MOD + MOD;
    if(v >= MOD)
      v = v % MOD;
    _v = int32_t(v);
  }

  dynamic_mint& operator++(){
    _v++;
    if(_v == MOD)
      _v = 0;
    return *this;
  }

  dynamic_mint& operator--(){
    if(_v == 0)
      _v = MOD;
    _v--;
    return *this;
  }

  dynamic_mint operator++(int32_t){
    dynamic_mint result = *this;
    ++(*this);
    return result;
  }

  dynamic_mint operator--(int32_t){
    dynamic_mint result = *this;
    --(*this);
    return result;
  }

  dynamic_mint& operator+=(const dynamic_mint& other){
    _v += other._v;
    if(_v >= MOD) 
      _v -= MOD;
    return *this;
  }

  dynamic_mint& operator-=(const dynamic_mint& other){
    _v -= other._v;
    if(_v < 0) 
      _v += MOD;
    return *this;
  }

  dynamic_mint& operator*=(const dynamic_mint& other){
    _v = (int64_t)_v * other._v % MOD;
    return *this;
  }

  dynamic_mint& operator/=(const dynamic_mint& other){
    (*this) = (*this) * other.inv();
    return *this;
  }

  dynamic_mint operator+() const {
    return *this;
  }

  dynamic_mint operator-() const {
    return (*this) * dynamic_mint(-1);
  }

  dynamic_mint pow(int64_t n) const {
    assert(0 <= n);
    dynamic_mint x = *this, r = 1;
    while(n){
      if(n & 1)
        r = r * x;
      x = x * x;
      n >>= 1;
    }
    return r;
  }

  dynamic_mint inv() const {
    return pow(MOD - 2);
  }

  friend bool operator==(const dynamic_mint& lhs, const dynamic_mint& rhs){
    return lhs.val() == rhs.val();
  }

  friend dynamic_mint operator+(const dynamic_mint& lhs, const dynamic_mint& rhs){
    return dynamic_mint(lhs) += rhs;
  }

  friend dynamic_mint operator-(const dynamic_mint& lhs, const dynamic_mint& rhs){
    return dynamic_mint(lhs) -= rhs;
  }

  friend dynamic_mint operator*(const dynamic_mint& lhs, const dynamic_mint& rhs){
    return dynamic_mint(lhs) *= rhs;
  }

  friend dynamic_mint operator/(const dynamic_mint& lhs, const dynamic_mint& rhs){
    return dynamic_mint(lhs) /= rhs;
  }

private:
  
  int32_t _v;

};

int32_t dynamic_mint::MOD = -1;
using mint = dynamic_mint;

void set_mod(int MOD){
  dynamic_mint::MOD = MOD;
}