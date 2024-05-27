// For every i, finds the largest j < i such that `compare(values[j], values[i])` is true, or -1 if no such j exists.
template<typename T, typename T_compare>
vector<int> closest_left(const vector<T> &values, T_compare &&compare){
  int n = int(values.size());
  vector<int> closest(n);
  vector<int> stack;
  stack.reserve(n);

  for(int i = 0; i < n; i++){
    while(!stack.empty() && !compare(values[stack.back()], values[i]))
      stack.pop_back();

    closest[i] = stack.empty() ? -1 : stack.back();
    stack.push_back(i);
  }

  return closest;
}
 
// For every i, finds the smallest j > i such that `compare(values[j], values[i])` is true, or `n` if no such j exists.
template<typename T, typename T_compare>
vector<int> closest_right(vector<T> values, T_compare &&compare){
  int n = int(values.size());
  reverse(values.begin(), values.end());
  vector<int> closest = closest_left(values, compare);
  reverse(closest.begin(), closest.end());

  for(int i = 0; i < n; i++)
    closest[i] = n - 1 - closest[i];

  return closest;
}