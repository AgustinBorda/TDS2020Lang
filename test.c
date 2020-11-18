int a;
long b;
int add(int a, int b) {
	return a+b;
}
int main() {
	long c;
	c = 5;
	a = 5;
	b = c;
	if(c == a) {
		a = 1;
	}
	else {
		a = 0;
	}
	add(a,c);
	return 0;
}
