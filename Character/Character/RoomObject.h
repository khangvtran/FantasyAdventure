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


/* Abstract class encompassing all room objects of book, flare, fountain, trasure and map */
class RoomObject
{
protected:
    std::string name, description;
public:
    //Constructors
    RoomObject() {};
    RoomObject(std::string name, std::string description);
    
    //Destructor
    virtual ~RoomObject() {};
    
    //Setters
    void setName(std::string n);
    void setDescription(std::string d);
    
    //Getters
    std::string getName() const;
    std::string getDescription() const;
    
    //Pure virtual functions
    virtual void use() const = 0;
};

class Book : public RoomObject
{
public:
    Book(std::string n, std::string d);
    ~Book() {};
    void use() const override;
};

class Flare : public RoomObject
{
public:
    Flare(std::string n, std::string d);
    ~Flare() {};
    void use() const override;
};

class Fountain : public RoomObject
{
public:
    Fountain(std::string n, std::string d);
    ~Fountain() {};
    void use() const override;
};

class Treasure : public RoomObject
{
public:
    Treasure(std::string n, std::string d);
    ~Treasure() {};
    void use() const override;
};

class Map : public RoomObject
{
public:
    Map(std::string n, std::string d);
    ~Map() {};
    void use() const override;
};
#endif

