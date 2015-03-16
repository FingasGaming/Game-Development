#pragma warning(once : C4251);
#pragma warning(once : C4244);
#pragma warning(once : C4083);
#pragma warning(once : C4305);
#pragma once
#ifndef KPSTRUCTURE_H
#define KPSTRUCTURE_H

#include <string>
#include <GL\glew.h>
#include <SDL2\SDL.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include <SDL2\SDL_opengl.h>
#include <SDL2\SDL_image.h>

#include "kpINI\kpINI.h"

#ifndef API_EXPORTS
#define JFE_API __declspec(dllexport) 
#else
#define JFE_API __declspec(dllimport)
#endif

#define RSA_HASH 0xE357DB46

/* A simple function that prints a message, the error code returned by SDL,
 * and quits the application */
static void sdldie(const char *msg)
{
    printf("%s: %s\n", msg, SDL_GetError());
    SDL_Quit();
    exit(1);
}
static void checkSDLError(int line = -1)
{
#ifndef NDEBUG
        const char *error = SDL_GetError();
        if (*error != '\0')
        {
                printf("SDL Error: %s\n", error);
                if (line != -1)
                        printf(" + line: %i\n", line);
                SDL_ClearError();
        }
#endif
}
//function to regulate refresh rate
static void regulateFPS(float rate, int ticks)
{
	if(1000/rate > SDL_GetTicks() - ticks)
	{
		SDL_Delay((Uint32)(1000/rate - ticks));
	}
}

