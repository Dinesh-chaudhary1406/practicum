#include <iostream>
#include <stdlib.h>
#include <bits/stdc++.h>
const int infinity = INT_MAX;
using namespace std;



struct customer
{
    int age;
    string name;
    string pizzaName;
    int quantity;
    double bill;

    customer() {}

    customer(int age, string name, int quantity, string pizzaName, double bill)
    {
        this->age = age;
        this->name = name;
        this->pizzaName = pizzaName;
        this->quantity = quantity;
        this->bill = bill;
    }
};

struct takeAwayCustomer
{
    customer cusotomer;
    takeAwayCustomer *next = NULL;

    takeAwayCustomer(int age, string name, int quantity, string pizzaName, double bill)
    {
        this->cusotomer = customer(age, name, quantity, pizzaName, bill);
    }
};

struct dineInCustomer
{
    customer cusotomer;
    dineInCustomer *next = NULL;

    dineInCustomer(int age, string name, int quantity, string pizzaName, double bill)
    {
        this->cusotomer = customer(age, name, quantity, pizzaName, bill);
    }
};

struct homeDeliveryCustomer
{

    customer cusotomer;
    string address;
    double deliveryCharges;
    int distanceDelivery;
    struct homeDeliveryCustomer *next = NULL;

    homeDeliveryCustomer(int age, string name, int quantity, string pizzaName, double bill, string address, double deliveryCharges, int distanceDelivery)
    {
        this->cusotomer = customer(age, name, quantity, pizzaName, bill);
        this->address = address;
        this->deliveryCharges = deliveryCharges;
        this->distanceDelivery = distanceDelivery;
    }
};

struct PizzaShop
{

    string shopName;
    string *menu;
    int *price;
    string address;
    takeAwayCustomer *nextTakeAwayCustomer = NULL;
    dineInCustomer *nextDineInCustomer = NULL;
    homeDeliveryCustomer *nextHomeDeliveryCustomer = NULL;
};


PizzaShop *myPizzaShop = NULL;


takeAwayCustomer *currentTakeAwayCustomer = NULL;
dineInCustomer *currentDineInCustomer = NULL;
homeDeliveryCustomer *currentHomeDeliveryCustomer = NULL;


double total, takeAway, dineIn, homeDelivery;

double servedTotal;



struct servedCustomer
{

    int age;
    string name;
    int quantity;
    string pizzaName;
    double bill;
    string customerType;
    servedCustomer *left;
    servedCustomer *right;

    
    servedCustomer(int age, string name, int quantity, string pizzaName, double bill, string customerType)
    {
        

        this->age = age;
        this->name = name;
        this->quantity = quantity;
        this->pizzaName = pizzaName;
        this->bill = bill;
        this->customerType = customerType;

        
        this->left = NULL;
        this->right = NULL;
    }
};

servedCustomer *root = NULL; // Global pointer for the root of AVLTree


int isEmpty(servedCustomer *root)
{
    return root == NULL;
}


void display(servedCustomer *root)
{
    cout << "Name :" << root->name << endl;
    cout << "Age  :" << root->age << endl;
    cout << "Pizza :" << root->pizzaName << endl;
    cout << "Quantity : " << root->quantity << endl;
    cout << "Bill : " << root->bill << endl;
    cout << "Customer Type: " << root->customerType << endl;
}



servedCustomer *displayAllServedOrders(servedCustomer *root)
{

    if (root)
    {
        displayAllServedOrders(root->left);
        display(root); // will display all the served Customers
        displayAllServedOrders(root->right);
    }

    return root;
}


int height(servedCustomer *root)
{
    if (!root)
        return 0;

    return max(height(root->left), height(root->right)) + 1;
}



int balanceFactor(servedCustomer *root)
{
    if (!root)
        return 0;

    return height(root->left) - height(root->right);
}


int max(int a, int b)
{
    return (a > b) ? a : b;
}



