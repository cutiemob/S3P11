#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

struct Product {
    int id;
    std::string name;
    std::string category;
    std::string manufacturer;
    int quantity;
    double price;
    double totalCost;
};

void loadFromFile(std::vector<Product>& products, const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    Product product;
    while (file >> product.id >> product.name >> product.category >> product.manufacturer >> product.quantity >> product.price) {
        product.totalCost = product.quantity * product.price;
        products.push_back(product);
    }
    file.close();
}

void saveToFile(const std::vector<Product>& products, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    for (const auto& product : products) {
        file << product.id << " " << product.name << " " << product.category << " "
             << product.manufacturer << " " << product.quantity << " " << product.price << std::endl;
    }
    file.close();
}

void displayProducts(const std::vector<Product>& products) {
    std::cout << std::setw(5) << "ID" << std::setw(15) << "Name" << std::setw(15) << "Category"
              << std::setw(15) << "Manufacturer" << std::setw(10) << "Quantity"
              << std::setw(10) << "Price" << std::setw(15) << "Total Cost" << std::endl;
    for (const auto& product : products) {
        std::cout << std::setw(5) << product.id << std::setw(15) << product.name << std::setw(15) << product.category
                  << std::setw(15) << product.manufacturer << std::setw(10) << product.quantity
                  << std::setw(10) << product.price << std::setw(15) << product.totalCost << std::endl;
    }
}

void addProduct(std::vector<Product>& products) {
    Product product;
    std::cout << "Enter the product data (id, name, category, manufacturer, quantity, price):\n";
    std::cin >> product.id >> product.name >> product.category >> product.manufacturer >> product.quantity >> product.price;
    product.totalCost = product.quantity * product.price;
    products.push_back(product);
    std::cout << "Product added.\n";
}

void updateProduct(std::vector<Product>& products) {
    int id;
    std::cout << "Enter the product ID for the update: ";
    std::cin >> id;

    for (auto& product : products) {
        if (product.id == id) {
            std::cout << "Enter new data (name, category, manufacturer, quantity, price):\n";
            std::cin >> product.name >> product.category >> product.manufacturer >> product.quantity >> product.price;
            product.totalCost = product.quantity * product.price;
            std::cout << "The product has been updated.\n";
            return;
        }
    }
    std::cout << "Product with this ID was not found.\n";
}

void deleteProduct(std::vector<Product>& products) {
    int id;
    std::cout << "Enter the product ID to be deleted: ";
    std::cin >> id;

    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->id == id) {
            products.erase(it);
            std::cout << "The product has been removed.\n";
            return;
        }
    }
    std::cout << "Product with this ID was not found.\n";
}

void calculateTotalCost(const std::vector<Product>& products) {
    double total = 0;
    for (const auto& product : products) {
        total += product.totalCost;
    }
    std::cout << "Total value of all goods: " << total << std::endl;
}

int main() {
    std::vector<Product> products;
    std::string filename;

    std::cout << "Enter the name of the file with the source data: ";
    std::cin >> filename;
    loadFromFile(products, filename);

    int choice;
    do {
        std::cout << "\nMenu:\n"
                  << "1. Data Viewing\n"
                  << "2. Add a product\n"
                  << "3. Update the product\n"
                  << "4. Remove product\n"
                  << "5. Calculate the total cost\n"
                  << "6. Save data\n"
                  << "0. Output\n"
                  << "Your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                displayProducts(products);
                break;
            case 2:
                addProduct(products);
                break;
            case 3:
                updateProduct(products);
                break;
            case 4:
                deleteProduct(products);
                break;
            case 5:
                calculateTotalCost(products);
                break;
            case 6:
                std::cout << "Enter the name of the file to be saved: ";
                std::cin >> filename;
                saveToFile(products, filename);
                break;
            case 0:
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Wrong choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
