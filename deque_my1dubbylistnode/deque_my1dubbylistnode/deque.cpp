#include<iostream>
#include<stdexcept>

using namespace std;

struct listnode {
	int val;
	listnode* next;
	listnode* prev;
	listnode(int x) :val(x), next(nullptr), prev(nullptr) {}
};

class linkeddeque {
private:
	listnode* head;
	listnode* tail;
	int size;
public:
	linkeddeque() :head(nullptr), tail(nullptr), size(0) {}
	~linkeddeque() {
		while (head) {
			listnode* temp = head;
			head = head->next;
			delete temp;
		}
	}
	int getsize()const {
		return size;
	}
	bool isempty()const {
		return size == 0;
	}
	int getfront()const {
		if (isempty()) throw out_of_range("Deque is empty");
		return head->val;
	}
	int getrear()const {
		if (isempty()) throw out_of_range("Deque is empty");
		return tail->val;
	}
	void push_front(int x) {
		listnode* node = new listnode(x);
		if (isempty()) {
			head = tail = node;
		}
		else {
			node->next = head;//why not head->prev = node first?because head may be nullptr
			head->prev = node;//remember to link back!!!!!
			head = node;
		}
		size++;
	}
	void push_rear(int x) {
		listnode* node = new listnode(x);
		if (isempty()) {
			head = tail = node;
		}
		else {
			tail->next = node;//why not node->prev = tail first?because tail may be nullptr
			node->prev = tail;//remember to link back!!!!!
			tail = node;
		}
		size++;
	}
	void pop_front() {
		listnode* temp;
		if (isempty()) throw out_of_range("Deque is empty");
		temp = head;
		head = head->next;
		delete temp;
		size--;
		if (isempty()) tail = nullptr;// If the deque becomes empty, set tail to nullptr,but why not head?because head is already set to head->next which is nullptr
		else head->prev = nullptr;//because head is not nullptr now,so we can set head->prev to nullptr                                          
	}                                             
	void pop_rear() {
		if (isempty()) throw out_of_range("Deque is empty");
		listnode* temp = tail;
		if (head == tail) { // 只有一个节点
			head = tail = nullptr;
		}
		else {
			tail = tail->prev;
			tail->next = nullptr;
		}
		delete temp;
		size--;
	}
};

int main() {
	linkeddeque dq;
	dq.push_front(10);
	dq.push_rear(20);
	dq.push_front(5);
	cout << "Front: " << dq.getfront() << endl; // 5
	cout << "Rear: " << dq.getrear() << endl;   // 20
	cout << "Size: " << dq.getsize() << endl;   // 3
	dq.pop_front();
	cout << "Front after pop: " << dq.getfront() << endl; // 10
	dq.pop_rear();
	cout << "Rear after pop: " << dq.getrear() << endl;   // 10
	cout << "Size after pops: " << dq.getsize() << endl;   // 1
	return 0;
}//时间复杂度O(1)，空间复杂度O(n)
//dubbylistnode remember to link back!!!!!