namespace OUT{

  template<class T>
  void __p(const T& a){
     std::cout<<a; 
  }

  template<class T, class F>
  void __p(const std::pair<T, F>& a){ 
    std::cout<<"{"; __p(a.first); std::cout<<","; __p(a.second); 
    std::cout<<"}\n"; 
  }

  template<class T, size_t N>
  void __p(const std::array<T,N>& a){ 
    std::cout<<"{"; for(int i=0;i<N;++i)__p(a[i]),std::cout<<",}\n"[i+1==N]; 
  }
  
  template<class T>
  void __p(const std::vector<T>& a){
    std::cout<<"{";for(auto it=a.begin();it<a.end();it++)__p(*it),std::cout<<",}\n"[it+1==a.end()]; 
  }
  
  template<class T, class ...Arg>
  void __p(T a1, Arg ...a){
    __p(a1); __p(a...);
  }
  
  template<class Arg1>
  void __f(const char *s, Arg1 &&arg1){ 
    std::cout<<s<<" : "; __p(arg1); 
    std::cout<<std::endl; 
  }
  
  template<class Arg1, class ... Args>
  void __f(const char *ss, Arg1 &&arg1, Args &&... args){
    int b=0,i=0; do{ if(ss[i]=='(') b++; if(ss[i]==')') b--; i++;}while(!(ss[i]==','&&b==0));
    const char *comma=ss+i; std::cout.write(ss,comma-ss)<<" : ";__p(arg1);std::cout<<" | ";__f(comma+1,args...);
  }
  
  #define trace(...) std::cout<<"Line:"<<__LINE__<<"  ", __f(#__VA_ARGS__, __VA_ARGS__)
}

using namespace OUT;

const auto start_time = std::chrono::high_resolution_clock::now();

void output_run_time(){
#ifndef ONLINE_JUDGE
  const auto end_time = std::chrono::high_resolution_clock::now();
  const std::chrono::duration<double> diff = end_time - start_time;
  std::cout << "\n\n\nTime Taken : " << diff.count();
#endif
}