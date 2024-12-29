#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>
using namespace std;

// Product class to store product details
class Product {
public:
    int id;
    string name;
    double price;
    int stock;

    // Default constructor
    Product() : id(0), name(""), price(0.0), stock(0) {}

    // Parameterized constructor
    Product(int id, string name, double price, int stock) 
        : id(id), name(name), price(price), stock(stock) {}
};

// Supermarket Management System class
class Supermarket {
private:
    map<int, Product> products; // Store products with ID as the key
    vector<string> feedbacks;   // Store user feedback

public:
    // Add a new product
    void addProduct(int id, string name, double price, int stock) {
        if (products.find(id) != products.end()) {
            cout << "Product with ID " << id << " already exists.\n";
            return;
        }
        products[id] = Product(id, name, price, stock);
        cout << "Product added successfully.\n";
    }

    // Display all products with improved formatting
    void displayProducts() {
        cout << "\nAvailable Products:\n";
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Stock" << endl;
        cout << "----------------------------------------------------------\n";
        for (const auto& entry : products) {
            const auto& id = entry.first;
            const Product& product = entry.second;
            cout << setw(10) << id << setw(20) << product.name << setw(10) << product.price << setw(10) << product.stock << endl;
        }
    }

    // Search for a product by name (subsequence search)
    void searchProduct(string query) {
        cout << "\nSearch Results for \"" << query << "\":\n";
        bool found = false;
        for (const auto& entry : products) {
            const auto& id = entry.first;
            const Product& product = entry.second;
            if (product.name.find(query) != string::npos) {
                cout << "ID: " << id << "\tName: " << product.name << "\tPrice: " << product.price << "\tStock: " << product.stock << "\n";
                found = true;
            }
        }
        if (!found) {
            cout << "No matching products found.\n";
        }
    }

    // Process an order and add products to the cart
    double processOrder(vector<pair<int, int>>& cart) {
        double totalCost = 0.0;

        cout << "\n\n----- BILL -----\n";
        cout << left << setw(20) << "Item Name" << setw(10) << "Price" << setw(10) << "Quantity" << setw(15) << "Total Price" << endl;
        cout << "---------------------------------------------------------------\n";

        for (const auto& item : cart) {
            int productId = item.first;
            int quantity = item.second;

            if (products.find(productId) == products.end()) {
                cout << "Product with ID " << productId << " not found.\n";
                continue;
            }

            Product& productRef = products[productId];
            if (productRef.stock < quantity) {
                cout << "Insufficient stock for product " << productRef.name << ".\n";
                continue;
            }

            productRef.stock -= quantity;
            double itemTotal = quantity * productRef.price;
            totalCost += itemTotal;

            cout << setw(20) << productRef.name << setw(10) << productRef.price << setw(10) << quantity << setw(15) << itemTotal << endl;
        }

        cout << "---------------------------------------------------------------\n";
        cout << "Total Cost: $" << totalCost << endl;

        return totalCost;
    }

    // Add user feedback with rating and product details
    void addFeedback(string feedback, int productId, int rating) {
        if (products.find(productId) == products.end()) {
            cout << "Product with ID " << productId << " not found.\n";
            return;
        }
        
        // Validate rating
        if (rating < 1 || rating > 5) {
            cout << "Invalid rating. Please enter a rating between 1 and 5.\n";
            return;
        }

        // Store the feedback along with the product ID and rating
        feedbacks.push_back("Product ID: " + to_string(productId) + ", Rating: " + to_string(rating) + " stars, Feedback: " + feedback);
        cout << "Feedback submitted successfully.\n";
    }

    // Display all feedback with product details and ratings
    void displayFeedback() {
        cout << "\nUser Feedback:\n";
        if (feedbacks.empty()) {
            cout << "No feedback available yet.\n";
        } else {
            for (const string& feedback : feedbacks) {
                cout << "- " << feedback << "\n";
            }
        }
    }
};

int main() {
    Supermarket supermarket;
    int choice;

    do {
        cout << "\nSupermarket Management System\n";
        cout << "1. Add Product\n";
        cout << "2. Display Products\n";
        cout << "3. Search Product\n";
        cout << "4. Process Order\n";
        cout << "5. Add Feedback\n";
        cout << "6. Display Feedback\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // Allow user to add multiple products at once
                char addMore = 'y';
                while (addMore == 'y' || addMore == 'Y') {
                    int id, stock;
                    string name;
                    double price;
                    cout << "Enter Product ID: ";
                    cin >> id;
                    cout << "Enter Product Name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter Product Price: ";
                    cin >> price;
                    cout << "Enter Product Stock: ";
                    cin >> stock;
                    supermarket.addProduct(id, name, price, stock);

                    cout << "Do you want to add more products? (y/n): ";
                    cin >> addMore;
                }
                break;
            }
            case 2:
                supermarket.displayProducts();
                break;
            case 3: {
                // Allow user to search multiple products at once
                char searchMore = 'y';
                while (searchMore == 'y' || searchMore == 'Y') {
                    string query;
                    cout << "Enter product name to search: ";
                    cin.ignore();
                    getline(cin, query);
                    supermarket.searchProduct(query);

                    cout << "Do you want to search for another product? (y/n): ";
                    cin >> searchMore;
                }
                break;
            }
            case 4: {
                vector<pair<int, int>> cart;
                int productId, quantity;
                char moreItems = 'y';

                // Allow the user to add multiple items to the cart
                while (moreItems == 'y' || moreItems == 'Y') {
                    cout << "Enter Product ID: ";
                    cin >> productId;
                    cout << "Enter Quantity: ";
                    cin >> quantity;

                    cart.push_back(make_pair(productId, quantity));

                    cout << "Do you want to add more items? (y/n): ";
                    cin >> moreItems;
                }

                // Process the order and display the total bill
                double total = supermarket.processOrder(cart);
                break;
            }
            case 5: {
                // Allow user to add multiple feedback at once
                char feedbackMore = 'y';
                while (feedbackMore == 'y' || feedbackMore == 'Y') {
                    string feedback;
                    int productId, rating;
                    
                    // Ask for product ID
                    cout << "Enter the Product ID for the feedback: ";
                    cin >> productId;
                    
                    // Ask for rating
                    cout << "Enter your rating (1 to 5 stars): ";
                    cin >> rating;

                    // Ask for feedback
                    cout << "Enter your feedback: ";
                    cin.ignore();
                    getline(cin, feedback);

                    supermarket.addFeedback(feedback, productId, rating);

                    cout << "Do you want to add feedback for another product? (y/n): ";
                    cin >> feedbackMore;
                }
                break;
            }
            case 6:
                supermarket.displayFeedback();
                break;
            case 7:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
