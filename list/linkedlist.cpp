#include <iostream>
#include <vector>
using namespace std;

class Node{
public:
	Node():m_next(NULL){}
	Node(int n):m_data(n),m_next(NULL){}
	Node(int n, Node* next):m_data(n),m_next(next){}
	int m_data;
	Node* m_next;
};

typedef Node *ListNode;

/*
 * 创建链表
 * return: head node
 * nums: node data
 */
//尾差法，新的结点放在最后
//一个head结点指向头，定义一个pend结点指向尾，每次从尾巴插入，再更新pend
ListNode CreateListByTail(vector<int> nums)
{
	if(nums.empty()) {
		return NULL;
	}
	ListNode head = new Node(nums[0]);
	Node* pend = head;
	 
	for(unsigned i = 1; i < nums.size(); i++){
		Node* tmpNode = new Node(nums[i]);
		pend->m_next = tmpNode;
		pend = tmpNode;
	}

	return head;
}

//头插法，新的结点放在头部
//这种方式 需要一个虚的头结点（没有数据），新的结点，每次都插在此虚结点的后面
ListNode CreateListByHead(vector<int> nums)
{
	ListNode head = new Node();
	for(auto n : nums){
		Node* tmpNode = new Node(n, head->m_next);
		head->m_next = tmpNode;
	}

	ListNode res = head->m_next;
	delete head; //avoid memory leak

	return res;
}

/*
 * 链表逆置（递归recursion）
 */
#if 0
void RevertListRecursion(ListNode* pHead)
{
	if(pHead == NULL || *pHead == NULL || (*pHead)->m_next == NULL){
		return;
	}
	
	ListNode* res =&((*pHead)->m_next);
	cout<<"res1 ==== "<<(*res)->m_data<<endl;
	cout<<"phead1 ==== "<<(*pHead)->m_data<<endl;
	RevertListRecursion(res);
	cout<<"res ==== "<<(*res)->m_data<<endl;
	cout<<"phead ==== "<<(*pHead)->m_data<<endl;
	ListNode tmp = *res;
	ListNode newHead = tmp;
	while(tmp->m_next != NULL){
	cout<<"xxxxx res32222222222222 == "<<(*res)->m_data<<endl;
		tmp = tmp->m_next;
	cout<<"xxxxx res111111111111 == "<<(*res)->m_data<<endl;
	}
	tmp->m_next = *pHead;
	(*pHead)->m_next = NULL;
	cout<<"xxxxx pHead1 == "<<(*pHead)->m_data<<endl;
	//cout<<"xxxxx res1 == "<<(*res)->m_data<<endl;
	pHead = &newHead;
	cout<<"xxxxx pHead == "<<(*pHead)->m_data<<endl;
}
#endif

ListNode RevertListRecursion(ListNode head)
{
	if(head == NULL || head->m_next == NULL){
		return head;
	}

	ListNode res = RevertListRecursion(head->m_next);
	ListNode tmp = res;
	while(tmp->m_next != NULL){
		tmp = tmp->m_next;
	}
	tmp->m_next = head;
	head->m_next = NULL;
	return res;
}

/*
 * 逆置链表（非递归）
 */
#if 0
void RevertList(ListNode* pHead)
{
	if(pHead == NULL || (*pHead) == NULL || (*pHead)->m_next == NULL) {
		return;
	}
	ListNode n1 = *pHead;
	ListNode n2 = n1->m_next;
	n1->m_next = NULL;
	while(n2 != NULL){
		ListNode n3 = n2->m_next;
		n2->m_next = n1;
		n1 = n2;
		n2 = n3;
	}

	*pHead = n1;
}
#endif

ListNode RevertList(ListNode head)
{
	if(head == NULL || head->m_next == NULL){
		return head;
	}

	ListNode n1 = head;
	ListNode n2 = head->m_next;
	n1->m_next = NULL;
	while(n2 != NULL){
		ListNode n3 = n2->m_next;
		n2->m_next = n1;
		n1 = n2;
		n2 = n3;
	}
	return n1;
}

/*
 * 链表的打印
 *
 */
void PrintList(ListNode head)
{
	cout<<"print list: ";
	while(head != NULL){
		cout<<head->m_data<<" ";
		head = head->m_next;
	}
	cout<<";\n";
}



int main()
{
	vector<int> v1;
	vector<int> v2{1};
	vector<int> v3{1,2,3,4,5,6,7,8,9,0};
	vector<int> v4{0,9,8,7,6,5,4,3,2,1};

	cout<<"test CreateListByTail: "<<endl;
	PrintList(CreateListByTail(v1));
	PrintList(CreateListByTail(v2));
	PrintList(CreateListByTail(v3));

	cout<<"test CreateListByHead: "<<endl;
	PrintList(CreateListByHead(v1));
	PrintList(CreateListByHead(v2));
	PrintList(CreateListByHead(v4));

	cout<<"test RevertListRecursion\n";
	ListNode l1 = CreateListByTail(v1);
	PrintList(RevertListRecursion(l1));
	ListNode l2 = CreateListByTail(v2);
	PrintList(RevertListRecursion(l2));
	ListNode l3 = CreateListByTail(v3);
	PrintList(RevertListRecursion(l3));

	cout<<"test RevertList\n";
	l1 = CreateListByTail(v1);
	PrintList(RevertList(l1));
	l2 = CreateListByTail(v2);
	PrintList(RevertList(l2));
	l3 = CreateListByTail(v3);
	PrintList(RevertList(l3));

	return 0;
}


