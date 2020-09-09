#include <iostream>

using namespace std;

namespace exception {
	class Exception {
		int err_no;
		string msg;
		public:
			Exception(int,string);
			int getErrorNumber();
			string getMessage();
	};
	Exception::Exception(int err_no,string msg) {
		Exception::err_no=err_no;
		Exception::msg=msg;
	}
	int Exception::getErrorNumber() {
		return Exception::err_no;
	}
	string Exception::getMessage() {
		return Exception::msg;
	}
	
	class QueueEmptyException:public Exception {
	public:
		QueueEmptyException():Exception(100,"Queue Empty Exception"){}
	};
	class QueueFullException:public Exception {
	public:
		QueueFullException():Exception(101,"Queue Full Exception"){}
	};
	class StackUnderflowException:public Exception {
	public:
        StackUnderflowException():Exception(200,"Stack Underflow Exception"){}
	};
	class StackOverflowException:public Exception {
	public:
        StackOverflowException():Exception(201,"Stack Overflow Exception"){}
	};
	class IndexOutOfBoundsException:public Exception {
	public :
		IndexOutOfBoundsException():Exception(300, "Linked list index out of bounds"){}
	};
	class LinkedListEmptyException:public Exception {
	public :
		LinkedListEmptyException():Exception(301, "Linked list is empty"){}
	};
}
