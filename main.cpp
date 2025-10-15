#include <iostream>
#include <string>
using namespace std;

// Node structure for BST
struct MobileNode {
    string imei;
    string ownerName;
    string model;
    string status; // Lost // Found
    MobileNode *left, *right;
};

// Function to create a new node
MobileNode* createNode(string imei, string owner, string model, string status) {
    MobileNode* newNode = new MobileNode();
    newNode->imei = imei;
    newNode->ownerName = owner;
    newNode->model = model;
    newNode->status = status;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert node in BST
MobileNode* insertNode(MobileNode* root, string imei, string owner, string model, string status) {
    if (root == NULL)
        return createNode(imei, owner, model, status);

    if (imei < root->imei)
        root->left = insertNode(root->left, imei, owner, model, status);
    else if (imei > root->imei)
        root->right = insertNode(root->right, imei, owner, model, status);
    else
        cout << "Duplicate IMEI not allowed.\n";

    return root;
}

// Search for a mobile by IMEI
MobileNode* searchMobile(MobileNode* root, string imei) {
    if (root == NULL || root->imei == imei)
        return root;

    if (imei < root->imei)
        return searchMobile(root->left, imei);
    else
        return searchMobile(root->right, imei);
}

// Update mobile status
void updateStatus(MobileNode* root, string imei, string newStatus) {
    MobileNode* found = searchMobile(root, imei);
    if (found != NULL) {
        found->status = newStatus;
        cout << "\nStatus updated successfully!\n";
    } else {
        cout << "\nMobile not found.\n";
    }
}

// Display mobiles (Inorder Traversal)
void displayMobiles(MobileNode* root) {
    if (root != NULL) {
        displayMobiles(root->left);
        cout << "IMEI: " << root->imei
             << " | Owner: " << root->ownerName
             << " | Model: " << root->model
             << " | Status: " << root->status << endl;
        displayMobiles(root->right);
    }
}

int main() {
    MobileNode* root = NULL;
    int choice;
    string imei, owner, model, status;

    cout << "==============================\n";
    cout << " LOST MOBILE TRACKING SYSTEM\n";
    cout << " Using Binary Search Tree (BST)\n";
    cout << "==============================\n";

    do {
        cout << "\n1. Add Mobile Record";
        cout << "\n2. Search Mobile";
        cout << "\n3. Update Status";
        cout << "\n4. Display All Records";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nEnter IMEI: ";
                cin >> imei;
                cout << "Enter Owner Name: ";
                cin.ignore();
                getline(cin, owner);
                cout << "Enter Model: ";
                getline(cin, model);
                cout << "Enter Status (Lost/Found): ";
                getline(cin, status);
                root = insertNode(root, imei, owner, model, status);
                break;

            case 2:
                cout << "\nEnter IMEI to Search: ";
                cin >> imei;
                {
                    MobileNode* found = searchMobile(root, imei);
                    if (found != NULL)
                        cout << "\nFound! Owner: " << found->ownerName
                             << " | Model: " << found->model
                             << " | Status: " << found->status << endl;
                    else
                        cout << "\nMobile not found.\n";
                }
                break;

            case 3:
                cout << "\nEnter IMEI to Update: ";
                cin >> imei;
                cout << "Enter New Status (Lost/Found): ";
                cin >> status;
                updateStatus(root, imei, status);
                break;

            case 4:
                cout << "\nAll Mobile Records:\n";
                displayMobiles(root);
                break;

            case 5:
                cout << "\nExiting... Thank you!\n";
                break;

            default:
                cout << "\nInvalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}
