#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
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
 * 输出倒数第K个节点
 * k > list长度返回空
 */
Node* LastKNode(ListNode head, int k)
{
	if(head == NULL || k <= 0) {
		return NULL;
	}

	int i = 0;
	Node* tmp = head;
	while(tmp != NULL && i < k){
		tmp = tmp->m_next;
		i++;
	}
	if(i < k){
		return NULL;
	}
	while(tmp != NULL){
		tmp = tmp->m_next;
		head = head->m_next;
	}

	return head;
}

/*
 * 逆序打印链表
 */
void PrintListReverse(ListNode head)
{
	stack<Node*> st;
	while(head!=NULL){
		st.push(head);
		head = head->m_next;
	}
	cout<<"list reverse: ";
	while(!st.empty()){
		cout<<st.top()->m_data<<" ";
		st.pop();
	}
	cout<<endl;
}

/*
 * 逆序打印链表 递归
 */
void PrintListReverseiRecursion(ListNode head)
{
	if(head == NULL){
		return;
	}

	PrintListReverseiRecursion(head->m_next);
	cout<<head->m_data<<" ";
}


/*
 * 单链表长度（无环）
 */
int ListSize(ListNode head)
{
	int len = 0;
	while(head != NULL){
		len++;
		head = head->m_next;
	}
	return len;
}

/*
 * 两个链表的第一个公共节点
 * 链接都是以NULL结尾的，所以两个单链表重合，必定是尾部重合
 * 思想：求两个链表的长度，n,m 长的链表先走|n-m|步，再开始逐个比较。
 */
Node* FindCommonNode(ListNode l1, ListNode l2)
{
	int n1 = ListSize(l1);
	int n2 = ListSize(l2);

	if(n1 == 0 || n2 == 0) {
		return NULL;
	}
	if(n1 < n2) {
		ListNode tmp = l2;
		l2 = l1;
		l1 = tmp;
		std::swap(n1, n2);
	}

	int i = 0;
	while(l1 != NULL && i < n1-n2){
		l1 = l1->m_next;
		i++;
	}
	while(l1 != l2 && l1 != NULL) {
		l1 = l1->m_next;
		l2 = l2->m_next;
	}

	return l1;
}

/*
 * 判断单链表是否有环
 * 通过快慢指针：
 *	一个每次走一步
 *	一个每次走两步
 * return 0 (无)，1（有） 
 */
int HasCycle(ListNode head)
{
	if(head == NULL){
		return 0;
	}
	Node* quick = head->m_next;
	Node* slow = head;
	while(quick != NULL && quick != slow) {
		slow = slow->m_next;
		if(quick->m_next == NULL){
			return 0;
		}
		quick = quick->m_next->m_next;
	}

	return (quick == slow) ? 1 : 0;
}

/*
 *	求单链表环的长度
 *	思想：环第一次相遇后，只走慢指针，到下次相遇，慢指针走的步数就是环长度。
 */
int GetCycleLength(ListNode head)
{
	if(!HasCycle(head)){
		cout<<"has no cycle\n";
		return 0;
	}

	Node* quick = head->m_next;
	Node* slow = head;

	while(quick != slow){
		quick = quick->m_next->m_next;
		slow = slow->m_next;
	}

	int len = 1;
	slow = slow->m_next;
	while(slow != quick){
		len++;
		slow = slow->m_next;
	}
	return len;
}

/*
 * 环的入口
 * 思想，找到环的长度n，让一个指针先走n步,让两个指针相差n步
 * 再两个指针一起走，当相遇时就是环入口
 */
Node* GetCycleFirstNode(ListNode head)
{
	if(!HasCycle(head)){
		return NULL;
	}

	int len = GetCycleLength(head);
	Node* first = head;
	while(len--){
		first = first->m_next;
	}
	while(first != head){
		first = first->m_next;
		head = head->m_next;
	}

	return first;
}

/*
 * 在单链表中按O(1)删除指定节点
 * 思想：正常情况，必须知道其上一个节点，才能删除此节点，
 * 这样就从头遍历到此节点的上一节点，这样就O(n).
 * 把删除节点与其后一节点的值交换，并删除后一节点，则可以做到O(1)
 * 除了当前节点是最后一个节点，必须从头开始找到倒数第二个节点。是O(n)
 */
void DeleteNode(ListNode* head, Node* del)
{
	if(head == NULL || *head == NULL || del == NULL){
		return;
	}
	if(del->m_next != NULL){
		Node* next = del->m_next;
		int tmp = del->m_data;
		del->m_data = next->m_data;
		next->m_data = tmp;
		del->m_next = next->m_next;
		next->m_next = NULL;
	} else { //del is the last node
		if(*head == del){ //the list only one node
			*head = NULL;
		} else {
			Node* tmp = *head;
			while(tmp->m_next != del){
				tmp = tmp->m_next;
			}
			tmp->m_next = NULL;
		}
	}
}

/*
 *合并两个已排序的链表
 * 思想：
 *	head ：新链表的head
 *	tail : 已合并链表的最后一个节点
 *	p1 p2 : 链表1,2下一个处理的结点
 */
