template<class T>	
struct compress{

public:
  
  void add(T x){
		values.push_back(x);
  }
  
  void gen(){
		sort(values.begin(),values.end());
		values.erase(unique(values.begin(),values.end()),values.end());
  }
  
  int get(T x) const {
		int j = lower_bound(values.begin(),values.end(),x) - values.begin();
		assert(values[j] == x); return j;
  }
  
  void clear(){
		values.clear();
  }

  int size() const {
  	return values.size();
  }

private:

	vector<T> values;

};