servedCustomer *search(servedCustomer *root, string keyName)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (root->name == keyName)
    {
        return root;
    }
    else if (root->name < keyName)
    {
        return search(root->right, keyName);
    }
    else if (root->name > keyName)
    {
        return search(root->left, keyName);
    }

    return root;
}



servedCustomer *maxservedCustomer(servedCustomer *root)
{
    

    servedCustomer *p = root;
    servedCustomer *temp = NULL;

    while (p != NULL)
    {
        temp = p;
        p = p->right;
    }

    return temp;
}




servedCustomer *LLRotation(servedCustomer *root)

{
    
    servedCustomer *x = root->left;
    servedCustomer *temp = x->right;

    
    x->right = root;
    root->left = temp;

    
    root = x;
    
    return x;
}


servedCustomer *RRRotation(servedCustomer *root)
{
    

    servedCustomer *x = root->right;
    servedCustomer *temp = x->left;

    
    x->left = root;
    root->right = temp;

    
    root = x;

    
    return x;
}


servedCustomer *LRRotation(servedCustomer *root)
{
    root->left = RRRotation(root->left);
    return LLRotation(root);
}


servedCustomer *RLRotation(servedCustomer *root)
{
    root->right = LLRotation(root->right);
    return RRRotation(root);
}



servedCustomer *insertion(int age, string name, int quantity, string pizzaName, double bill, string customerType, servedCustomer *root)
{
    servedCustomer *newNode = new servedCustomer(age, name, quantity, pizzaName, bill, customerType);

    if (root == NULL)
    {
        root = newNode;
    }

    else if (root->name > newNode->name)
    {
        root->left = insertion(age, name, quantity, pizzaName, bill, customerType, root->left);
    }
    else if (root->name < newNode->name)
    {
        root->right = insertion(age, name, quantity, pizzaName, bill, customerType, root->right);
    }

    else
    {
        cout << "No duplicates Values are Allowed " << endl;
        return root;
    }

    int bf = balanceFactor(root);

    if (bf == 2)
    {
        
        if (root->left->name > newNode->name)
        {
            return LLRotation(root);
        }

        // LR
        if (root->left->name < newNode->name)
        {
            return LRRotation(root);
        }
    }
    else if (bf == -2)
    {
        
        if (root->right->name < newNode->name)
        {
            return RRRotation(root);
        }

        
        if (root->right->name > newNode->name)
        {
            return RLRotation(root);
        }
    }

    return root; 
}

servedCustomer *deleteNode(servedCustomer *root, string key)
{
    if (root == NULL)
        return root;
    else if (key < root->name)
        root->left = deleteNode(root->left, key);
    else if (key > root->name)
        root->right = deleteNode(root->right, key);
    else
    {
       
        if ((root->left == NULL) || (root->right == NULL))
        {
            servedCustomer *temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            delete (temp);
        }
        else
        {
            
            servedCustomer *temp = maxservedCustomer(root->right);
            root->name = temp->name;
            root->right = deleteNode(root->right, temp->name);
        }
    }

    if (root == NULL)
        return root;

    
    int balance = balanceFactor(root);

    
    if (balance > 1 && key < root->left->name)
        return LLRotation(root);
// LEFT RIGHT CASE
    if (balance > 1 && key > root->left->name)
    {
        root->left = LLRotation(root->left);
        return LRRotation(root);
    }

    
    if (balance < -1 && key > root->right->name)
        return RRRotation(root);

    
    if (balance < -1 && key < root->right->name)
    {
        return RLRotation(root);
    }

    return root;
}

void deleteAllServedCustomers(servedCustomer *root)
{

    while (root)
    {
        root = deleteNode(root, root->name);
    }

    cout << "The Served Customer's List is Cleared " << endl;
}



