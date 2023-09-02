/*
*  Title: Automat
*  Abstract: This program simulates a vending mashine, where the User can order food, drinks and such and cancel or pay for the order
*  Author: Luke Winter
*  Email: lwinter@csumb.edu
*  Date: 09/24/2022
*/

#include <iostream>
using namespace std;

const int AUTOMAT_MAX = 10;
const int ORDER_MAX = 5;

//---Food---
class Food{
public:
  Food();
  Food(string name, int calories, double price);
  string getName();
  int getCalories();
  double getPrice();
  void setName(string name);
  void setCalories(int calories);
  void setPrice(double price);
  void display();
private:
  string myName;
  int myCalories;
  double myPrice;
};

//---Drink---
class Drink{
public:
  Drink();
  Drink(string name, int ounces, double price);
  string getName();
  int getOunces();
  double getPrice();
  void setName(string name);
  void setOunces(int ounces);
  void setPrice(double price);
  void display();
private:
  string myName;
  int myOunces;
  double myPrice;
};

class Automat{
public:
  Automat();
  bool emptyFood();
  bool emptyDrink();
  void enqueue(Food f);
  void enqueue(Drink d);
  void dequeueFood();
  void dequeueDrink();
  Food frontFood();
  Drink frontDrink();
  int foodCount();
  int drinkCount();
  int getTotalCalories();
  int getTotalOunces();
  double getTotalPrice();
  void display();
private:
  //Food Queue
  int myFoodFront;
  int myFoodBack;
  Food myFood[AUTOMAT_MAX];
  //Drink Queue
  int myDrinkFront;
  int myDrinkBack;
  Drink myDrink[AUTOMAT_MAX];
};

class Order{
public:
  Order();
  bool emptyFood();
  bool emptyDrink();
  void push(Food f);
  void push(Drink d);
  void popFood();
  void popDrink();
  Food topFood();
  Drink topDrink();
  int foodCount();
  int drinkCount();
  double getTotalPrice();
  void display();
  void cancel(Automat & a);
  void purchase();
  static int getTotalOrder();
  
private:
  int myFoodTop;
  int myDrinkTop;
  Food myFood[ORDER_MAX];
  Drink myDrink[ORDER_MAX];
  static int myTotalOrders;
};
int Order::myTotalOrders = 0;


//---FOOD METHODS---//

Food::Food(){}

Food::Food(string name, int calories, double price)
:myName(name), myCalories(calories), myPrice(price)
{}

string Food::getName(){
  return myName;
}
int Food::getCalories(){
  return myCalories;
}
double Food::getPrice(){
  return myPrice;
}
void Food::setName(string name){
  myName = name;
}
void Food::setCalories(int calories){
  myCalories = calories;
}
void Food::setPrice(double price){
  myPrice = price;
}
void Food::display(){
  cout << myName << ": " << myCalories << " calories, $" << myPrice << "\n";
}


//---DRINK METHODS---
Drink::Drink(){}

Drink::Drink(string name, int ounces, double price)
:myName(name), myOunces(ounces), myPrice(price){}

string Drink::getName(){
  return myName;
}

int Drink::getOunces(){
  return myOunces;
}

double Drink::getPrice(){
  return myPrice;
}

void Drink::setName(string name){
  myName = name;
}

void Drink::setOunces(int ounces){
  myOunces = ounces;
}

void Drink::setPrice(double price){
  myPrice = price;
}

void Drink::display(){
  cout << myName << ": " << myOunces << " ounces, $" << myPrice << "\n";
}

//---AUTOMAT METHODS---
Automat::Automat():myFoodFront(0), myFoodBack(0), myDrinkFront(0), myDrinkBack(0){}

bool Automat::emptyFood(){
  return myFoodFront == myFoodBack;
}

bool Automat::emptyDrink(){
  return myDrinkFront == myDrinkBack;
}

void Automat::enqueue(Food f){
  //Check if full
  if((myFoodBack + 1) % AUTOMAT_MAX == myFoodBack){
    cout << "Automat food full; new food not added\n";
    return;
  }
  //Adding Food item
  myFood[myFoodBack] = f;
  myFoodBack = (myFoodBack + 1) % AUTOMAT_MAX;
}

void Automat::enqueue(Drink d){
  //Check if full
  if((myDrinkBack + 1) % AUTOMAT_MAX == myDrinkBack){
    cout << "Automat drink full; new drink not added\n";
    return;
  }
  //Adding dring item
  myDrink[myDrinkBack] = d;
  myDrinkBack = (myDrinkBack + 1) % AUTOMAT_MAX;  
}

void Automat::dequeueFood(){
  if(emptyFood()){
    cout << "Automat food empty; food not deleted\n";
    return;
  }
  myFoodFront = (myFoodFront + 1) % AUTOMAT_MAX;
}

void Automat::dequeueDrink(){
  if(emptyDrink()){
    cout << "Automat drink empty; drink not deleted\n";
    return;
  }
  myDrinkFront = (myDrinkFront + 1) % AUTOMAT_MAX;
}

