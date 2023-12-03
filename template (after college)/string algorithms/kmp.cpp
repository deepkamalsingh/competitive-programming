template<typename T>
vector<int> get_pi(T pattern){
    int n = int(pattern.size());
    vector<int> pi(n + 1, 0);
    int len = 0;
    for(int i = 1; i < n; ++i){
        while(len > 0 && pattern[len] != pattern[i]){
            len = pi[len];
        }
        if(pattern[len] == pattern[i]){
            len++;
        }
        pi[i + 1] = len;
    }
    return pi;
}



template<typename T>
vector<int> get_matches(T text, T pattern){

    int n = int(pattern.size()), m = int(text.size());
    if(n > m){
        return {};
    }

    auto pi = get_pi(pattern);
    int len = 0;
    vector<int> matches;

    for(int i = 0; i < m; ++i){
        while(len > 0 && pattern[len] != text[i]){
            len = pi[len];
        }
        if(pattern[len] == text[i]){
            len++;
        }
        if(len == n){
            matches.push_back(i - n + 1);
            len = pi[len];
        }
    }

    return matches;
}