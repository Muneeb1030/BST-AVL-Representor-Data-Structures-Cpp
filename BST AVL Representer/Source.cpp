#include<iostream>
#include<SFML/Graphics.hpp>
using namespace std;
using namespace sf;
////////////////////////////////////////////////////////
//Setting Size of SFML Windows
float window_x = 1000, window_y = 650;
//Creating SFML Windows
RenderWindow window(VideoMode(window_x, window_y), "BST AVL Representer");
/////////////////////////////////
//------------>> Objects of Fonts......
Font TimesNewRoman;
//////////////////////////////////
//graph data structure concept
Vertex Vertex1;// endpoints of line v1
Vertex Vertex2;// endpoints of line v2
VertexArray LinesBetween(Lines, 2);// lines

/////////////////////////////////
//------->> Data Presentation
CircleShape CircleAroundData;//Nodes
Text ValueInserted;//Key_Value

//////////////////////////////////
//------>> Screen Identifier
Text Tree_Name;
const float Tree_Namex = window_x / 2 - 160;
const float Tree_Namey = 50;

//////////////////////////////////////////
//------>> Position of Root 
const float Root_x = window_x / 2;
const float Root_y = Tree_Namey + 150;

//------------<< BSTNode Class >>------------ 
class BSTNode
{
public:
	//------------<< Data Members >>------------
	int Data;//This is used for Storing Values in objects
	///////////////////////////////////////////
	//----->> Pointer to left child
	BSTNode* Left;
	//----->> Pointer to right child
	BSTNode* Right;
	//----->> Pointer to Parent
	BSTNode* Parent;
	////////////////////////////////////
	//---->> SFML Required
	float NodeXPosition;//Node Position_x
	float NodeYPosition;//Node Position_y
	float RadiusofCircle;//Size of Node
	Color Node_Color;//Node Color
	float OutlineThickness;//Node Outline
	Color OutlineThicknessColor;//Outline Color
	Color Text_Color;//KeyValue Color
	//------------<< Constructor >>------------
	//This will initialize all the data members with there default values
	BSTNode(int data)
	{
		Left = Right = Parent = NULL;
		Data = data;
		RadiusofCircle = 20;
		Node_Color = Color::Color(179, 240, 197);
		OutlineThickness = 5;
		OutlineThicknessColor = Color::Color(32, 98, 52);
		Text_Color = OutlineThicknessColor;
	}
};
/////////////////////////////////////
//-----<< BST Tree >>------ 
class BST
{
private:
	/////////////////////////////
	//------------<< Data Members >>------------
	//This Pointer will act as Root, means this will act as the base address
	//holder
	BSTNode* BSTRoot;
public:
	//////////////////////////////
	//------>> Member Methods
	/////////////////////////////
	//------>> Insertion
	//This function will Insert the Values in thee tree
	bool Insert(int Info)
	{
		BSTNode* NewNode = new BSTNode(Info);//Creating New Node
		if (!BSTRoot)//If the Node is the Very First
			//Insert it at Node
		{
			BSTRoot = NewNode;
			DisplayTree();
			sleep(seconds(4));
			return true;
		}
		else
		{
			BSTNode* CurrentNode = BSTRoot;
			//Get the Right Position for the Data
			//If it is greater than root in right subtree
			//else in left subtree
			while (true)
			{
				if (Info < CurrentNode->Data)//checking condition
				{
					if (CurrentNode->Left)//if there exist a child
					{
						CurrentNode = CurrentNode->Left;//moving forward
					}
					else
					{
						CurrentNode->Left = NewNode;//Placing the Node
						CurrentNode->Left->Parent = CurrentNode;
						DisplayTree();
						sleep(seconds(4));
						break;
					}
				}
				else if (Info > CurrentNode->Data)//Checking the condition
				{
					if (CurrentNode->Right)//if there exist a child
					{
						CurrentNode = CurrentNode->Right;//moving forward
					}
					else
					{
						CurrentNode->Right = NewNode;//Placing the Node
						CurrentNode->Right->Parent = CurrentNode;
						DisplayTree();
						sleep(seconds(4));
						break;
					}
				}
				//if Duplication is taking place no insertion takes place
				else
				{
					cout << "\n\tInvalid!\n";
					return false;
				}
			}
		}
	}
	///////////////////////////////
	//------>> Search
	//This function will Search the provided data in the tree
	BSTNode* Search_Node(int InfoProvided)
	{
		BSTNode* CurrentNode = BSTRoot;//Starting from root
		while (CurrentNode)//Until last child is not reached
		{
			if (CurrentNode->Data == InfoProvided)//if match found
			{
				CurrentNode->OutlineThicknessColor = Color::Red;//FOUNDED FOR WINDOW
				DisplayTree();
				sleep(seconds(3));
				CurrentNode->OutlineThicknessColor = CurrentNode->Text_Color;
				return CurrentNode;//FOR CONSOLE
			}
			else if (CurrentNode->Data < InfoProvided)//if the data is in right sub tree
			{
				CurrentNode = CurrentNode->Right;//moving forward
			}
			else//else it wil be in left sub tree
			{
				CurrentNode = CurrentNode->Left;
			}
		}
		return NULL;//no match found
	}
	int TreeHeight(BSTNode* ProvideNode)
	{
		int LeftHeight, RightHeight;
		if (!ProvideNode)
		{
			//Base Condition
			return -1;
		}
		else
		{
			LeftHeight = TreeHeight(ProvideNode->Left);//getting left subtree height
			RightHeight = TreeHeight(ProvideNode->Right);//getting right subtree height
			if (LeftHeight > RightHeight)//if left subtree has more height than right
				//then the tree height will be the higher and vice versa
			{
				return LeftHeight + 1;
			}
			else
			{
				return RightHeight + 1;
			}
		}
	}
	/////////////////////////////
	//------>> TreeNodes
	int TreeNodes(BSTNode* ProvidedNode)
	{
		int NumberofNodes = 0;
		NodeCounter(ProvidedNode, NumberofNodes);
		return NumberofNodes;
	}
	//////////////////////////////////
	void NodeCounter(BSTNode* ProvidedNode, int& Count)
	{
		if (ProvidedNode)
		{
			Count++;
			//left Most child then move backward
			NodeCounter(ProvidedNode->Left, Count);
			NodeCounter(ProvidedNode->Right, Count);
		}
	}
	/////////////////////////////
	//------>> GetRoot
	//This function will return the address of root pointer
	BSTNode* GetRoot()
	{
		return BSTRoot;
	}
	/////////////////////////////
	//------>> SetRoot
	//This function will the address to root pointer
	void SetRoot(BSTNode* Passed)
	{
		this->BSTRoot = Passed;
	}
	/////////////////////////////
	//------>> Destructor
	//This function will free all the memory occupied by tree
	~BST()
	{
		FreeNodes(BSTRoot);
		BSTRoot = nullptr;
	}
	/////////////////////////////
	//------>> Sub Ordinate for Destructor
	//This function will free all the memory occupied by tree
	void FreeNodes(BSTNode* ProvidedNode)
	{
		if (ProvidedNode)
		{
			//deleting the children first and then the parent
			FreeNodes(ProvidedNode->Left);
			FreeNodes(ProvidedNode->Right);
			delete ProvidedNode;
		}
	}
	////////////////////////////////////////
	void ClassName()// Name of Tree Draw Function
	{
		Tree_Name.setString(" \" BST \" ");
		Tree_Name.setOutlineThickness(5);
		Tree_Name.setOutlineColor(BSTRoot->OutlineThicknessColor);
		Tree_Name.setFillColor(BSTRoot->Node_Color);
		Tree_Name.setCharacterSize(80);
		Tree_Name.setFont(TimesNewRoman);
		Tree_Name.setLetterSpacing(1.5);
		Tree_Name.setPosition(Tree_Namex, Tree_Namey);
		window.draw(Tree_Name);
	}
	void Set_Root_Position()//Setting Root Node Position on Sfml Window
	{
		if (BSTRoot != NULL)
		{
			BSTRoot->NodeXPosition = Root_x;//MAIN ROOT NODE POSITION X
			BSTRoot->NodeYPosition = Root_y;//MAIN ROOT NODE POSITION Y
		}
	}
	void Set_SubTree_X_Axis(BSTNode* ProvidedNode, bool check)//SETTING X-AXIS OF ROOT SUB-TREES
	{
		if (ProvidedNode != NULL)
		{
			Set_SubTree_X_Axis(ProvidedNode->Left, 0);
			if (ProvidedNode != BSTRoot)
			{
				if (check == 0)//LEFT CHILD
				{
					ProvidedNode->NodeXPosition =
						ProvidedNode->Parent->NodeXPosition -
						(TreeNodes(ProvidedNode)) * 30;
				}
				else//RIGHT CHILD
				{
					ProvidedNode->NodeXPosition =
						ProvidedNode->Parent->NodeXPosition +
						(TreeNodes(ProvidedNode)) * 30;
				}
			}
			Set_SubTree_X_Axis(ProvidedNode->Right, 1);
		}
	}
	void Set_SubTree_Y_Axis(BSTNode* ProvidedNode, int increment)//SETTING Y-AXIS OF ROOT SUBTREES
	{
		if (ProvidedNode != NULL)
		{
			Set_SubTree_Y_Axis(ProvidedNode->Left, increment + 75);
			if (ProvidedNode != BSTRoot)
			{
				ProvidedNode->NodeYPosition = increment;
			}
			Set_SubTree_Y_Axis(ProvidedNode->Right, increment + 75);
		}
	}
	void Draw_line(BSTNode* Root)//WILL DRAW EDGES ON WINDOW
	{
		if (Root != NULL)
		{
			Draw_line(Root->Left);
			if (Root->Left != NULL)
			{
				Vertex1.position = Vector2f(Root->NodeXPosition, Root->NodeYPosition);
				Vertex1.color = Color::Color::Red;
				Vertex2.position = Vector2f(Root->Left->NodeXPosition, Root->Left->NodeYPosition);
				Vertex2.color = Color::Color::Green;
				LinesBetween[0] = Vertex1;
				LinesBetween[1] = Vertex2;
				window.draw(LinesBetween);
			}
			if (Root->Right != NULL)
			{
				Vertex1.position = Vector2f(Root->NodeXPosition, Root->NodeYPosition);
				Vertex1.color = Color::Color::Red;
				Vertex2.position = Vector2f(Root->Right->NodeXPosition, Root->Right->NodeYPosition);
				Vertex2.color = Color::Color::Green;
				LinesBetween[0] = Vertex1;
				LinesBetween[1] = Vertex2;
				window.draw(LinesBetween);
			}
			Draw_line(Root->Right);
		}
	}
	void Draw_CircleANDText(BSTNode* ProvidedNode)//WILL DRAW KEYVALUE AND NODES
	{
		if (ProvidedNode != NULL)
		{
			Draw_CircleANDText(ProvidedNode->Left);
			CircleAroundData.setRadius(BSTRoot->RadiusofCircle);
			CircleAroundData.setPosition(ProvidedNode->NodeXPosition - 20, ProvidedNode->NodeYPosition - 20);
			CircleAroundData.setFillColor(ProvidedNode->Node_Color);
			CircleAroundData.setOutlineThickness(ProvidedNode->OutlineThickness);
			CircleAroundData.setOutlineColor(ProvidedNode->OutlineThicknessColor);
			window.draw(CircleAroundData);
			ValueInserted.setString(to_string(ProvidedNode->Data));
			ValueInserted.setCharacterSize(20);
			ValueInserted.setPosition(CircleAroundData.getPosition().x + BSTRoot->RadiusofCircle / 2 - 3,
				CircleAroundData.getPosition().y + BSTRoot->RadiusofCircle / 2 - 3);
			ValueInserted.setFillColor(ProvidedNode->OutlineThicknessColor);
			ValueInserted.setFont(TimesNewRoman);
			window.draw(ValueInserted);
			Draw_CircleANDText(ProvidedNode->Right);
		}
	}
	void Display()//will draw all stuff
	{
		if (BSTRoot != NULL)
		{
			Set_Root_Position();
			Set_SubTree_X_Axis(BSTRoot, 0);
			Set_SubTree_Y_Axis(BSTRoot, Root_y);
			for (int loop = 0; loop < TreeHeight(BSTRoot) + 2; loop++)
			{
				Draw_line(BSTRoot);
				Draw_CircleANDText(BSTRoot);
			}
		}
	}
	void DisplayTree()//will display all stuff
	{
		for (int loop = 0; loop < TreeHeight(BSTRoot) + 1; loop++)
		{
			window.clear(BSTRoot->Node_Color);
			ClassName();
			Display();
			window.display();
		}
	}
};
//------------<< AVLNode Class >>------------ 
class AVLNode
{
public:
	//------------<< Data Members >>------------
	int Key;//This is used for Storing Values in objects
	///////////////////////////////////////////
	//----->> Pointer to left child
	AVLNode* Left;
	//----->> Pointer to right child
	AVLNode* Right;
	//----->> Pointer to Parent
	AVLNode* Parent;
	//----->> Object of BST
	BST ChainedBST;
	////////////////////////////////////
	//---->> SFML Required
	float NodeXPosition;//Node Position_x
	float NodeYPosition;//Node Position_y
	float RadiusofCircle;//Size of Node
	Color Node_Color;//Node Color
	float OutlineThickness;//Node Outline
	Color OutlineThicknessColor;//Outline Color
	Color Text_Color;//KeyValue Color
	//------------<< Constructor >>------------
	//This will initialize all the data members with there default values
	AVLNode()
	{
		Key = 0;
		Left = Right = Parent = NULL;
		RadiusofCircle = 20;
		Node_Color = Color::Color(179, 240, 197);
		OutlineThickness = 5;
		OutlineThicknessColor = Color::Color(32, 98, 52);
		Text_Color = OutlineThicknessColor;
	}
};
/////////////////////////////////////
//-----<< AVL Tree >>------
/////////////////////////////////////
//This class is the main class,means all the functionality and the operations 
//that are to be performed by the respective user of the program are in this class
class AVL
{
private:
	/////////////////////////////
	//------------<< Data Members >>------------
	//This Pointer will act as Root, means this will act as the base address
	//holder
	AVLNode* AVLRoot;
public:
	//////////////////////////////
	//------>> Member Methods
	/////////////////////////////
	//------>> Insertion
	//This function will Insert the Values in thee tree
	bool Insert(int Info)
	{
		AVLNode* NewNode = new AVLNode();//Creating New Node
		NewNode->Key = Info % 10;
		bool AlreadyExist = false;
		if (!AVLRoot)//If the Node is the Very First
			//Insert it at Node
		{
			AVLRoot = NewNode;
			DisplayTree();
			sleep(seconds(3));
			AVLRoot->ChainedBST.Insert(Info);
			return true;
		}
		else
		{
			AVLNode* CurrentNode = AVLRoot;
			//Get the Right Position for the Data
			//If it is greater than root in right subtree
			//else in left subtree
			while (true)
			{
				if (NewNode->Key < CurrentNode->Key)//checking condition
				{
					if (CurrentNode->Left)//if there exist a child
					{
						CurrentNode = CurrentNode->Left;//moving forward
					}
					else
					{
						CurrentNode->Left = NewNode;//Placing the Node
						CurrentNode->Left->Parent = CurrentNode;
						DisplayTree();
						sleep(seconds(3));
						CurrentNode->Left->ChainedBST.Insert(Info);
						AlreadyExist = false;
						break;
					}
				}
				else if (NewNode->Key > CurrentNode->Key)//Checking the condition
				{
					if (CurrentNode->Right)//if there exist a child
					{
						CurrentNode = CurrentNode->Right;//moving forward
					}
					else
					{
						CurrentNode->Right = NewNode;//Placing the Node
						CurrentNode->Right->Parent = CurrentNode;
						DisplayTree();
						sleep(seconds(3));
						CurrentNode->Right->ChainedBST.Insert(Info);
						AlreadyExist = false;
						break;
					}
				}
				//if Duplication is taking place no insertion takes place
				else
				{
					DisplayTree();
					sleep(seconds(3));
					CurrentNode->ChainedBST.Insert(Info);
					break;
				}
			}
		}
		DisplayTree();
		sleep(seconds(3));
		if (AlreadyExist)//if insert didn't occured not need to
			//balance the tree
		{
			return false;
		}
		else
			//maintain the balance
		{
			BalanceIt(AVLRoot);
			return true;
		}
	}
	///////////////////////////////
	//------>> Search
	//This function will Search the provided data in the tree
	AVLNode* Search_Node(int InfoProvided)
	{
		AVLNode* CurrentNode = AVLRoot;//Starting from root
		int CurrentKey = InfoProvided % 10;
		while (CurrentNode)//Until last child is not reached
		{
			if (CurrentNode->Key == CurrentKey)//if match found
			{
				CurrentNode->OutlineThicknessColor = Color::Red;//FOUNDED FOR WINDOW
				DisplayTree();
				sleep(seconds(3));
				CurrentNode->ChainedBST.Search_Node(InfoProvided);
				sleep(seconds(3));
				CurrentNode->OutlineThicknessColor = CurrentNode->Text_Color;
				return CurrentNode;//FOR CONSOLE
			}
			else if (CurrentNode->Key < CurrentKey)//if the data is in right sub tree
			{
				CurrentNode->OutlineThicknessColor = Color::Red;//FOUNDED FOR WINDOW
				CurrentNode = CurrentNode->Right;//moving forward
				CurrentNode->Parent->OutlineThicknessColor = CurrentNode->Text_Color;
			}
			else//else it wil be in left sub tree
			{
				CurrentNode = CurrentNode->Left;
			}
		}
		return NULL;//no match found
	}
	/////////////////////////////
	//------>> TreeNodes
	int TreeNodes(AVLNode* ProvidedNode)
	{
		int NumberofNodes = 0;
		NodeCounter(ProvidedNode, NumberofNodes);
		return NumberofNodes;
	}
	//////////////////////////////////
	void NodeCounter(AVLNode* ProvidedNode, int& Count)
	{
		if (ProvidedNode)
		{
			Count++;
			//left Most child then move backward
			NodeCounter(ProvidedNode->Left, Count);
			NodeCounter(ProvidedNode->Right, Count);
		}
	}
	int TreeHeight(AVLNode* ProvideNode)
	{
		int LeftHeight, RightHeight;
		if (!ProvideNode)
		{
			//Base Condition
			return -1;
		}
		else
		{
			LeftHeight = TreeHeight(ProvideNode->Left);//getting left subtree height
			RightHeight = TreeHeight(ProvideNode->Right);//getting right subtree height
			if (LeftHeight > RightHeight)//if left subtree has more height than right
				//then the tree height will be the higher and vice versa
			{
				return LeftHeight + 1;
			}
			else
			{
				return RightHeight + 1;
			}
		}
	}
	/////////////////////////////
	//------>> Balancing Factor
	//This function will Calculate the Balancing factor for tree
	int BalanceFactor(AVLNode* ProvidedNode)
	{
		if (ProvidedNode == NULL)
		{
			return 0;
		}
		//BFactor = LeftSubtree Height-Right Subtree Height
		return TreeHeight(ProvidedNode->Left) - TreeHeight(ProvidedNode->Right);
	}
	/////////////////////////////
	//------>> Right Right Rotation
	//This function will Rotate towards left side to balance
	void RightRotate(AVLNode*& ProvidedNode)
	{
		AVLNode* AuxiliaryNode = ProvidedNode->Left;
		ProvidedNode->Left = AuxiliaryNode->Right;
		AuxiliaryNode->Right = ProvidedNode;
		AuxiliaryNode->Parent = ProvidedNode->Parent;
		ProvidedNode->Parent = AuxiliaryNode;
		if (ProvidedNode->Left != NULL)
			ProvidedNode->Left->Parent = ProvidedNode;
		ProvidedNode = AuxiliaryNode;
	}
	/////////////////////////////
	//------>> Left Left Rotation
	//This function will Rotate towards right side to balance
	void LeftRotate(AVLNode*& ProvidedNode)
	{
		AVLNode* AuxiliaryNode = ProvidedNode->Right;
		ProvidedNode->Right = AuxiliaryNode->Left;
		AuxiliaryNode->Left = ProvidedNode;
		AuxiliaryNode->Parent = ProvidedNode->Parent;
		ProvidedNode->Parent = AuxiliaryNode;
		if (ProvidedNode->Right != NULL)
			ProvidedNode->Right->Parent = ProvidedNode;
		ProvidedNode = AuxiliaryNode;
	}
	/////////////////////////////////
	//------>> Balance Checker
	//This function will maintain the balance of Tree
	void BalanceIt(AVLNode*& ProvidedNode)
	{
		if (ProvidedNode)
		{
			int B_Factor;
			BalanceIt(ProvidedNode->Left);
			BalanceIt(ProvidedNode->Right);
			B_Factor = BalanceFactor(ProvidedNode);
			// Left Left Case
			if (B_Factor > 1)
			{
				if (BalanceFactor(ProvidedNode->Left) >= 0)
				{
					RightRotate(ProvidedNode);
				}
				else
				{
					sleep(seconds(3));//TRY TO VISUALIZE THE DOUBLE ROTATION
					LeftRotate(ProvidedNode->Left);
					DisplayTree();
					sleep(seconds(4));// WINDOW SLEEP FUNCTION
					RightRotate(ProvidedNode);
					DisplayTree();
				}
			}
			//Right Right case
			if (B_Factor < -1)
			{
				if (BalanceFactor(ProvidedNode->Right) > 0)
				{
					sleep(seconds(3));//TRY TO VISUALIZE THE DOUBLE ROTATION
					RightRotate(ProvidedNode->Right);
					DisplayTree();
					sleep(seconds(4));// WINDOW SLEEP FUNCTION
					LeftRotate(ProvidedNode);
					DisplayTree();
				}
				else
				{
					LeftRotate(ProvidedNode);
				}
			}
		}
	}
	/////////////////////////////
	//------>> GetRoot
	//This function will return the address of root pointer
	AVLNode* GetRoot()
	{
		return AVLRoot;
	}
	/////////////////////////////
	//------>> SetRoot
	//This function will the address to root pointer
	void SetRoot(AVLNode* Passed)
	{
		this->AVLRoot = Passed;
	}
	/////////////////////////////
		//------>> Destructor
		//This function will free all the memory occupied by tree
	~AVL()
	{
		FreeNodes(AVLRoot);
		AVLRoot = nullptr;
	}
	/////////////////////////////
	//------>> Sub Ordinate for Destructor
	//This function will free all the memory occupied by tree
	void FreeNodes(AVLNode* ProvidedNode)
	{
		if (ProvidedNode)
		{
			//deleting the children first and then the parent
			FreeNodes(ProvidedNode->Left);
			FreeNodes(ProvidedNode->Right);
			delete ProvidedNode;
		}
	}
	////////////////////////////////////////
	void ClassName()// Name of Tree Draw Function
	{
		Tree_Name.setString(" \" AVL \" ");
		Tree_Name.setOutlineThickness(5);
		Tree_Name.setOutlineColor(AVLRoot->OutlineThicknessColor);
		Tree_Name.setFillColor(AVLRoot->Node_Color);
		Tree_Name.setCharacterSize(80);
		Tree_Name.setFont(TimesNewRoman);
		Tree_Name.setLetterSpacing(1.5);
		Tree_Name.setPosition(Tree_Namex, Tree_Namey);
		window.draw(Tree_Name);
	}
	void Set_Root_Position()//Setting Root Node Position on Sfml Window
	{
		if (AVLRoot != NULL)
		{
			AVLRoot->NodeXPosition = Root_x;//MAIN ROOT NODE POSITION X
			AVLRoot->NodeYPosition = Root_y;//MAIN ROOT NODE POSITION Y
		}
	}
	void Set_SubTree_X_Axis(AVLNode* ProvidedNode, bool check)//SETTING X-AXIS OF ROOT SUB-TREES
	{
		if (ProvidedNode != NULL)
		{
			Set_SubTree_X_Axis(ProvidedNode->Left, 0);
			if (ProvidedNode != AVLRoot)
			{
				if (check == 0)//LEFT CHILD
				{
					ProvidedNode->NodeXPosition =
						ProvidedNode->Parent->NodeXPosition -
						(TreeNodes(ProvidedNode)) * 30;
				}
				else//RIGHT CHILD
				{
					ProvidedNode->NodeXPosition =
						ProvidedNode->Parent->NodeXPosition +
						(TreeNodes(ProvidedNode)) * 30;
				}
			}
			Set_SubTree_X_Axis(ProvidedNode->Right, 1);
		}
	}
	void Set_SubTree_Y_Axis(AVLNode* ProvidedNode, int increment)//SETTING Y-AXIS OF ROOT SUBTREES
	{
		if (ProvidedNode != NULL)
		{
			Set_SubTree_Y_Axis(ProvidedNode->Left, increment + 75);
			if (ProvidedNode != AVLRoot)
			{
				ProvidedNode->NodeYPosition = increment;
			}
			Set_SubTree_Y_Axis(ProvidedNode->Right, increment + 75);
		}
	}
	void Draw_line(AVLNode* Root)//WILL DRAW EDGES ON WINDOW
	{
		if (Root != NULL)
		{
			Draw_line(Root->Left);
			if (Root->Left != NULL)
			{
				Vertex1.position = Vector2f(Root->NodeXPosition, Root->NodeYPosition);
				Vertex1.color = Color::Color::Red;
				Vertex2.position = Vector2f(Root->Left->NodeXPosition, Root->Left->NodeYPosition);
				Vertex2.color = Color::Color::Green;
				LinesBetween[0] = Vertex1;
				LinesBetween[1] = Vertex2;
				window.draw(LinesBetween);
			}
			if (Root->Right != NULL)
			{
				Vertex1.position = Vector2f(Root->NodeXPosition, Root->NodeYPosition);
				Vertex1.color = Color::Color::Red;
				Vertex2.position = Vector2f(Root->Right->NodeXPosition, Root->Right->NodeYPosition);
				Vertex2.color = Color::Color::Green;
				LinesBetween[0] = Vertex1;
				LinesBetween[1] = Vertex2;
				window.draw(LinesBetween);
			}
			Draw_line(Root->Right);
		}
	}
	void Draw_CircleANDText(AVLNode* ProvidedNode)//WILL DRAW KEYVALUE AND NODES
	{
		if (ProvidedNode != NULL)
		{
			Draw_CircleANDText(ProvidedNode->Left);
			CircleAroundData.setRadius(AVLRoot->RadiusofCircle);
			CircleAroundData.setPosition(ProvidedNode->NodeXPosition - 20, ProvidedNode->NodeYPosition - 20);
			CircleAroundData.setFillColor(ProvidedNode->Node_Color);
			CircleAroundData.setOutlineThickness(ProvidedNode->OutlineThickness);
			CircleAroundData.setOutlineColor(ProvidedNode->OutlineThicknessColor);
			window.draw(CircleAroundData);
			ValueInserted.setString(to_string(ProvidedNode->Key));
			ValueInserted.setCharacterSize(20);
			ValueInserted.setPosition(CircleAroundData.getPosition().x + AVLRoot->RadiusofCircle / 2 + 5,
				CircleAroundData.getPosition().y + AVLRoot->RadiusofCircle / 2 - 3);
			ValueInserted.setFillColor(ProvidedNode->OutlineThicknessColor);
			ValueInserted.setFont(TimesNewRoman);
			window.draw(ValueInserted);
			Draw_CircleANDText(ProvidedNode->Right);
		}
	}
	void Display()//will draw all stuff
	{
		if (AVLRoot != NULL)
		{
			Set_Root_Position();
			Set_SubTree_X_Axis(AVLRoot, 0);
			Set_SubTree_Y_Axis(AVLRoot, Root_y);
			for (int loop = 0; loop < TreeHeight(AVLRoot) + 2; loop++)
			{
				Draw_line(AVLRoot);
				Draw_CircleANDText(AVLRoot);
			}
		}
	}
	void DisplayTree()//will display all stuff
	{
		for (int loop = 0; loop < TreeHeight(AVLRoot) + 1; loop++)
		{
			window.clear(AVLRoot->Node_Color);
			ClassName();
			Display();
			window.display();
		}
	}
};

