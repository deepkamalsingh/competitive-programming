template<typename T>
struct matrix{

public:

  matrix(){}

  matrix(int r,int c) : mat(vector<vector<T>> (r,vector<T> (c, 0))) {}

  template<typename U>
  matrix(const vector<vector<U>> M) {
    mat(vector<vector<T>> (M.rows(), vector<T> (M.cols(), 0)));
    for(int i = 0; i < rows(); ++i)
      for(int j = 0; j < cols(); ++j)
        mat[i][j] = M[i][j];
  }

  int rows() const {
    return mat.size();
  }

  int cols() const {
    return (mat.size() == 0 ? 0 : mat[0].size());
  }

  vector<T>& operator[](int i){
    return mat[i];
  }

  const vector<T>& operator[](int i) const {
    return mat[i];
  }

  void fill(T val){
    for(int i = 0; i < rows(); ++i){
      for(int j = 0; j < cols(); ++j){
        mat[i][j] = val;
      }
    }
  }

  void make_identity(){
    assert(rows() == cols());
    fill(0);
    for(int i = 0; i < rows(); ++i)
      mat[i][i] = 1;
  }

  matrix& operator+=(const matrix &a){
    assert(rows() == a.rows() && cols() == a.cols());

    for(int i = 0; i < rows(); ++i)
      for(int j = 0; j < cols(); ++j)
        mat[i][j] += a[i][j];

    return *this;
  }

  matrix& operator-=(const matrix &a){
    assert(rows() == a.rows() && cols() == a.cols());

    for(int i = 0; i < rows(); ++i)
      for(int j = 0; j < cols(); ++j)
        mat[i][j] -= a[i][j];

    return *this;
  }

  matrix& operator*=(const matrix &a){
    assert(cols() == a.rows());
    
    matrix<T> res(rows(),a.cols());
    for(int i = 0; i < rows(); ++i)
      for(int j = 0; j < a.cols(); ++j)
        for(int k = 0; k < cols(); ++k)
          res[i][j] += mat[i][k] * a[k][j];

    (*this) = res;
    return *this;
  }

  matrix& operator*=(const T &val){
    for(int i = 0; i < rows(); ++i){
      for(int j = 0; j < cols(); ++j){
        mat[i][j] *= val;
      }
    }
    return *this;
  }
  

  friend matrix operator*(const matrix &lhs, const matrix &rhs){
    matrix res(lhs);
    res *= rhs;
    return res;
  }

  friend matrix operator+(const matrix& lhs, const matrix& rhs){
    matrix res(lhs);
    res += rhs;
    return res;
  }

  friend matrix operator-(const matrix& lhs, const matrix& rhs){
    matrix res(lhs);
    res -= rhs;
    return res;
  }

  matrix operator-() const {
    matrix res(*this);
    res *= T(-1);
    return res;
  }

  matrix pow(long long n){
    matrix<T> res(rows(),cols());
    res.make_identity();

    matrix<T> a = *this;

    while(n){
      if(n&1)
        res *= a;
      a = a * a;
      n >>= 1;
    }

    return res;
  }

  friend ostream& operator<<(ostream& out,const matrix &M){
    for(int i = 0; i < M.rows(); ++i)
      for(int j = 0; j < M.cols(); ++j)
        out << M[i][j] << " \n"[j + 1 == M.cols()];
    return out;
  }

private:

  vector<vector<T>> mat;

};