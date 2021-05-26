#include "sources/BinaryTree.hpp"
#include "doctest.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace ariel;
using namespace std;

BinaryTree<int> bt;
void init_tree();
/*********************************************************************/
/*                         Int Binary Tree                           */
/*********************************************************************/
TEST_CASE ("add root & left & right") {
    BinaryTree<int> ibt;
    CHECK_NOTHROW(ibt.add_root(1).add_left(1, 2).add_right(1,3));
    CHECK_NOTHROW(ibt.add_root(11).add_root(12).add_root(13).add_root(14));
    CHECK_EQ(*(ibt.begin()), 14);
    CHECK_NE(*(ibt.begin()), 1);
    CHECK_THROWS(ibt.add_left('a', 'b'));
    CHECK_THROWS(ibt.add_left(2, 4).add_right(4, 'c').add_left('c', 'd'));
}

TEST_CASE ("inorder traversal") {
    init_tree();
    string expected = "8 4 9 12 2 5 1 6 3 13 10 7 11 ";
    string actual = "";

    for (auto it = bt.begin_inorder(); it != bt.end_inorder(); it ++) {
            actual += to_string(*it) + " ";
    }
    
    CHECK_EQ(actual, expected);

    string actual_default = "";
    for (auto it = bt.begin(); it != bt.end(); it ++) {
            actual += to_string(*it) + " ";
    }
    
    CHECK_EQ(actual, expected);
}

TEST_CASE ("preorder traversal") {
    init_tree();
    string expected = "1 2 4 8 9 12 5 3 6 7 10 15 11 ";
    string actual = "";

    for (auto it = bt.begin_preorder(); it != bt.end_preorder(); it ++) {
            actual += to_string(*it) + " ";
    }
    
    CHECK_EQ(actual, expected);
}

TEST_CASE ("postorder traversal") {
    init_tree();
    string expected = "8 12 9 4 5 2 6 13 10 11 7 3 1 ";
    string actual = "";

    for (auto it = bt.begin_postorder(); it != bt.end_postorder(); it ++) {
            actual += to_string(*it) + " ";
    }
    
    CHECK_EQ(actual, expected);
}

TEST_CASE ("Iterator") {
    init_tree();
    auto in_it = bt.begin_inorder();
    auto pr_it = bt.begin_preorder();
    auto po_it = bt.begin_postorder();

    CHECK(*in_it == 8);
    CHECK(*pr_it == 1);
    CHECK(*po_it== 8);

    CHECK(*(in_it++) == 8);
    CHECK(*(in_it) == 4);
    CHECK(*(++in_it) == 9);

    CHECK(*(pr_it++) == 1);
    CHECK(*(pr_it) == 2);
    CHECK(*(++pr_it) == 4);

    CHECK(*(po_it++) == 8);
    CHECK(*(po_it) == 12);
    CHECK(*(++po_it) == 9);
}
    
/**              1
 *              / \
 *             2   3
 *            / \ / \
 *           4  5 6  7
 *          / \     / \
 *         8   9   10 11
 *              \  /
 *             12 13
 **/

void init_tree(){
     bt.add_root(1).add_left(1,2).add_right(1,3)
     .add_left(2,4).add_right(2,5).add_left(3,6).add_right(3,7)
     .add_left(4,8).add_right(4,9).add_left(7,10).add_right(7,11)
     .add_right(9,12).add_left(10,13);
}


class Person{
public:
    const string name;
    int age;
    Person(string n, int a) : name(n), age(a){};
    Person& operator=(const Person& other){
        return *this;
    }
    bool operator==(const Person &p) const{return name == p.name && age == p.age;};
    bool operator!=(const Person &p) const{return !(*this==p);};
    // friend std::ostream &operator<<(std::ostream &os, const Person &p){
    //     return os << p.name << std::endl;
    // }
};

BinaryTree<Person> person_bt;
void init_person_tree();
/*********************************************************************/
/*                       Person Binary Tree                          */
/*********************************************************************/
TEST_CASE ("add root & left & right") {
    BinaryTree<Person> pbt;
    Person avi{"Avi", 30};
    Person batia{"Batia", 22};
    Person chris{"Chris", 12};
    Person david{"David", 43};
    Person efrat{"Efrat", 37};
    Person fatma{"Fatma", 62};
    Person gadi{"Gadi", 50};
    Person haim{"Haim", 81};
    Person itai{"Itai", 25};

    CHECK_NOTHROW(pbt.add_root(avi).add_left(avi, batia).add_right(avi,chris));
    CHECK_NOTHROW(pbt.add_root(gadi).add_root(haim).add_root(itai));
    CHECK_EQ(*(pbt.begin()), itai);
    CHECK_NE(*(pbt.begin()), avi);
    CHECK_THROWS(pbt.add_left(david, gadi));
}

TEST_CASE ("inorder traversal") {
    init_person_tree();
    string expected = "David Haim Gadi Itai Batia Avi Efrat Chris Fatma ";
    string actual = "";

    for (auto it = person_bt.begin_inorder(); it != person_bt.end_inorder(); it ++) {
            actual += (*it).name + " ";
    }
    
    CHECK_EQ(actual, expected);

    string actual_default = "";
    for (auto it = person_bt.begin(); it != person_bt.end(); it ++) {
            actual += (*it).name + " ";
    }
    
    CHECK_EQ(actual, expected);
}

TEST_CASE ("preorder traversal") {
    init_person_tree();
    string expected = "Avi Batia David Gadi Haim Itai Chris Efrat Fatma ";
    string actual = "";

    for (auto it = person_bt.begin_preorder(); it != person_bt.end_preorder(); it ++) {
            actual += (*it).name + " ";
    }
    
    CHECK_EQ(actual, expected);
}

TEST_CASE ("postorder traversal") {
    init_person_tree();
    string expected = "Haim Itai Gadi David Batia Efrat Fatma Chris Avi ";
    string actual = "";

    for (auto it = person_bt.begin_postorder(); it != person_bt.end_postorder(); it ++) {
            actual += (*it).name + " ";
    }
    
    CHECK_EQ(actual, expected);
}

TEST_CASE ("Iterator") {
    init_person_tree();
    Person david{"David",43};
    Person gadi{"Gadi", 50};
    Person haim{"Haim", 81};

    auto in_it = person_bt.begin();
    CHECK(*in_it == david);
    CHECK(*(in_it++) == david);
    CHECK(*(in_it) == haim);
    CHECK(*(++in_it) == gadi);

}
    
/**             avi
 *              / \
 *          batia chris
 *            /    /   \
 *         david efrat fatma
 *            \    
 *           gadi
 *           /  \
 *         haim itai
 **/

void init_person_tree(){
    Person avi{"Avi", 30};
    Person batia{"Batia", 22};
    Person chris{"Chris", 12};
    Person david{"David", 43};
    Person efrat{"Efrat", 37};
    Person fatma{"Fatma", 62};
    Person gadi{"Gadi", 50};
    Person haim{"Haim", 81};
    Person itai{"Itai", 25};
     person_bt.add_root(avi).add_left(avi,batia).add_right(avi,chris)
     .add_left(batia,david).add_left(chris, efrat).add_right(chris,fatma)
     .add_right(david,gadi).add_left(gadi,haim).add_right(gadi,itai);
}