void placeOrderTakeAwayCustomer(int age, string name, string pizzaName, int quantity, double bill)
{
   
    currentTakeAwayCustomer = new takeAwayCustomer(age, name, quantity, pizzaName, bill);

    if (myPizzaShop->nextTakeAwayCustomer == NULL)
    {
        
        myPizzaShop->nextTakeAwayCustomer = currentTakeAwayCustomer;
    }
    else
    {
       
        takeAwayCustomer *temp = myPizzaShop->nextTakeAwayCustomer;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        if (temp->cusotomer.age < currentTakeAwayCustomer->cusotomer.age)
        {
            
            takeAwayCustomer *firstCustomer = myPizzaShop->nextTakeAwayCustomer;
            myPizzaShop->nextTakeAwayCustomer = currentTakeAwayCustomer;
            currentTakeAwayCustomer->next = firstCustomer;
        }
        else
        {
            
            temp->next = currentTakeAwayCustomer;
            currentTakeAwayCustomer->next = NULL;
        }
    }
    cout << "Your Order has been Placed MR/MRS " << name << " and your order is " << pizzaName << " with " << quantity << " quantity and total bill is " << bill << endl;
}
void serveOrderTakeAwayCustomer()
{
    if (myPizzaShop->nextTakeAwayCustomer == NULL)
    {
        cout << "No Take Away Customer to Serve" << endl;
    }
    else
    {
       
        takeAwayCustomer *temp = myPizzaShop->nextTakeAwayCustomer;
       
        if(temp->next != NULL){
            myPizzaShop->nextTakeAwayCustomer = temp->next;
        }
        else{
            myPizzaShop->nextTakeAwayCustomer = NULL;
        }
        
        cout << "Take Away Customer Served : " << temp->cusotomer.name << endl;

        string customerType = "Take-Away";
       
        root = insertion(temp->cusotomer.age, temp->cusotomer.name, temp->cusotomer.quantity, temp->cusotomer.pizzaName, temp->cusotomer.bill, customerType, root);

        delete temp; 
    }
}



void placeOrderDineInCustomer(int age, string name, string pizzaName, int quantity, double bill)
{
    
    currentDineInCustomer = new dineInCustomer(age, name, quantity, pizzaName, bill);

    if (myPizzaShop->nextDineInCustomer == NULL)
    {
       
        myPizzaShop->nextDineInCustomer = currentDineInCustomer;
    }
    else
    {
       
        dineInCustomer *temp = myPizzaShop->nextDineInCustomer;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = currentDineInCustomer;
        currentDineInCustomer->next = NULL;
    }
    cout << "Your Order has been Placed MR/MRS " << name << " and your order is " << pizzaName << " with " << quantity << " quantity and total bill is " << bill << endl;
}
void serveOrderDineInCustomer()
{
    if (myPizzaShop->nextDineInCustomer == NULL)
    {
        cout << "No Dine-In Customer to Serve" << endl;
    }
    else
    {
        
        dineInCustomer *temp = myPizzaShop->nextDineInCustomer;
        if(temp->next != NULL){
            myPizzaShop->nextDineInCustomer = temp->next;
        }
        else{
            myPizzaShop->nextDineInCustomer = NULL;
        }

        cout << "Dine-In Customer Served : " << temp->cusotomer.name << endl;

        string customerType = "Dine-In";
        // Now before deleting the node we need to update the servedCustomer Tree
        root = insertion(temp->cusotomer.age, temp->cusotomer.name, temp->cusotomer.quantity, temp->cusotomer.pizzaName, temp->cusotomer.bill, customerType, root);

        delete temp; 
    }
}


