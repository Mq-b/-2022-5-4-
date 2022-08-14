#include<thread>
#include<iostream>

class joining_thread {
	std::thread t;
public:
	joining_thread()noexcept = default;
	template<typename Callable,typename ...Args>
	explicit joining_thread(Callable&& func,Args&&...args):t{std::forward<Callable>(func),std::forward<Args>(args)...}
	{}
	joining_thread(joining_thread&& other)noexcept :t{ std::move(other.t) }
	{}
	joining_thread& operator=(joining_thread&& other)noexcept {
		if (t.joinable()) 
			t.join();
		t = std::move(other.t);
		return *this;
	}
	joining_thread& operator=(std::thread other)noexcept {
		if (t.joinable())
			t.join();
		t = std::move(other);
		return *this;
	}
	~joining_thread()noexcept {
		if (t.joinable())
			t.join();
	}
	void swap(joining_thread& other)noexcept {
		t.swap(other.t);
	}
	std::thread::id get_id()const noexcept {
		return t.get_id();
	}
	bool joinable()const noexcept {
		return t.joinable();
	}
	void join() {
		t.join();
	}
	void detach() {
		t.detach();
	}
	std::thread& as_thread()noexcept {
		return t;
	}
	const std::thread& as_thread()const noexcept {
		return t;
	}
};
void test(int i,double b) {
	std::cout << std::this_thread::get_id() << std::endl;
	std::cout << i << std::endl;
	std::cout << b << std::endl;
}
int main() {
	joining_thread Thread(test,10,1.5);
}