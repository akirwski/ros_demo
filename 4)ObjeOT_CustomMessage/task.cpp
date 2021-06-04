package: animal_lib
  -include
    -animal_lib
      -Animal.h
      -Dog.h
      -Cat.h
  -src
    -Animal.cpp
    -Dog.cpp
    -Cat.cpp



Animal
protected:
  string name
  int age
  bool sex
public:
  Animal( string, int, bool )
  introduce_myself()


Dog : public Animal
private:
  Breed breed(enum)

public:
  Dog( string, int, bool, Breed )
  Dog( Dog male, Dog female )
  Dog( animal_msgs::dogMsg )

  void set_msg( animal_msgs::dogMsg & )

  // animal_msgs::dogMsg msg;
  // fido.set_msg( msg );
  // pub.publish( msg );
  //
  // Dog newDog( msg );
  //
  // Dog babyDog( newDog1, newDog2 );

  Dog newDog = receivedMsg;

Cat : public Animal
  Country country(enum)