void placeOrderHomeDeliveryCustomer(int age, string name, string pizzaName, int quantity, double bill, string address, int deliveryCharges, int distanceDelivery)
{
   
    currentHomeDeliveryCustomer = new homeDeliveryCustomer(age, name, quantity, pizzaName, bill, address, deliveryCharges, distanceDelivery);

    if (myPizzaShop->nextHomeDeliveryCustomer == NULL)
    {
        myPizzaShop->nextHomeDeliveryCustomer = currentHomeDeliveryCustomer;
    }
    else
    {
        
        homeDeliveryCustomer *temp = myPizzaShop->nextHomeDeliveryCustomer;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = currentHomeDeliveryCustomer;
        currentHomeDeliveryCustomer->next = NULL;
    }
    cout << "Your Order has been Placed MR/MRS " << name << " and your order is " << pizzaName << " with " << quantity << " quantity and total bill is " << bill << endl;
}

void serveOrderHomeDeliveryCustomer()
{
    if (myPizzaShop->nextHomeDeliveryCustomer == NULL)
    {
        cout << "No Home Delivery Customer to Serve" << endl;
    }
    else
    {

       
        homeDeliveryCustomer *first = myPizzaShop->nextHomeDeliveryCustomer;

        if (first->next == NULL)
        {
            

            myPizzaShop->nextHomeDeliveryCustomer = NULL;

            cout << "Home Delivery Customer Served : " << first->cusotomer.name << endl;
            string customerType = "Home-Delivery Customer";
            root = insertion(first->cusotomer.age, first->cusotomer.name, first->cusotomer.quantity, first->cusotomer.pizzaName, first->cusotomer.bill, customerType, root);

            
            delete (first);
        }
        else {
            homeDeliveryCustomer *s = first->next;
            while(s->next !=NULL){
                first = first->next;
                s = s->next;
            }

            first->next = NULL;

            cout << "Home Delivery Customer Served : " << s->cusotomer.name << endl;
            string customerType = "Home-Delivery Customer";
            root = insertion(s->cusotomer.age, s->cusotomer.name, s->cusotomer.quantity, s->cusotomer.pizzaName, s->cusotomer.bill, customerType, root);

            

            delete (s);
        }

        
        
    }
}



void serveAllOrders()
{

    while (myPizzaShop->nextTakeAwayCustomer != NULL)
    {
        serveOrderTakeAwayCustomer();
    }
    while (myPizzaShop->nextDineInCustomer != NULL)
    {
        serveOrderDineInCustomer();
    }
    while (myPizzaShop->nextHomeDeliveryCustomer != NULL)
    {
        serveOrderHomeDeliveryCustomer();
    }
}

void displayAllOrdersTakeAwayCustomers()
{
    if (myPizzaShop->nextTakeAwayCustomer == NULL)
    {
        cout << "There is no Order for Walking Customer till yet" << endl;
    }
    else
    {
        takeAwayCustomer *traversal = myPizzaShop->nextTakeAwayCustomer;
        while (traversal != NULL)
        {

            cout << "-----------------------------------------------------" << endl;
            cout << "Take-Away Customer : " << traversal->cusotomer.name << endl;
            cout << "Age : " << traversal->cusotomer.age << endl;
            cout << "Pizza Name : " << traversal->cusotomer.pizzaName << endl;
            cout << "Quantity : " << traversal->cusotomer.quantity << endl;
            cout << "Bill : " << traversal->cusotomer.bill << " RS/_" << endl;
            cout << "-----------------------------------------------------" << endl;

            traversal = traversal->next;
        }
    }
}

void displayAllOrdersHomeDeliveryCustomers()
{
    if (myPizzaShop->nextHomeDeliveryCustomer == NULL)
    {
        cout << "There is no Order for Home Delivery Customer till yet" << endl;
    }
    else
    {
        homeDeliveryCustomer *traversal = myPizzaShop->nextHomeDeliveryCustomer;
        while (traversal != NULL)
        {
            cout << "-----------------------------------------------------" << endl;
            cout << "Home Delivery Customer : " << traversal->cusotomer.name << endl;
            cout << "Age : " << traversal->cusotomer.age << endl;
            cout << "Pizza Name : " << traversal->cusotomer.pizzaName << endl;
            cout << "Quantity : " << traversal->cusotomer.quantity << endl;
            cout << "Delivery Distance : " << traversal->deliveryCharges << "KM"<<endl;
            cout << "Delivery Charges : " << traversal->distanceDelivery << endl;
            cout << "Bill : " << traversal->cusotomer.bill << " RS/_" << endl;
            cout << "Delivery Address : " << traversal->address << endl;
            cout << "-----------------------------------------------------" << endl;

            traversal = traversal->next;
        }
    }
}

