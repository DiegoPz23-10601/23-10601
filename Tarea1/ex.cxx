#include <vector>
#include <cmath>
#include <numeric>
#include <string>
#include <algorithm>

using namespace std;


int main(){
  return 0;
}

// --- EJERCICIO 3: Promedio y Varianza ---
double mean(vector<double> v){
    if (v.empty()) return 0.0;
    double sum = 0.0;
    for (double x : v) sum += x;
    return sum / v.size();
}

double variance(vector<double> v){
    if (v.size() < 2) return 0.0;
    double m = mean(v);
    double desc_sq_sum = 0.0;
    for (double x : v) desc_sq_sum += (x - m) * (x - m);
    return desc_sq_sum / v.size();
}

// --- EJERCICIO 4:
double pearson_r(vector<double> A, vector<double> B){
    if (A.size() != B.size() || A.empty()) return 0.0;
    double mean_A = mean(A), mean_B = mean(B);
    double num = 0.0, den_A = 0.0, den_B = 0.0;
    for (size_t i = 0; i < A.size(); ++i) {
        double diff_A = A[i] - mean_A;
        double diff_B = B[i] - mean_B;
        num += diff_A * diff_B;
        den_A += diff_A * diff_A;
        den_B += diff_B * diff_B;
    }
    if (den_A == 0.0 || den_B == 0.0) return 0.0;
    return num / (sqrt(den_A) * sqrt(den_B));
}

// --- EJERCICIO 5: Sistema de Numeración de los Pulpos Espaciales ---
const string HEX_CHARS = "0123456789ABCDEF";

vector<char> int_to_base(int n, int base) {
    if (n == 0) return {'0'};
    vector<char> result;
    bool is_negative = n < 0;
    long long num = abs(static_cast<long long>(n));
    while (num > 0) {
        result.push_back(HEX_CHARS[num % base]);
        num /= base;
    }
    if (is_negative) result.push_back('-');
    reverse(result.begin(), result.end());
    return result;
}

int base_to_int(vector<char> s, int base) {
    if (s.empty()) return 0;
    bool is_negative = s[0] == '-';
    size_t start = is_negative ? 1 : 0;
    long long result = 0;
    for (size_t i = start; i < s.size(); ++i) {
        char c = toupper(s[i]);
        size_t val = HEX_CHARS.find(c);
        if (val == string::npos || val >= static_cast<size_t>(base)) return 0;
        result = result * base + val;
    }
    return is_negative ? -result : result;
}

vector<char> dec_to_septapus(int n){ return int_to_base(n, 7); }
vector<char> dec_to_octopus(int n){ return int_to_base(n, 8); }
vector<char> dec_to_hexakaidecapus(int n){ return int_to_base(n, 16); }

vector<char> septapus_to_dec(vector<char> s){
    string res = to_string(base_to_int(s, 7));
    return vector<char>(res.begin(), res.end());
}
vector<char> octopus_to_dec(vector<char> s){
    string res = to_string(base_to_int(s, 8));
    return vector<char>(res.begin(), res.end());
}
vector<char> hexakaidecapus_to_dec(vector<char> s){
    string res = to_string(base_to_int(s, 16));
    return vector<char>(res.begin(), res.end());
}
vector<char> septapus_to_octopus(vector<char> s){ return dec_to_octopus(base_to_int(s, 7)); }
vector<char> septapus_to_hexakaidecapus(vector<char> s){ return dec_to_hexakaidecapus(base_to_int(s, 7)); }
vector<char> octapus_to_septapus(vector<char> s){ return dec_to_septapus(base_to_int(s, 8)); }
vector<char> octopus_to_hexakaidecapus(vector<char> s){ return dec_to_hexakaidecapus(base_to_int(s, 8)); }
vector<char> hexakaidecapus_to_septapus(vector<char> s){ return dec_to_septapus(base_to_int(s, 16)); }
vector<char> hexakaidecapus_to_octopus(vector<char> s){ return dec_to_octopus(base_to_int(s, 16)); }
