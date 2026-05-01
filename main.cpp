#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
class product {
public:
    int id;
    char name[30];
    char category[20]; 
    float price;
    int stock;
    void addproduct() {
        product temp;
        cout << "\nEnter product id: ";
        cin >> temp.id;
        cin.ignore();
        cout << "Enter Product Name: ";
        cin.getline(temp.name, 30); 
        cout << "Enter Category (Clothes, Laptop, etc.): ";
        cin.getline(temp.category, 20);
        
        cout << "Enter Price: ";
        cin >> temp.price;
        cout << "Enter Stock Quantity: ";
        cin >> temp.stock;

        ofstream file("products.dat", ios::app | ios::binary);
        if (!file) {
            cout << "Error opening file!\n";
            return;
        }
        file.write((char*)&temp, sizeof(product));
        file.close();
        cout << "Product Added Successfully!\n";
    }
    void showproducts() {
        ifstream file("products.dat", ios::binary);
        if (!file) {
            cout << "\nNo products available.\n";
            return;
        }
        product p;
        cout << "\n--- All Shop Items ---\n";
        while (file.read((char*)&p, sizeof(product))) {
            cout << "ID: " << p.id 
                 << " | Name: " << p.name 
                 << " | Cat: " << p.category
                 << " | Price: Rs." << p.price 
                 << " | Items Left: " << p.stock << endl;
        }
        file.close();
    }
    void showByCategory(const char* catagory) {
        ifstream file("products.dat", ios::binary);
        if (!file) {
            cout << "\nNo products available.\n";
            return;
        }
        product p;
        int flag = 0; 
        cout << "\n--- Showing: " << catagory << " ---\n";
        while (file.read((char*)&p, sizeof(product))) {
            if (strcmp(p.category, catagory) == 0 || strstr(p.name, catagory) != nullptr) {
                cout << "ID: " << p.id 
                     << " | Name: " << p.name 
                     << " | Price: Rs." << p.price 
                     << " | Items Left: " << p.stock << endl;
                flag = 1;
            }
        }
        if (flag == 0) {
            cout << " No items found in this category.\n";
        }
        file.close();
    }
};
class cart {
public:
    float total = 0;
    void buyproduct() {
        product p;
        int pid, qty;
        int flag = 0; 
        cout << "\nenter the product ID you want to buy: ";
        cin >> pid;
        cout << "How many do you need? ";
        cin >> qty;
        ifstream file("products.dat", ios::binary);
        if (!file) {
            cout << "no products available\n";
            return;
        }
        while (file.read((char*)&p, sizeof(product))) {
            if (p.id == pid) {
                total += (p.price * qty);
                cout << "Success! [" << p.name << "] added to your cart\n";
                flag = 1;
                break;
            }
        }

        if (flag == 0) {
            cout << "Product not found.\n";
        }

        file.close();
        cout << "Your total bill is: Rs." << total << endl;
    }
};
void categoryMenu(product &p) {
    int catChoice;
    cout << "\n--- PICK A CATEGORY ---";
    cout << "\n1. Clothes";
    cout << "\n2. Electronics";
    cout << "\n3. Cosmetics";
    cout << "\n4. Jewelry";
    cout << "\n5. Groceries";
    cout << "\n6. Home Appliances";
    cout << "\n7. Footwear";
    cout << "\n8. Laptops";
    cout << "\n9. Go Back";
    cout << "\nChoose (1-9): ";
    cin >> catChoice;

    switch(catChoice) {
        case 1: p.showByCategory("Clothes"); break;
        case 2: p.showByCategory("Electronics"); break;
        case 3: p.showByCategory("Cosmetics"); break;
        case 4: p.showByCategory("Jewelry"); break;
        case 5: p.showByCategory("Groceries"); break;
        case 6: p.showByCategory("Appliances"); break;
        case 7: p.showByCategory("Footwear"); break;
        case 8: p.showByCategory("Laptop"); break;
        case 9: return;
        default: cout << "Invalid category!\n";
    }
}
int main() {
    product p;
    cart c;
    int choice;
    do {
        cout << "\n===== STUDENT SHOP MENU =====";
        cout << "\n1. show all products";
        cout << "\n2. search by category";
        cout << "\n3. Buy Something";
        cout << "\n4. Exit Shop";
        cout << "\nchose a option from above (1-4): ";
        if (!(cin >> choice)) { 
            cout << "enter a number.\n";
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }
        cin.ignore();
        switch (choice) {
            case 0: p.addproduct(); break; 
            case 1: p.showproducts(); break;
            case 2: categoryMenu(p); break;
            case 3: c.buyproduct(); break;
            case 4: cout << "\nThank you for visiting!\n"; break;
            default: cout << "\nInvalid choice. Please try again.\n";
        }
    } while (choice != 4);
    return 0;
}