void displayAllOrdersDineInCustomers()
{
    if (myPizzaShop->nextDineInCustomer == NULL)
    {
        cout << "There is no Order for Dine-In Customer till yet" << endl;
    }
    else
    {
        dineInCustomer *traversal = myPizzaShop->nextDineInCustomer;
        while (traversal != NULL)
        {
            cout << "-----------------------------------------------------" << endl;
            cout << "Walking Customer : " << traversal->cusotomer.name << endl;
            cout << "Age : " << traversal->cusotomer.age << endl;
            cout << "Pizza Name : " << traversal->cusotomer.pizzaName << endl;
            cout << "Quantity : " << traversal->cusotomer.quantity << endl;
            cout << "Bill : " << traversal->cusotomer.bill << " RS/_" << endl;
            cout << "-----------------------------------------------------" << endl;

            traversal = traversal->next;
        }
    }
}

void displayAllOrders()
{

    cout << "The Take-Away Customers Are :" << endl;
    displayAllOrdersTakeAwayCustomers();

    cout << "The Dine-IN Customers Are :" << endl;
    displayAllOrdersDineInCustomers();

    cout << "The Home Delivery Customers Are :" << endl;
    displayAllOrdersHomeDeliveryCustomers();
}

void totalbillofPendingOrders()
{
    takeAwayCustomer *p = myPizzaShop->nextTakeAwayCustomer;
    while (p != NULL)
    {
        takeAway += p->cusotomer.bill;
        p = p->next;
    }
    dineInCustomer *q = myPizzaShop->nextDineInCustomer;
    while (q != NULL)
    {
        dineIn += q->cusotomer.bill;
        q = q->next;
    }
    homeDeliveryCustomer *r = myPizzaShop->nextHomeDeliveryCustomer;
    while (r != NULL)
    {
        homeDelivery += r->cusotomer.bill;
        r = r->next;
    }
    total = takeAway + dineIn + homeDelivery;

    cout << "The total bill of pending orders for Take-Away customers are : " << takeAway << " RS/_" << endl;
    cout << "The total bill of pending orders for Dine-In customers are : " << dineIn << " RS/_" << endl;
    cout << "The total bill of pending orders for Delivery customers are : " << homeDelivery << " RS/_" << endl;
    cout << "The Total orders pending are : " << total << " RS/_" << endl;
}

double totalEarnings(servedCustomer *root){

    if(root){
        totalEarnings(root->left);
        servedTotal += root->bill;
        totalEarnings(root->right);
    }

    return servedTotal;
}




string deliveryPoints[] = {"Pizza Shop", "Civil Lines", "Chawri Bazar", "Hauz Khas", "Green Park", "IFFCO Chowk"};


vector<vector<pair<int, int>>> deliveryMap = {

    // first value in the pair is vertex and second is the distance (weight) in KM
    {{1, 2}, {2, 3}, {3, 5}, {5, 4}}, //  0  (Pizza Shop)
    {{0, 2}, {5, 1}},                 //  1  (Civil Lines)
    {{0, 3}, {3, 1}},                 //  2  (Chawri Bazar))
    {{0, 5}, {4, 2}, {5, 2}, {2, 1}}, //  3  (Hauz Khas)
    {{3, 2}, {5, 2}},                 //  4  (Green Park)
    {{0, 4}, {1, 1},{3,2} ,{4, 2}}          //  5  (IFFCO Chowk)

};

