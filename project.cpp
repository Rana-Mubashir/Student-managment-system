#include<iostream>
#include <stdlib.h>
using namespace std;
class Student{
	public:
		string name;
		int age,Class,rollNo;
		int nodeHeight;
		Student* left;
		Student* right;
		Student(string Name,int Age,int clas,int rollno)
		{
			name=Name;
			age=Age;
			Class=clas;
			rollNo=rollno;
			left=0;
			right=0;
			nodeHeight=1;
		}
		void displayStudentData()
		{
			cout<<endl;
			cout<<"Name of student :"<<name<<endl;
			cout<<"Age of student :"<<age<<endl;
			cout<<"Class of student :"<<Class<<endl;
			cout<<"Roll no of student :"<<rollNo<<endl;
			cout<<endl;
		}
};
int getHeight(Student* node)
{
	if(node!=0)
	{
		return node->nodeHeight;
	}
	else
	{
		return 0;
	}
}
int getMaxHeight(int a,int b)
{
	if(a > b)
	{
		return a;
	}
	else if(a==b)
	{
		return a;
	}
	else{
		return b;
	}
}
int getNodeBalance(Student* node)
{
	return getHeight(node->left)-getHeight(node->right);
}
void llCase(Student* &node)
{
	Student* temp=node->left;
	Student* temp2=temp->right;
	temp->right=node;
	node->left=temp2;
	node->nodeHeight=1+getMaxHeight(getHeight(node->left),getHeight(node->right));
	temp->nodeHeight=1+getMaxHeight(getHeight(temp->left),getHeight(temp->right));
	node=temp;
}
void rrCase(Student* &node)
{
	Student* temp=node->right;
	Student* temp2=temp->left;
	temp->left=node;
	node->right=temp2;
	node->nodeHeight=1+getMaxHeight(getHeight(node->left),getHeight(node->right));
	temp->nodeHeight=1+getMaxHeight(getHeight(temp->left),getHeight(temp->right));
	node=temp;
}
void lrCase(Student* &node)
{
	Student* temp=node->left;
	Student* temp2=temp->right;
	Student* temp3=temp2->left;
	node->left=temp2;
	temp2->left=temp;
	temp->right=temp3;
	node->nodeHeight=1+getMaxHeight(getHeight(node->left),getHeight(node->right));
	temp->nodeHeight=1+getMaxHeight(getHeight(temp->left),getHeight(temp->right));
	temp2->nodeHeight=1+getMaxHeight(getHeight(temp2->left),getHeight(temp2->right));
	llCase(node);
}
void rlCase(Student* &node)
{
	Student* temp=node->right;
	Student* temp2=temp->left;
	Student* temp3=temp2->right;
	node->right=temp2;
	temp2->right=temp;
	temp->left=temp3;
	node->nodeHeight=1+getMaxHeight(getHeight(node->left),getHeight(node->right));
	temp->nodeHeight=1+getMaxHeight(getHeight(temp->left),getHeight(temp->right));
	temp2->nodeHeight=1+getMaxHeight(getHeight(temp2->left),getHeight(temp2->right));
	rrCase(node);
}
void createNode(Student* &node,string Name,int Age,int clas,int rollno)
{
	//Bst code 
	
	if(node==0)
	{
		node=new Student(Name,Age,clas,rollno);
	}
	else if(rollno > node->rollNo)
	{
		createNode(node->right,Name,Age,clas,rollno);
	}
	else if(rollno < node->rollNo)
	{
		createNode(node->left,Name,Age,clas,rollno);
	}
	else {
		cout<<"Student with rollNo already in data."<<endl;
	}
	
	// Avl Tree code
	
	node->nodeHeight=1+getMaxHeight(getHeight(node->left),getHeight(node->right));
	int balance=getNodeBalance(node);
	if(balance < -1 && rollno > node->right->rollNo)
	{
		rrCase(node);
	}
	else if(balance > 1 && rollno < node->left->rollNo)
	{
	    llCase(node);
	}
	else if(balance > 1 && rollno > node->left->rollNo)
	{
		lrCase(node);
	}
	else if(balance < -1 && rollno < node->right->rollNo)
	{
		rlCase(node);
	}
	
}
Student* getMaxToDel(Student* &node)
{
	if(node->right)
	{
		getMaxToDel(node->right);
	}
	else
	{
		Student* temp=node;
		node=0;
		return temp;
	}
}
void delNode(Student* &node,int rollno,bool &flag)
{
	if(node!=0)
	{
		if(rollno == node->rollNo)
		{
			if(!node->left && !node->right)
			{
				Student* temp=node;
				node=0;
				delete temp;
				flag=true;
				return;
			}
			else if(node->left && node->right)
			{
				Student* data=getMaxToDel(node->left);
				node->name=data->name;
				node->age=data->age;
				node->Class=data->Class;
				node->rollNo=data->rollNo;
				delete data;
				flag=true;
				
			}
			else if(node->left && !node->right)
			{
				Student* temp=node->left;
				node->name=temp->name;
				node->age=temp->age;
				node->Class=temp->Class;
				node->rollNo=temp->rollNo;
				node->left=0;
				delete temp;
				flag=true;
				
			}
			else
			{
			    Student* temp=node->right;
			    node->name=temp->name;
			    node->age=temp->age;
			    node->Class=temp->Class;
			    node->rollNo=temp->rollNo;
			    node->right=0;
			    delete temp;
			    flag=true;
			    
			}
		}
		else if(rollno > node->rollNo)
		{
			delNode(node->right,rollno,flag);
		}
		else{
			delNode(node->left,rollno,flag);
		}
		
		
		// adjusting height after deletion
			
		if(flag)
		{
			node->nodeHeight=1+getMaxHeight(getHeight(node->left),getHeight(node->right));
			int balance=getNodeBalance(node);
			if(balance > 1 && getNodeBalance(node->left) >=0)
			{
				llCase(node);
			}
			else if(balance > 1 && getNodeBalance(node->left) < 0)
			{
				lrCase(node);
			}
			else if(balance < -1 && getNodeBalance(node->right) <= 0)
			{
				rrCase(node);
			}
			else if(balance < -1 && getNodeBalance(node->right) > 0)
			{
				rlCase(node);
			}
		}
	}
	else
	{
		return;
	}
}
void searchStudentByRollNo(Student* node,int rollno)
{
	if(node!=0)
	{
		if(node->rollNo == rollno)
		{
		 node->displayStudentData();
		}
		else if(node->rollNo > rollno)
		{
		 searchStudentByRollNo(node->left,rollno);
		}
		else
		{
		searchStudentByRollNo(node->right,rollno);
		}
	}
	else{
		cout<<"No student with this roll no."<<endl;
	}
}
void searchStudentByName(Student* node,string name)
{
	if(node!=0)
	{
		if(node->name==name)
		{
			node->displayStudentData();
		}
		searchStudentByName(node->left,name);
		searchStudentByName(node->right,name);
	}
	else {
		return;
	}
}
void updateStudentData(Student* &node,int rollno,string whatToUpdate)
{
	if(node!=0)
	{
		if(node->rollNo == rollno)
		{
			if(whatToUpdate == "name")
			{
				cout<<"Student name is "<<node->name<<endl;
				cout<<"Enter new name :";
				cin>>node->name;
			}
			else if(whatToUpdate == "age")
			{
				cout<<"Student age is "<<node->age<<endl;
				cout<<"Enter new age :";
				cin>>node->age;
			}
			else if(whatToUpdate == "class")
			{
				cout<<"Student class is "<<node->Class<<endl;
				cout<<"Enter new class  :";
				cin>>node->Class;
			}
		}
		else if(node->rollNo < rollno)
		{
			updateStudentData(node->right,rollno,whatToUpdate);
		}
		else{
			updateStudentData(node->left,rollno,whatToUpdate);
		}
	}
	else{
		cout<<"No student with this roll no."<<endl;
	}
}
void display(Student* node)
{
	if(node!=0)
	{
	   display(node->left);
	   node->displayStudentData();
	   display(node->right);
	}
	else{
		return;
	}
}
int main()
{
	string name;
	int choice,again=1,data,age,Class,rollno;
	Student* node=0;
	while(again)
	{
		cout<<"1.Add a student."<<endl;
		cout<<"2.Delete a student."<<endl;
		cout<<"3.Search student by roll no."<<endl;
		cout<<"4.Search student by name."<<endl;
		cout<<"5.Update student data."<<endl;
		cout<<"6.Display all students."<<endl;
		cout<<"Enter your choice :";
		cin>>choice;
		if(choice==1)
		{
			cout<<"Enter name of student :";
			cin>>name;
			cout<<"Enter age of student :";
			cin>>age;
			cout<<"Enter class of student :";
			cin>>Class;
			cout<<"Enter roll no of student :";
			cin>>rollno;
			createNode(node,name,age,Class,rollno);
		}
		else if(choice==2)
		{
			bool flag=false;
			cout<<"Enter roll no of student you want  to delete :";
			cin>>rollno;
			delNode(node,rollno,flag);
		}
		else if(choice==3)
		{
			cout<<"Enter roll no of student you want to search :";
			cin>>rollno;
			searchStudentByRollNo(node,rollno);
		}
		else if(choice==4)
		{
			cout<<"Enter name of student you want to search :";
			cin>>name;
			searchStudentByName(node,name);
		}
		else if(choice==5)
		{
			cout<<"Enter roll no of student you want  to delete :";
			cin>>rollno;
			cout<<"1.Update name."<<endl;
			cout<<"2.Update Age."<<endl;
			cout<<"3.Update class."<<endl;
			cout<<"Enter your choice :";
			cin>>choice;
			if(choice==1)
			{
				updateStudentData(node,rollno,"name");
			}
			else if(choice==2)
			{
				updateStudentData(node,rollno,"age");
			}
			else if(choice==3)
			{
				updateStudentData(node,rollno,"class");
			}
			else{
				cout<<"Enter valid option."<<endl;
			}
		}
		else if(choice==6)
		{
			display(node);
		}
		cout<<"Enter 0 to end: ";
		cin>>again;
		if (again)
        {
            system("cls");
        }
	}
	
	
	
	
	
	
	

	
}