ListNode MergeSortedList(ListNode l1, ListNode l2)
{
	if(l1 == NULL){
		return l2;
	}else if(l2 == NULL){
		return l1;
	}

	ListNode head = new Node();
	Node* tail = head;
	while(l1 != NULL && l2 != NULL){
		if(l1->m_data < l2->m_data){
			tail->m_next = l1;
			tail = l1;
			l1 = l1->m_next;
		}else{
			tail->m_next = l2;
			tail = l2;
			l2 = l2->m_next;
		}
	}
	if(l1 == NULL) {
		tail->m_next = l2;
	}else if(l2 == NULL){
		tail->m_next = l1;
	}
	ListNode res = head->m_next;
	delete head;
	return res;
}




/*
 * 链表的打印(无环)
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

	/********************************************************/
	cout<<"test CreateListByTail: "<<endl;
	PrintList(CreateListByTail(v1));
	PrintList(CreateListByTail(v2));
	PrintList(CreateListByTail(v3));

	/********************************************************/
	cout<<"test CreateListByHead: "<<endl;
	PrintList(CreateListByHead(v1));
	PrintList(CreateListByHead(v2));
	PrintList(CreateListByHead(v4));

	/********************************************************/
	cout<<"test RevertListRecursion\n";
	ListNode l1 = CreateListByTail(v1);
	PrintList(RevertListRecursion(l1));
	ListNode l2 = CreateListByTail(v2);
	PrintList(RevertListRecursion(l2));
	ListNode l3 = CreateListByTail(v3);
	PrintList(RevertListRecursion(l3));

	/********************************************************/
	cout<<"test RevertList\n";
	l1 = CreateListByTail(v1);
	PrintList(RevertList(l1));
	l2 = CreateListByTail(v2);
	PrintList(RevertList(l2));
	l3 = CreateListByTail(v3);
	PrintList(RevertList(l3));

	/********************************************************/
	cout<<"test last k node"<<endl;
	ListNode l4 = CreateListByTail(v4);
	PrintList(l4);
	vector<int> k{-1, 0, 1, 2, 4, 5, 9, 10, 11};
	for (int i : k) {
		Node* knode = LastKNode(l4, i);
		if (knode == nullptr) {
			cout<<"last "<<i<<" node is null\n";
		} else {
			cout<<"last "<<i<<" node is "<<knode->m_data<<endl;
		}
	}

	/********************************************************/
	cout<<"test PrintListReverse\n";
	PrintListReverse(l4);

	/********************************************************/
	cout<<"test PrintListReverseRecursion\n";
	cout<<"list: ";
	PrintListReverseiRecursion(l4);
	cout<<endl;

	/********************************************************/
	cout<<"test FindCommonNode:\n";
	vector<int> vv1{1,2,3};
	vector<int> vv2{1,2,3,4,5};
	vector<int> vv3{6,7,8,9};

	ListNode ll1 = CreateListByTail(vv1);
	ListNode ll2 = CreateListByTail(vv2);
	ListNode ll3 = CreateListByTail(vv3);

	ListNode tmp = ll1;
	while(tmp->m_next!=NULL){
		tmp = tmp->m_next;
	}
	tmp->m_next = ll3;
	tmp = ll2;
	while(tmp->m_next!=NULL){
		tmp = tmp->m_next;
	}
	tmp->m_next = ll3;
	PrintList(ll1);
	PrintList(ll2);
	Node* mnode = FindCommonNode(ll1, ll2);
	if(mnode == NULL){
		cout<<"mnode is nulli";
	}else{
		cout<<"node: "<<mnode->m_data;
	}
	cout<<endl;

	/********************************************************/
	cout<<"test HasCycle:\n";
	vector<int> vc{1,2,3,4,5,6,7,8,9};
	ListNode lvc = CreateListByTail(vc);
	tmp = lvc;
	while(tmp->m_next != NULL){
		tmp = tmp->m_next;
	}
	tmp->m_next = lvc->m_next->m_next->m_next; //9->4
	if(HasCycle(lvc)){
		cout<<"lvc has cycle\n";
	}else{
		cout<<"lvc no cycle\n";
	}
	vector<int> v{1,2};
	if(HasCycle(CreateListByTail(v))){
		cout<<"lv has cycle\n";
	}else{
		cout<<"lv no cycle\n";
	}

	/********************************************************/
	cout<<"test GetCycleLength(6) size:";
	cout<<GetCycleLength(lvc)<<endl;

	/********************************************************/
	cout<<"test GetCycleFirstNode(4): ";
	cout<<GetCycleFirstNode(lvc)->m_data<<endl;

	/********************************************************/
	cout<<"test DeleteNode: ";
	vector<int> delv{1,2,3};
	ListNode delList = CreateListByTail(delv);
	Node* del = delList->m_next;
	cout<<"delete 2: ";
	DeleteNode(&delList, del);
	PrintList(delList);
	cout<<"delete 3: ";
	DeleteNode(&delList, del);
	PrintList(delList);
	cout<<"delete 1: ";
	DeleteNode(&delList, delList);
	PrintList(delList);


	/********************************************************/
	cout<<"test MergeSortedList: \n";
	vector<int> sortV1{1,3,5,7};
	vector<int> sortV2{2,3,4,6,8,9};
	ListNode sortL1 = CreateListByTail(sortV1);
	ListNode sortL2 = CreateListByTail(sortV2);
	PrintList(sortL1);
	PrintList(sortL2);
	PrintList(MergeSortedList(sortL1, sortL2));

	return 0;
}


