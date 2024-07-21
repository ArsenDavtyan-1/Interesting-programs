#include <iostream>
#include <memory>
#include "uniquePointer.h"
#include "sharedPointer.h"


class A
{
	int a;
public:
	A()
	{
		a = 4;
		std::cout << "Constructor of A called" << std::endl;
	}
	void show()
	{
		std::cout << "Called A show" << std::endl;
	}
	~A()
	{
		std::cout << "Destructor of A called" << std::endl;
	}
};

int main()
{
	//int* p = new int[4];
	//uniquePointer<int[]> array(new int[5] {1, 2, 5, 2, 4});

	//std::unique_ptr<A[4]> pyy;
	//A* ppp = new A;
	//sharedPointer<A> pt(ppp);
	//sharedPointer<A> ptt(pt);
	//sharedPointer<A> pttt(std::move(pt));
	//std::cout << "--------------------------" << std::endl;
	//ptt = std::move(pttt);
	//std::cout << "--------------------------" << std::endl;
	//std::cout << std::endl << std::endl << std::endl;
	//sharedPointer<A[]> ptrarray(new A[4]);
	//sharedPointer<A[]> ptrbrray(ptrarray);
	//sharedPointer<A[]> ptrcrray(std::move(ptrbrray));
	sharedPointer<int> p(new int(77));
	sharedPointer<int> b(p);
	std::cout << *b << std::endl << std::endl << std::endl;
	sharedPointer<int[]> sharedarray(new int[10] {1, 45, 21, 1, -2, 6, 7, -77, 4, 44});
	sharedPointer<int[]> sharedarray2(sharedarray);
	for (int i = 0; i < 10; ++i)
		std::cout << sharedarray[i] << "   " << sharedarray2[i] << '\t';
	std::cout << std::endl << std::endl;
	uniquePointer<float> upfl(new float(33.2));
	std::cout << "upfl = " << *upfl << std::endl;
	uniquePointer<double[]> updoub(new double[10] {11.2, 0.3, -55, -6.3, 1, -44, 22.3, 3.1, 1.7, -7.2});
	uniquePointer<double[]> updoub2(std::move(updoub));
	for (int i = 0; i < 10; ++i)
		std::cout << updoub2[i] << '\t';
	std::cout << std::endl << std::endl;
	uniquePointer<A> uptoA(new A);
	uptoA->show();
	sharedPointer<A> sptoA(new A);
	sptoA->show();
	sharedPointer<A[]> sptoarray(new A[3]);
	sptoarray[2].show();
}
	
