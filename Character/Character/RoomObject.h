/*

Specification file for the RoomObject class.
 
The RoomObject class is a polymorphic class that is based on the following hierarchy:
 
 
                                   Room Object
 
                               /   /    |    \   \
                              /   /     |     \   \
                             /   /      |      \   \
 
                        Book  Flare  Fountain  Map  Treasure
 
 Book prints useful hints on how to win the game.
 Flare prints the contents of four adjacent rooms.
 Fountain prints its description.
 Map prints its description and use.
 Treasure prints a message that the treasure has been activated.
 
 
*/

#ifndef RoomObject_h
#define RoomObject_h

#include <iostream>
#include <string>
using namespace std;


/* Abstract class encompassing all room objects of book, flare, fountain, trasure and map */
class RoomObject
{
protected:
    string name, description;
public:
    //Constructors
    RoomObject() {};
    RoomObject(string name, string description);
    
    //Destructor
    virtual ~RoomObject() {};
    
    //Setters
    void setName(string n);
    void  setDescription(string d);
    
    //Getters
    string  getName() const;
    string  getDescription() const;
    
    //Pure virtual functions
    virtual void use() const = 0;
};

class Book : public RoomObject
{
public:
    Book(string n, string d);
    ~Book() {};
    void use() const override;
};

class Flare : public RoomObject
{
public:
    Flare(string n, string d);
    ~Flare() {};
    void use() const override;
};

class Fountain : public RoomObject
{
public:
    Fountain(string n, string d);
    ~Fountain() {};
    void use() const override;
};

class Treasure : public RoomObject
{
public:
    Treasure(string n, string d);
    ~Treasure() {};
    void use() const override;
};

class Map : public RoomObject
{
public:
    Map(string n, string d);
    ~Map() {};
    void use() const override;
};
#endif

