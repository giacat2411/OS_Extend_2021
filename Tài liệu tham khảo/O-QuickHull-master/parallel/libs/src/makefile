all: x32 runnable_x32 x64 runnable_x64

x32: src_x32
	g++ -fPIC *.o -m32 -o OrthogonalConvexHull_x32.so -shared -fopenmp
x64: src_x64
	g++ -fPIC *.o -m64 -o OrthogonalConvexHull_x64.so -shared -fopenmp

src_x64: convex_ohq.cpp data.cpp utils.cpp
	g++ -fPIC -c *.cpp -fopenmp -m64

src_x32: convex_ohq.cpp data.cpp utils.cpp
	g++ -fPIC -c *.cpp -fopenmp -m32

runnable_x64: src_x64
	g++ -c main.cpp -m64
	g++ *.o -fPIC -o runnable_x64 -fopenmp -m64

runnable_x32: src_x32
	g++ -c main.cpp -m32
	g++ *.o -fPIC -o runnable_x32 -fopenmp -m32

clean:
	rm -f *.o *.so *x32 *x64