//global function 
//JFE_API static SDL_Window* loadWindowSettings(const char* path);
static SDL_Window* loadWindowSettings(const char* path)
{	
	INIReader* read = new INIReader(path);

	string title = "";
	title = read->Get("MAIN WINDOW", "title", "noTitle").c_str();
	int width = read->GetInteger("MAIN WINDOW", "width", 300);
	int height = read->GetInteger("MAIN WINDOW", "height", 200);

	delete read;

	SDL_Window *tmp = SDL_CreateWindow(title.c_str(), 100, 100, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	return tmp;
}
namespace JackFruitEngine{

	class kpStructure
	{
	public:
		kpStructure(void);
		~kpStructure(void);
	};

	////////////////////////////////////////////////////////////////////
	//data structures
	////////////////////////////////////////////////////////////////////
	//Stacks
	template <class T>
	struct kpNodeType
	{
		T data;
		kpNodeType<T> *link;
	};
	template <class T>
	struct kpNode
	{
		T data;
		kpNode<T> *next;
		int wieght;
	};
	//interface class: stack base class
	template <class T>
	class JFE_API kpStack
	{
	public:
		//Function: initialise the stack
		virtual void initStack(){}
		//Function: check if stack empty
		virtual bool isEmpty()const = 0;
		//Function: check if stack full
		virtual bool isFull()const = 0;
		//Function: add to stack
		virtual void push(const T& type){}
		//Function: return top of stack
		virtual T top()const = 0;
		//Function: remove from stack
		virtual void pop(){}
	
	};
	//linked list stack - unsorted
	template <class T>
	class JFE_API kpLStack : public kpStack<T>
	{
	public:
		kpLStack()
		{
			sTop = nullptr;
		}
		~kpLStack()
		{
			initStack();
		}
		//Function: copy constructor
		kpLStack(const kpLStack<T>& stack)
		{
			sTop = nullptr;
			copyStack(stack);
		}
		//Function: copy operator
		const kpLStack<T>& operator = (const kpLStack<T>& stack)
		{
			if(this != &stack)
			{
				copyStack(stack);
			}
			return *this;
		}
		//Function: initialise the stack
		void initStack()
		{
			kpNodeType<T>*tmp;
			while( sTop != nullptr)
			{
				tmp = sTop;
				sTop = sTop->link;
				delete tmp;
			}
		}
		//Function: check if stack empty
		bool isEmpty()const{ return (sTop == nullptr); }
		//Function: check if stack full
		bool isFull()const{ return false; }
		//Function: add to stack
		void push(const T& type)
		{
			kpNodeType<T>*tmp = new kpNodeType<T>;// temp variable
			tmp->data = type; //store new type/node
			tmp->link = sTop; //link to current top of stack
			sTop = tmp; //set top of stack to new type/node
		}
		//Function: return top of stack
		T top()const
		{
			if(sTop != nullptr)//check if stack empty
				return sTop->data; // return top element
			else
				return NULL;
		}
		//Function: remove from stack
		void pop()
		{
			kpNodeType<T>*tmp;
			if( sTop != nullptr)
			{
				tmp = sTop;
				sTop = sTop->link;
				delete tmp;
			}
		}

	private:
		kpNodeType<T>* sTop;
		//Function: makes a copy of the stack
		void copyStack(const kpLStack<T>& stack)
		{
			kpNodeType<T> *tp, *curr, *last;

			if(sTop != nullptr)
			{
				initStack();
			}

			if(stack.sTop == nullptr)
			{
				sTop = nullptr;
			}
			else
			{
				curr = stack.sTop; //set curr to stack to be copy
				sTop = new kpNodeType<T>;

				sTop->data = curr->data;
				sTop->link = nullptr;
				last = sTop;
				curr = curr->link;

				while(curr != nullptr)
				{
					tp = new kpNodeType<T>;
					tp->data = curr->data;
					tp->link = nullptr;
					last->link = tp;
					last = tp;
					curr = curr->link;
				}

			}
		}
	};
	//interface class: stack base class
	template <class T>
	class JFE_API kpList
	{
	public:
		//Function: initialise the stack
		virtual void initList(){}
		//Function: check if stack empty
		virtual bool isEmpty()const = 0;
		//Function: check if stack full
		virtual bool isFull()const = 0;
		//Function: add to stack
		virtual void push(const T& type){}
		//Function: remove from stack
		virtual void pop(){}
	
	};
	//double linked list - sorted
	template <class T>
	class JFE_API kpDList : public kpList<T>
	{
		//TO DO: fix list and make useable
		//current state un-usable
	public:
		kpDList()
		{
			head = nullptr;
			end = nullptr;
			count = 0;
		}
		~kpDList()
		{
			initList();
		}
		//Function: init
		void initList()
		{
			if(!isEmpty())
			{
				kpNode<T>*curr = head;
				kpNode<T>*c;
				while(curr != end->next)
				{
					c = curr;
					curr = curr->next;
					delete c;
					count--;			
				}
			}
		}
		//Function: insert
		void insert(T ptr)
		{
			kpNode<T>*tmp = new kpNode<T>();
			tmp->data = ptr;
			if(isEmpty())
			{			
				head = tmp;
				end = head;
				head->next = end;
				end->next = nullptr;
				count++;
			}
			else if(!isEmpty())
			{
				if(count == 1)
				{
					if(head->data < tmp->data)
					{
						end = tmp;
						head->next = end;
						count++;
					}else
					{
						head->next = end;
						head = tmp;
						count++;
					}
				}
				else if (count > 1)
				{
					kpNode<T>*curr = head;
					kpNode<T>*c = end;
					while(curr != end)
					{
						if(curr->data > tmp->data)
						{
							c = curr;
							tmp->next = c;
							curr = tmp;						
							//break;
						}
						else if(curr->data < tmp->data )
						{
							c = curr->next;
							curr->next = tmp;
							tmp->next = c;
							//break;
						} 
						else
							curr = curr->next;
					}
					count++;
				}
			}
		}
		//Function: check if stack empty
		bool isEmpty()const{ return (count == 0); }
		//Function: check if stack full
		bool isFull()const { return false;}
		//Function: return data
	
		//Function: remove from stack
		void pop()
		{
			kpNode<T>*tmp;
			if( head != nullptr)
			{
				tmp = head;
				head = head->next;
				delete tmp;
			}
		}
	private:
		kpNode<T>* head;
		kpNode<T>* end;
		int count;
	};
	//Queues
	template <class T>
	class JFE_API kpQueue
	{
	public:
		//Function: initialise the queue
		virtual void initQueue(){}
		//Function: check if queue empty
		virtual bool isEmpty()const = 0;
		//Function: check if queue full
		virtual bool isFull()const = 0;
		//Function: add to queue
		virtual void addQ(const T& type){}
		//Function: return front of queue
		virtual T front()const = 0;
		//Function: return front of queue
		virtual T back()const = 0;
		//Function: remove from queue
		virtual void deleteQ(){}
	};

	template <class T>
	class JFE_API kpLQueue : public kpQueue<T>
	{
	public:
		kpLQueue()
		{
			qFront = nullptr;
			qBack = nullptr;
		}
		~kpLQueue()
		{
			initQueue();
		}
		kpLQueue(const kpLQueue<T>& Que)
		{
			qFront = nullptr;
			qBack = nullptr;
			copyQueue(Que);
		}

		const kpLQueue<T>& operator = (const kpLQueue<T>& Que)
		{
			if(this != &Que)
			{
				copyQueue(Que);
			}
			return *this;
		}
		//Function: initialise the queue
		void initQueue()
		{
			kpNodeType<T>*tmp;
			while( qFront != nullptr)
			{
				tmp = qFront;
				qFront = qFront->link;
				delete tmp;
			}
			qBack = nullptr;
		}
		//Function: check if queue empty
		bool isEmpty()const 
		{
			return (qFront == nullptr);
		}
		//Function: check if queue full
		bool isFull()const {return false;}
		//Function: add to queue
		void addQ(const T& type)
		{
			kpNodeType<T>*tmp = new kpNodeType<T>;

			tmp->data = type;
			tmp->link = nullptr;

			if(qFront == nullptr)
			{
				qFront = tmp;
				qBack = tmp;
			}
			else
			{
				qBack->link = tmp;
				qBack = qBack->link;
			}		
		}
		//Function: return front of queue
		T front()const 
		{
			if(qFront != nullptr)
			{
				return qFront->data;
			}
			return NULL;
		}
		//Function: return front of queue
		T back()const 
		{
			if(qBack != nullptr)
			{
				return qBack->data;
			}
			return NULL;
		}
		//Function: remove from queue
		void deleteQ()
		{
			kpNodeType<T>*tmp;
			if(!isEmpty())
			{
				tmp = qFront;
				qFront = qFront->link;

				delete tmp;

				if(qFront == nullptr)
				{
					qBack = nullptr;
				}
			}
		}
	private:
		kpNodeType<T> *qFront;
		kpNodeType<T> *qBack;
		//Function: makes a copy of the queue
		void copyQueue(const kpLQueue<T>& stack)
		{
			kpNodeType<T> *tp, *curr, *last;

			if(qFront != nullptr)
			{
				initQueue();
			}

			if(stack.qFront == nullptr)
			{
				qFront = nullptr;
			}
			else
			{
				curr = stack.qFront; //set curr to stack to be copy
				qFront = new kpNodeType<T>;

				qFront->data = curr->data;
				qFront->link = nullptr;
				last = qFront;
				curr = curr->link;

				while(curr != nullptr)
				{
					tp = new kpNodeType<T>;
					tp->data = curr->data;
					tp->link = nullptr;
					last->link = tp;
					last = tp;
					curr = curr->link;
				}
				qBack = stack.qBack;
				qBack->link = stack.qBack->link;
			}
		}
	};
	
	//Graphs
	template <class T>
	class kpGraph
	{
	public:
	};
	//Binary Trees
	template <class T>
	struct kpTreeNode
	{
		std::string id;
		int index;
		T data;
		kpTreeNode<T> * leftptr;
		kpTreeNode<T> * rightptr;
		kpTreeNode<T>* next;
	};
	//interface class: stack base class
	template <class T>
	class JFE_API kpBTree
	{//To Do: 
	public:
		kpBTree()
		{
			rootptr = nullptr;
		}
		~kpBTree()
		{
			if(rootptr)
			{
				killTree(rootptr);
				rootptr = nullptr;
			}
		}
		//insert into tree
		void insert(std::string key, int index, const T &data)
		{
			kpTreeNode<T> *n = new kpTreeNode<T>;
			n->id = key;
			n->index = index;
			n->data = data;
			n->leftptr = nullptr;
			n->rightptr = nullptr;
			n->next = nullptr;
			if ( this->rootptr == NULL )
			{
				rootptr = n;
			}
			else
			{
				kpTreeNode<T> *current = rootptr;
				kpTreeNode<T> *trial;
				kpTreeNode<T> *ptr;
				while(current != NULL)
				{
					trial = current;
					if(n->index == current->index)
					{
						ptr = current;
						while(ptr->next != nullptr)
						{
							ptr = ptr->next;
						}
						ptr->next = n;
						std::cout << "Already exist and will be added to index next...\n" ;
						return;
						//current = current->leftptr;
					}
					else if ( n->index < current->index )
					{
						current = current->leftptr;
					}
					else if ( n->index > current->index )
					{
						current = current->rightptr;
					}
				}
				if(trial->index == index)
				{
					return;
				}
				if(trial->index > index)
				{
					trial->leftptr = n;
				}
				else
				{
					trial->rightptr = n;
				}
			}
			count++;
		}
		//Function return the number of leaf in the tree
		void leafCount(kpTreeNode<T> *x, T &y)
		{
			y = lCount(x);
		}
		//Function calculate the height of tree
		int calculateHeight(kpTreeNode<T> *Tree = rootptr)
		{
			if(Tree == nullptr)
				return 0;
			else
				return (1 + ( max( calculateHeight(Tree->leftptr), calculateHeight(Tree->leftptr) )));
		}
		//Function print what level the node was found, and which side of the tree
		T search(std::string key, int index)
		{	
			kpTreeNode<T> *n = this->getRoot();
			if(n == nullptr)
			{
				std::cout << "Does not exist - Root of tree is null...\n";
				return NULL;
			}
			else 
			{
				kpTreeNode<T> *current = n;
				kpTreeNode<T> *trial = nullptr;
				kpTreeNode<T> *ptr = nullptr;
				bool found = false;
				while(current != NULL && found == false)
				{
					trial = current;
					if( index == current->index )
					{
						ptr = current;					
						while(ptr->next != nullptr || found == false)
						{
							if(ptr->id == key)
							{
								found = !found;
								break;
							}
							else
							{
								ptr = ptr->next;
							}
						}					
					}				
					else if ( index < current->index )
					{
						current = current->leftptr;
					}
					else if ( index > current->index )
					{
						current = current->rightptr;
					}
				}		
				if(found == true)
				{
					return ptr->data;
				}
				else
				{
					std::cout << key << " :Was not found in BTHashMap" << std::endl;
					return NULL;
				}
			}
		}
		void remove(std::string key, int index)
		{	
			kpTreeNode<T> *n = this->getRoot();
			if(n == nullptr)
			{
				std::cout << "Does not exist - Root of tree is null...\n";
			}
			else 
			{
				kpTreeNode<T> *current = n;
				kpTreeNode<T> *trial = nullptr;
				kpTreeNode<T> *ptr = nullptr;
				bool found = false;
				while(current != NULL && found == false)
				{
					trial = current;
					if( index == current->index )
					{
						ptr = current;					
						while(ptr->next != nullptr || found == false)
						{
							if(ptr->id == key)
							{
								found = !found;
							}
							else
							{
								ptr = ptr->next;
							}
						}					
					}				
					else if ( index < current->index )
					{
						current = current->leftptr;
					}
					else if ( index > current->index )
					{
						current = current->rightptr;
					}
				}		
				if(found == true)
				{
					kpTreeNode<T> *t, *d, *x = nullptr;
					d = ptr;
					t = trial;
					x = d->next;
					if(t->leftptr == nullptr && t->rightptr == nullptr && d->next == nullptr)
					{
						//at the root
						delete d;
					}
					else if(d->leftptr == nullptr && d->rightptr == nullptr)
					{
						//at next
						t->next = x;
						d->next = nullptr;
						delete d;
					}
					 //search left of tree
					else if(d->leftptr == nullptr)
					{
						//process node before we delete node
						if(t->index >= d->index)
						{
							killFromTree(d);
						}
					}
					//search right of tree
					else if(d->rightptr == nullptr)
					{
						if(t->index <= d->index)
						{
							killFromTree(d);
						}
					}
					//if both left and right of tree not null
					else if(d->leftptr != nullptr && d->rightptr != nullptr)
					{
						//search depth/next
					
					}
				}
				else
				{
					std::cout << key << " :Was not found in BTHashMap" << std::endl;
					return ;
				}
			}
		}
		T pop(std::string key, int index)
		{
			kpTreeNode<T> *n = this->getRoot();
			if(n == nullptr)
			{
				std::cout << "Does not exist - Root of tree is null...\n";
				return nullptr;
			}
			else 
			{
				kpTreeNode<T> *current = n;
				kpTreeNode<T> *trial = nullptr;
				kpTreeNode<T> *ptr = nullptr;
				kpTreeNode<T> *prev = nullptr;
				bool found = false;
				T tmp = nullptr;
				while( current != NULL && found == false)
				{
					prev = trial;
					trial = current;
					if( index == current->index )
					{
						found = true;
						if(current->id != key)
						{
							tmp = popBucket(key, current);
						}
						else
						{
							tmp = popTreeLB(key, current);
						}
					}
					else if ( index < current->index )
					{
						current = current->leftptr;
					}
					else if ( index > current->index )
					{
						current = current->rightptr;
					}
				}
				count--;
				return tmp;
			}
		}
		kpTreeNode<T> *getRoot(){ return rootptr;}
		int getCount(){ return count; }
	private:
		kpTreeNode<T> *rootptr;
		int count;
		//Tree cleanup
		void killTree(kpTreeNode<T> *t)
		{
			if(t != nullptr)
			{
				killTree(t->leftptr);
				killTree(t->rightptr);			
			}
			delete t;
			count--;
		}
		void killFromTree(kpTreeNode<T> *t)
		{
			kpTreeNode<T> *curr = rootptr;
			kpTreeNode<T> *trail;
			kpTreeNode<T> *tmp;

			if(t == nullptr)//check root
			{
				return;
			}
			else if(t->leftptr == nullptr && t->rightptr == nullptr)//check leaf
			{
				tmp = t;
				t = nullptr;
				delete tmp;
			}
			else if(t->leftptr == nullptr)//check left
			{
				if(t == rootptr)
				{
					tmp = t;
					t = t->rightptr;
					rootptr = t;
					delete tmp;
				}
				else
				{
					tmp = t;
					t = t->rightptr;
					delete tmp;
				}
			}
			else if(t->rightptr == nullptr)//check right
			{
				if(t == rootptr)
				{
					tmp = t;
					t = t->leftptr;
					rootptr = t;
					delete tmp;
				}
				tmp = t;
				t = t->leftptr;
				delete tmp;
			}
			else //check subtree
			{
				curr = t->leftptr;
				trail = nullptr;

				while(curr->rightptr != nullptr)
				{
					trail = curr;
					curr = curr->rightptr;
				}

				t->data = curr->data;

				if(trail == nullptr)
				{
					t->leftptr = curr->leftptr;
				}
				else 
				{
					trail->rightptr = curr->leftptr;
				}
				delete curr;
			}
		}
		T popBucket(std::string key, kpTreeNode<T> *t)
		{
			T tmp = nullptr;
			kpTreeNode<T> *curr = t;
			kpTreeNode<T> *prev;
			while(curr->next != nullptr)
			{
				prev = curr;
				if(curr->id == key)
				{
					tmp = curr->data;

					prev->next = curr->next;
					delete curr;				
				}
				else
				{
					curr = curr->next;
				}
			}
			return tmp;
		}
		T popTreeLB(std::string key, kpTreeNode<T> *t)
		{
			T tmp;
			if(t->id == key)
			{
				tmp = t->data;

				if(t->next == nullptr)
				{
					killFromTree(t);
				}
				else
				{
					kpTreeNode<T> * o;
					o = t;
					t->next->leftptr = t->leftptr;
					t->next->rightptr = t->rightptr;
					t = t->next;
					delete o;
				}
			}
			return tmp;
		}
		void killBucket(kpTreeNode<T> *n)
		{
			kpTreeNode<T> *b;
			if(n->next != nullptr)
			{

			}
		}
		//Functions:
		int lCount(kpTreeNode<T> *n)
		{
			int tmp = 0;
		
			if(n->leftptr != nullptr)
			{
				tmp+= lCount(n->leftptr);
			}
			if(n->rightptr != nullptr)
			{
				tmp+= lCount(n->rightptr);
			}
			else if(n->leftptr == nullptr && n->rightptr == nullptr)
			{
				tmp++;
			}
			return tmp;
		}
		static int max(int x , int y)
		{
			if(x >= y)
				return x;
			else
				return y;
		}
	};
	//hashMaps
	template <class T>
	class JFE_API kpHashMap
	{
	public:
		kpHashMap(){}
		kpHashMap(int i, int hashC)
		{ 
		
			for(i; i < hashC; i++)
			{
				hashTable[i] = new item;
				hashTable[i]->data = NULL;
				hashTable[i]->next = nullptr;
			}
		}
		~kpHashMap(){}
		virtual void add(std::string key,const T& data)
		{
			int index = hash(key);
			if(hashTable[index]->data == nullptr)
			{
				hashTable[index]->data = data;
			}else
			{
				item *ptr = hashTable[index];
				item *n = new item;
				n->data = data;
				n->next = nullptr;
				while(ptr->next != nullptr)
				{
					ptr = ptr->next;
				}
				ptr->next = n;
			}
		}
		virtual T get(std::string key)
		{
			return hashTable[hash(key)]->data;
		}
		virtual void remove(std::string key){}
		virtual int numInIndex(int index)
		{
			int count = 0;
			if(hashTable[index]->data == NULL)
			{
				return count;
			}
			else
			{
				count++;
				item *ptr = hashTable[index];
				while(ptr->next != nullptr)
				{
					count++;
					ptr = ptr->next;
				}
			}
			return count;
		}
	private:
		static const int hashCode = RSA_HASH;
		struct item
		{
			T data;
			item* next;
		};
	
		item* hashTable[255];
	protected:
		int hash(std::string key)
		{
			int h = 0;
			int index = key.length();

			for(int i = 0; i < (int)key.length(); i++)
			{
				h = h + (int)key[i];
			}
			index = h % hashCode;
			return index;
		}
	};
	
	template <class T>
	class JFE_API kpBTHashMap :public kpHashMap<T>
	{
	private:
		kpBTree<T> *table;
		int count;
	public:
		kpBTHashMap() 
		{
			table = new kpBTree<T>();
			count = 0;
		}
		~kpBTHashMap() 
		{ 
			if(table)
				delete table; 
		}
		void add(std::string key,const T data)
		{
			int index = hash(key);		
			table->insert(key,index,data);
			count++;
		}
		void remove(std::string key)
		{
			int index = hash(key);
			table->remove(key, index);
			count--;
		}
		T pop(std::string key)
		{ 
			int index = hash(key);
			T tmp = table->pop(key,index);
			if(tmp != nullptr)
				count--;
			else
			{}

			return tmp;
		}
		T get(std::string key)
		{
			return table->search(key,hash(key));
		}
		int getCount()
		{ 
			if(count != table->getCount())
			{
				count = table->getCount();
				return count;
			}
			return count;}
	};
}
#endif