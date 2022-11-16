#include<windows.h>
#include<iostream>
#include <string>
using namespace std;

void clrscr()
{
  system("cls");
}

struct node
{
  string first_name, last_name, number;
  node *next;
};

node *head = NULL, *newnode, *temp=NULL;
int len = 0;

void add_node()
{
  newnode = new node;
  clrscr();
  cout<<"CONTACT INFORMATION\n"<<endl;
  cout<<"Enter first Name: ";
  cin>>newnode->first_name;

  cout<<"Enter last Name: ";
  cin>>newnode->last_name;

  cout<<"Enter number: ";
  cin>>newnode->number;

  newnode->first_name[0] = toupper(newnode->first_name[0]);
  newnode->last_name[0] = toupper(newnode->last_name[0]);
  newnode->next = NULL;

  if(head == NULL)
  {
    head = newnode;
    temp = newnode;
  }
  else
  {
    node *prev = head;
    temp = head;
    bool add_to_end = false;
    while((temp->first_name+temp->last_name)<(newnode->first_name+newnode->last_name))
    {
      if(temp->next==NULL)
      {
        add_to_end = true;
        break;
      }
      prev = temp;
      temp = temp->next;
    }
    if(temp==head&&!add_to_end)
    {
      newnode->next = temp;
      head = newnode;
    }
    else if(temp==head)
    {
      temp->next=newnode;
    }
    else if(add_to_end)
      temp->next = newnode;
    else
    {
      newnode->next = temp;
      prev->next = newnode;
    }
  }
  cout<<"\nContact added."<<endl;
  cout<<"\nPress ENTER to return to MAIN MENU."<<endl;
  cin.ignore();
  getchar();
}

void display_all()
{
  clrscr();
  if(head == NULL)
    cout<<"Contact list is Empty"<<endl;
  else
  {
    node *trav = head;
    int n=1;
    while (trav != NULL)
    {
      cout<<"CONTACT "<<n++<<endl;
      cout<<"Full Name: "<<trav->first_name<<" "<<trav->last_name<<endl;
      cout<<"Phone Number: "<<trav->number<<endl;
      trav= trav->next;
      len++;
      cout<<endl;
    }
    cout<<"Total contacts in the list: "<<len<<endl;
  }
  cout<<"\nPress ENTER to return to MAIN MENU."<<endl;
  cin.ignore();
  getchar();
}

void search_contact()
{
  clrscr();
  node *search_node = head;
  string srch;
  int count = 1;
  cout<<"Enter your desired contact you want to search: ";
  cin.ignore();
  getline(cin,srch);
  bool found = false;
  if(head == NULL)
    cout<<"List is Empty"<<endl;
  else
  {
    while(search_node != NULL)
    {
      if(srch == search_node->first_name || srch == search_node->last_name || srch == search_node->number || srch == (search_node->first_name+" "+search_node->last_name))
      {

        cout<<"\nCONTACT "<<count<<endl;
        cout<<"Full Name: "<<search_node->first_name<<" "<<search_node->last_name<<endl;
        cout<<"Phone number: "<<search_node->number<<endl;
        found =true;
        count++;
        cout<<endl;
      }
      search_node = search_node->next;
    }
  }
  if(!found)
    cout<<"Desired contact not found."<<endl;
  cout<<"\nPress ENTER to return to MAIN MENU."<<endl;
  getchar();
}

void delete_at_pos(int pos)
{
  node *temp = head;
  node *prev;
  if(pos==0)
  {
    head = head->next;
    delete temp;
    return;
  }
  else
  {
    for(int i=0;i<pos;i++)
    {
      prev = temp;
      temp = temp->next;
    }
    prev->next = temp->next;
    delete temp;
  }
}

void contact_at_pos(int pos)
{
  temp = head;
  for(int i=0;i<pos;i++)
    temp = temp->next;
  cout<<"Full Name: "<<temp->first_name<<" "<<temp->last_name<<endl;
  cout<<"Phone number: "<<temp->number<<endl;
}

void delete_contact()
{
  clrscr();
  node *search_node = head;
  if(search_node == NULL)
  {
    cout<<"List is Empty"<<endl;
    getchar();
  }
  else
  {
    int match[5] = {-1,-1,-1,-1,-1}, index = 0, x=0;
    string srch;
    cout<<"Enter the name of the contact: ";
    cin.ignore();
    getline(cin,srch);
    while(search_node != NULL)
    {
      if(srch == search_node->first_name || srch == search_node->last_name || srch == search_node->number || srch == (search_node->first_name+" "+search_node->last_name))
        match[x++] = index++;
      else
        index++;
      search_node = search_node->next;
    }
    if(x==1)
    {
      delete_at_pos(match[0]);
      cout<<"CONTACT DELETED"<<endl;
      cout<<"\nPress ENTER to return to MAIN MENU."<<endl;
      getchar();
    }
    else if(x>1)
    {
      int d=-1;
      cout<<"Multiple Contacts Found"<<endl;
      int j=0;
      while(match[j]!=-1)
      {
        cout<<"CONTACT "<<j+1<<endl;
        contact_at_pos(match[j]);
        cout<<endl;
        j++;
      }
      while(d==-1)
      {
        char c;
        cout<<"Which one do you want to delete: ";
        cin>>c;
        if(c>=49 && c<49+j)
        {
          d=int(c-48);
          break;
        }
        else
          cout<<"Invalid Input. TRY AGAIN"<<endl;
      }
      delete_at_pos(match[d-1]);
      cout<<"CONTACT DELETED"<<endl;
      cout<<"\nPress ENTER to return to MAIN MENU."<<endl;
      cin.ignore();
      getchar();
    }
    else
    {
      cout<<"No matching contact"<<endl;
      cout<<"\nPress ENTER to return to MAIN MENU."<<endl;
      getchar();
    }
  }
}

void menu()
{
  clrscr();
  cout<<"--------------------------------------MENU--------------------------------------"<<endl;
  cout<<"1. Add contact"<<endl;
  cout<<"2. Display all contact"<<endl;
  cout<<"3. Search contact"<<endl;
  cout<<"4. Delete Contact"<<endl;
  cout<<"5. Exit"<<endl;
}

int main()
{
  int op;
  while(true)
  {
    menu();
    cin>>op;
    switch (op)
    {
      case 1:
        add_node();
        break;
      case 2:
        len = 0;
        display_all();
        break;
      case 3:
        search_contact();
        break;
      case 4:
        delete_contact();
        break;
      case 5:
        exit(0);
      default:
        cout<<"Invalid Option "<<endl;
    }
  }
}
