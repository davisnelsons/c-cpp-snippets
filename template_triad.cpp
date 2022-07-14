#include <iostream>

template <typename T>
struct Triad
{
    T f{};
    T s{};
    T t{};
};

template <typename T>
Triad(T, T, T) -> Triad<T>;

template <typename T>
void print(Triad<T>& s) {
    std::cout << s.f << s.s << s.t;
}



int main()
{
	Triad t1{ 1, 2, 3 }; // note: uses CTAD to deduce template arguments
	print(t1);

	Triad<double> t2{ 1.2, 3.4, 5.6 }; // note: uses CTAD to deduce template arguments
	print(t2);

	return 0;
}