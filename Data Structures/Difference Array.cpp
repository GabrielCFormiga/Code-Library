// Difference Arrays
//
// https://codeforces.com/blog/entry/78762

int main() {
	int n = 5; // Size of array
	vector<int> elements{0, 1, 1, 1, 1, 1}; // 1 based indexing
    // n+2 because we need are not using the 0-th index and we need one more element in the array.
	vector<int> diff(n + 2, 0); 
	
	int updateValue = 10;
	int l = 2, r = 5;
	diff[l] += updateValue;
	diff[r + 1] -= updateValue;
	
	for (int i = 1; i <= n; i++) {
		diff[i] += diff[i - 1];
		elements[i] += diff[i];
	}
	for (int i = 1; i <= n; i++) cout << elements[i] << " ";
}