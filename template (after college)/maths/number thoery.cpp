template<int N>
struct sieve{

    array<int, N + 1> spf;

    sieve(){

        for(int i = 1; i <= N; ++i){
            spf[i] = i;
        }

        for(int i = 2; i <= N; ++i){
            if(spf[i] == i){
                for(int j = i * i; j <= N; j += i){
                    if(spf[j] == j){
                        spf[j] = i;
                    }
                }
            }
        }

    }

    vector<pair<int,int>> prime_factors(int n){
        vector<pair<int,int>> res;
        while(n > 1){
            if(!res.empty() && res.back().first == spf[n]){
                res.back().second += 1;
            }else{
                res.push_back({spf[n], 1});
            }
            n /= spf[n];
        }
        return res;
    }

    vector<int> divisors(int n){
        if(n == 1)
            return {1};
        int p = 0, x = spf[n];
        while(spf[n] == x){
            n /= x;
            p++;
        }
        vector<int> res, d = divisors(n);
        for(int j = 0, v = 1; j <= p; v *= x,++j){
            for(auto c : d){
                res.push_back(c * v);
            }
        }
        return res;
    }

};