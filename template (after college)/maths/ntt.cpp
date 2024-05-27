template<class ntt_int, int MOD = ntt_int::mod()>
struct number_theoric_transform{

  vector<ntt_int> roots = {0, 1};
  vector<int> bit_reverse;
  int max_size = -1;
  ntt_int root;
    
  int is_power_of_two(int n){
    return (n & (n - 1)) == 0;
  }

  int round_up_power_two(int n){
    while(!is_power_of_two(n)){
      n = (n | (n - 1)) + 1;
    }
    return max(n, int(1));
  }

  int get_length(int n){
    assert(is_power_of_two(n));
    return __builtin_ctz(n);
  }

  void find_root(){
    max_size = 1 << __builtin_ctz(MOD - 1);
    root = 2;
    while(!(root.pow(max_size) == 1 && root.pow(max_size/2) != 1)){
      root++;
    }
  }

  void prepare_roots(int n){
    if(max_size < 0){
      find_root();
    }

    assert(n <= max_size);

    if(int(roots.size()) >= n){
      return;
    }

    int length = get_length(int(roots.size()));
    roots.resize(n);
    while((1 << length) < n){
      ntt_int z = root.pow(max_size >> (length + 1));
      for(int i = 1 << (length - 1); i < (1 << length); ++i){
        roots[2 * i] = roots[i];
        roots[2 * i + 1] = roots[i] * z;
      }
      length++;
    }

  }

  void bit_reorder(int n, vector<ntt_int> &v){
    if(int(bit_reverse.size()) != n){
      bit_reverse.assign(n, 0);
      int length = get_length(n);

      for(int i = 1; i < n; i++){
        bit_reverse[i] = (bit_reverse[i >> 1] >> 1) | ((i & 1) << (length - 1));
      }
    }

    for(int i = 0; i < n; ++i){
      if(i < bit_reverse[i]){
        swap(v[i], v[bit_reverse[i]]);
      }
    }
  }


  void fft(int n, vector<ntt_int> &v){
    assert(is_power_of_two(n));
    prepare_roots(n);
    bit_reorder(n, v);

    for(int len = 1; len < n; len *= 2){
      for(int start = 0; start < n; start += 2 * len){
        for(int i = 0; i < len; i++){
          ntt_int even = v[start + i];
          ntt_int odd = v[start + len + i] * roots[len + i];
          v[start + len + i] = even - odd;
          v[start + i] = even + odd;
        }
      }
    }
  }

  void invert_fft(int n, vector<ntt_int> &v){
      ntt_int inv_n = ntt_int(n).inv();

      for(int i = 0; i < n; i++)
        v[i] *= inv_n;

      reverse(v.begin() + 1, v.end());
      fft(n, v);
  } 

  template<typename T>
  vector<ntt_int> multiply(const vector<T>& _l, const vector<T>& _r){

    vector<ntt_int> l(_l.begin(),_l.end());
    vector<ntt_int> r(_r.begin(),_r.end());

    int n = int(l.size()), m = int(r.size());
    int output_size = n + m - 1;

    int N = round_up_power_two(output_size);
    l.resize(N,0);
    r.resize(N,0);

    if(l == r){
      fft(N, l);
      r = l;
    }else{
      fft(N, l);
      fft(N, r);
    }

    for(int i = 0; i < N; ++i){
      l[i] *= r[i];
    }

    invert_fft(N, l);

    return vector<ntt_int>(l.begin(), l.begin() + output_size);
  }

};