/////////////////////////////////////////
/////////////////////////////////////////
void MainMenu()
{
	system("color 3f");
	AVL Hashing;
	bool MenuBreak = false;
	int Input;
	int Option;
	do
	{
		cout << "\n\tPlease Select an Option from Following!"
			<< "\n\tPress 1 ===>> Insert"
			<< "\n\tPress 2 ===>> Search"
			<< "\n\tPress 3 ===>> Exit"
			<< "\n\n\tSelect Option = ";
		cin >> Option;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\n\n\tSelect Option = ";
			cin >> Option;
		}
		system("cls");
		switch (Option)
		{
		case 1:
			system("color 2f");
			cout << "\n\tPlease Enter the Number to Insert = ";
			cin >> Input;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "\n\tPlease Enter the Number to Insert = ";
				cin >> Input;
			}
			if (Input != -1)
			{
				if (!Hashing.Insert(Input))
				{
					cout << "\n\tInsertion is not Possible!\n";
				}
			}
			Hashing.DisplayTree();
			cout << "\n\n\t";
			system("pause");
			system("cls");
			break;
		case 2:
			system("color 4f");
			cout << "\n\tPlease Enter the Number to Search = ";
			cin >> Input;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "\n\tPlease Enter the Number to Search = ";
				cin >> Input;
			}
			if (!Hashing.Search_Node(Input))
			{
				cout << "\n\tData Does not Exist in the Tree\n";
			}
			else
			{
				cout << "\n\tData Exists in the Tree\n";
			}
			Hashing.DisplayTree();
			cout << "\n\n\t";
			system("pause");
			system("cls");
			break;
		case 3:
			MenuBreak = true;
			window.close();
			break;
		default:
			cout << "\n\tPlease Select a Valid Option!\n\tTry Again!\n";
			break;
		}
	} while (!MenuBreak);
}
int main()
{
	TimesNewRoman.loadFromFile("Fonts/Agdasima.ttf");
	while (window.isOpen())
	{
		Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == Event::Closed() || evnt.key.code == Keyboard::Escape)
			{
				window.close();
			}
		}
		MainMenu();
	}
	system("pause>0");
	return 0;
}