Food Automat::frontFood(){
  return myFood[myFoodFront];
}

Drink Automat::frontDrink(){
  return myDrink[myDrinkFront];
}

int Automat::foodCount(){
  int count = 0;
  for(int i = myFoodFront; i != myFoodBack; i = (i+1) % AUTOMAT_MAX){
    count++;
  }
  return count;
}

int Automat::drinkCount(){
  int count = 0;
  for(int i = myDrinkFront; i != myDrinkBack; i = (i+1) % AUTOMAT_MAX){
    count++;
  }
  return count;  
}

int Automat::getTotalCalories(){
  int calorieCount = 0;
  for(int i = myFoodFront; i != myFoodBack; i = (i+1) % AUTOMAT_MAX){
    calorieCount += myFood[i].getCalories();
  }
  return calorieCount;  
}

int Automat::getTotalOunces(){
  int ounceCount = 0;
  for(int i = myDrinkFront; i != myDrinkBack; i = (i+1) % AUTOMAT_MAX){
    ounceCount += myDrink[i].getOunces();
  }
  return ounceCount;    
}

double Automat::getTotalPrice(){
  double totalPrice = 0;
  for(int i = myDrinkFront; i != myDrinkBack; i = (i+1) % AUTOMAT_MAX){
    totalPrice += myDrink[i].getPrice();
  }
  for(int i = myFoodFront; i != myFoodBack; i = (i+1) % AUTOMAT_MAX){
    totalPrice += myFood[i].getPrice();
  }
  return totalPrice;
}

void Automat::display(){
  cout << "Automat:\n";
  cout << "\tFood:\n";
  for(int i = myFoodFront; i != myFoodBack; i = (i+1)%AUTOMAT_MAX){
    cout << "\t\t";
    myFood[i].display();
  }
  cout << "\t\t" << foodCount() << " food items - Total Calories: " << getTotalCalories() << "\n";
  cout << "\tDrinks:\n";
  for(int i = myDrinkFront; i != myDrinkBack; i = (i+1)%AUTOMAT_MAX){
    cout << "\t\t";
    myDrink[i].display();
  }
  cout << "\t\t" << drinkCount() << " drinks - Total Ounces: " << getTotalOunces() << "\n\n";
}

//---ORDER METHODS---
Order::Order(): myFoodTop(-1), myDrinkTop(-1)
{
  myTotalOrders++;
}
bool Order::emptyFood(){
  return myFoodTop == -1;
}
bool Order::emptyDrink(){
  return myDrinkTop == -1;
}
void Order::push(Food f){
  if(myFoodTop == ORDER_MAX -1){
    cout << "Order food full; food not added\n";
    return;
  }
  myFoodTop++;
  myFood[myFoodTop] = f;
}
void Order::push(Drink d){
  if(myDrinkTop == ORDER_MAX -1){
    cout << "Order drink full; drink not added\n";
    return;
  }
  myDrinkTop++;
  myDrink[myDrinkTop] = d;  
}
void Order::popFood(){
  if(emptyFood()){
    cout << "Order food empty; did not delete food\n";
    return;
  }
  myFoodTop--;
}
void Order::popDrink(){
  if(emptyDrink()){
    cout << "Order drink empty; did not delete drink\n";
    return;
  }
  myDrinkTop--;  
}
Food Order::topFood(){
  return myFood[myFoodTop];
}
Drink Order::topDrink(){
  return myDrink[myDrinkTop];  
}
int Order::foodCount(){
  return myFoodTop + 1;
}
int Order::drinkCount(){
  return myDrinkTop + 1;
}
double Order::getTotalPrice(){
  double totalPrice = 0;
  for(int i = 0; i < myFoodTop + 1; i++){
    totalPrice += myFood[i].getPrice();
  }
  for(int i = 0; i < myDrinkTop + 1; i++){
    totalPrice += myDrink[i].getPrice();
  }
  return totalPrice;
}
void Order::display(){
  cout << "Order:\n";
  cout << "\tFood (" << foodCount() << " items):\n";
  for(int i = 0; i < myFoodTop + 1; i++){
    cout << "\t\t";
    myFood[i].display();
  }
  cout << "\tDrink (" << drinkCount() << " items):\n";
  for(int i = 0; i < myDrinkTop + 1; i++){
    cout << "\t\t";
    myDrink[i].display();
  }
  cout << "\tOrder total: $" << getTotalPrice() << "\n\n";
}
/*
Order:
  Food (1 items):
      Let's Potato Chips: 300 calories, $1.5
  Drink (1 items):
      Coffee: 6 ounces, $5.5
  Order total: $7
*/
void Order::cancel(Automat & a){
  while(!emptyFood()){
    a.enqueue(topFood());
    popFood();
  }
  while(!emptyDrink()){
    a.enqueue(topDrink());
    popDrink();
  }
}
void Order::purchase(){
  myFoodTop = -1;
  myDrinkTop = -1;
}
int Order::getTotalOrder(){
  return myTotalOrders;
}
