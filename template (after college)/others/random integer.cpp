mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int my_rand(int L, int R){ 
    return uniform_int_distribution<int>(L,R)(rng); 
}

// double my_rand(double L,double R){
//   return uniform_real_distribution<double>(L,R)(rng);
// }