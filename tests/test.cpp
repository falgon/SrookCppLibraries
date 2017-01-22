#include"../srook/range/adaptor/print.hpp"
#include<vector>

int main()
{
	std::vector<int> v{1,2,3,4,5};
	v | srook::adaptors::print();
}