vector<int> dijkstra(int sourceNode)
{
    vector<int> distance(6, infinity);
    set<pair<int, int>> s;
    distance[sourceNode] = 0; // Pizza Shop
    s.insert(make_pair(0, sourceNode));

    while (!s.empty())
    {
        auto top = *(s.begin());
        int u = top.first;  //   current weight
        int v = top.second; //  current vertex

        s.erase(s.begin());

        
        for (auto child : deliveryMap[v])
        {
            int childVertex = child.first;
            int childWeight = child.second;

            if (u + childWeight < distance[childVertex])
            {
                distance[childVertex] = u + childWeight;
                s.insert(make_pair(distance[childVertex], childVertex));
            }
        }
    }

    return distance;
}

int main()
{
   
    myPizzaShop = new PizzaShop;

    
    myPizzaShop->shopName = "Supermax Original";

    
    myPizzaShop->address = "Rajiv Chowk, Delhi";

   
    myPizzaShop->menu = new string[11]{"",
                                       "Paneer Butter Masala", "Malai Kofta",
                                       "Paneer Tikka Masala", "Kadai Paneer ",
                                       "Dosa (Butter)", "Chilli Cheese Gralic Toast",
                                       "Tandoori Paneer Tikka", "Dal Makhani",
                                       "Plain Cheese Pizza", "Butter Naan"};

   
    myPizzaShop->price = new int[11]{0, 2000, 2500, 2400, 2200, 2700, 2000, 2100, 3000, 3000, 2800};

    int option = -99;

    
    do
    {

        cout << "-------------------------------------------------------------------------" << endl;
        cout << "--------------" << myPizzaShop->shopName << "----------------" << endl;
        cout << "-------------------Project Partner-------------------------" << endl;
        cout << "SHUBHAM KANNOJIYA,DINESH CHAUDHARY and PRASU GUPTA" << endl;

        cout << "Located at " << myPizzaShop->address << endl;
        cout << "Our Menu is as follows: " << endl;
        for (int i = 1; i <= 10; i++)
        {
            cout << i << ". " << myPizzaShop->menu[i] << " - " << myPizzaShop->price[i] << endl;
        }

        cout << "-------------------------------------------------------------------------" << endl;
        cout << "---------------------------------Operations------------------------------" << endl;
        cout << "-------------------------------------------------------------------------" << endl;
        cout << "-------------------------------------------------------------------------" << endl;

       
        cout << "1. Place order for Take-Away Customer" << endl;
        cout << "2. Place order for Home Delivery Customer" << endl;
        cout << "3. Place order for Dine-In Customer" << endl;

        
        cout << "4. Serve order for Take-Away Customer" << endl;
        cout << "5. Serve order for Home Delivery Customer" << endl;
        cout << "6. Serve order for Dine-In Customer" << endl;
        cout << "7. Serve All Orders " << endl;

        
        cout << "8. Display all orders of Take-Away Customer" << endl;
        cout << "9. Display all orders of Home Delivery Customers" << endl;
        cout << "10. Display all orders of Dine-In Customers" << endl;
        cout << "11. Display all orders of all Customers" << endl;

        
        cout << "12. Display all served Orders" << endl;
        cout << "13. Search Served Orders " << endl;
        cout << "14. Clear the Served Orders List " << endl;
        cout << "15. Display total bill of Pending Orders " << endl;
        cout << "16. Display the total Earnings of Served Orders " << endl;
        cout << "0.  EXIT " << endl;

        cout << "Enter your choice: ";

        cin >> option;

        
        int age, quantity, pizzaIndex;
        double bill;
        string address;
        string name;

        switch (option)
        {
        case 1:
        { 
            cout << "Enter the name of the customer: ";
            cin >> name;
            cout << "Enter the age of the customer: ";
            cin >> age;
            cout << "Enter the quantity of Your Selected Food: ";
            cin >> quantity;
            cout << "Enter the option for the Food: ";
            cin >> pizzaIndex;

            bill = quantity * myPizzaShop->price[pizzaIndex];
            placeOrderTakeAwayCustomer(age, name, myPizzaShop->menu[pizzaIndex], quantity, bill);
        }
        break;

        case 2:

        {                                               // placing order for Home Delivery customer
            vector<int> distanceFromShop = dijkstra(0); // As Zero is our Source Node

            int optionDelivery = -999;

            do
            {
                cout << "The delivery is available for following Areas : " << endl;
                for (int i = 1; i <= 5; i++)
                {
                    cout << i << ". " << deliveryPoints[i] << endl;
                }

                cout << "Enter your option :" << endl;
                cin >> optionDelivery;

            } while (!(optionDelivery >= 0 && optionDelivery <= 5));

           
            address = deliveryPoints[optionDelivery];

            cout << "Enter the name of the customer: ";
            cin >> name;
            cout << "Enter the age of the customer: ";
            cin >> age;
            cout << "Enter the quantity of the your Selected Food: ";
            cin >> quantity;
            cout << "Enter the option for the food: ";
            cin >> pizzaIndex;

            int deliveryChargesPerKM = 50;
            int deliveryCharges = deliveryChargesPerKM * distanceFromShop[optionDelivery];
            bill = quantity * myPizzaShop->price[pizzaIndex] + deliveryCharges;

            
            int distanceFromTheShop = distanceFromShop[optionDelivery];
            placeOrderHomeDeliveryCustomer(age, name, myPizzaShop->menu[pizzaIndex], quantity, bill, address, distanceFromTheShop, deliveryCharges);
        }
        break;

        case 3:
        { 

            cout << "Enter the name of the customer: ";
            cin >> name;
            cout << "Enter the age of the customer: ";
            cin >> age;
            cout << "Enter the quantity of your Selected Food: ";
            cin >> quantity;
            cout << "Enter the option for the food: ";
            cin >> pizzaIndex;

            bill = quantity * myPizzaShop->price[pizzaIndex];
            placeOrderDineInCustomer(age, name, myPizzaShop->menu[pizzaIndex], quantity, bill);
        }
        break;

        case 4:
            
            serveOrderTakeAwayCustomer();
            break;

        case 5:
            
            serveOrderHomeDeliveryCustomer();
            break;

        case 6:
            
            serveOrderDineInCustomer();
            break;

        case 7:
            
            serveAllOrders();
            break;

        case 8:
           
            displayAllOrdersTakeAwayCustomers();
            break;

        case 9:
           
            displayAllOrdersHomeDeliveryCustomers();
            break;

        case 10:
          
            displayAllOrdersDineInCustomers();
            break;

        case 11:
            
            displayAllOrders();
            break;

        case 12:
        { 
            servedCustomer *r = displayAllServedOrders(root);
            if (!r)
                cout << "No Served Customer yet " << endl;
        }
        break;

        case 13:
        { 
            cout << "Enter the name of the customer you want to search: " << endl;
            cin >> name;
            servedCustomer *searchedCustomer = search(root, name);
            if (searchedCustomer == NULL)
                cout << "No such Customer was Served " << endl;
            else
                display(searchedCustomer);
        }
        break;

        case 14:
        { 
            deleteAllServedCustomers(root);
            root = NULL;
        }
        break;

        case 15:
        { 

            
            takeAway = 0, dineIn = 0, homeDelivery = 0, total = 0; 
            totalbillofPendingOrders();
        }
        break;

        case 16:
        { 

        
        servedTotal = 0;
        double totalx = totalEarnings(root);
        cout << "The Total Earnings are : " << totalx << endl;
        }
        break;
        }

    } while (option != 0);

    cout << "Pizza Order Management System -- Terminated" << endl;
    cout << "Thank you for Using our Services " << endl;

    return 0;
}
